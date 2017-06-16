/*
** Save.hh for cpp in /home/lecler_2/delivery/cpp/Save.hh
**
** Made by Mickaël Leclerc
** Login   <mickael.leclerc@epitech.eu>
**
** Started on  Wed Jun 14 11:23:55 2017 Mickaël Leclerc
** Last update Wed Jun 14 11:23:55 2017 Mickaël Leclerc
*/
#ifndef CPP_SAVE_HH
#define CPP_SAVE_HH

#include "Referee.hh"

class Save {
public:
    Save() = delete;
    Save(Save const & other) = delete;
    Save(Save const && other) = delete;
    ~Save() = delete;

    static std::string getGameDirectory(void);
    static void save(Referee const& ref);
    static std::vector<std::string> getSaves(void);
    static void load(Referee & ref, std::string const& file);
};

#endif //CPP_SAVE_HH
