#include <iostream>
#include <vector>
#include <random>

#include <memory>
#include <unordered_map>
#include <expected>
#include "Aliases.h"
#include "MPSC.h"

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using Trade = Aliases::Trade;
using Trades = Aliases::Trades;

   
Ticker(const Symbol& Name) : m_Name{Name} {}
~Ticker() {}

void Ticker::PerformPerCLK(){

    PerformOrderMatch(m_TickerQueuePtr->pop());                                                               
    m_DataPtr->TickerUpdate();                                                                                                                                  
} 

void Ticker::PerformOrderMatch(const OrderPointer& order){
    m_OrderBookPtr->OrderBook::AddOrder(order);
}

