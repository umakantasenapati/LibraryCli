// Authenticator.h

#ifndef AUTHENTICATOR_H
#define AUTHENTICATOR_H

#include <string>
#include <unordered_map>
#include <mutex>

class Authenticator {
public:
    Authenticator();

    void addUser(const std::string &username, const std::string &password, const std::string &role);
    bool authenticate(const std::string &username, const std::string &password);
    std::string getUserRole(const std::string &username);

private:
    std::unordered_map<std::string, std::pair<std::string, std::string>> users; // username -> (password, role)
    std::mutex authMutex;
};

#endif // AUTHENTICATOR_H