
#include "Timer.h"
#include "TimeStamp.h"


Timer::Timer(const unsigned long long& iterCount) 
    : m_IterationCount{iterCount}, 
    m_Start{}
{}



void Timer::CLK() {m_IterationCount++;}

TimeStamp Timer::SnapShot() const {
    auto elapsed = std::chrono::steady_clock::now() - m_Start;
    return TimeStamp{std::chrono::duration_cast<std::chrono::milliseconds>(elapsed)};
}



