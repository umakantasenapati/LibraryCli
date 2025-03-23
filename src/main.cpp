#include "Library.h"
#include "Authenticator.h"
#include "Logger.h"
#include "RedisClient.h"
#include "AuditObserver.h"
#include "BookFactory.h"
#include <iostream>
#include <memory>

void printHelp() {
    std::cout << "Usage: ./LibraryCLI <username> <password> <operation> [parameters]\n";
    std::cout << "Operations:\n";
    std::cout << "  list                             - List all books\n";
    std::cout << "  add <title> <author> <isbn> <genre> <year> <copies> <description> - Add a new book (librarian only)\n";
    std::cout << "  get <isbn>                      - Get details of a book\n";
    std::cout << "  update <isbn> <copies>          - Update copies available (librarian only)\n";
    std::cout << "  delete <isbn>                   - Delete a book (librarian only)\n";
}

int main(int argc, char* argv[]) {
    if (argc < 4) {
        printHelp();
        return 1;
    }

    std::string username = argv[1];
    std::string password = argv[2];
    std::string operation = argv[3];

    Authenticator auth;
    if (!auth.authenticate(username, password)) {
        std::cout << "Authentication failed!\n";
        return 1;
    }

    std::string role = auth.getUserRole(username);

    // Create a RedisClient with a connection pool
    auto redisClient = std::make_shared<RedisClient>("tcp://127.0.0.1:6379");

    // Create a Logger instance (no longer a Singleton)
    auto auditLogger = std::make_shared<Logger>("library_audit.log");

    // Create the Library with RedisClient and Logger
    Library library(redisClient, auditLogger);

    // Create and register an AuditObserver
    auto auditObserver = std::make_shared<AuditObserver>(auditLogger);
    library.registerObserver(auditObserver);

    if (operation == "list") {
        auto books = library.getAllBooks();
        for (const auto &book : books) {
            std::cout << book.toJson().dump(4) << std::endl;
        }
    } else if (operation == "add") {
        if (role != "librarian") {
            std::cout << "Only librarian can add books.\n";
            return 1;
        }
        if (argc < 11) {
            printHelp();
            return 1;
        }
        // Use BookFactory to create a new book
        Book book = BookFactory::createBook(
            argv[4],  // title
            argv[5],  // author
            argv[6],  // isbn
            argv[7],  // genre
            std::stoi(argv[8]),  // publicationYear
            std::stoi(argv[9]),  // copiesAvailable
            argv[10]  // description
        );
        library.addBook(book, username);
    } else if (operation == "get") {
        if (argc < 5) {
            printHelp();
            return 1;
        }
        auto bookOpt = library.getBookByISBN(argv[4]);
        if (bookOpt.has_value()) {
            std::cout << bookOpt.value().toJson().dump(4) << std::endl;
        } else {
            std::cout << "Book not found.\n";
        }
    } else if (operation == "update") {
        if (role != "librarian") {
            std::cout << "Only librarian can update books.\n";
            return 1;
        }
        if (argc < 6) {
            printHelp();
            return 1;
        }
        auto bookOpt = library.getBookByISBN(argv[4]);
        if (bookOpt.has_value()) {
            Book book = bookOpt.value();
            book.setCopiesAvailable(std::stoi(argv[5]));
            library.updateBook(book, username);
        } else {
            std::cout << "Book not found.\n";
        }
    } else if (operation == "delete") {
        if (role != "librarian") {
            std::cout << "Only librarian can delete books.\n";
            return 1;
        }
        if (argc < 5) {
            printHelp();
            return 1;
        }
        library.deleteBook(argv[4], username);
    } else {
        printHelp();
        return 1;
    }

    return 0;
}