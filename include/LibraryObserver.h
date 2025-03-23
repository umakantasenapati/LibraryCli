#ifndef LIBRARYOBSERVER_H
#define LIBRARYOBSERVER_H

#include <string>
#include <memory>

class LibraryObserver {
public:
    virtual ~LibraryObserver() = default;
    virtual void onBookChanged(const std::string &message) = 0;
};

#endif // LIBRARYOBSERVER_H