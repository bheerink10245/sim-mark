#pragma once 

#include <iostream>
#include <string>
#include <list>
#include <limits>
#include <memory>
#include <vector>
#include <format>
#include <stdexcept>

//  using Price = Aliases::Price;
//  using Quantity = Aliases::Quantity;
//  using OrderId = Aliases::OrderId;
//  using Symbol = Aliases::Symbol;
//  using Constants = Aliases::Constants;
//  using LevelInfo = Aliases::LevelInfo;
//  using LevelInfos = Aliases::LevelInfos;
//  using OrderBookLevelInfos = Aliases::OrderBookLevelInfos;
//  using Side =  Aliases::Side;
//  using OrderType = Aliases::OrderType;
//  using Order = Aliases::Order;
//  using OrderPointer = Aliases::OrderPointer;
//  using OrderPointers =  Aliases::OrderPointers;
//  using OrderIds = Aliases::OrderIds;
//  using OrderModify = Aliases::OrderModify; 
//  using TradeInfo = Aliases::TradeInfo;
//  using Trade = Aliases::Trade;
//  using Trades = Aliases::Trades;
//  using Signal = Aliases::Signal  



namespace Aliases {
    

    using Price = std::int32_t;
    using Quantity = std::uint32_t;
    using OrderId = std::uint64_t;
    using Symbol = std::string;
    
    struct Constants {
        static const Price InvalidPrice = std::numeric_limits<Price>::quiet_NaN();
    };

    struct LevelInfo
    {
        Price m_Price;
        Quantity m_Quantity;
    };

    using LevelInfos = std::vector<LevelInfo>;

    class OrderBookLevelInfos{
    public:
        OrderBookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
        : m_bids{bids}
        , m_asks{asks}
        {}

        const LevelInfos& GetBids() const {return m_bids;}
        const LevelInfos& GetAsks() const {return m_asks;}

    private:
        LevelInfos m_bids;
        LevelInfos m_asks;

    };

    enum class Side
    {
        Buy,
        Sell

    };

    enum class OrderType
    {
        FillAndKill,
        FillOrKill,
        GoodTillCancel,
        GoodForDay,
        Market

    };

    class Order
    {
    public:
        Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
            : m_OrderType{ orderType }
            , m_OrderId{ orderId }
            , m_Side{ side }
            , m_Price{ price }
            , m_initialQuantity{ quantity }
            , m_RemainingQuantity{ quantity }
        { }

        Order(OrderId orderId, Side side, Quantity quantity)
            : Order(OrderType::Market, orderId, side, Constants::InvalidPrice, quantity)
        { }

        OrderId GetOrderId() const { return m_OrderId; }
        Side GetSide() const { return m_Side; }
        Price GetPrice() const { return m_Price; }
        OrderType GetOrderType() const { return m_OrderType; }
        Quantity GetInitialQuantity() const { return m_initialQuantity; }
        Quantity GetRemainingQuantity() const { return m_RemainingQuantity; }
        Quantity GetFilledQuantity() const { return GetInitialQuantity() - GetRemainingQuantity(); }
        bool IsFilled() const { return GetRemainingQuantity() == 0; }
        void Fill(Quantity quantity)
        {
            if (quantity > GetRemainingQuantity())
                throw std::logic_error("Order ({}) cannot be filled for more than its remaining quantity.", GetOrderId()));

            m_RemainingQuantity -= quantity;
        }
        void ToGoodTillCancel(Price price) 
        { 
            if (GetOrderType() != OrderType::Market)
                throw std::logic_error("Order ({}) cannot have its price adjusted, only market orders can.", GetOrderId());

            m_Price = price;
            m_OrderType = OrderType::GoodTillCancel;
        }

    private:
        OrderType m_OrderType;
        OrderId m_OrderId;
        Side m_Side;
        Price m_Price;
        Quantity m_initialQuantity;
        Quantity m_RemainingQuantity;
    };

    using OrderPointer = std::shared_ptr<Order>;
    using OrderPointers = std::list<OrderPointer>;
    using OrderIds = std::vector<OrderId>;
    
    class OrderModify {
    private:
        OrderId orderId;
        Side orderSide;
        Price orderPrice;
        Quantity orderQuantity;

    public:
        OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
            :    orderId{orderId}
            ,    orderSide{side}
            ,    orderPrice{price}
            ,    orderQuantity{quantity}
        {}

        OrderPointer ToOrderPointer(Order order) {
            return std::make_shared<Order>(orderId, orderSide,orderQuantity);
        }

        OrderId GetOrderId() const {return orderId;}
        Side GetOrderSide() const {return orderSide;}
        Price GetOrderPrice() const {return orderPrice;}
        Quantity GetOrderQuantity() const {return orderQuantity;}

        
    };
    
    struct TradeInfo {

        OrderId m_OrderId;
        Price m_Price;
        Quantity m_Quantity;
    };

    class Trade {

    public:
        Trade (const TradeInfo& bidTrade, const TradeInfo& askTrade)
        : m_bidTrade{bidTrade}
        , m_askTrade{askTrade}
        {}

        const TradeInfo& GetBidTrade() const {return m_bidTrade;}
        const TradeInfo& GetAskTrade() const {return m_askTrade;}
    private:
        TradeInfo m_bidTrade;
        TradeInfo m_askTrade;
    
    };

    using Trades = std::vector<Trade>;

    class Signal {
    private:
        bool m_Valid;
        Side m_SignalSide;    
        Price m_SignalPrice;


    public:

        Signal(bool validity, Side orderside, Price sigprice)
        : m_Valid{validity}
        , m_SignalSide{orderside}
        , m_SignalPrice{sigprice} {}

        bool GetSignalValidity() const {return m_Valid;}
        Side GetSignalSide() const {return m_SignalSide;}
        Price GetSignaPrice() const {return m_SignalPrice;}



    };

}
