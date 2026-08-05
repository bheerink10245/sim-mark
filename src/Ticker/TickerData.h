#pragma once

#include "Aliases.h"
#include "OrderBook/OrderBook.h"
#include <random>


using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using Trade = Aliases::Trade;
using Trades = Aliases::Trades;


class TickerData{
public:
    TickerData();
    TickerData(const TickerData&) = delete;
    void operator=(const TickerData&) = delete;
    TickerData(const TickerData&&) = delete;
    void operator=(const TickerData&&) = delete;
    ~TickerData();

    Price GetPrice() const {return m_Price;}
    Quantity GetQuantity() const {return m_Quantity;}
    Quantity Getvolume() const {return m_Volume;}


    void TickerUpdate(const OrderBook& OrderBook);

private:
    Price m_Price;
    Quantity m_Quantity;
    Quantity m_Volume;
};