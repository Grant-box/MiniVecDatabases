#include "http_server.h"
#include "logger.h"
#include "index_factory.h"

int main(){
    init_global_logger();
    set_log_level(spdlog::level::debug);

    GlobalLogger->info("VDB Server is starting...");

    int dim = 1;
    IndexFactory* globalIndexFactory = getGlobalIndexFactory();
    globalIndexFactory->init(IndexFactory::IndexType::FLAT, dim);
    GlobalLogger->info("VDB Server is initialized");
    
    HttpServer http_server("localhost", 8080);
    GlobalLogger->info("VDB Server is running");
    http_server.start();
    return 0;
}