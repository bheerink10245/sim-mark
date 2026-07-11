#include <atomic>
#include <memory>
#include "Aliases.cpp"

using Order = Aliases::Order;


// Vyukov Queue
struct Node {
    std::atomic<Node*> next;
    Order value;


};

class MPSC{

public:
    MPSC() : stub(new Node()), head(stub.get()), tail(stub.get()) {

        stub->next.store(nullptr)

    }
    void push(Node* node)
    {
        node->next.store(nullptr, memory_order_relaxed);
        Node* prev = tail.exchange(node, memory_order_acq_rel);
        prev->next.store(node, memory_order_release);

    }

    Node* pop()
    {
        Node* head_copy = head.load(memory_order_relaxed);
        Node* next = head_copy->next.load(memory_order_accquire);

        if(next != nullptr){
            head.store(next, memory_order_accquire);
            head_copy-> value = next_value->value;
            return head_copy;

        }
        return null_ptr;

    }

private:
    std::unique_ptr<Node> stub;
    std::atomic<Node*> head;
    std::atomic<Node*> tail;


};