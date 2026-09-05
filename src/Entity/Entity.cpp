
#include "Entity.h"

Entity::Entity(const Symbol& name, Price initCapital, IdGenerator id_generator)
    : m_Name{name}
    , m_InitCapital{initCapital}
    , m_RemainingCapital{initCapital}
    , m_TradeLog{std::make_unique<std::map<TimeStamp, OrderId, std::greater<OrderId>>>()}
    , m_OrderLog{std::make_unique<std::map<TimeStamp, OrderId, std::greater<OrderId>>>()}
    , m_IdGenerator{id_generator}

{ }

void Entity::LogTrade(const TimeStamp& timeS,const OrderId& OrderID){
    m_TradeLog->insert({timeS, OrderID});
}

void Entity::LogOrder(const TimeStamp& timeS, const OrderId& OrderID){
    m_OrderLog->insert({timeS, OrderID});
    std::cout << "Ticker: " << this.m_Name << OrderID << " place @ timestamp: " << timeS << std::endl;
}

std::expected<Order, std::invalid_argument> Entity::GetOrderInfo(const OrderId& OrderID) const {
    auto keyValue = m_OrderLog->find(OrderID);
    if(keyValue != m_OrderLog->end()){
        return keyValue->second;
    }
    return std::unexpected(std::invalid_argument("OrderID not found"));
}

std::expected<TradeInfo, std::invalid_argument> Entity::GetTradeInfo(const OrderId& OrderID) const
{
    auto keyValue = m_TradeLog->find(OrderID);
    if (keyValue != m_TradeLog->end()){
        return keyValue->second;
    }

    return std::unexpected(std::invalid_argument("OrderID not found"));
}