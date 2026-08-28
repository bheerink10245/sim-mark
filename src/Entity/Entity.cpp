
#include "Entity.h"


void Entity::LogTrade(const TimeStamp& timeS,const OrderId& OrderID){
    TradeLog.insert({timeS, OrderID});
}

void Entity::LogOrder(const TimeStamp& timeS, const OrderId& OrderID){
    OrderLog.insert({timeS, OrderID});
}

std::expected<Order, std::invalid_argument> Entity::GetOrderInfo(const OrderId& OrderID) const {
    auto keyValue = OrderLog.find(OrderID);
    if(keyValue != OrderLog.end()){
        return keyValue->second;
    }
    return std::unexpected(std::invalid_argument("OrderID not found"));
}

std::expected<TradeInfo, std::invalid_argument> Entity::GetTradeInfo(const OrderId& OrderID) const
{
    auto keyValue = TradeLog.find(OrderID);
    if (keyValue != TradeLog.end()){
        return keyValue->second;
    }

    return std::unexpected(std::invalid_argument("OrderID not found"));
}