
#include "Aliases.h"
#include "System/Time/Timer.h"
#include "System/Exchange/ExchangeData.h"
#include "System/Exchange/Exchange.h"
#include "Ticker/Ticker.h"

#include <map>


using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Constants = Aliases::Constants;
using LevelInfo = Aliases::LevelInfo;
using LevelInfos = Aliases::LevelInfos;
using OrderBookLevelInfos = Aliases::OrderBookLevelInfos;
using Side =  Aliases::Side;
using OrderType = Aliases::OrderType;
using Order = Aliases::Order;
using OrderPointer = Aliases::OrderPointer;
using OrderPointers =  Aliases::OrderPointers;
using OrderIds = Aliases::OrderIds;
using OrderModify = Aliases::OrderModify; 
using TradeInfo = Aliases::TradeInfo;
using Trade = Aliases::Trade;
using Trades = Aliases::Trades;
using ActionFunction = Aliases::ActionFunction;


class Entity {
public:


    std::expected<Order, std::invalid_argument> GetOrderInfo(const OrderId& OrderID) const;
    std::expected<TradeInfo, std::invalid_argument> GetTradeInfo(const OrderId& OrderID) const;
    void LogTrade(const TimeStamp& ts, const OrderId& ID);
    void LogOrder(const TimeStamp& ts, const OrderId& ID);
    
    void virtual PerformPerCLK(const ExchangeData& Data) = 0;

    Price GetPnL() const {return m_InitCapital - m_RemainingCapital;}


protected:

    Symbol m_Name;
    std::map<TimeStamp, OrderId, std::greater<OrderId>> TradeLog;
    std::map<TimeStamp, OrderId, std::greater<OrderId>> OrderLog;
    Price m_InitCapital;
    Price m_RemainingCapital;

};