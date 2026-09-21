#pragma once

#include "../Aliases/Aliases.h"
#include "../Aliases/Order.h"

#include <atomic>
#include <memory>

class Order;
using OrderPointer = std::shared_ptr<Order>;


struct OrderNode{
    OrderNode() = default;
    OrderNode(const OrderPointer& Order) : NodeValue{Order} {}
    std::atomic<OrderNode*> NextNode{nullptr};
    OrderPointer NodeValue;
};


class MPSC{
public:
    MPSC();
    MPSC(const MPSC&) = delete;
    void operator=(const MPSC&) = delete;
    MPSC(MPSC&&) = delete;
    void operator=(MPSC&&) = delete;
    ~MPSC();

    void push(OrderPointer Order);
    OrderPointer pop();

private:
    std::unique_ptr<OrderNode> Stub;
    std::atomic<OrderNode*> HeadNode;
    std::atomic<OrderNode*> TailNode;

};