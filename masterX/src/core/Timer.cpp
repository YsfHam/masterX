#include "Timer.hpp"


mx::Timer::Timer() 
    : m_time(std::chrono::high_resolution_clock::now())
{   
}

mx::Time mx::Timer::getElapsedTime() const 
{
    auto now = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = now - m_time;

    return Time(duration.count());
}

mx::Time mx::Timer::restart() 
{
    Time elapsed = getElapsedTime();
    m_time = std::chrono::high_resolution_clock::now();
    return elapsed;
}
