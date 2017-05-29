//
// Created by fraiss_c on 01/02/17.
//

#include <iostream>
#include "Error.hh"

Error::Error(std::string const &message, std::string const &function) {
    this->_msg = "[THROW] in function " + function + ": " + message;
}

Error::~Error() throw() {

}

const char *
Error::what() const throw() {
    return this->_msg.c_str();
}

OutOfRange::OutOfRange(std::string const &message, std::string const &function)
        : Error(message, function) {

}

OutOfRange::~OutOfRange() {

}

BadArgument::BadArgument(std::string const &message, std::string const &function)
        : Error(message, function) {

}

BadArgument::~BadArgument() {

}

RuntimeError::RuntimeError(std::string const &message, std::string const &function)
        : Error(message, function) {

}

RuntimeError::~RuntimeError() {

}
