#pragma once

#include "Aliases.h"
#include "TimeStamp.h"

#include <chrono>
#include <ctime>


class Timer{
public:

    Timer(const unsigned long long& iterCount);
    Timer(const Timer&) = delete;
    Timer& operator=(const Timer&) = delete;
    Timer(const Timer&&) = delete;
    Timer& operator=(const Timer&&) = delete;

    void CLK();
    TimeStamp SnapShot() const;
    unsigned long long GetIterationCount() const {return m_IterationCount;}
    
private:
    std::chrono::steady_clock::time_point m_Start;
    unsigned long long m_IterationCount; 

};