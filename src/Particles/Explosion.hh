//
// Created by kevin on 26/05/17.
//

#ifndef INDIESTUDIO_EXPLOSION_HH
#define INDIESTUDIO_EXPLOSION_HH


class Explosion {
public:
    explicit Explosion();
    Explosion(Explosion const & other)                  = delete;
    Explosion(Explosion && other)                       = delete;
    Explosion & operator = (Explosion const & other)    = delete;

    ~Explosion();
};


#endif //INDIESTUDIO_EXPLOSION_HH
