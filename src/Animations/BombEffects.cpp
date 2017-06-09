//
// Created by kevin on 09/06/17.
//

#include <iostream>
#include "BombEffects.hh"
#include "InternalExplosion.hh"
#include "Explosion.hh"


//1.0f is the time of the explosion
BombEffects::BombEffects(irr::core::vector3df const &pos, float duration):
        _pos(pos), _timer(duration + 1.0f), _next(false) {
    _currentEffect = std::make_shared<InternalExplosion>(pos, duration);
}

BombEffects::BombEffects(BombEffects const &other):
        _pos(other._pos), _timer(other._timer), _currentEffect(other._currentEffect), _next(other._next) {
}

BombEffects::BombEffects(BombEffects &&other):
        _pos(other._pos), _timer(other._timer), _currentEffect(other._currentEffect), _next(other._next)  {

}

BombEffects &BombEffects::operator=(BombEffects const &other) {
    _pos            = other._pos;
    _timer          = other._timer;
    _currentEffect  = other._currentEffect;
    _next           = other._next;
    return *this;
}

BombEffects::~BombEffects() {

}

bool BombEffects::isOver() const {
    return _timer.isOver();
}

void BombEffects::update() {
    if (_timer.left() <= 1.0f && !_next) {
        _next = true;
        _currentEffect = std::make_shared<Explosion>(_pos, 1.0f);
    }
}