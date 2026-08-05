#include "Aliases.h"
#include <map>

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using TradeInfo = Aliases::TradeInfo;



class Player{
public:

    Player();
    Player(const Player&) = delete;
    void operator=(const Player&) = delete;
    Player(const Player&&) = delete;
    void operator=(const Player&&) = delete;
    ~Player();

    Order GetOrderInfo(const OrderId& ID);
    TradeInfo GetTradeInfo(const OrderId& ID);
    void PerformPerClk();
    Price GetPnL() const {return m_InitCapital - m_RemainingCapital;}


private:

    Symbol m_Name;
    std::map<OrderId, TradeInfo, std::greater<OrderId>> TradeLog;
    std::map<OrderId, Order, std::greater<OrderId>> OrderLog;
    Price m_InitCapital;
    Price m_RemainingCapital;

};