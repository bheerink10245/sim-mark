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
        FillorKill,
    };
    struct TradeInfo
    {
        Side m_Side;
        OrderId m_OrderId;
        Price m_Price;
        Quantity m_Quantity;

    };
    class Trade
    {
    public:
        Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade)
        : m_BidTrade{bidTrade}
        , m_AskTrade {askTrade}
        {}

        const TradeInfo& GetBidTrade() const {return m_BidTrade;}
        const TradeInfo& GetAskTrade() const {return m_AskTrade;}


    private:
        TradeInfo m_BidTrade;
        TradeInfo m_AskTrade;

    };



}