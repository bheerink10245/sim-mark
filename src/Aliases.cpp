#pragma once 


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
        FillorKill,
        GoodTillCancel
    };

    struct Order {

        OrderId orderID;
        OrderType orderType;
        Side orderSide;
        Price orderPrice;
        Quantity initialQuantity;
        Quantity remainingQuantity;
        uint64_t placedTimestamp;


        Order(OrderId orderID, OrderType orderType,Side side, Price pice, Quantity quantity, uint64_t timestamp)
            : orderType {orderType}
            , orderID {orderID}
            , orderSide {side}
            , orderPrice {price}
            , initialQuantity {quantity}
            , remainingQuantity {quantity}
            , placedTimestamp {timestamp}
        {}

        
        Quantity GetFilledQuantity() const {return InitialQuantity - RemainingQuantity() ;}
        bool IsFilled() const {return GetFilledQuantity == 0;}
    };

    using OrderPointer = std::shared_ptr<Order>;
    using OrderPointers = std::list<OrderPointer>;
    
    struct OrderModify {

        OrderId orderID;
        Side orderSide;
        Price orderPrice;
        Quantity orderQuantity;


        OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
            :    orderID{orderId}
            ,    orderSide{side}
            ,    orderPrice{price}
            ,    orderQuantity{quantity}
        {}

        OrderPointer ToOrderPointer(Order order) {
            return std::make_shared<Order>(order, orderID, orderSide, orderPrice, orderQuantity);
        }
        
    };

    struct Trade {

        OrderId tradeID;
        Price executedPrice;
        Quantity filledQuantity;
        uint64_t filledTimestamp;

        Trade(OrderId tradeID, Price executedprice, Quantity filledquantity, uint64_t filledtimestamp)
            : tradeId{ tradeId }
            , executedPrice{ executedPrice }
            , filledQuantity{ filledquantity }
            , filledTimestamp{ filledtimestamp }
        {
        }

    };

}
