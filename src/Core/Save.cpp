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
#include <chrono>
#include <vector>
#include <pwd.h>
#include "ResourceManager.hh"
#include "Save.hh"

std::string Save::getGameDirectory() {
#ifdef __unix__
    struct passwd *pw = getpwuid(getuid());
    const char *homedir = pw->pw_dir;
    std::string path(std::string(homedir) + "/TronBerman/");
    struct stat sb;
    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)))
        if (mkdir(path.c_str(), 0755) == -1)
            return "./";
    return path;
#else
    return "./"; //TODO: should return a valid path for Windows
#endif
}

void Save::save(Referee const &ref) {
    //ResourceManager::videoDriver()->writeImageToFile(ResourceManager::videoDriver()->createScreenShot(), "tmp.jpg");
    std::string gameDir = Save::getGameDirectory();
    std::string path1(gameDir);
    std::string path(gameDir + std::string("saves/"));
    struct stat sb;
    if (!(stat(path.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode)))
        if (mkdir(path.c_str(), 0755) == -1)
            throw RuntimeError("Cannot create saves folder", "save");

    std::ostringstream oss;
    oss << path;
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    oss << std::put_time(std::localtime(&now_c), "Save_TronBerman_%d-%m-%Y-%H-%M-%S");
    std::ofstream ofs(oss.str());
    if (!ofs.is_open())
        throw RuntimeError("Cannot open file " + oss.str(), "save");
    boost::archive::binary_oarchive oa(ofs, boost::archive::no_header);
    oa << ref;
    ofs.close();
}

std::vector<std::string> Save::getSaves() {
    std::vector<std::string> saves;
    std::string path(Save::getGameDirectory() + std::string("saves/"));
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(path.c_str())) != nullptr) {
        while ((ent = readdir (dir)) != nullptr) {
            if (ent->d_name[0] != '.')
                saves.push_back(std::string(ent->d_name));
        }
    }
    closedir(dir);
    return saves;
}

void Save::load(Referee & ref, std::string const &file) {
    std::ifstream ifs(Save::getGameDirectory() + "saves/" + file);
    if (!ifs.is_open())
        throw RuntimeError("Cannot open file " + file, "load");
    boost::archive::binary_iarchive ia(ifs, boost::archive::no_header);
    ia >> ref;
    ifs.close();
}