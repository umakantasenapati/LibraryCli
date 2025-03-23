// Authenticator.cpp

#include "Authenticator.h"

Authenticator::Authenticator() {
    // Add default librarian user
    addUser("admin", "admin123", "librarian");
    addUser("reader", "reader123", "reader");
}

void Authenticator::addUser(const std::string &username, const std::string &password, const std::string &role) {
    std::lock_guard<std::mutex> lock(authMutex);
    users[username] = std::make_pair(password, role);
}

bool Authenticator::authenticate(const std::string &username, const std::string &password) {
    std::lock_guard<std::mutex> lock(authMutex);
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second.first == password;
    }
    return false;
}

std::string Authenticator::getUserRole(const std::string &username) {
    std::lock_guard<std::mutex> lock(authMutex);
    auto it = users.find(username);
    if (it != users.end()) {
        return it->second.second;
    }
    return "reader";
}
