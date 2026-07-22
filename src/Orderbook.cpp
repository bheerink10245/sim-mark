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



    using LevelInfos = std::vector<LevelInfo>;

    class OrderBookLevelInfos{
    public:
        OrderBookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
            : MEM_BIDS{bids}
            , MEM_ASKS {asks}
        {}

        const LevelInfos& GetBids() const {return MEM_BIDS;}
        const LevelInfos& GetAsks() const {return MEM_ASKS;}
    private:
        LevelInfos MEM_BIDS;
        LevelInfos MEM_ASKS;


    };  


    using Trades = std::vector<Trade>;

    struct OrderBook
    {
        struct OrderEntry
        {
            OrderPointer order_(nullptr);
            OrderPointers::iterator location;

        };

        std::map<Price,OrderPointers, std::greater<Price>> MEM_BIDS;
        std::map<Price,OrderPointers, std::less<Price>> MEM_ASKS;
        std::unordered_map<OrderId,OrderEntry> ORDERS;


        Trades AddOrder(OrderPointer order){
            if(ORDERS.contains(order->GetOrderId())){
                return {};
            }
            if(orders->GetOrderType() == OrderType::FillAndKill && !CanMatch(order->GetSide(), order->GetPrice()))
                return{};
            OrderPointers::iterator iterator;

            if (order->GetSide() == Side::Buy){
                auto& orders = MEM_ASKS[order->GetPrice()];
                orders.push_back(order);
                iterator = std::next(order.begin(),orders.size() - 1);
            
                
            }

            ORDERS.insert({order->GetOrderId(), OrderEntry(){order_, iterator}});
            return MatchOrder();

        }
        void CancelOrder(OrderId orderId) {
            if(!ORDERS.contains(orderId))
                return;
            const auto& [order, orderItertor] = ORDERS.at(orderId);
            ORDERS.erase(orderId);

            if(orders->GetSide() == Side::Sell){
                auto price = order->GetPrice();
                auto price = order->GetPrice();
                auto& orders = MEM_ASKS.at(price);
                orders.erase(orderIterator);
                if ( orders.empty())
                    MEM_ASKS.erase(price);
            }
            else
            {
                auto price = order->GetPrice();
                auto& orders = MEM_BIDS.at(price);
                orders.erase(iterator);
                if(orders.empty())
                    MEM_BIDS.erase(price);
            }
        }

        Trades MatchOrder(OrderModify order){
        
            if(!ORDERS.contains(order.GetOrderId()))
                return  {};
            }
            const auto& [existisingOrder , _] = ORDERS.at(order.GetOrderId());
            CancelOrder(order.GetOrderId());
            return AddOrder(order.ToOrderPointer(existingOrder->GetOrderType()));


        }

        size_t Size() const {return ORDERS.size();}

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
            for(const auto& [price,orders] : MEM_BIDS)
                bidInfos.push_back(CreateLevelInfos(price orders));
            for(const auto& [price, odrders] : MEM_ASKS)
                asksInfos.push_back(CreateLevelInfos(price,orders));
            return OrderBookLevelInfos{bidInfos, asksInfos};
        }



    };

    
    
}
int main()
{
    Orderbook::OrderBook orderbook;
    const OrderId = 1;
    orderbook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel,orderId, Side::Buy, 100, 10));
    std::cout<< orderbook.Size() << std::endl; // 1
    orderBook.CancelOrder(orderId);
    std::cout << orderbook.Size() << std::endl; // 0
    return 0;
}

 
