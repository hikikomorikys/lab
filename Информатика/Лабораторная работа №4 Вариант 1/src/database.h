#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <string>
#include <stdexcept>

class Database{
    pqxx::connection conn;

public:
    Database(const std::string& conninfo) : conn(conninfo){
        if (!conn.is_open())
            throw std::runtime_error("Failed to open database connection.");
    }
    pqxx::connection& get() { return conn; }
};
#endif