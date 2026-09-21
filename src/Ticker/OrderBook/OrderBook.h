#pragma once


#include "../../Aliases/Aliases.h"

#include <map>
#include <unordered_map>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <atomic>
#include <list>
#include <vector>


class Order;
class OrderBookLevelInfos;
class Trade;
class OrderModify;
class Constant;
enum class Side;

using OrderIds = std::vector<OrderId>;
using Trades = std::vector<Trade>;
using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;

 
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

    //ACTION FUNCTIONS
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
