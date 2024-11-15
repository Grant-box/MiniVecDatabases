#include "faiss_index.h"
#include "logger.h"
#include "constants.h"
#include <iostream>
#include <vector>

FaissIndex::FaissIndex(faiss::Index* index) : index(index) {}

void FaissIndex::insert_vectors(const std::vector<float>& data, uint64_t label) {
    long id = static_cast<long>(label);
    // 从前到后三个变量分别为向量个数，向量，标签
    index->add_with_ids(1, data.data(), &id);
}

// 定义搜索向量的函数，返回索引和距离的配对
std::pair<std::vector<long>, std::vector<float>> FaissIndex::search_vectors(const std::vector<float>& query, int k) {
    // 获取索引的维度
    int dim = index->d;
    // 计算查询的数量
    int num_queries = query.size() / dim;
    // 创建存储索引和距离的向量
    std::vector<long> indices(num_queries * k);
    std::vector<float> distances(num_queries * k);

    // 执行搜索操作
    // 返回的内容存放在传入的distances和indices中
    index->search(num_queries, query.data(), k, distances.data(), indices.data());
    // 记录检索到的值
    GlobalLogger->debug("Retrieved values:");
    // 遍历索引结果
    for(size_t i = 0; i < indices.size(); ++i) {
        // 如果索引有效，记录ID和距离
        if(indices[i] != -1) {
            GlobalLogger->debug("ID: {}, Distance: {}", indices[i], distances[i]);
        }
        // 如果索引无效，记录未找到特定值
        else{
            GlobalLogger->debug("No specific value found");
        }
    }

    // 返回索引和距离的配对
    return {indices, distances};
}
