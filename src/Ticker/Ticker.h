#pragma once

#include "Aliases.h"
#include "OrderBook/OrderBook.h"
#include "MPSC.h"
#include "TickerData.h"
#include "Timer.h"


#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <unordered_map>
#include <map>
#include <expected>



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


class Ticker{
public:

    Ticker(const Symbol& name);
    Ticker(const Ticker&) = delete;
    void operator=(const Ticker&) = delete;
    Ticker(const Ticker&&) = delete;
    void operator=(const Ticker&&) = delete;
    ~Ticker();
   
    Price GetTickerPrice() const ;
    Quantity GetTickerQuantity() const;
    Quantity GetTickerVolume() const ;
    
    void PerformPerCLK();
    void PerformOrderMatch(const OrderPointer& order, OrderBook& OrderBook);

    void LogTrade(const OrderId& OrderID, const TradeInfo& Info);
    void LogOrder(const OrderId& OrderID, const Order& Info);
    TradeInfo GetTradeInfo(const TimeStamp& OrderID) const;
    Order GetOrderInfo(const TimeStamp& OrderID) const;


private:

    Symbol m_Name;
    std::unique_ptr<OrderBook> m_OrderBookPtr;
    std::shared_ptr<MPSC> m_TickerQueuePtr;
    std::unique_ptr<TickerData> m_DataPtr;
    std::map<TimeStamp, OrderId, std::greater<TimeStamp>> TradeLog;
    std::map<TimeStamp, OrderId, std::greater<TimeStamp>> OrderLog;
};