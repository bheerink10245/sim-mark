#include <atomic>
#include <memory>
#include "Aliases.h"

using Order = Aliases::Order;


// Vyukov Queue


struct OrderNode {
    std::atomic<OrderNode*> next;
    Order value;
};



class MPSC{

public:
    MPSC() 
        : stub{new OrderNode()}, 
        head(stub.get()), 
        tail(stub.get()) {

        stub->next.store(nullptr);

    }

    ~MPSC(){
        
    }
    void push(OrderNode* OrderNode){

        OrderNode->next.store(nullptr, std::memory_order_relaxed);
        OrderNode* prev = tail.exchange(OrderNode, std::memory_order_acq_rel);
        prev->next.store(OrderNode, std::memory_order_release);

    }

    OrderNode* pop(){

        OrderNode* head_copy = head.load(std::memory_order_relaxed);
        OrderNode* next = head_copy->next.load(std::memory_order_accquire);

        if(next != nullptr){
            head.store(next, std::memory_order_accquire);
            head_copy-> value = next_value->value;
            return head_copy;

        }
        return nullptr;

    }

private:
    std::unique_ptr<OrderNode> stub;
    std::atomic<OrderNode*> head;
    std::atomic<OrderNode*> tail;


};
