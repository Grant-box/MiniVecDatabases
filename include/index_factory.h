#pragma once

#include "faiss_index.h"
#include <map>

class IndexFactory {
public:
    // 枚举类，便于判断工厂调用方法
    enum class IndexType {
        FLAT,
        HNSW,
        UNKNOWN = -1
    };

    enum class MetricType {
        L2,
        IP
    };
    // 默认使用L2距离
    void init(IndexFactory::IndexType type,int dim, int num_data = 0, IndexFactory::MetricType metric = MetricType::L2);
    // 获取索引
    void* getIndex(IndexFactory::IndexType type) const;

private:
    
    std::map<IndexType, void*> index_map;
};

IndexFactory* getGlobalIndexFactory();