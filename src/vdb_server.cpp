#include "http_server.h"
#include "logger.h"
#include "vector_database.h"
#include "index_factory.h"

int main(){
    
    // 初始化全局日志记录器
    init_global_logger();
    // 设置日志级别为调试
    set_log_level(spdlog::level::debug);

    // 记录服务器启动信息
    GlobalLogger->info("VDB Server is starting...");

    // 设置索引的维度
    int dim = 1;
    int num_data = 1000;
    // 获取全局索引工厂
    IndexFactory* globalIndexFactory = getGlobalIndexFactory();
    // 初始化索引工厂
    globalIndexFactory->init(IndexFactory::IndexType::FLAT, dim);
    globalIndexFactory->init(IndexFactory::IndexType::HNSW, dim, num_data);
    // 记录服务器初始化信息
    
    GlobalLogger->info("VDB Server is initialized");
    std::string db_path = "./ScalarStorage";
    VectorDatabase vector_database(db_path);
    GlobalLogger->info("VectorDatabase initialized");
    // 创建HTTP服务器实例
    HttpServer http_server("localhost", 8080, &vector_database);
    // 记录服务器运行信息
    GlobalLogger->info("VDB Server is running");
    // 启动HTTP服务器
    http_server.start();
    // 返回0表示程序正常结束
    return 0;
}