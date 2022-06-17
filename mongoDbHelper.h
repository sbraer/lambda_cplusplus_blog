#pragma once

#include <optional>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pool.hpp>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include "helper.h"

class MongoDbHelper final {

private:
    const std::string _database;
    std::unique_ptr<mongocxx::instance> _inst;
    std::unique_ptr<mongocxx::uri> _uri;
    std::unique_ptr<mongocxx::pool> _pool;
    
    explicit MongoDbHelper(const std::string& connectionString, const std::string& database);

    MongoDbHelper (const MongoDbHelper&) = delete; // copy constructor
    MongoDbHelper& operator= (const MongoDbHelper&) = delete; // copy operator

public:
    static MongoDbHelper& Instance();    
    [[nodiscard]] std::optional<std::string> FindOne(const std::string& collection, const std::string& key, const std::string& value) const;

};