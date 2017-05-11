//
// Created by kevin on 11/05/17.
//

#ifndef INDIESTUDIO_CORE_HH
#define INDIESTUDIO_CORE_HH

class Core {
public:
    Core();
    ~Core();

    int run();

    Core(Core const & other)                = delete;
    Core & operator=(Core const & other)    = delete;
};


#endif //INDIESTUDIO_CORE_HH
