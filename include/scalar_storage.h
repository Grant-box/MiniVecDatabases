#pragma once

#include <rocksdb/db.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>


// ScalarStorage类用于管理标量数据的存储
class ScalarStorage
{
public:
    // 构造函数，接受数据库路径作为参数
    ScalarStorage(const std::string& db_path);
    
    // 析构函数
    ~ScalarStorage();

    // 插入标量数据的方法，接受ID和数据文档作为参数
    void insert_scalar(uint64_t id, const rapidjson::Document& data);
    
    // 获取标量数据的方法，接受ID作为参数，返回数据文档
    rapidjson::Document get_scalar(uint64_t id);
private:
    // RocksDB数据库指针
    rocksdb::DB* db_;
};