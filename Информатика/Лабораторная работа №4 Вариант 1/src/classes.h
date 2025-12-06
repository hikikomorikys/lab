#ifndef CLASSES_H
#define CLASSES_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <pqxx/pqxx>
#include "database.h"

class Logger{
    std::ofstream ofs;

public:
    Logger(const std::string& filename = "../logs/log.txt"){
        ofs.open(filename, std::ios::app);
        if (!ofs)
            throw std::runtime_error("Cannot open log file");
    }

    void log(const std::string& text){
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        std::ostringstream ss;
        ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        ofs << "[" << ss.str() << "] " << text << std::endl;
    }
};

template<typename A, typename B>
class Pair{
public:
    A first;
    B second;

    Pair() = default;
    Pair(const A& f, const B& s) : first(f), second(s) {}
};

class Author{
public:
    static int add(Database& db, const std::string& name, int birth_year, Logger& logger){
        try{
            pqxx::work txn(db.get());
            pqxx::result r = txn.exec(
                "INSERT INTO authors (name, birth_year) VALUES (" +
                txn.quote(name) + ", " + txn.quote(birth_year) +
                ") RETURNING id"
            );
            txn.commit();
            int id = r[0][0].as<int>();
            logger.log("Added author: " + name + " id=" + std::to_string(id));
            return id;
        }
        catch (const std::exception& e){
            logger.log(std::string("Error adding author: ") + e.what());
            throw;
        }
    }
};

class Book{
public:
    virtual ~Book() = default;
    static int add(Database& db, const std::string& title, int author_id,
                   int pub_year, const std::string& genre, Logger& logger)
    {
        try{
            pqxx::work txn(db.get());
            pqxx::result r = txn.exec(
                "INSERT INTO books (title, author_id, publication_year, genre) VALUES (" +
                txn.quote(title) + ", " + txn.quote(author_id) + ", " +
                txn.quote(pub_year) + ", " + txn.quote(genre) + ") RETURNING id"
            );
            txn.commit();
            int id = r[0][0].as<int>();
            logger.log("Added book: " + title + " id=" + std::to_string(id));
            return id;
        }
        catch (const std::exception& e){
            logger.log(std::string("Error adding book: ") + e.what());
            throw;
        }
    }
    static void listByAuthor(Database& db, const std::string& authorName){
        pqxx::work txn(db.get());
        pqxx::result r = txn.exec_params(
            "SELECT b.title, b.publication_year FROM books b "
            "JOIN authors a ON b.author_id = a.id WHERE a.name = $1",
            authorName
        );
        for (auto row : r)
            std::cout << row["title"].c_str() << " (" << row["publication_year"].as<int>() << ")\n";
        txn.commit();
    }
    static void top3(Database& db){
        pqxx::nontransaction ntx(db.get());
        pqxx::result r = ntx.exec(
            "SELECT b.title, COUNT(*) AS c FROM books b "
            "JOIN borrowed_books bb ON b.id=bb.book_id "
            "GROUP BY b.title ORDER BY c DESC LIMIT 3"
        );
        int i = 1;
        for (auto row : r)
            std::cout << i++ << ". " << row["title"].c_str()
                      << " — " << row["c"].as<int>() << " times\n";
    }
};

class FictionBook : public Book {};
class NonFictionBook : public Book {};

class User{
public:
    static int add(Database& db, const std::string& name, const std::string& reg_date, Logger& logger)
    {
        try{
            pqxx::work txn(db.get());
            pqxx::result r = txn.exec(
                "INSERT INTO users (name, registration_date) VALUES (" +
                txn.quote(name) + ", " + txn.quote(reg_date) + ") RETURNING id"
            );
            txn.commit();
            int id = r[0][0].as<int>();
            logger.log("Added user: " + name + " id=" + std::to_string(id));
            return id;
        }
        catch (const std::exception& e){
            logger.log(std::string("Error adding user: ") + e.what());
            throw;
        }
    }
    static int countRegisteredLastYear(Database& db)
    {
        pqxx::nontransaction ntx(db.get());
        pqxx::result r = ntx.exec(
            "SELECT COUNT(*) FROM users "
            "WHERE registration_date >= CURRENT_DATE - INTERVAL '1 year'"
        );
        return r[0][0].as<int>();
    }
};

class BorrowedBook{
public:
    static void borrow(Database& db, int user_id, int book_id,
                       const std::string& date, Logger& logger)
    {
        try{
            pqxx::work txn(db.get());
            txn.exec(
                "INSERT INTO borrowed_books (user_id, book_id, borrow_date) VALUES (" +
                txn.quote(user_id) + ", " + txn.quote(book_id) + ", " +
                txn.quote(date) + ")"
            );
            txn.commit();
            logger.log("Borrowed book id=" + std::to_string(book_id));
        }
        catch (const std::exception& e){
            logger.log(std::string("Error borrow: ") + e.what());
            throw;
        }
    }
    static void listLast30Days(Database& db)
    {
        pqxx::nontransaction ntx(db.get());
        pqxx::result r = ntx.exec(
            "SELECT b.title, u.name, bb.borrow_date "
            "FROM borrowed_books bb "
            "JOIN books b ON b.id = bb.book_id "
            "JOIN users u ON u.id = bb.user_id "
            "WHERE bb.borrow_date >= CURRENT_DATE - INTERVAL '30 days'"
        );
        for (auto row : r)
            std::cout << row["borrow_date"].c_str() << " — "
                      << row["name"].c_str() << " — "
                      << row["title"].c_str() << "\n";
    }
};
#endif