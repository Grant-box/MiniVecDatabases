#include "scalar_storage.h"
#include "logger.h"
#include <rocksdb/db.h>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <stdexcept>
#include <vector>

ScalarStorage::ScalarStorage(const std::string& db_path){
    rocksdb::Options options;
    options.create_if_missing = true;
    rocksdb::Status status = rocksdb::DB::Open(options, db_path, &db_);
    if(!status.ok()){
        throw std::runtime_error("Failed to open RocksDB: " + status.ToString());
    }
}

ScalarStorage::~ScalarStorage(){
    delete db_;
}

// 插入标量数据的函数
void ScalarStorage::insert_scalar(uint64_t id, const rapidjson::Document& data){
    // 创建一个字符串缓冲区
    rapidjson::StringBuffer buffer;
    // 创建一个写入器，用于将文档写入缓冲区
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    // 接受数据并写入缓冲区
    data.Accept(writer);
    // 获取缓冲区中的字符串
    std::string value = buffer.GetString();
    // 将数据插入到数据库中
    rocksdb::Status status = db_->Put(rocksdb::WriteOptions(), std::to_string(id), value);
}

// 获取标量数据的函数
rapidjson::Document ScalarStorage::get_scalar(uint64_t id){
    // 定义一个字符串用于存储从数据库中获取的值
    std::string value;
    rocksdb::Status status = db_->Get(rocksdb::ReadOptions(), std::to_string(id), &value);


    if(!status.ok()){
        return rapidjson::Document();
    }
    
    // 创建一个rapidjson文档对象
    rapidjson::Document data;
    // 解析获取的字符串值
    data.Parse(value.c_str());
    
    // 创建一个字符串缓冲区
    rapidjson::StringBuffer buffer;
    // 创建一个写入器，用于将文档写入缓冲区
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    // 将文档内容写入缓冲区
    data.Accept(writer);

    GlobalLogger->debug("Data retrieved from ScalarStorage: {}, RocksDB status: {}", buffer.GetString(), status.ToString()); // 添加rocksdb::Status status

    
    // 返回文档对象
    return data;
}