#include "index_factory.h"
#include <faiss/IndexFlat.h>
#include <faiss/IndexIDMap.h>

 // Start of Selection
// 这里使用匿名命名空间来定义一个全局的IndexFactory实例，
// 这样做的目的是为了限制globalIndexFactory的作用域，
// 使其仅在当前文件中可见，避免与其他文件中的同名变量冲突。
namespace {
    IndexFactory globalIndexFactory;
}

IndexFactory* getGlobalIndexFactory() {
    return &globalIndexFactory;
}

void IndexFactory::init(IndexType type, int dim, MetricType metric) {
    
    // 根据选择的度量类型，设置faiss的度量类型。如果选择的是L2距离，则使用METRIC_L2；否则使用METRIC_INNER_PRODUCT（内积度量）。
    faiss::MetricType faiss_metric = (metric == MetricType::L2) ? faiss::MetricType::METRIC_L2 : faiss::MetricType::METRIC_INNER_PRODUCT;
    // 根据不同的索引类型创建不同的索引
    // 该代码段使用switch语句根据索引类型创建相应的索引对象。
    // 当索引类型为FLAT时，创建一个新的FaissIndex实例。
    // 具体实现是先创建一个IndexFlat对象，使用指定的维度和度量类型（faiss_metric），
    // 然后将其包装在IndexIDMap2中，最后将这个组合对象赋值给index_map中的相应类型。
    // 如果索引类型不是FLAT，则不执行任何操作。
    switch (type) {
        case IndexType::FLAT:
            index_map[type] = new FaissIndex(new faiss::IndexIDMap(new faiss::IndexFlat(dim, faiss_metric)));
            break;
        default:
            break;
    }
}

// 找到对应的索引类型
void* IndexFactory::getIndex(IndexType type) const {
    auto it = index_map.find(type);
    if(it != index_map.end()) {
        return it->second;
    }
    return nullptr;
}
