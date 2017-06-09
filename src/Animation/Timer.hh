//
// Created by kevin on 09/06/17.
//

#ifndef INDIESTUDIO_TIMER_HH
#define INDIESTUDIO_TIMER_HH


#include <chrono>

class Timer {
public:
    Timer(float duration);
    ~Timer();

    Timer(Timer const & other);
    Timer(Timer && other);
    Timer & operator = (Timer const & other);

    float   duration()  const;
    bool    isOver()    const;
    float   elapse()    const;
    float   left()      const;
private:
    float                                                   _duration;
    std::chrono::steady_clock::time_point                   _tStart;
};


#endif //INDIESTUDIO_TIMER_HH
