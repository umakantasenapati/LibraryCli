#include "Library.h"
#include "Logger.h"
#include "RedisClient.h"
#include "BookFactory.h"

Library::Library(std::shared_ptr<RedisClient> redisClient, std::shared_ptr<Logger> logger)
    : redis(redisClient), auditLogger(logger) {}

void Library::addBook(const Book &book, const std::string &username) {
    std::lock_guard<std::mutex> lock(libraryMutex);
    redis->set(bookKey(book.getISBN()), book.toJson().dump());
    auditLogger->log(username + " added book with ISBN: " + book.getISBN());
    notifyObservers("Book added: " + book.getISBN());
}

std::optional<Book> Library::getBookByISBN(const std::string &isbn) {
    std::lock_guard<std::mutex> lock(libraryMutex);
    auto jsonStr = redis->get(bookKey(isbn));
    if (jsonStr.empty()) {
        return std::nullopt;
    }
    return Book::fromJson(nlohmann::json::parse(jsonStr));
}

std::vector<Book> Library::getAllBooks() {
    std::lock_guard<std::mutex> lock(libraryMutex);
    std::vector<Book> books;
    auto keys = redis->keys("book:*");
    for (const auto &key : keys) {
        auto jsonStr = redis->get(key);
        if (!jsonStr.empty()) {
            books.push_back(Book::fromJson(nlohmann::json::parse(jsonStr)));
        }
    }
    return books;
}

void Library::updateBook(const Book &book, const std::string &username) {
    std::lock_guard<std::mutex> lock(libraryMutex);
    redis->set(bookKey(book.getISBN()), book.toJson().dump());
    auditLogger->log(username + " updated book with ISBN: " + book.getISBN());
    notifyObservers("Book updated: " + book.getISBN());
}

void Library::deleteBook(const std::string &isbn, const std::string &username) {
    std::lock_guard<std::mutex> lock(libraryMutex);
    redis->del(bookKey(isbn));
    auditLogger->log(username + " deleted book with ISBN: " + isbn);
    notifyObservers("Book deleted: " + isbn);
}

void Library::registerObserver(std::shared_ptr<LibraryObserver> observer) {
    std::lock_guard<std::mutex> lock(libraryMutex);
    observers.insert(observer);
}

void Library::unregisterObserver(std::shared_ptr<LibraryObserver> observer) {
    std::lock_guard<std::mutex> lock(libraryMutex);
    observers.erase(observer);
}

void Library::notifyObservers(const std::string &message) {
    for (auto &observer : observers) {
        observer->onBookChanged(message);
    }
}

std::string Library::bookKey(const std::string &isbn) const {
    return "book:" + isbn;
}