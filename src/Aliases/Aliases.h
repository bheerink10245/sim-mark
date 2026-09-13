#pragma once 

#include <string>
#include <list>
#include <memory>
#include <vector>
#include <cstdint>


using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;
using Symbol = std::string;

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


using OrderPointer = std::shared_ptr<Order>;
using OrderPointers = std::list<OrderPointer>;
using OrderIds = std::vector<OrderId>;




