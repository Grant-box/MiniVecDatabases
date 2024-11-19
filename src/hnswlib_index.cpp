#include "hnswlib_index.h"
#include "logger.h"

#include <vector>
#include <algorithm>


HNSWLibIndex::HNSWLibIndex(int dim, int num_data, IndexFactory::MetricType metric, int M, int ef_construction) : dim(dim) {
    bool normalize = false;
    if (metric == IndexFactory::MetricType::L2) {
        space = new hnswlib::L2Space(dim);
    } else {
        throw std::runtime_error("Invalid metric type.");
    }

    index = new hnswlib::HierarchicalNSW<float>(space, num_data, M, ef_construction);
}

void HNSWLibIndex::insert_vectors(const std::vector<float>& data, uint64_t label) {
    index->addPoint(data.data(), label);
}

std::pair<std::vector<long>, std::vector<float>> HNSWLibIndex::search_vectors(const std::vector<float>& query, int k, int ef_search) {
    index->setEf(ef_search);
    // 查询结果存在result（优先队列）中
    auto result = index->searchKnn(query.data(), k);
    // 查看查询结果是否小于k
    // k = std::min(k, (int)result.size());

    std::vector<long> indices;
    std::vector<float> distances;
    // 调试 result
    // GlobalLogger->debug("Result size : {}", result.size());

    while(!result.empty()){
        auto item = result.top();
        indices.push_back(item.second);
        distances.push_back(item.first);
        result.pop();
    }
    // 调试 id 和 distance
    // for(size_t i = 0; i < indices.size(); ++i) {
    //     // 如果索引有效，记录ID和距离
    //     if(indices[i] != -1) {
    //         GlobalLogger->debug("ID: {}, Distance: {}", indices[i], distances[i]);
    //     }
    // }
    return {indices, distances};
}