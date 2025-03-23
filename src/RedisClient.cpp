#include "RedisClient.h"

RedisClient::RedisClient(const std::string &connectionUri) {
    redis = std::make_shared<sw::redis::Redis>(connectionUri);
}

void RedisClient::set(const std::string &key, const std::string &value) {
    std::lock_guard<std::mutex> lock(redisMutex);
    redis->set(key, value);
}

std::string RedisClient::get(const std::string &key) {
    std::lock_guard<std::mutex> lock(redisMutex);
    auto val = redis->get(key);
    return val.value_or("");
}

void RedisClient::del(const std::string &key) {
    std::lock_guard<std::mutex> lock(redisMutex);
    redis->del(key);
}

std::vector<std::string> RedisClient::keys(const std::string &pattern) {
    std::lock_guard<std::mutex> lock(redisMutex);
    std::vector<std::string> allKeys;
    redis->keys(pattern, std::back_inserter(allKeys));
    return allKeys;
}