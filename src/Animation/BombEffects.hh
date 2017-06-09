//
// Created by kevin on 09/06/17.
//

#ifndef INDIESTUDIO_BOMBEXPLOSION_HH
#define INDIESTUDIO_BOMBEXPLOSION_HH

#include <memory>

#include "irrlicht.h"
#include "IEffect.hh"
#include "Timer.hh"

class BombEffects: public IEffect {
public:
    BombEffects(irr::core::vector3df const & pos, float duration = 1.0f);
    BombEffects(BombEffects const & other);
    BombEffects(BombEffects && other);
    BombEffects &operator = (BombEffects const & other);

    ~BombEffects();
    bool isOver() const;
    void update();
private:
    irr::core::vector3df        _pos;
    Timer                       _timer;
    std::shared_ptr<IEffect>    _currentEffect;
    bool                        _next;
};


#endif //INDIESTUDIO_BOMBEXPLOSION_HH
