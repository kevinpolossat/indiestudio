//
// Created by kevin on 30/04/17.
//

#include <iostream>
#include <ctime>
#include <iomanip>

#include "Logger.hh"

Logger::LogLevel const Logger::_log_level_reported = Logger::LogLevel::DEBUG;

std::array<std::string, 3> const Logger::_log_to_string = {
        std::string("ERROR"),
        std::string("INFO"),
        std::string("DEBUG")
};

Logger::Logger() {

}

Logger::~Logger() {
    std::cerr << _os.str();
    std::flush(std::cerr);
}

void Logger::debug(std::string const &msg) {
    if (Logger::LogLevel::DEBUG <= Logger::_log_level_reported) {
        std::unique_lock<std::mutex> u_lock(_mtx);
        _os << "[" << Logger::_log_to_string[Logger::LogLevel::DEBUG] << " ";
        insertFormattedTime();
        _os << "] " << msg << std::endl;
    }
}

void Logger::info(std::string const &msg) {
    if (Logger::LogLevel::INFO <= Logger::_log_level_reported) {
        std::unique_lock<std::mutex> u_lock(_mtx);
        _os << "[" << Logger::_log_to_string[Logger::LogLevel::INFO] << " ";
        insertFormattedTime();
        _os << "] " << msg << std::endl;
    }
}

void Logger::error(std::string const & msg) {
    if (Logger::LogLevel::ERROR <= Logger::_log_level_reported) {
        std::unique_lock<std::mutex> u_lock(_mtx);
        _os << "[" << Logger::_log_to_string[Logger::LogLevel::ERROR] << " ";
        insertFormattedTime();
        _os << "] " << msg << std::endl;
    }
}

void Logger::insertFormattedTime() {
}
