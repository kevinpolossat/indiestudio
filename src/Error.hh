//
// Created by fraiss_c on 01/02/17.
//


#ifndef CPP_ERROR_HH
#define CPP_ERROR_HH

#include <exception>
#include <string>

class 					Error : public std::exception {
protected:
    std::string         _msg;

public:
    Error(std::string const & = "", std::string const & = "");
    virtual ~Error() throw();

    virtual const char*     what() const throw();
};

class                   OutOfRange : public Error {
public:
    OutOfRange(std::string const &, std::string const &);
    virtual ~OutOfRange() throw();
};

class                   BadArgument : public Error {
public:
    BadArgument(std::string const &, std::string const &);
    virtual ~BadArgument() throw();
};

class                   RuntimeError : public Error {
public:
    RuntimeError(std::string const &, std::string const &);
    virtual ~RuntimeError() throw();
};

#endif //CPP_ERROR_HH
