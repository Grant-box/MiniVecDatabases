#pragma once

#include <spdlog/spdlog.h>
// 设置全局日志对象
extern std::shared_ptr<spdlog::logger> GlobalLogger;

// 用于初始化日志器,设置为彩色控制台输出
void init_global_logger();
// 用于设置日志级别(如debug、info、error等)
void set_log_level(spdlog::level::level_enum log_level);

/*
spdlog的主要优点是:
1. 支持彩色输出
2. 性能很好
3. 使用{}作为格式化占位符,比printf更现代
4. 支持多种日志级别
*/