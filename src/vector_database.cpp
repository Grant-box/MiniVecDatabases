#include "vector_database.h"
#include "logger.h"
#include "scalar_storage.h"
#include "index_factory.h"
#include "faiss_index.h"
#include "hnswlib_index.h"
#include <vector>
#include <rapidjson/document.h>

VectorDatabase::VectorDatabase(const std::string& db_path) : scalar_storage_(db_path){}

void VectorDatabase::upsert(uint64_t id, const rapidjson::Document& data, IndexFactory::IndexType index_type){
    rapidjson::Document existingData;

    try{
        existingData = scalar_storage_.get_scalar(id);
    }catch(const std::runtime_error& e){
        // 向量不存在，忽略error，继续后续流程
    }
    
    if(existingData.IsObject()){
        std::vector<float> existingVector(existingData["vectors"].Size());
        for(rapidjson::SizeType i = 0;i < existingData["vectors"].Size();++i){
            existingVector[i] = existingData["vectors"][i].GetFloat();
        }
        void* index = getGlobalIndexFactory()->getIndex(index_type);
        switch(index_type){
            case IndexFactory::IndexType::FLAT: {
                FaissIndex* faiss_index = static_cast<FaissIndex*>(index);
                faiss_index->remove_vectors({static_cast<long>(id)});
                break;
            }
            case IndexFactory::IndexType::HNSW: {
                HNSWLibIndex* hnsw_index = static_cast<HNSWLibIndex*>(index);
                break;
            }
            default:
                break;
        }
    }
    std::vector<float> newVector(data["vectors"].Size());
    for(rapidjson::SizeType i = 0;i < data["vectors"].Size();++i){
        newVector[i] = data["vectors"][i].GetFloat();
    }

    void* index = getGlobalIndexFactory()->getIndex(index_type);
    switch(index_type){
        case IndexFactory::IndexType::FLAT: {
            FaissIndex* faiss_index = static_cast<FaissIndex*>(index);
            faiss_index->insert_vectors(newVector, id);
            break;
        }
        case IndexFactory::IndexType::HNSW: {
            HNSWLibIndex* hnsw_index = static_cast<HNSWLibIndex*>(index);
            hnsw_index->insert_vectors(newVector, id);
            break;
        }
        default:
            break;
    }

    scalar_storage_.insert_scalar(id, data);
}

rapidjson::Document VectorDatabase::query(uint64_t id){
    return scalar_storage_.get_scalar(id);
}