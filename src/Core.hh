//
// Created by kevin on 11/05/17.
//

#ifndef INDIESTUDIO_CORE_HH
#define INDIESTUDIO_CORE_HH

#include "ResourceManager.hh"

class Core {
public:
    explicit Core();
    ~Core();

    Core(Core const &)              = delete;
    Core(Core &&)                   = delete;
    Core & operator=(Core const &)  = delete;

    int run();
private:
    ResourceManager _rm;
};


#endif //INDIESTUDIO_CORE_HH
