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
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <vector>
#include <pwd.h>
#include "ResourceManager.hh"
#include "Save.hh"

void Save::save(Referee const &ref) {
    //ResourceManager::videoDriver()->writeImageToFile(ResourceManager::videoDriver()->createScreenShot(), "tmp.jpg");

#ifdef __unix__
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string path1(homedir + std::string("/TronBerman/"));
    std::string path(homedir + std::string("/TronBerman/saves/"));
    struct stat sb;
    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
        mkdir(path1.c_str(), 0755);
        if (mkdir(path.c_str(), 0755) == -1)
            throw RuntimeError("Cannot create saves folder", "save");
    }
#else
    std::string path("./");
#endif

    std::ostringstream oss;
    oss << path;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    oss << std::put_time(&tm, "Save_TronBerman_%d-%m-%Y-%H-%M-%S");
    std::cout << oss.str() << std::endl;
    std::ofstream ofs(oss.str());
    if (!ofs.is_open())
        throw RuntimeError("Cannot open file " + oss.str(), "save");
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << ref;
    ofs.close();
}

std::vector<std::string> Save::getSaves() {
    std::vector<std::string> saves;

#ifdef __unix__
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string path(homedir + std::string("/TronBerman/saves/"));
#else
    std::string path("./");
#endif

    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            saves.push_back(std::string(ent->d_name));
        }
    }
    return saves;
}

void Save::load(Referee & ref, std::string const &file) {
    std::ifstream ifs(file);
    if (!ifs.is_open())
        throw RuntimeError("Cannot open file " + file, "load");
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia >> ref;
    ifs.close();
}