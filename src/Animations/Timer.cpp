//
// Created by kevin on 09/06/17.
//

#include "Timer.hh"

Timer::Timer(uint32_t duration): _duration(duration), _left(duration) {

}

Timer::~Timer() {

}

bool Timer::isOver() const {
    return !_left;
}

Timer::Timer(Timer const &other) {
    _duration   = other._duration;
    _left     = other._left;
}

Timer::Timer(Timer &&other) {
    _duration   = other._duration;
    _left     = other._left;
}

Timer &Timer::operator=(Timer const &other) {
    _duration   = other._duration;
    _left     = other._left;
    return *this;
}

uint32_t Timer::elapse() const {
    return _duration - _left;
}

uint32_t Timer::duration() const {
    return _duration;
}

uint32_t Timer::left() const {
    return _left;
}

void Timer::update() {
    --_left;
}
