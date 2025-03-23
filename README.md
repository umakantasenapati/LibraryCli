Project Structure:

📂LibraryManager
 ├── 📁include
 │    ├── Book.h
 │    ├── Library.h
 │    ├── RedisClient.h
 │    ├── Logger.h
 │    └── Authenticator.h
 ├── 📁src
 │    ├── Book.cpp
 │    ├── Library.cpp
 │    ├── RedisClient.cpp
 │    ├── Logger.cpp
 │    └── Authenticator.cpp
 ├── CMakeLists.txt
 └── main.cpp

**Modern C++17 Concepts Used:**
- Smart pointers (`std::unique_ptr`, `std::shared_ptr`)
- `std::optional` for handling optional fields
- `std::unordered_map` for CLI argument parsing
- `std::mutex` and `std::lock_guard` for thread safety
- Structured bindings for cleaner code
- Proper move semantics
- String formatting with `std::ostringstream`

**Data Persistence:**
- All book records are stored and managed in Redis.
- Keys are structured as `book:<isbn>` and values are JSON serialized.
- Redis client interactions are encapsulated in `RedisClient` class for easy extension and thread-safe access.
