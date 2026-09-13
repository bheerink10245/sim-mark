#pragma once

#include <cstdint>
#include <limits>

using Price = std::int32_t;

struct Constants {
    static const Price InvalidPrice = std::numeric_limits<Price>::quiet_NaN();
};