//
// Created by kevin on 09/06/17.
//

#include "Timer.hh"

Timer::Timer(float duration): _duration(duration), _tStart(std::chrono::steady_clock::now()) {

}

Timer::~Timer() {

}

bool Timer::isOver() const {
    return std::chrono::duration_cast<std::chrono::seconds>(
            std::chrono::steady_clock::now() - _tStart
    ).count() > _duration;
}

Timer::Timer(Timer const &other) {
    _duration   = other._duration;
    _tStart     = other._tStart;
}

Timer::Timer(Timer &&other) {
    _duration   = other._duration;
    _tStart     = other._tStart;
}

Timer &Timer::operator=(Timer const &other) {
    _duration   = other._duration;
    _tStart     = other._tStart;
    return *this;
}
