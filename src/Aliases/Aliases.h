#pragma once 

#include <string>
#include <vector>
#include <cstdint>

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;
using Symbol = std::string;
using OrderIds = std::vector<OrderId>;

enum class Side
{
    Buy,
    Sell

};

enum class OrderType
{
    FillAndKill,
    FillOrKill,
    GoodTillCancel,
    GoodForDay,
    Market

};

enum class ActionFunction
{
    AddOrder,
    CancelOrder,
    ModifyOrder,
    Default
};

enum class OrderError
{
    Invalid,
    NotFound
};

enum class TickerError
{
    Invalid,
    NotFound
};

enum class OrderStatus
{
    Recieved,
    Steady,
    Unfillable,
    Filled
};



