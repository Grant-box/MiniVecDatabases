# 编译器
CXX = g++  # 使用 g++ 作为 C++ 编译器

# 编译选项
CXXFLAGS = -std=c++11 -g -Wall $(INCLUDES)  # 设置编译选项：使用 C++11 标准，开启调试信息，显示所有警告

# 链接选项
LDFLAGS = -lfaiss -fopenmp -lopenblas -lpthread -lspdlog -lfmt  # 链接所需的库：faiss、OpenMP、OpenBLAS、pthread 和 spdlog

INCLUDES = -I ./hnswlib
# 目标文件
TARGET = vdb_server# 定义最终生成的可执行文件名为 vdb_server

# 源文件
SOURCES = vdb_server.cpp faiss_index.cpp http_server.cpp index_factory.cpp logger.cpp  # 定义所有源文件

# 获取当前路径
# CURRENT_DIR := $(shell pwd)

# 构建目录
BUILD_DIR = build/
# 定义存放对象文件的目录

# 对象文件
OBJECTS = $(patsubst %.cpp, $(BUILD_DIR)%.o, $(SOURCES))  # 将源文件名转换为对象文件名（.o）
# OBJECTS = $(SOURCES:.cpp=.o)  # 将源文件名转换为对象文件名（.o）

# 默认目标
all: $(TARGET)  # 默认目标为生成可执行文件

# 创建 build 文件夹
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# 生成目标文件
$(TARGET): $(OBJECTS)  # 当目标文件依赖于对象文件时
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)# 使用编译器链接对象文件生成可执行文件

# 编译源文件为对象文件
$(BUILD_DIR)%.o: %.cpp | $(BUILD_DIR) # 规则：将 .cpp 文件编译为 .o 文件
	$(CXX) $(CXXFLAGS) -c $< -o $@ # 使用编译器编译源文件，生成对象文件

# 清理目标
clean:  # 定义清理目标
	rm -rf $(BUILD_DIR) $(TARGET)  # 删除所有对象文件和可执行文件
# rm -f $(BUILD_DIR)/*.o $(TARGET)  # 删除所有对象文件和可执行文件
# rm -rf $(BUILD_DIR)  # 删除 build 文件夹