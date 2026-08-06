#include "Timer.h"



Timer::Timer(const long long& iterCount) : m_IterationCount{iterCount}
{
    m_Start = std::chrono::steady_clock::now();
}

void Timer::CLK() {m_IterationCount++;}

auto Timer::SnapShot() const {return std::chrono::steady_clock::now() - m_Start;}

long long& Timer::GetIterationCount() const {return m_IterationCount;}


