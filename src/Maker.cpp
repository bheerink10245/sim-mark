#include "Aliases.cpp"
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
    Maker(const Symbol& name) : m_Name{name}, m_InitCapital{1000000}
    {

    }

    
    
    Price GetPnL()
    {
        return m_InitCapital - m_RemainingCapital;
    }

    void PerformPerCLK()
    {
        
    }
private:
    Symbol m_Name;
    std::vector<Order>* m_OrderLog = new std::vector<Order>{};
    Price m_InitCapital;
    Price m_RemainingCapital;


};