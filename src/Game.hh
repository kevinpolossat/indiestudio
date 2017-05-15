//
// Created by kevin on 11/05/17.
//

#ifndef INDIESTUDIO_CORE_HH
#define INDIESTUDIO_CORE_HH

#include <chrono>
#include <vector>
#include <memory>

#include "IScene.hh"
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
    std::vector<std::unique_ptr<IScene>> _scenes;

    using Time = std::chrono::duration<float>;
};

#endif //INDIESTUDIO_CORE_HH
