#pragma once

#include <cstdint>
#include <vector>

using Price = std::int32_t;
using Quantity = std::uint32_t;

struct LevelInfo
{
    Price m_Price;
    Quantity m_Quantity;
};

using LevelInfos = std::vector<LevelInfo>;

