#pragma once

#include "Aliases.h"
#include "System/Time/Timer.h"
#include "System/Exchange/ExchangeData.h"
#include "System/Exchange/Exchange.h"
#include "Ticker/Ticker.h"
#include "System/IdGenerator/IdGenerator.h"

#include <map>


using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Constants = Aliases::Constants;
using LevelInfo = Aliases::LevelInfo;
using LevelInfos = Aliases::LevelInfos;
using OrderBookLevelInfos = Aliases::OrderBookLevelInfos;
using Side =  Aliases::Side;
using OrderType = Aliases::OrderType;
using Order = Aliases::Order;
using OrderPointer = Aliases::OrderPointer;
using OrderPointers =  Aliases::OrderPointers;
using OrderIds = Aliases::OrderIds;
using OrderModify = Aliases::OrderModify; 
using TradeInfo = Aliases::TradeInfo;
using Trade = Aliases::Trade;
using Trades = Aliases::Trades;
using ActionFunction = Aliases::ActionFunction;


class Entity {
public:

    Entity(const Symbol& name, Price initCapital, IdGenerator id_generator);

    std::expected<Order, std::invalid_argument> GetOrderInfo(const OrderId& OrderID) const;
    std::expected<TradeInfo, std::invalid_argument> GetTradeInfo(const OrderId& OrderID) const;
    void LogTrade(const TimeStamp& ts, const OrderId& ID);
    void LogOrder(const TimeStamp& ts, const OrderId& ID);

    


    Price GetPnL() const {return m_InitCapital - m_RemainingCapital;}

protected:

    Symbol m_Name;
    std::unique_ptr<std::multimap<TimeStamp, OrderId, std::greater<OrderId>>> m_TradeLog;
    std::unique_ptr<std::multimap<TimeStamp, OrderId, std::greater<OrderId>>> m_OrderLog;
    std::shared_ptr<IdGenerator> m_IdGenerator;
    Price m_InitCapital;
    Price m_RemainingCapital;

    
};