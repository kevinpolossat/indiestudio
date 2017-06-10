//
// Created by kevin on 09/06/17.
//

#ifndef INDIESTUDIO_TIMER_HH
#define INDIESTUDIO_TIMER_HH


#include <chrono>

class Timer {
public:
    Timer(uint32_t duration);
    ~Timer();

    Timer(Timer const & other);
    Timer(Timer && other);
    Timer & operator = (Timer const & other);

    uint32_t    elapse()    const;
    uint32_t    left()      const;
    uint32_t    duration()  const;
    bool        isOver()    const;
    void        update();
private:
    uint32_t    _duration;
    uint32_t    _left;
};


#endif //INDIESTUDIO_TIMER_HH
