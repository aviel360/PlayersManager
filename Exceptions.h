//
// Created by Sofia Blyufer on 28/11/2021.
//

#ifndef PROJNAME_EXCEPTIONS_H
#define PROJNAME_EXCEPTIONS_H
#include <exception>
#include <string>
/**
 *
 */
class Exception : public std::exception
{
public:
    virtual const char * what () const noexcept;
};

class ValueExists : public Exception
{
public:
    const char * what () const noexcept;
};

class InvalidInput : public Exception
{
public:
    const char * what () const noexcept;
};

class ValueNotExists : public Exception
{
public:
    const char * what () const noexcept;
};
#endif //PROJNAME_EXCEPTIONS_H
