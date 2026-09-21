

#include <stdexcept>

#include "Order.h"
#include "Contsants.h"
#include "Aliases.h"



Order::Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity, ActionFunction action)
    : m_OrderType{ orderType }
    , m_OrderId{ orderId }
    , m_Side{ side }
    , m_Price{ price }
    , m_initialQuantity{ quantity }
    , m_RemainingQuantity{ quantity }
    , m_Action { action}
{ }

Order::Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity) 
    : Order(orderType, orderId, side, price, quantity, ActionFunction::Default )
{ }

Order::Order(OrderId orderId, Side side, Quantity quantity)
    : Order(OrderType::Market, orderId, side, Constants::InvalidPrice, quantity)
{ }

OrderId Order::GetOrderId() const { return m_OrderId; }
Side Order::GetOrderSide() const { return m_Side; }
Price Order::GetOrderPrice() const { return m_Price; }
OrderType Order::GetOrderType() const { return m_OrderType; }
Quantity Order::GetInitialQuantity() const { return m_initialQuantity; }
Quantity Order::GetRemainingQuantity() const { return m_RemainingQuantity; }
ActionFunction Order::GetOrderAction() const {return m_Action; }
Quantity Order::GetFilledQuantity() const { return GetInitialQuantity() - GetRemainingQuantity(); }
bool Order::IsFilled() const { return GetRemainingQuantity() == 0; }

void Order::Fill(Quantity quantity){
    if (quantity > GetRemainingQuantity())
        throw std::logic_error("Order (" + std::to_string(GetOrderId()) +") cannot be filled for more than its remaining quantity.");

    m_RemainingQuantity -= quantity;
}

void Order::ToGoodTillCancel(Price price) { 
    if (GetOrderType() != OrderType::Market)
        throw std::logic_error("Order (" + std::to_string(GetOrderId()) + ") cannot have its price adjusted, only market orders can."
);
    m_Price = price;
    m_OrderType = OrderType::GoodTillCancel;
}
