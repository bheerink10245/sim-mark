#pragma once

#include "Aliases.h"
#include "OrderBook/OrderBook.cpp"
#include "MPSC.cpp"

#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <unordered_map>
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

    Ticker();
    Ticker(const Ticker&) = delete;
    void operator=(const Ticker&) = delete;
    Ticker(const Ticker&&) = delete;
    void operator=(const Ticker&&) = delete;
    ~Ticker();
   
    
    void PerformPerClk();
    void PerformOrderMatch(const OrderPointer& order);

private:
    Symbol m_Name;
    std::unique_ptr<TickerData> m_DataPtr;
    std::unique_ptr<OrderBook::OrderBook> m_OrderBookPtr;
    std::shared_ptr<MPSC> m_TickerQueuePtr;

};