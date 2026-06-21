#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <unordered_map>
#include "OrderBook/Orderbook.cpp"
#include "Aliases.cpp"
#include "Entity.hpp"

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using TradeInfo = Orderbook::TradeInfo;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;

class Ticker {
public:

    Ticker(Symbol ticker, Price price)
    {

    }

    Ticker(Symbol ticker) 
    {

    }



    Price GetPrice() const {return m_Price;}

    Symbol GetTicker() const {return m_Ticker;}

    Quantity GetQuantity() const {return m_Quantity;}

    void SetPrice(double change) { m_Price + change;}




    /**
     * Log a Trade on a ticker
     * @param Individual: 1 of the 6 individuals that made the trade
     * @param Info: TradeInfo obj with trade details
     * 
     * 
     * 
     */
    void TradeExecuted(Entity& Individual, TradeInfo& Info) 
    {
        m_TradeLog.emplace(Individual,Info);

    }




private:

    Price m_Price;
    Symbol m_Ticker;
    Quantity m_Quantity;
    std::unordered_map<Entity,TradeInfo> m_TradeLog;


};