#pragma once

#include <vector>
#include "hnswlib/hnswlib.h"
#include "index_factory.h"

class HNSWLibIndex {
public:
    HNSWLibIndex(int dim, int num_data, IndexFactory::MetricType metric, int M = 16, int ef_construction = 200);
    // 插入对应的向量
    void insert_vectors(const std::vector<float>& data, uint64_t label);
    // 查找对应的向量
    std::pair<std::vector<long>, std::vector<float>> search_vectors(const std::vector<float>& query, int k, int ef_search = 50);
private:
    int dim;
    // 计算相似度成员
    hnswlib::SpaceInterface<float>* space;
    // 存储向量数据和查询数据
    hnswlib::HierarchicalNSW<float>* index;
};