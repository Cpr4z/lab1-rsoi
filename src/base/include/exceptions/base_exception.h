#pragma once

#include <exception>
#include <string>


#define PROJECT_EXCEPTION(ExceptionName, ExceptionParent, message)                                                     \
    class ExceptionName : public ExceptionParent                                                                       \
    {                                                                                                                  \
    public:                                                                                                            \
        ExceptionName() = default;                                                                                     \
        ExceptionName(const std::string &msg) : ExceptionParent(std::string(message) + msg)                            \
        {                                                                                                              \
        }                                                                                                              \
    };

class BaseException : public std::exception {
public:
    BaseException() = default;
    explicit BaseException(const std::string& message) : m_message(message) {}

    [[nodiscard]] const char* what() const noexcept override
    {
        return m_message.c_str();
    }

    [[nodiscard]] const std::string& getInfo() const noexcept
    {
        return m_message;
    }

private:
    std::string m_message;
};