#include <chrono>
#include <ctime>
class Timer{
public:

    Timer(const long long& iterCount) : m_IterationCount{iterCount}
    {
        m_Start = std::chrono::steady_clock::now();
    }

    auto CLK() {m_IterationCount++;}
    auto Snapshot() const{return std::chrono::steady_clock::now() - m_Start;}
    long long& GetIterationCount() const {return m_IterationCount;}

private:
    std::chrono::steady_clock::time_point m_Start;
    long long m_IterationCount = 0;
};

