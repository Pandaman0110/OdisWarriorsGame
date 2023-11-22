#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <queue>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <array>
#include <ranges>

constexpr size_t max_frame_times = 120;
constexpr size_t min_frame_times = 0;

class Timer
{
private:
    typedef std::chrono::steady_clock Clock;
    typedef std::chrono::time_point<Clock> float_tp;

    float_tp real_start_time;
    float_tp current_frame_time;
    float_tp last_frame_time;

    std::deque<float> frame_queue;

    bool started = false;
    bool paused = true;

    int calculate_fps() const
    {
        return static_cast<int>(max_frame_times / std::accumulate(frame_queue.begin(), frame_queue.end(), 0.0));
    }

    constexpr inline float get_time_dif(float_tp time_1, float_tp time_2) const
    {
        return (std::chrono::duration_cast<std::chrono::duration<float>>(time_1 - time_2)).count();
    }

    float_tp get_time()
    {
        return Clock::now();
    }
public:
    Timer() 
        : 
        real_start_time(get_time()),
        current_frame_time(get_time()),
        last_frame_time(get_time())
    {
        frame_queue.resize(max_frame_times);
        std::fill(frame_queue.begin(), frame_queue.end(), 0.0f);
    };

    void update() 
    {
        if (not paused)
        {
            last_frame_time = current_frame_time;
            current_frame_time = get_time();

            frame_queue.push_front(get_delta_time());
            if (frame_queue.size() > max_frame_times)
                frame_queue.pop_back();
        }
    }


    void start()
    {
        started = true;
        paused = false;
    }

    void stop()
    {
        started = false;
        paused = true;
    }

    void pause()
    {
        
    }

    void unpause()
    {

    }


    inline float get_delta_time() const
    {
        return get_time_dif(current_frame_time, last_frame_time);
    }

    inline float get_time_since_start() const
    {
        return get_time_dif(current_frame_time, real_start_time);
    }

    inline int get_fps() const
    {
        return calculate_fps();
    }
};

#endif