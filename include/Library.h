#ifndef LIBRARY_H
#define LIBRARY_H

#include "Book.h"
#include "RedisClient.h"
#include "Logger.h"
#include "LibraryObserver.h"
#include <mutex>
#include <optional>
#include <vector>
#include <memory>
#include <set>

class Library {
public:
    explicit Library(std::shared_ptr<RedisClient> redisClient, std::shared_ptr<Logger> logger);

    void addBook(const Book &book, const std::string &username);
    std::optional<Book> getBookByISBN(const std::string &isbn);
    std::vector<Book> getAllBooks();
    void updateBook(const Book &book, const std::string &username);
    void deleteBook(const std::string &isbn, const std::string &username);

    void registerObserver(std::shared_ptr<LibraryObserver> observer);
    void unregisterObserver(std::shared_ptr<LibraryObserver> observer);

private:
    void notifyObservers(const std::string &message);

    std::string bookKey(const std::string &isbn) const;
    std::shared_ptr<RedisClient> redis;
    std::shared_ptr<Logger> auditLogger;
    std::mutex libraryMutex;
    std::set<std::shared_ptr<LibraryObserver>> observers;
};

#endif // LIBRARY_H