#pragma once

#include "Aliases.h"

#include <atomic>



class IdGenerator {

public:

    [[nodiscard]] OrderId GenerateId();

private:
    std::atomic<uint64_t> next_id_{1};

};

