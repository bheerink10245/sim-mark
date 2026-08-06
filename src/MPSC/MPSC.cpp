#include "MPSC.h"



MPSC::MPSC() 
    : Stub{new OrderNode()}, 
    HeadNode(Stub.get()), 
    TailNode(Stub.get()) 
{

    Stub->NextNode.store(nullptr);

}

MPSC::~MPSC(){

    
}

void MPSC::push(OrderPointer Order){
    OrderNode Ordernode = OrderNode(Order);
    Ordernode->NextNode.store(nullptr, std::memory_order_relaxed);
    Ordernode* prev = TailNode.exchange(Ordernode, std::memory_order_acq_rel);
    prev->NextNode.store(Ordernode, std::memory_order_release);

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




