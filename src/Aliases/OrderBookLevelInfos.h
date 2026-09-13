#pragma once

#include <vector>

struct LevelInfo;
using LevelInfos = std::vector<LevelInfo>;

class OrderBookLevelInfos{
public:
    OrderBookLevelInfos(const LevelInfos& bids, const LevelInfos& asks);
    
    const LevelInfos& GetBids() const;
    const LevelInfos& GetAsks() const;

private:
    LevelInfos m_bids;
    LevelInfos m_asks;

};