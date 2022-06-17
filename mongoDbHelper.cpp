#include "mongoDbHelper.h"

MongoDbHelper& MongoDbHelper::Instance() {
    static MongoDbHelper _instance{
        Helper::GetEnvironmentVariable("MongoDbConnectionString", "mongodb+srv://#######:############@cluster0.3bedg.mongodb.net/?retryWrites=true&w=majority&tlsAllowInvalidCertificates=true"),
        Helper::GetEnvironmentVariable("MongoDbDatabase", "MyDatabase")
    };

    return _instance;
}

MongoDbHelper::MongoDbHelper(const std::string& connectionString, const std::string& database)
    : _database(database) {
    _inst = std::make_unique<mongocxx::instance>();
    _uri  = std::make_unique<mongocxx::uri>(connectionString);
    _pool = std::make_unique<mongocxx::pool>(*_uri.get());
}

std::optional<std::string> MongoDbHelper::FindOne(
    const std::string& collection,
    const std::string& key,
    const std::string& value) const
{

    auto conn = _pool.get()->acquire();
    auto db = (*conn)[_database];
    auto coll = db[collection];

    auto cursor1 = coll.find_one({
        bsoncxx::builder::stream::document{}
        << key << value
        << bsoncxx::builder::stream::finalize
    });

    if (cursor1) {
        std::string returnString{bsoncxx::to_json(cursor1.value())};
        return {returnString};
    }
    else {
        return std::nullopt; 
    }
}

// https://github.com/mongodb/mongo-cxx-driver/blob/master/examples/mongocxx/pool.cpp