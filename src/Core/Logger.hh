//
// Created by kevin on 30/04/17.
//

#ifndef INDIESTUDIO_LOGGER_HH
#define INDIESTUDIO_LOGGER_HH


#include <sstream>
#include <mutex>

class Logger {
public:
    enum LogLevel {
        ERROR,
        INFO,
        DEBUG
    };

    Logger();
    ~Logger();

    Logger(Logger const &)              = delete;
    Logger & operator=(Logger const &)  = delete;

    // THREAD SAFE LOGGER
    void debug(std::string const &);
    void info(std::string const &);
    void error(std::string const &);
private:
    std::ostringstream  _os;
    std::mutex          _mtx;

    void insertFormattedTime();

    static std::array<std::string, 3> const _log_to_string;
    static LogLevel const                   _log_level_reported;
};


#endif //INDIESTUDIO_LOGGER_HH
