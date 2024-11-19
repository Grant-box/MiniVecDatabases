#pragma once

#include "faiss_index.h"
#include "index_factory.h"
#include "httplib.h"
#include "vector_database.h"
#include <rapidjson/document.h>
#include <string>

class HttpServer {
public:
    enum class CheckType {
        SEARCH,
        INSERT,
        UPSERT
    };
    
    HttpServer(const std::string& host, int port, VectorDatabase* vector_database);

    void start();
private:

    // 处理搜索请求的处理函数
    void searchHandler(const httplib::Request& req, httplib::Response& res);
    // 处理插入请求的处理函数
    void insertHandler(const httplib::Request& req, httplib::Response& res);
    void upsertHandler(const httplib::Request& req, httplib::Response& res);
    void queryHandler(const httplib::Request& req, httplib::Response& res);
    // 设置JSON格式的响应
    void setJsonResponse(const rapidjson::Document& json_response, httplib::Response& res);
    // 设置错误信息的JSON响应
    void setErrorJsonResponse(httplib::Response& json_response, int error_code, const std::string& errorMsg);
    // 检查请求是否有效
    bool isRequestValid(const rapidjson::Document& json_request, CheckType check_type);
    // 从请求中获取索引类型
    IndexFactory::IndexType getIndexTypeFromRequest(const rapidjson::Document& json_request);

    httplib::Server server;
    std::string host;
    int port;
    VectorDatabase* vector_database_;
};
