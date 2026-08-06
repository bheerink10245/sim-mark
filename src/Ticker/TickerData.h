#pragma once

#include "Aliases.h"
#include "OrderBook/OrderBook.h"



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

    Price GetPrice() const;
    Quantity GetQuantity() const;
    Quantity GetVolume () const;

    void TickerUpdate(const OrderBook& OrderBook);

private:
    Price m_Price;
    Quantity m_Quantity;
    Quantity m_Volume;

};