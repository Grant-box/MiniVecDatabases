#include "logger.h"
#include <spdlog/sinks/stdout_color_sinks.h>

std::shared_ptr<spdlog::logger> GlobalLogger;

void init_global_logger() {
    // 设置输出格式
    // 创建一个名为 "GlobalLogger" 的日志记录器，并将其输出到标准输出（通常是控制台）
    // 同时使用带颜色的输出格式。
    GlobalLogger = spdlog::stdout_color_mt("GlobalLogger");
}

void set_log_level(spdlog::level::level_enum log_level) {
    // 设置日志记录器的日志级别
    GlobalLogger->set_level(log_level);
}
