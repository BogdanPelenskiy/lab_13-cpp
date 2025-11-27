#pragma once
#include <exception>
#include <string>

class FileException : public std::exception {
    std::string message;
public:
    explicit FileException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class ValidationException : public std::exception {
    std::string message;
public:
    explicit ValidationException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};
