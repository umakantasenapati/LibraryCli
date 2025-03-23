// Book.cpp

#include "Book.h"

Book::Book(const std::string &title, const std::string &author, const std::string &isbn,
           const std::string &genre, int publicationYear, int copiesAvailable,
           const std::string &description, const std::string &borrowingStatus)
        : title(title), author(author), isbn(isbn), genre(genre),
          publicationYear(publicationYear), copiesAvailable(copiesAvailable),
          description(description), borrowingStatus(borrowingStatus) {}

std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
std::string Book::getISBN() const { return isbn; }
std::string Book::getGenre() const { return genre; }
int Book::getPublicationYear() const { return publicationYear; }
int Book::getCopiesAvailable() const { return copiesAvailable; }
std::string Book::getDescription() const { return description; }
std::string Book::getBorrowingStatus() const { return borrowingStatus; }

void Book::setCopiesAvailable(int copies) { copiesAvailable = copies; }
void Book::setBorrowingStatus(const std::string &status) { borrowingStatus = status; }

nlohmann::json Book::toJson() const {
    return nlohmann::json{{"title", title},
                          {"author", author},
                          {"isbn", isbn},
                          {"genre", genre},
                          {"publicationYear", publicationYear},
                          {"copiesAvailable", copiesAvailable},
                          {"description", description},
                          {"borrowingStatus", borrowingStatus}};
}

Book Book::fromJson(const nlohmann::json &j) {
    return Book(j.at("title").get<std::string>(),
                j.at("author").get<std::string>(),
                j.at("isbn").get<std::string>(),
                j.at("genre").get<std::string>(),
                j.at("publicationYear").get<int>(),
                j.at("copiesAvailable").get<int>(),
                j.at("description").get<std::string>(),
                j.at("borrowingStatus").get<std::string>());
}
