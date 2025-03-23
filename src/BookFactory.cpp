#include "BookFactory.h"

Book BookFactory::createBook(const std::string &title, const std::string &author, const std::string &isbn,
                             const std::string &genre, int publicationYear, int copiesAvailable,
                             const std::string &description, const std::string &borrowingStatus) {
    return Book(title, author, isbn, genre, publicationYear, copiesAvailable, description, borrowingStatus);
}