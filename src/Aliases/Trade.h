

#include <cstdint>

using Price = std::int32_t;
using Quantity = std::uint32_t;
using OrderId = std::uint64_t;


struct TradeInfo {

    OrderId m_OrderId;
    Price m_Price;
    Quantity m_Quantity;
    
};


class Trade {

public:
    Trade (const TradeInfo& bidTrade, const TradeInfo& askTrade);

    const TradeInfo& GetBidTrade() const;
    const TradeInfo& GetAskTrade() const;
    
private:
    TradeInfo m_bidTrade;
    TradeInfo m_askTrade;

};