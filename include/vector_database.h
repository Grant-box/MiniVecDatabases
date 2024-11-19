#pragma once

#include "scalar_storage.h"
#include "index_factory.h"
#include <string>
#include <vector>
#include <rapidjson/document.h>

class VectorDatabase
{
public:
    VectorDatabase(const std::string& db_path);
    
    void upsert(uint64_t id, const rapidjson::Document& data, IndexFactory::IndexType index_type);
    rapidjson::Document query(uint64_t id);
private:
    ScalarStorage scalar_storage_;
};

