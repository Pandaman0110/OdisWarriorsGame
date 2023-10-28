#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include <chrono>

typedef std::chrono::steady_clock Clock;
typedef std::chrono::time_point<Clock> float_tp;

const int FPS_AVERAGE = 30;

class Timer
{
private:
    float_tp current_frame_time;
    float_tp last_frame_time;

    std::vector<int> frame_queue;
    int current_fps = 0;
public:
    Timer() : current_frame_time(Clock::now()), last_frame_time(Clock::now()) {};

    inline void update() 
    {
        last_frame_time = current_frame_time;
        current_frame_time = Clock::now();

        frame_queue.push_back(static_cast<int>(100.0f / get_delta_time()));
        if (frame_queue.size() > FPS_AVERAGE)
            frame_queue.pop_back();

        //for (auto& e : frame_queue)
            //std::cout << e <<"\n"

        current_fps = std::accumulate(frame_queue.begin(), frame_queue.end(), 0);
        current_fps /= FPS_AVERAGE;
    }

    inline float get_delta_time() const
    {
        std::chrono::duration<float> deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(current_frame_time - last_frame_time);
        return deltaTime.count();
    }

    inline int get_fps() const
    {
        return 100 / get_delta_time();
    }
};

#endif