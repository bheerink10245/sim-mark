

#include "Aliases.h"
#include "OrderModify.h"
#include "Order.h"



OrderModify::OrderModify(OrderId orderId, Side side, Price price, Quantity quantity)
    :    orderId{orderId}
    ,    orderSide{side}
    ,    orderPrice{price}
    ,    orderQuantity{quantity}
{ }

OrderPointer OrderModify::ToOrderPointer(OrderType type) {
    return std::make_shared<Order>(type, GetOrderId(), GetOrderSide(), GetOrderPrice() , GetOrderQuantity() );
}

OrderId OrderModify::GetOrderId() const {return orderId;}
Side OrderModify::GetOrderSide() const {return orderSide;}
Price OrderModify::GetOrderPrice() const {return orderPrice;}
Quantity OrderModify::GetOrderQuantity() const {return orderQuantity;}
