#include "Aliases.h"

#include <chrono>
#include <ctime>


class Timer{
public:

    Timer(const long long& iterCount);
    Timer(const Timer&) = delete;
    void operator=(const Timer&) = delete;
    Timer(const Timer&&) = delete;
    void operator=(const Timer&&) = delete;

    void CLK();
    auto SnapShot() const;
    long long& GetIterationCount() const;
    
private:
    std::chrono::steady_clock::time_point m_Start;
    long long m_IterationCount; 

};