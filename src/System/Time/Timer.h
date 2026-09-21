#pragma once

#include "../../Aliases/Aliases.h"


#include <chrono>
#include <ctime>

class TimeStamp;

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

    unsigned long long m_IterationCount; 
    std::chrono::steady_clock::time_point m_Start;


};