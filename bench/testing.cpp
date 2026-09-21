
#include <chrono>
#include <iostream>

#include "../src/MPSC/MPSC.h"
#include "../src/Aliases/Order.h"
#include "../src/Aliases/Aliases.h"


int main() {

    std::unique_ptr<MPSC> ring_buffer = std::make_unique<MPSC>();
    std::shared_ptr<Order> order_1 = std::make_unique<Order>(1, Side::Buy, 10);
    std::shared_ptr<Order> order_2 = std::make_unique<Order>(2, Side::Buy, 20);


    auto start = std::chrono::steady_clock::now();

    //**Single threaded impl */
    ring_buffer->push(order_1); //pushing order_1 on buffer
    ring_buffer->push(order_2); // pushing order_2 on buffer

    auto orderOne = ring_buffer->pop();
    auto orderTwo = ring_buffer->pop();

    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    std::cout << "Elapsed: " << elapsed.count() << std::endl;

    return 0;
}