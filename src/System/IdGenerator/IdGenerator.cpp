
#include "IdGenerator.h"


[[nodiscard]] OrderId IdGenerator::GenerateId(){

    return next_id_.fetch_add(1, std::memory_order_relaxed);
}

