# 编译器
CXX = g++# 使用 g++ 作为 C++ 编译器

# 编译选项
CXXFLAGS = -std=c++17 -g -Wall $(INCLUDES)# 设置编译选项：使用 C++11 标准，开启调试信息，显示所有警告

# 链接选项
LDFLAGS = -lfaiss -lrocksdb -fopenmp -lopenblas -lpthread -lspdlog -lfmt -ldl -lrt -lsnappy -lgflags -lz -lbz2 -llz4 -lzstd# 链接所需的库：faiss、OpenMP、OpenBLAS、pthread 和 spdlog

INCLUDES = -Ihnswlib -Iinclude
# 目标文件
TARGET = $(TARGET_BUILD_DIR)vdb_server# 定义最终生成的可执行文件名为 vdb_server


SOURCES_DIR = src/
# 源文件
SOURCES = $(wildcard $(SOURCES_DIR)*.cpp)# 定义所有源文件

# 获取当前路径
# CURRENT_DIR := $(shell pwd)

# 构建目录
BUILD_DIR = build/
SOURCES_BUILD_DIR = build/sources/
TARGET_BUILD_DIR = build/target/
# 定义存放对象文件的目录

# 对象文件
OBJECTS = $(patsubst $(SOURCES_DIR)%.cpp, $(SOURCES_BUILD_DIR)%.o, $(SOURCES))
# 将源文件名转换为对象文件名（.o）
# OBJECTS = $(SOURCES:.cpp=.o)  # 将源文件名转换为对象文件名（.o）

# 默认目标
all: $(TARGET)
# 默认目标为生成可执行文件

# 创建 build 文件夹
$(SOURCES_BUILD_DIR):
	mkdir -p $(SOURCES_BUILD_DIR)

$(TARGET_BUILD_DIR):
	mkdir -p $(TARGET_BUILD_DIR)

# 生成目标文件
$(TARGET): $(OBJECTS) | $(TARGET_BUILD_DIR)
# 当目标文件依赖于对象文件时
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
# 使用编译器链接对象文件生成可执行文件

# 编译源文件为对象文件
$(SOURCES_BUILD_DIR)%.o: $(SOURCES_DIR)%.cpp | $(SOURCES_BUILD_DIR) # 规则：将 .cpp 文件编译为 .o 文件
# 使用编译器编译源文件，生成对象文件
	$(CXX) $(CXXFLAGS) -c $< -o $@ 


# 清理目标
clean:  # 定义清理目标
	rm -rf $(BUILD_DIR)
# rm -rf $(BUILD_DIR) $(TARGET)  # 删除所有对象文件和可执行文件
# rm -f $(BUILD_DIR)/*.o $(TARGET)  # 删除所有对象文件和可执行文件
# rm -rf $(BUILD_DIR)  # 删除 build 文件夹


# examples部分
# examples部分主要是对用到的库的某些功能写一些例子
EXAMPLES_DIR = examples/
EXAMPLES_BIN_DIR = bin/examples/

$(EXAMPLES_DIR):
	mkdir -p $(EXAMPLES_DIR)

$(EXAMPLES_BIN_DIR):
	mkdir -p $(EXAMPLES_BIN_DIR)

rapidjson-exp: | $(EXAMPLES_DIR) $(EXAMPLES_BIN_DIR)
	$(CXX) $(EXAMPLES_DIR)rapidjson_exp.cpp -o $(EXAMPLES_BIN_DIR)rapidjson_exp $(CXXFLAGS) $(LDFLAGS)

rocksdb-exp: | $(EXAMPLES_DIR) $(EXAMPLES_BIN_DIR)
	$(CXX) $(EXAMPLES_DIR)rocksdb_exp.cpp -o $(EXAMPLES_BIN_DIR)rocksdb_exp $(CXXFLAGS) $(LDFLAGS)

# tests部分
# tests部分主要是对vdb内部模块进行测试
TESTS_DIR = tests/
TESTS_BIN_DIR = bin/tests/

$(TESTS_DIR):
	mkdir -p $(TESTS_DIR)

$(TESTS_BIN_DIR):
	mkdir -p $(TESTS_BIN_DIR)

log-test: | $(TESTS_DIR) $(TESTS_BIN_DIR)
	$(CXX) $(CXXFLAGS) $(TESTS_DIR)log_test.cpp $(SOURCES_DIR)logger.cpp -o $(TESTS_BIN_DIR)log_test $(LDFLAGS)