#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::time_point<Clock> float_tp;

class Timer
{
private:
    float_tp current_frame_time;
    float_tp last_frame_time;

public:
    Timer() : current_frame_time(Clock::now()), last_frame_time(Clock::now()) {};

    inline void update() 
    {
        last_frame_time = current_frame_time;
        current_frame_time = Clock::now();
    }

	inline float get_delta_time() const
	{
        std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(current_frame_time - last_frame_time);
        return deltaTime.count();
	}	
};

#endif