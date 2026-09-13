


#include <memory>


class Order;
enum class Side;

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;
using OrderPointer = std::shared_ptr<Order>;


class OrderModify {
private:

    OrderId orderId;
    Side orderSide;
    Price orderPrice;
    Quantity orderQuantity;

public:

    OrderModify(OrderId orderId, Side side, Price price, Quantity quantity);

    OrderPointer ToOrderPointer(Order order);

    OrderId GetOrderId() const;
    Side GetOrderSide() const;
    Price GetOrderPrice() const; 
    Quantity GetOrderQuantity() const;

    
};