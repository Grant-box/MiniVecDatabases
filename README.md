# 项目笔记

## 依赖库安装
### 安装faiss
安装faiss需要安装cmake\
#### cmake编译安装
直接用`apt`安装版本不满足faiss条件\
[cmake安装链接](https://cmake.org/download/#latest)
```bash
// 解压
tar -zxvf <cmake-file-name>
// 进入对应目录
cd <cmake-file-name>
// 执行bootstrap文件进行检查
./bootstrap
// 编译，-j8是选择八核编译，如果是电脑是四核就make -j4
make -j8
// 安装
sudo make install
```
安装成功调用`cmake --version`查看你cmake版本信息

查看cmake路径 `which cmake`

### 安装rapidjson

`sudo apt-get install rapidjson-dev`

### 安装spdlog
`sudo apt-get install libspdlog-dev`

# test测试相关

## 日志模块
日志模块测试时注意，报错fmt相关时注意链接fmt库\
例：`g++ -o bin/test/log_test test/log_test.cpp logger.cpp -I. -lspdlog -lfmt`