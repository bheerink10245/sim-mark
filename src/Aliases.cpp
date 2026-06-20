#pragma once 


#include <string>


namespace Aliases {
    
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
        GoodTillCancel,
        FillAndKill,
        Market
    };
    struct TradeInfo
    {
        Side m_Side;
        OrderId m_OrderId;
        Price m_price;
        Quantity m_quantity;

    };



}