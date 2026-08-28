
#pragma once
 
#include "Aliases.h"
#include "OrderBook/OrderBook.h"
#include "MPSC/MPSC.h"
#include "TickerData.h"
#include "System/Time/Timer.h"
#include "Entity.h"
 
 
 
#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <unordered_map>
#include <map>
#include <expected>
#include <stdexcept>
#include <functional>
 
 
 
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
 
 
class Ticker{
public:
 
    Ticker(const Symbol& name);
    Ticker(const Ticker&) = delete;
    Ticker& operator=(const Ticker&) = delete;
    Ticker(Ticker&&) = delete;
    Ticker& operator=(Ticker&&) = delete;
    ~Ticker();
 
   // All Self Exlplanatory APIs
    const Symbol& GetName() const;
    Price GetTickerPrice() const ;
    Quantity GetTickerQuantity() const;
    Quantity GetTickerVolume() const ;
    
    /**
    * @purpose: This is what the object will peform each exhcange iteration
    */
    void PerformPerCLK();
    /**
     * @purpose:
     * @param: Order thats being processed
     * @param: Orderbook of the ticker. It is a derefrecned pointer of the tickers Orderbook
     * @returns: Result of the order processing
     */
    void PerformOrderMatch(const OrderPointer& order, OrderBook& OrderBook);
    /**
     * @purpose: Log a Trade action of ticker.
     * @param timeS: is a TimeStamp obj created by running Timer.SnapShot() , returns a TimeStamp value.
     * @param OrderId: is the ID of the  TRADE thats getting logged
     */
    void LogTrade(const TimeStamp& timeS, const OrderId& OrderID);
    /** 
     * @purpose: Log an ORDER action of ticker.
     * @param timeS: is a TimeStamp obj created by running Timer.SnapShot() , returns a TimeStamp value.
     * @param OrderId: is the ID of the ORDER thats getting logged
     */
    void LogOrder(const TimeStamp& timeS, const OrderId& OrderID);
    /**
     * @purpose: Get information on a Trade that was processed on ticker
     * @param: ID of Trade attempting to find
     * @returns: Either TradeInfo if OrderID value existed within TradeLog, returns invalid arguement if not.
     */
    std::expected<TradeInfo, std::invalid_argument> GetTradeInfo(const OrderId& OrderID) const;
    /**
     * @purpose: Get information on an Order that was processed on ticker
     * @param: ID of Order attempting to find
     * @returns: Either Order if OrderID value existed within TradeLog, returns invalid arguement if not.
     */
    std::expected<Order, std::invalid_argument> GetOrderInfo(const OrderId& OrderID) const;
    // Self Explanatory
    bool operator==(const Ticker& other) const;
 
private:
 
    Symbol m_Name;
    std::unique_ptr<OrderBook> m_OrderBookPtr;
    std::shared_ptr<MPSC> m_TickerQueuePtr;
    std::unique_ptr<TickerData> m_DataPtr;
    std::map<TimeStamp, OrderId, std::greater<TimeStamp>> TradeLog;
    std::map<TimeStamp, OrderId, std::greater<TimeStamp>> OrderLog;
};
 

struct TickerHash {
    using is_transparent = void;
 
    size_t operator()(const Ticker& t) const noexcept {
        return std::hash<Symbol>{}(t.GetName());
    }
    size_t operator()(const Symbol& s) const noexcept {
        return std::hash<Symbol>{}(s);
    }
};
 
struct TickerEqual {
    using is_transparent = void;
 
    bool operator()(const Ticker& a, const Ticker& b) const {
        return a.GetName() == b.GetName();
    }
    bool operator()(const Ticker& a, const Symbol& b) const {
        return a.GetName() == b;
    }
    bool operator()(const Symbol& a, const Ticker& b) const {
        return a == b.GetName();
    }
};