# 项目笔记
笔记用于学习使用
## 依赖库安装
### 安装faiss
安装faiss需要安装cmake
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
#### 编译faiss库(1.9.0)
克隆faiss库
```bash
git clone https://github.com/facebookresearch/faiss.git
```
具体安装说明见INSTALL.md，个人安装说明如下：
```bash
# 进入克隆目录
cd faiss
# 由于是在服务器上就把GPU选项关闭了，由于是C++项目，python选项也关闭
cmake -B build . -DFAISS_ENABLE_GPU=OFF -DFAISS_ENABLE_PYTHON=OFF
# 编译，根据自己电脑配置选择编译线程数量，如四核就 make -C build -j4 faiss
make -C build -j faiss
# 安装
make -C build install

# 注意上述命令，非root用户需要加sudo
```
## 安装编译问题汇总
### 第三方库缺失问题
可以通过`apt`安装的三方库，根据报错内容安装对应的三方库。
#### 安装openblas

`sudo apt-get install libopenblas-dev`

#### 安装rapidjson

`sudo apt-get install rapidjson-dev`

#### 安装spdlog
`sudo apt-get install libspdlog-dev`
#### 安装openssl

`sudo apt-get install libssl-dev`

#### 安装swig

`sudo apt-get install swig`

#### 安装gflags

`sudo apt-get install libgflags-dev`

# test测试相关

## 日志模块
日志模块测试时注意，报错fmt相关时注意链接fmt库\
例：`g++ -o bin/test/log_test test/log_test.cpp logger.cpp -I. -lspdlog -lfmt`