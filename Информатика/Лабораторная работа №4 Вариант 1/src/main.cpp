#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include "classes.h"
#include "database.h"

int promptInt(const std::string& msg)
{
    std::cout << msg;
    int x;
    std::cin >> x;
    std::cin.ignore(1024, '\n');
    return x;
}

std::string promptStr(const std::string& msg)
{
    std::cout << msg;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

int main()
{
    try{
        std::string conninfo;
        std::cout << "Enter PostgreSQL connection string:\n> ";
        std::getline(std::cin, conninfo);
        Database db(conninfo);
        Logger logger("../logs/log.txt");
        while (true)
        {
            std::cout << "\n--- MENU ---\n"
                      << "1. Add author\n"
                      << "2. Add book\n"
                      << "3. Add user\n"
                      << "4. Register borrow\n"
                      << "5. Analytics\n"
                      << "0. Exit\n> ";
            int choice;
            std::cin >> choice;
            std::cin.ignore(1024, '\n');
            if (choice == 0) break;
            try{
                if (choice == 1)
                {
                    std::string name = promptStr("Author name: ");
                    int birth = promptInt("Birth year: ");
                    Author::add(db, name, birth, logger);
                }
                else if (choice == 2)
                {
                    std::string title = promptStr("Title: ");
                    int aid = promptInt("Author ID: ");
                    int year = promptInt("Publication year: ");
                    std::string genre = promptStr("Genre: ");
                    Book::add(db, title, aid, year, genre, logger);
                }
                else if (choice == 3)
                {
                    std::string name = promptStr("User name: ");
                    std::string date = promptStr("Registration date (YYYY-MM-DD): ");
                    User::add(db, name, date, logger);
                }
                else if (choice == 4)
                {
                    int uid = promptInt("User ID: ");
                    int bid = promptInt("Book ID: ");
                    std::string date = promptStr("Borrow date (YYYY-MM-DD): ");
                    BorrowedBook::borrow(db, uid, bid, date, logger);
                }
                else if (choice == 5)
                {
                    std::cout << "\nAnalytics:\n"
                              << "1. Books by author\n"
                              << "2. Users registered last year\n"
                              << "3. Books borrowed last 30 days\n"
                              << "4. Top 3 books\n> ";
                    int a;
                    std::cin >> a;
                    std::cin.ignore(1024, '\n');
                    if (a == 1){
                        std::string an = promptStr("Author name: ");
                        Book::listByAuthor(db, an);
                    }
                    else if (a == 2){
                        int c = User::countRegisteredLastYear(db);
                        std::cout << "Users registered last year: " << c << "\n";
                    }
                    else if (a == 3){
                        BorrowedBook::listLast30Days(db);
                    }
                    else if (a == 4){
                        Book::top3(db);
                    }
                }
            }
            catch (const std::exception& e){
                std::cout << "Error: " << e.what() << "\n";
            }
        }

    }
    catch (const std::exception& e){
        std::cerr << "Fatal: " << e.what() << std::endl;
    }
    return 0;
}