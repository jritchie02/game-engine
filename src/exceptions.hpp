#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace engine
{
    class SpriteError : public std::exception
    {
    public:
        SpriteError(const std::string &msg) : m_msg(msg) {}

        const char *what() const noexcept override
        {
            return m_msg.c_str();
        }

    private:
        std::string m_msg;
    };
}

#endif