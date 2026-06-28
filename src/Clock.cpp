#include <chrono>


class Clock
{
public:
    Clock() : m_LastTime(std::chrono::system_lock::now(), m_Accumulator(0))
    {}

    void ticK()



private:

    std::chrono::system_clock::time_point m_LastTime;
    std::chrono::milliseconds m_Accumulator;

};