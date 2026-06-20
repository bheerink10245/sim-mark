#include "Aliases.cpp"
#include <vector>
#include <iostream>


using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using TradeInfo = Aliases::TradeInfo;


class Entity {
public:


    virtual bool CapitalChecK() = 0;

    virtual Price GetProfitLoss() = 0;




protected:  
    std::vector<TradeInfo> m_TradeLog;
};

