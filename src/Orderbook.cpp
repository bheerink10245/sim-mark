#include <iostream>
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <stack>
#include <limits>
#include <string>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <optional>
#include <format>
#include "Aliases.cpp"

namespace OrderBook { 

    using Price = Aliases::Price;
    using Side = Aliases::Side;
    using OrderId = Aliases::OrderId;
    using OrderType = Aliases::OrderType;
    using Order = Aliases::Order;
    using OrderPointer = Aliases::OrderPointer;
    using OrderPointers = Aliases::OrderPointers;
    using OrderModify = Aliases::OrderModify;
    using Trade = Aliases::Trade;


    using Trades = std::vector<Trade>;

    struct OrderBook
    {
        struct OrderEntry
        {
            OrderPointer order_(nullptr);
            OrderPointers::iterator location;

        };

        std::map<Price,OrderPointers, std::greater<Price>> m_BidsMap;
        std::map<Price,OrderPointers, std::less<Price>> m_AsksMap;
        std::unordered_map<OrderId,OrderEntry> m_OrdersMap;


        Trades AddOrder(OrderPointer order){
            if(m_OrdersMap.contains(order->GetOrderId())){
                return {};
            }
            if(order->GetOrderType() == OrderType::FillAndKill && !CanMatch(order))
                return{};
            OrderPointers::iterator iterator;


            //FIx 
            if (order->GetOrderSide() == Side::Buy){
                auto& orders = m_AsksMap[order->GetOrderPrice()];
                orders.push_back(order);
                iterator = std::next(order.begin(),orders.size() - 1);
            
                
            }

            m_OrdersMap.insert({order->GetOrderId(), OrderEntry(){order_, iterator}});
            return MatchOrder();

        }
        
        void CancelOrder(OrderId orderId) {
            if(!m_OrdersMap.contains(orderId))
                return;
            const auto& [order, orderIterator] = m_OrdersMap.at(orderId);
            m_OrdersMap.erase(orderId);

            if(orders->GetOrderSide() == Side::Sell){
                auto price = order->GetOrderPrice();
                auto price = order->GetOrderPrice();
                auto& orders = m_AsksMap.at(price);
                orders.erase(orderIterator);
                if ( orders.empty())
                    m_AsksMap.erase(price);
            }
            else
            {
                auto price = order->GetOrderPrice();
                auto& orders = m_BidsMap.at(price);
                orders.erase(iterator);
                if(orders.empty())
                    m_BidsMap.erase(price);
            }
        }

        Trades MatchOrder(OrderModify order){
        
            if(!m_OrdersMap.contains(order.GetOrderId())){
                return  {};
            }
            const auto& [existingOrder , _] = m_OrdersMap.at(order.GetOrderId());
            CancelOrder(order.GetOrderId());
            return AddOrder(order.ToOrderPointer(existingOrder->GetOrderType()));


        }

        size_t Size() const {return m_OrdersMap.size();}

        OrderBookLevelInfos GetOrderInfos() const
        {
            LevelInfos bidInfos,asksInfos;
            bidInfos.reserve(ORDERS.size());
            asksInfos.reserve(order_.size());
            auto CreateLevelInfos = [](Price price, const OrderPointers& const){ // mess
                return LevelInfo{price, std::accumulate(orders.begin(), orders.end(), (Quantity)0, )
                    [](size_t runningSum, constOrderPointers& order)
                    {return runningSum + order->GetRemainingQuantity(); } };

            };
            for(const auto& [price,orders] : m_BidsMap)
                bidInfos.push_back(CreateLevelInfos(price orders));
            for(const auto& [price, odrders] : m_AsksMap)
                asksInfos.push_back(CreateLevelInfos(price,orders));
            return OrderBookLevelInfos{bidInfos, asksInfos};
        }



    };

    
    
}
int main()
{
    OrderBook::OrderBook OrderBook;
    const int OrderId = 1;
    OrderBook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel,orderId, Side::Buy, 100, 10));
    std::cout<< OrderBook.Size() << std::endl; // 1
    OrderBook.CancelOrder(orderId);
    std::cout << OrderBook.Size() << std::endl; // 0
    return 0;
}

 
