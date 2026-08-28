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
    MPSC(MPSC&) = delete;
    void operator=(MPSC&) = delete;
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