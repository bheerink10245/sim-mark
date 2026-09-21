#pragma once

#include "../Aliases/Aliases.h"
#include "OrderBook/OrderBook.h"

class OrderBook;


class TickerData{
public:

    TickerData();
    TickerData(const TickerData&) = delete;
    TickerData& operator=(const TickerData&) = delete;
    TickerData(TickerData&&) = delete;
    TickerData& operator=(TickerData&&) = delete;
    ~TickerData();

    Price GetPrice() const;
    Quantity GetQuantity() const;
    Quantity GetVolume () const;
    void TickerUpdate(const OrderBook& OrderBook);


private:
    Price m_Price;
    Quantity m_Quantity;
    Quantity m_Volume;

    void ReCalculateVolume();
    void ReCalculateQuantity();

};