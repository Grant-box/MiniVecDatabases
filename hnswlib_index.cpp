#include "hnswlib_index.h"
#include <vector>


HnswLibIndex::HnswLibIndex(int dim, int num_data, IndexFactory::MetricType metric, int M = 16, int ef_construction = 200) {
    bool normalize = false;
    if (metric == IndexFactory::MetricType::L2) {
        space = new hnswlib::L2Space(dim);
    } else {
        throw std::runtime_error("Invalid metric type.");
    }

    index = new hnswlib::HierarchicalNSW<float>(space, num_data, M, ef_construction);
}

void HnswLibIndex::insert_vectors(const std::vector<float>& data, uint64_t label) {
    index->addPoint(data.data(), label);
}

std::pair<std::vector<long>, std::vector<float>> HnswLibIndex::search_vectors(const std::vector<float>& query, int k, int ef_search = 50) {
    index->setEf(ef_search);
    // 查询结果存在result（优先队列）中
    auto result = index->searchKnn(query.data(), k);


    std::vector<long> indices(k);
    std::vector<float> distances(k);
    for(int j = 0;j < k;j++){
        auto item = result.top();
        indices[j] = item.first;
        distances[j] = item.second;
        result.pop();
    }
    return {indices, distances};
}