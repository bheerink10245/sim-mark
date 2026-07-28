#pragma once 


#include <iostream>
#include <string>
#include <list>
#include <memory>

namespace Aliases {
    
    using Price = std::int32_t;
    using Quantity = std::uint32_t;
    using OrderId = std::uint64_t;
    using Symbol = std::string;
    
    enum class Side
    {
        Buy,
        Sell

    };

    enum class OrderType
    {
        FillAndKill,
        GoodTillCancel
    };

    class Order {
    private:
        OrderId orderId;
        OrderType orderType;
        Side orderSide;
        Price orderPrice;
        Quantity initialQuantity;
        Quantity remainingQuantity;
        uint64_t placedTimestamp;

    public:
        Order(OrderId orderId, OrderType orderType,Side side, Price price, Quantity quantity, uint64_t timestamp)
            : orderType {orderType}
            , orderId {orderId}
            , orderSide {side}
            , orderPrice {price}
            , initialQuantity {quantity}
            , remainingQuantity {quantity}
            , placedTimestamp {timestamp}
        {}

        OrderId GetOrderId() const {return orderId;}
        OrderType GetOrderType() const {return orderType;}
        Side GetOrderSide() const {return orderSide;}
        Price GetOrderPrice() const {return orderPrice;}         
        Quantity GetInitialQuantity() const {return initialQuantity;}
        Quantity GetRemainingQuantity() const {return remainingQuantity;}
        uint64_t GetPlaceTimeStamp() const {return placedTimestamp;}
        Quantity GetFilledQuantity() const {return GetInitialQuantity() - GetRemainingQuantity();}
        bool IsFilled() const {return GetFilledQuantity == 0;}

    };

    using OrderPointer = std::shared_ptr<Order>;
    using OrderPointers = std::list<OrderPointer>;
    
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
            return std::make_shared<Order>(order, orderId, orderSide, orderPrice, orderQuantity);
        }

        OrderId GetOrderId() const {return orderId;}
        Side GetOrderSide() const {return orderSide;}
        Price GetOrderPrice() const {return orderPrice;}
        Quantity GetOrderQuantity() const {return orderQuantity;}

        
    };

    class Trade {
    private:
        OrderId tradeId;
        Price executedPrice;
        Quantity filledQuantity;
        uint64_t filledTimestamp;
    public:
        Trade(OrderId tradeId, Price executedprice, Quantity filledquantity, uint64_t filledtimestamp)
            : tradeId { tradeId }
            , executedPrice{ executedprice }
            , filledQuantity{ filledquantity }
            , filledTimestamp{ filledtimestamp }
        {}
        
        OrderId GetOrderId() const {return tradeId;}
        Price GetExecutedPrice() const {return executedPrice;}
        Quantity GetFilledQuantity() const {return filledQuantity;}
        uint64_t GetFilledTimeStamp() const {return filledTimestamp;}

        

    };

    class Signal {
    private:
        bool m_Valid;
        Side m_SignalSide;    
        Price m_SignalPrice;


    public:

        Signal(bool validity, Side orderside, Price sigprice)
        : m_Valid{validity}
        , m_SignalSide{orderside}
        , m_SignalPrice{sigprice}

        bool GetSignalValidity() const {return m_Valid;}
        Side GetSignalSide() const {return m_SignalSide;}
        Price GetSignaPrice() const {return m_SignalPrice;}



    };

}
