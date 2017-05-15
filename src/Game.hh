//
// Created by kevin on 11/05/17.
//

#ifndef INDIESTUDIO_CORE_HH
#define INDIESTUDIO_CORE_HH

#include "ResourceManager.hh"

class Game {
public:
    explicit Game();
    ~Game();

    Game(Game const &)              = delete;
    Game(Game &&)                   = delete;
    Game & operator=(Game const &)  = delete;

    int run();
private:
    ResourceManager _rm;
};


#endif //INDIESTUDIO_CORE_HH
