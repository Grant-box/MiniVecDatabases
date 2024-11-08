#pragma once  // 防止头文件被重复包含,确保编译时该头文件只被包含一次

#include <faiss/Index.h>

#include <vector>

class FaissIndex {
public:
    FaissIndex(faiss::Index* index);
    // 将一个向量插入到索引中，并指定标签
    void insert_vectors(const std::vector<float>& data, uint64_t label);
    // 搜索与给定向量最相似的向量，并返回??
    std::pair<std::vector<long>, std::vector<float>> search_vectors(const std::vector<float>& query, int k);

private:
    faiss::Index* index;
};
