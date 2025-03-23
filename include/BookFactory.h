#ifndef BOOKFACTORY_H
#define BOOKFACTORY_H

#include "Book.h"
#include <string>

class BookFactory {
public:
    static Book createBook(const std::string &title, const std::string &author, const std::string &isbn,
                           const std::string &genre, int publicationYear, int copiesAvailable,
                           const std::string &description, const std::string &borrowingStatus = "Available");
};

#endif // BOOKFACTORY_H