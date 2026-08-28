
#include "Timestamp.h"


explicit TimeStamp::TimeStamp(std::chrono::milliseconds timePoint) 
    : m_Value{timePoint} 
    {}

TimeStamp::TimeStamp(const TimeStamp& other)
    : m_Value{other.m_Value}
{}

TimeStamp& TimeStamp::operator=(const TimeStamp& other){
    if (this != &other){
        this->m_Value = other.m_Value;
    }

    return *this;
}

TimeStamp::TimeStamp(TimeStamp&& other) noexcept
    : m_Value{std::move(other.m_Value)}
{}

TimeStamp& TimeStamp::operator=(TimeStamp&& other) noexcept{
    if (this != &other){
        this->m_Value = std::move(other.m_Value);
    }

    return *this;
}