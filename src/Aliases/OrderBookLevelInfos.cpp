
#include "OrderBookLevelInfos.h"
#include "LevelInfo.h"



OrderBookLevelInfos::OrderBookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
: m_bids{bids}
, m_asks{asks}
{}

const LevelInfos& OrderBookLevelInfos::GetBids() const {return m_bids;}
const LevelInfos& OrderBookLevelInfos::GetAsks() const {return m_asks;}

