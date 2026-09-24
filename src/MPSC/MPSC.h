#pragma once

#include "../Aliases/Aliases.h"
#include "../Aliases/Order.h"

#include <atomic>
#include <memory>
#include <optional>



template <typename T>
class MPSCQueue{
public:
    MPSCQueue();
    ~MPSCQueue();

    [[nodiscard]] std::optional<T> pop noexcept;
    [[nodiscard]] bool push(const T& msg) noexcept;

private:

    static constexpr size_t capacity = 2056;
    static constexpr size_t maxIndexMask = capacity -1;

    alignas(64) std::atomic<size_t> readIndex{0};
    alignas(64) std::atomic<size_t> commitWriteIndex{0};
    alignas(64) std::atomic<size_t> reserveWriteIndex{0};

    T* buf =  nullptr;
};

template<typename T>
MPSCQueue<T>::MPSCQueue() {
    static_assert((capacity > 0 && ((capacity & (capacity-1)) == 0)),"CAPACITY ISNT POWER OF 2");
    static_assert(std::atomic<size_t>::is_always_lock_free, "REQUIRES LOCK FREE ATOMICS");
    buff = new T[capacity];
}

template <typename T>
MPSCQueue<T>::~Queue(){
    delete[] buf;
}

template<typename T>
bool MPSCQueue<T>::push(const T& msg) noexcept {

    while(true){
        size_t rw = reserveWriteIndex.load(std::memory_order_relaxed);
        size_t r = readIndex.load(std::memory_order_relaxed);

        if(rw - r == capacity){
            return false;
        }
        if(reserveWriteIndex.compare_exchange_weak(rw,rw+1,std::memory_order_relaxed)){
            buf[rw & maxIndexMask] = msg;
            
            while(!commitWrideIndex.compare_exchange_weal(rw,rw+1,std::memory_order_release, std::memory_order_relaxed)){
                std::this_thread::yield(); // Problematic
            }
            return true;
        }
    }
}



template<typename T>
std::optional<T> MPSCQueue<T>::pop() noexcept {
    size_t r = readIndex.load(std::memory_order_relaxed);
    size_t cw = commitWriteIndex.load(std::memory_order_acquire);

    if(cw == r){
        return std::nullopt;
    }

    auto msg = buf[r & maxIndexMask];

    readIndex.store(r+1, std::memory_order_relaxed);

    return std::make_optional(msg);
}
