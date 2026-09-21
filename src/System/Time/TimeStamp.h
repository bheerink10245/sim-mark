#pragma once


#include <chrono>
#include <ctime>


class TimeStamp{

    std::chrono::milliseconds m_Value;
    
public:

    explicit TimeStamp(std::chrono::milliseconds timePoint);
    TimeStamp(const TimeStamp& other);
    TimeStamp& operator=(const TimeStamp& other);
    TimeStamp(TimeStamp&& other) noexcept;
    TimeStamp& operator=(TimeStamp&& other) noexcept;

    auto operator<=>(const TimeStamp&) const;

    inline std::chrono::milliseconds GetTimeStampValue() const {return m_Value;}

};