
# 0.0.1 版本测试
curl -X POST -H "Content-Type: application/json" -d '{"vectors": [0.8], "id": 2, "indexType": "FLAT"}' http://localhost:8080/insert

curl -X POST -H "Content-Type: application/json" -d '{"vectors": [0.5], "k": 2, "indexType": "FLAT"}' http://localhost:8080/search

# 0.0.2 版本测试

# 写入类型为HNSW的向量数据
curl -X POST -H "Content-Type: application/json" -d '{"vectors": [0.2], "id": 3, "indexType": "HNSW"}' http://localhost:8080/insert
# 目标返回： {"retCode":0}

# 查询类型为HNSW的向量数据
curl -X POST -H "Content-Type: application/json" -d '{"vectors": [0.5], "k": 2, "indexType": "HNSW"}' http://localhost:8080/search
# 目标返回： {"vectors":[3],"distances":[0.09<....>],"retCode":0}