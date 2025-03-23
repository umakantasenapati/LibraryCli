#ifndef REDISCLIENT_H
#define REDISCLIENT_H

#include <sw/redis++/redis++.h>
#include <string>
#include <vector>
#include <memory>
#include <mutex>

class RedisClient {
public:
    explicit RedisClient(const std::string &connectionUri);

    void set(const std::string &key, const std::string &value);
    std::string get(const std::string &key);
    void del(const std::string &key);
    std::vector<std::string> keys(const std::string &pattern);

private:
    std::shared_ptr<sw::redis::Redis> redis;
    std::mutex redisMutex;
};

#endif // REDISCLIENT_H