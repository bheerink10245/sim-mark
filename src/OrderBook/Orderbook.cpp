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
#include <variant>
#include <optional>
#include <tuple>
#include <format>
#include "Aliases.cpp"

namespace Orderbook { 




    using Price = Aliases::Price;
    using Quantity = Aliases::Quantity ;
    using OrderId = Aliases::OrderId;
    using Side = Aliases::Side;
    using OrderType = Aliases::OrderType;
    using TradeInfo = Aliases::TradeInfo;
    
    struct LevelInfo
    {
        Price m_price;
        Quantity m_quantity;

    };

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

    class Order
    {
    public:
        Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
        : m_OrderType {orderType}
        , m_OrderId {orderId}
        , m_side {side}
        , m_price {price}
        , m_InitialQuantity {quantity}
        , m_RemainingQuantity {quantity}

        {}

        OrderId GetOrderId() const {return m_OrderId;}
        Side GetSide() const {return m_side;}
        Price GetPrice() const {return m_price;}
        OrderType GetOrderType() const {return m_OrderType;}
        Quantity GetInitialQuantity() const {return m_InitialQuantity;}
        Quantity GetRemainingQuantity() const {return m_RemainingQuantity;}
        Quantity GetFilledQuantity() const {return GetInitialQuantity() - GetRemainingQuantity() ;}
        bool IsFilled() const {return GetFilledQuantity == 0;}

        void Fill(Quantity quantity)
        {
            if (quantity > GetRemainingQuantity())
                throw std::logic_error(std::format("Order ({}) cannot be filled for more that  its remaing quantity", GetOrderId()));
            
            m_RemainingQuantity -= quantity;
            
        }


    private:
        OrderType m_OrderType;
        OrderId m_OrderId;
        Side m_side;
        Price m_price;
        Quantity m_InitialQuantity;
        Quantity m_RemainingQuantity;

        
    };

    using OrderPointer = std::shared_ptr<Order>;
    using OrderPointers = std::list<OrderPointer>;

    class OrderModify
    {
    public:
        OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
        : m_OrderId{orderId}
        , m_price {price}
        , m_side {side}
        , m_quantity {quantity}

        {}
        OrderId GetOrderId() const {return m_OrderId;}
        Price GetPrice() const {return m_price;}
        Side GetSide() const {return m_side;}
        Quantity GetQuantity() const {m_quantity;}
        
        
        //converting given order into a new order

        OrderPointer ToOrderPointer(OrderType orderType) const {
            return std::make_shared<Order>(orderType, GetOrderId(), GetSide(), GetPrice(), GetQuantity());
        }


    private:
        OrderId m_OrderId;
        Price m_price;
        Side m_side;
        Quantity m_quantity;
    };

    class Trade
    {
    public:
        Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade)
        : m_BidTrade{bidTrade}
        , m_AskTrade {askTrade}
        {}

        const TradeInfo& GetBidTrade() const {return m_BidTrade;}
        const TradeInfo& GetAskTrade() const {return m_AskTrade;}


    private:
        TradeInfo m_BidTrade;
        TradeInfo m_AskTrade;

    };

    using Trades = std::vector<Trade>;

    class OrderBook
    {
    private:
        struct OrderEntry
        {
            OrderPointer order_(nullptr);
            OrderPointers::iterator location;

        };

        std::map<Price,OrderPointers, std::greater<Price>> MEM_BIDS;
        std::map<Price,OrderPointers, std::less<Price>> MEM_ASKS;
        std::unordered_map<OrderId,OrderEntry> ORDERS;

        bool CanMatch(Side side, Price price) const
        {
            if (side == Side::Buy)
            {
                if(MEM_ASKS.empty())
                    return false;
                const auto& [bestAsk, _] = *MEM_ASKS.begin();
                return price >= bestAsk;

            }
            else
            {
                if(MEM_BIDS.empty())
                    return false;
                const auto& [bestBid, _] = *MEM_BIDS.begin();    
                    return price <= bestBid;
                
            }
        }



        Trades MatchOrders()
        {
            Trades trades;
            Trade.reserve(ORDERS.size());

            while (true)
            {
                if(MEM_BIDS.empty() || MEM_ASKS.empty())
                {
                    break;
                }
                auto& [bidPrice, bids] = *MEM_BIDS.begin();
                auto& [askPrice, asks] = *MEM_ASKS.begin();
                
                if(bidPrice < askPrice)
                {
                    break;
                }

                while (bids.size() && asks.size())
                {
                    auto& bid = bids.front();
                    auto& ask = asks.front();

                    Quantity quantity = std::min(bid->GetRemainingQuantity, ask->GetRemainingQuantity());
                    
                    bid->Fill(quantity);
                    ask->Fill(quantity);

                    if(bid->IsFilled())
                    {
                        bids.pop_front();
                        ORDERS.erase(bid->GetOrderId());

                    }
                    if(ask->IsFilled())
                    {
                        asks.pop_front();
                        ORDERS.erase(ask->GetOrderId);
                    }
                    if(bids.empty())
                    {
                        MEM_BIDS.erase(bidPrice);

                    }
                    if (bids.empty())
                    {
                        MEM_ASKS.erase(askPrice);
                    }

                    trades.push_back(Trade{
                        TradeInfo{bid->GetOrderId(), bid->GetPrice(), quantity},
                        TradeInfo{ask->GetOrderId(), ask->GetPrice(), quantity}
                    });
                }
            
            if(!MEM_BIDS.empty()){
                auto& [_,bids] = *MEM_BIDS.begin();
                auto& order = bids.front();
                if(order->GetOrderType() == OrderType::FillAndKill){
                    CancelOrder(order->GetOrderId());
                
                }
                if(!.empty()){
                    auto& [_,asks] = *asks.begin();
                    auto& order = asks,front();
                    if(order->GetOrderType() == OrderType::FillAndKill)
                        CancelOrder(order->GetOrderId());
                    
                }
            }
            return trades;
        }

    public: 
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

    
    
    
    
    int main()
    {
        Orderbook orderbook;
        const OrderId = 1;
        orderbook.AddOrder(std::make_shared<Order>(OrderType::GoodTillCancel,orderId, Side::Buy, 100, 10));
        std::cout<< orderBook.Size() << std::endl; // 1
        orderBook.CancelOrder(orderId);
        std::count << orderbook.Size() << std::endl; // 0
        return 0;
    }

}