#include <logger.h>

int main() {
    // 初始化日志器
    init_global_logger();
    set_log_level(spdlog::level::debug);
    // 测试不同级别的日志
    GlobalLogger->debug("这是调试信息");    // 调试级别
    GlobalLogger->info("这是普通信息");     // 信息级别
    GlobalLogger->warn("这是警告信息");     // 警告级别
    GlobalLogger->error("这是错误信息");    // 错误级别
    
    // 测试带参数的日志
    int value = 42;
    GlobalLogger->info("当前值是: {}", value);
    
    return 0;
}