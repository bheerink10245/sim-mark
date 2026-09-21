
#pragma once 

#include "../Aliases/Aliases.h"
#include "../System/Time/TimeStamp.h"

#include <map>
#include <expected>
#include <stdexcept>
#include <memory>

class Order;
class IdGenerator;
class TimeStamp;
class Timer;
class TradeInfo;



class Entity {
public:

    Entity(const Symbol& name, 
                const Timer& timer,
                IdGenerator& generator,
                Price initCapital);


                
    virtual ~Entity() = default;

    std::expected<OrderId, OrderError> GetOrderInfo(const OrderId& ID) const;
    std::expected<OrderId, OrderError> GetTradeInfo(const OrderId& ID) const;
    void LogTrade(const TimeStamp& ts, const OrderId& ID);
    void LogOrder(const TimeStamp& ts, const OrderId& ID);
    inline Price GetPnL() const {return m_InitCapital - m_RemainingCapital;}

protected:

    Symbol m_Name;

    const Timer& m_Timer;
    IdGenerator& m_IdGenerator;

    Price m_InitCapital;
    Price m_RemainingCapital;

    std::multimap<OrderId, TimeStamp, std::greater<OrderId>> m_TradeLog;
    std::multimap<OrderId, TimeStamp, std::greater<OrderId>> m_OrderLog;

    
};