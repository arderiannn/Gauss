#ifndef GAUSSEXCEPTION_H
#define GAUSSEXCEPTION_H

#include <stdexcept>
#include <string>

class GaussException : public std::exception {
public:
    explicit GaussException(const std::string& message) : message(message) {}

    const char* what() const noexcept override {
        return message.c_str();
    }

private:
    std::string message;
};

#endif // GAUSSEXCEPTION_H
