**Library Management System**
This is a Library Management System implemented in C++. It allows users to manage books in a library, including adding, updating, deleting, and retrieving books. The system uses Redis as the backend data store and supports concurrency through a connection pool.

Features
   Book Management:
       Add a new book.
       Update an existing book (e.g., change the number of copies available).
       Delete a book.
       Retrieve book details by ISBN.
       List all books in the library.

User Authentication:
       Supports two roles: librarian and reader.
       Librarians can add, update, and delete books.
       Readers can only view book details.

Audit Logging:
      All actions (e.g., adding, updating, deleting books) are logged for auditing purposes.



**Prerequisites**
Before running the application, ensure you have the following installed:

C++ Compiler:
   Supports C++17 (e.g., g++ or clang++).

Redis Server:
    Install and run a Redis server locally or use a remote Redis instance.
    Default connection: tcp://127.0.0.1:6379.
  
redis-plus-plus Library:
    Install the redis-plus-plus C++ client for Redis.

CMake:
    Required for building the project.




**Running the Application**
Command-Line Interface (CLI)
The application is a command-line tool. Use the following syntax to perform operations:

    ./LibraryCLI <username> <password> <operation> [parameters]

Operations
List all books:
    ./LibraryCLI <username> <password> list

Add a new book (librarian only):
    ./LibraryCLI <username> <password> add <title> <author> <isbn> <genre> <year> <copies> <description>
Get book details by ISBN:
   ./LibraryCLI <username> <password> get <isbn>

Update book copies (librarian only):
    ./LibraryCLI <username> <password> update <isbn> <copies>
Delete a book (librarian only):
    ./LibraryCLI <username> <password> delete <isbn>

**Design and Implementation**
Key Components
 **RedisClient:**
    Manages connections to the Redis server.

 ** Library:**
   Implements the core logic for managing books.
   Uses RedisClient to interact with Redis.

 **Logger:**
   Logs all actions (e.g., adding, updating, deleting books) to a file (library_audit.log).

**Authenticator:**
  Handles user authentication and role-based access control.

**BookFactory:**
  Centralizes the creation of Book objects.

**AuditObserver:**
  Observes changes to the library (e.g., book additions, updates, deletions) and logs them.
