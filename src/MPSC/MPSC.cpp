


#include "MPSC.h"

#include "../Aliases/Order.h"

MPSC::MPSC() 
    : Stub{new OrderNode()}, 
    HeadNode(Stub.get()), 
    TailNode(Stub.get()) 
{

    Stub->NextNode.store(nullptr);

}

MPSC::~MPSC(){

    return;
}

void MPSC::push(OrderPointer Order){
    OrderNode* order_node = new OrderNode(Order);
    order_node->NextNode.store(nullptr, std::memory_order_relaxed);
    OrderNode* prev = TailNode.exchange(order_node, std::memory_order_acq_rel);
    prev->NextNode.store(order_node, std::memory_order_release);

}

OrderPointer MPSC::pop(){

    OrderNode* HeadCopy = HeadNode.load(std::memory_order_relaxed);
    OrderNode* next = HeadCopy->NextNode.load(std::memory_order_acquire);

    if(next != nullptr){
        HeadNode.store(next, std::memory_order_acquire);
        HeadCopy->NodeValue = next->NodeValue;
        return HeadCopy->NodeValue;
    }
    return nullptr;
    
}




