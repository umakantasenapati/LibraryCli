// Book.h

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <nlohmann/json.hpp>

class Book {
public:
    Book() = default;
    Book(const std::string &title, const std::string &author, const std::string &isbn,
         const std::string &genre, int publicationYear, int copiesAvailable,
         const std::string &description, const std::string &borrowingStatus);

    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    std::string getGenre() const;
    int getPublicationYear() const;
    int getCopiesAvailable() const;
    std::string getDescription() const;
    std::string getBorrowingStatus() const;

    void setCopiesAvailable(int copies);
    void setBorrowingStatus(const std::string &status);

    nlohmann::json toJson() const;
    static Book fromJson(const nlohmann::json &j);

private:
    std::string title;
    std::string author;
    std::string isbn;
    std::string genre;
    int publicationYear{};
    int copiesAvailable{};
    std::string description;
    std::string borrowingStatus;
};

#endif // BOOK_H
