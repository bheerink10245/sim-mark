#pragma once

#include "Aliases.h"

#include <list>
#include <memory>
#include <cstdint>

enum class Side;
enum class OrderType;
enum class ActionFunction;


class Order
{

public:

    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity, ActionFunction action);
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity);
    Order(OrderId orderId, Side side, Quantity quantity);

    OrderId GetOrderId() const;
    Side GetOrderSide() const;
    Price GetOrderPrice() const; 
    OrderType GetOrderType() const; 
    Quantity GetInitialQuantity() const; 
    Quantity GetRemainingQuantity() const; 
    ActionFunction GetOrderAction() const; 
    Quantity GetFilledQuantity() const; 
    bool IsFilled() const; 


    void Fill(Quantity quantity);

    void ToGoodTillCancel(Price price);

private:

    OrderType m_OrderType;
    OrderId m_OrderId;
    Side m_Side;
    Price m_Price;
    Quantity m_initialQuantity;
    Quantity m_RemainingQuantity;
    ActionFunction m_Action;
};

using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;