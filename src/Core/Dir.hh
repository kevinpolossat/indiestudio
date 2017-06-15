//
// Created by kevin on 15/06/17.
//

#ifndef INDIESTUDIO_DIR_HH
#define INDIESTUDIO_DIR_HH

#include <string>

#ifdef __unix__
#include <sys/stat.h>
#include <dirent.h>
#else
#include <windows.h>
#endif // __unix__

class Dir {
    Dir(std::string const &);
    Dir(Dir const & other)          = delete;
    Dir(Dir && other)               = delete;
    Dir & operator = (Dir const &)  = delete;

    ~Dir();

    static bool exists(std::string const & name);
};


#endif //INDIESTUDIO_DIR_HH
