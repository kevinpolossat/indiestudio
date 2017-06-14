/*
** Save.cpp for cpp in /home/lecler_2/delivery/cpp/Save.cpp
**
** Made by Mickaël Leclerc
** Login   <mickael.leclerc@epitech.eu>
**
** Started on  Wed Jun 14 11:23:55 2017 Mickaël Leclerc
** Last update Wed Jun 14 11:23:55 2017 Mickaël Leclerc
*/

#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <pwd.h>
#include "ResourceManager.hh"
#include "Save.hh"

void Save::save(Referee const &ref) {
    //ResourceManager::videoDriver()->writeImageToFile(ResourceManager::videoDriver()->createScreenShot(), "tmp.jpg");
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string path(homedir + std::string("/TronBerman/"));
    struct stat sb;

    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
        if (mkdir(path.c_str(), 0755) == -1)
            throw RuntimeError("Cannot create save folder", "save");
    }
    std::ostringstream oss;
    oss << path;
    oss << std::put_time(&tm, "Save_TronBerman_%d-%m-%Y-%H-%M-%S");
    std::ofstream ofs(oss.str());
    if (!ofs.is_open())
        throw RuntimeError("Cannot open file", "save");
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << ref;
    ofs.close();
}

std::vector<std::string> Save::getSaves() {
    return std::vector<std::string>();
}

void Save::load(Referee const &ref, std::string const &file) {
    std::ifstream ifs(file);
    if (!ifs.is_open())
        throw RuntimeError("Cannot open file", "load");
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia >> ref;
    ifs.close();
}