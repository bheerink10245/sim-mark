
#pragma once
 
#include "../Aliases/Aliases.h"

 

#include <iostream>
#include <vector>
#include <random>
#include <memory>
#include <unordered_map>
#include <map>
#include <expected>
#include <stdexcept>
#include <functional>
 
 
class Maker;
class MPSC;
class Timer;
class TimeStamp;
class Signal;
class IdGenerator;
class OrderBook;
class TickerData;
class Order;
class OrderModify;
class Trade;
class TradeInfo;
enum class TickerError;
using OrderPointer = std::shared_ptr<Order>;
using ModelFunction = std::function<Signal(const TickerData&)>;

 
class Ticker{
public:
 
    Ticker(const Symbol& name, const Timer& timer, IdGenerator& idGenerator);
    Ticker(const Ticker&) = delete;
    Ticker& operator=(const Ticker&) = delete;
    Ticker(Ticker&&) = delete;
    Ticker& operator=(Ticker&&) = delete;
    ~Ticker();
 
   // All Self Exlplanatory APIs
    Symbol GetName() const;
    Price GetTickerPrice() const ;
    Quantity GetTickerQuantity() const;
    Quantity GetTickerVolume() const ;
    

    void PerformPerCLK();

    OrderStatus PerformOrderMatch(const std::shared_ptr<Order>& order, OrderBook& OrderBook);

    void LogTrade(const OrderId& ID, const TimeStamp& ts);

    void LogOrder(const OrderId& ID, const TimeStamp& ts);

    std::expected<OrderId, TickerError> GetTradeInfo(const OrderId& ID) const;

    std::expected<OrderId, TickerError> GetOrderInfo(const OrderId& ID) const;

    OrderStatus TickerEnqueue(OrderPointer order);
 
private:
 

    Symbol m_Name;

    //OUTSIDE DEPENDICIES
    const Timer& m_Timer;
    IdGenerator& m_IdGenerator;

    //INSIDE MEMBER VARs

    std::unique_ptr<OrderBook> m_OrderBookPtr;
    std::shared_ptr<MPSC> m_TickerQueuePtr;
    std::unique_ptr<TickerData> m_DataPtr;

    static ModelFunction strat1; // DECLARE AHEAD OF TICKER CONSTRUCTION
    static ModelFunction strat2; // DECLARE AHEAD OF TICKER CONSTRUCTION
    
    std::shared_ptr<Maker> m_MakerOne;
    std::shared_ptr<Maker> m_MakerTwo;

    std::map<OrderId, TimeStamp, std::greater<TimeStamp>> m_TradeLog;
    std::map<OrderId, TimeStamp, std::greater<TimeStamp>> m_OrderLog;

};
 

