

#include "Entity.h"

#include "../Aliases/Trade.h"
#include "../Aliases/Order.h"
#include "../System/Time/Timer.h"
#include "../System/Time/TimeStamp.h"
#include "../Maker/Maker.h"
#include "../Player/Player.h"
#include "../Ticker/Ticker.h"
#include "../System/Exchange/ExchangeData.h"
#include "../System/IdGenerator/IdGenerator.h"




Entity::Entity(const Symbol& name, 
                const Timer& timer,
                IdGenerator& generator,
                Price initCapital)
                 
    : m_Name{name}
    , m_Timer{timer}
    , m_IdGenerator{generator}
    , m_InitCapital{initCapital}
    , m_RemainingCapital{initCapital}
    , m_TradeLog{}
    , m_OrderLog{}
{ }

void Entity::LogTrade(const TimeStamp& ts,const OrderId& ID){
    m_TradeLog.insert({ID , ts});
}

void Entity::LogOrder(const TimeStamp& ts, const OrderId& ID){
    m_OrderLog.insert({ID , ts});
}

std::expected<OrderId, OrderError> Entity::GetOrderInfo(const OrderId& ID) const {
    auto keyValue = m_OrderLog.find(ID);
    if(keyValue != m_OrderLog.end()){
        return keyValue->first;
    }
    return std::unexpected(OrderError::NotFound);
}

std::expected<OrderId, OrderError> Entity::GetTradeInfo(const OrderId& ID) const {
    auto keyValue = m_TradeLog.find(ID);
    if (keyValue != m_TradeLog.end()){
        return keyValue->first;
    }

    return std::unexpected(OrderError::NotFound);
}

