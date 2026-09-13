#pragma once


#include "Aliases/Aliases.h"
#include <map>
#include <expected>
#include <stdexcept>
#include <memory>

class IdGenerator;
class TimeStamp;
class Timer;
class TradeInfo;

class Entity {
public:

    Entity(const Symbol& name
        , Price initCapital
        , std::shared_ptr<const Timer> timer
        , IdGenerator& generator);

    std::expected<Order, std::invalid_argument> GetOrderInfo(const OrderId& OrderID) const;
    std::expected<TradeInfo, std::invalid_argument> GetTradeInfo(const OrderId& OrderID) const;
    void LogTrade(const TimeStamp& ts, const OrderId& ID);
    void LogOrder(const TimeStamp& ts, const OrderId& ID);

    


    Price GetPnL() const {return m_InitCapital - m_RemainingCapital;}

protected:


    // OUTSIDE DEPENDICIES
    std::shared_ptr<const Timer> m_SharedTimer;
    std::shared_ptr<IdGenerator> m_SharedIdGenerator;

    //INSIDE MEMBER VARs
    Symbol m_Name;
    std::unique_ptr<std::multimap<TimeStamp, OrderId, std::greater<OrderId>>> m_TradeLog;
    std::unique_ptr<std::multimap<TimeStamp, OrderId, std::greater<OrderId>>> m_OrderLog;
    std::shared_ptr<IdGenerator> m_IdGenerator;
    Price m_InitCapital;
    Price m_RemainingCapital;

    
};