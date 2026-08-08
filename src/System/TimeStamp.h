

class TimeStamp{

    TimeStamp(const long long& CLK);
    TimeStamp(const TimeStamp&);
    long long operator=(const TimeStamp&);
    TimeStamp(const TimeStamp&&);
    long long operator=(const TimeStamp&&);


    long long m_TimeStamp;
    
public:

    long long GetTimeStampTime() const {return m_TimeStamp;}

    



};