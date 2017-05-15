//
// Created by kevin on 11/05/17.
//

#ifndef INDIESTUDIO_CORE_HH
#define INDIESTUDIO_CORE_HH

#include "ResourcesManager.hh"

class Core {
public:
    Core();
    ~Core();

    Core(Core const &)              = delete;
    Core(Core &&)                   = delete;
    Core & operator=(Core const &)  = delete;

    int run();
private:
    ResourcesManager _rm;
};


#endif //INDIESTUDIO_CORE_HH
