#include "Trade.h"


Trade::Trade(const TradeInfo& bidTrade, const TradeInfo& askTrade)
: m_bidTrade{bidTrade}
, m_askTrade{askTrade}
{ }

const TradeInfo& Trade::GetBidTrade() const {return m_bidTrade;}
const TradeInfo& Trade::GetAskTrade() const {return m_askTrade;}


