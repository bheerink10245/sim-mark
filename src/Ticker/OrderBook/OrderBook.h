#pragma once

#include <map>
#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>

#include "Aliases.h"


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

 
class OrderBook{
private:

    struct OrderEntry
    {
        OrderPointer orderPtr {nullptr};
        OrderPointers::iterator orderLocation;

    };

    struct LevelData
    {
        Quantity m_quantity{};
        Quantity m_count{};

        enum class Action{
            Add,
            Remove,
            Match
        };

    };

    std::unordered_map<Price,LevelData> dataMap;
    std::map<Price, OrderPointers, std::greater<Price>> bidsMap;
    std::map<Price, OrderPointers, std::less<Price>> asksMap;
    std::unordered_map<OrderId, OrderEntry> ordersMap;

    mutable std::mutex ordersMutex;
    std::thread ordersPruneThread;
    std::condition_variable shutdownCondtionVariables;
    std::atomic<bool> shutdownVariable{false};

    void PruneGoodForDayOrders();

    void CancelOrder(OrderIds orderIds);
    void CancelOrderInternal(OrderId orderId);

    void OnOrderCancelled(OrderPointer order);
    void OnOrderAdded(OrderPointer order);
    void OnOrderMatched(Price price, Quantity quantity, bool isFullyFilled);
    void UpdateLevelData(Price price, Quantity quantity, LevelData::Action action);

    bool CanFullyFill(Side side, Price price, Quantity quantity) const;
    bool CanMatch(Side side, Price price) const;
    Trades MatchOrders();

public:

    OrderBook();
    OrderBook(const OrderBook&) = delete;
    void operator=(const OrderBook&) = delete;
    OrderBook(OrderBook&&) = delete;
    void operator=(OrderBook&&) = delete;
    ~OrderBook();

    Trades AddOrder(OrderPointer order);
    void CancelOrder(OrderId orderId);
    Trades ModifyOrder(OrderModify order);

    std::size_t Size() const;
    OrderBookLevelInfos GetOrderInfos() const;

    std::unordered_map<Price,LevelData> GetDataMap() const {return  dataMap;}
    std::map<Price,OrderPointers, std::greater<Price>> GetBidsMap() const {return bidsMap;}
    std::map<Price,OrderPointers, std::less<Price>> GetAsksMap() const {return asksMap;} 
    std::unordered_map<OrderId,OrderEntry> GetOrdersMap() const {return ordersMap;}

};
