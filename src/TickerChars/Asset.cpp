#include <iostream>
#include <vector>
#include <random>
#include <string>
#include "OrderBook/Orderbook.cpp"
#include "Aliases.cpp"

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using TradeInfo = Orderbook::TradeInfo;
using Symbol = Aliases::Symbol;


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


    void GeneratePriceFluctuation()
    {

    }


    void TradeExecuted(Price price, Quantity quantity, Side side) 




private:

    Price m_Price;
    Symbol m_Ticker;
    Quantity m_Quantity;
    std::vector<TradeInfo> m_TradeLog;


};