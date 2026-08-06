#include "Aliases.h"

#include <atomic>
#include <memory>

using Order = Aliases::Order;
using OrderPointer = Aliases::OrderPointer;

struct OrderNode{
    OrderNode(const OrderPointer& Order) : NodeValue{Order} {}
    std::atomic<OrderNode*> NextNode;
    OrderPointer NodeValue;
};

//Vyukov Queue

class MPSC{
public:
    MPSC();
    MPSC(const MPSC&) = delete;
    void operator=(const MPSC&) = delete;
    MPSC(const MPSC&&) = delete;
    void operator=(const MPSC&&) = delete;
    ~MPSC();

    void push(OrderPointer Order);
    OrderPointer pop();

private:
    std::unique_ptr<OrderNode> Stub;
    std::atomic<OrderNode*> HeadNode;
    std::atomic<OrderNode*> TailNode;

};