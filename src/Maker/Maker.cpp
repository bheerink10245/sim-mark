#include "Aliases.h"

#include <queue>
#include <vector>
#include <iostream>
#include <unordered_map>

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using Trade = Aliases::Trade;

class Maker {
public:
    Maker(const Symbol& name, const Ticker& ServicedTicker) : m_Name{name}, m_InitCapital{1000000}{


    }

    Price GetPnL() {return m_InitCapital - m_RemainingCapital;}

    void PerformPerCLK(){
        
    }

private:
    Symbol m_Name;
    std::shared_ptr<std::vector<Order>> m_OrderLog = std::make_shared<std::vector<Order>>(new std::vector<Order>{});
    Price m_InitCapital;
    Price m_RemainingCapital;    
};