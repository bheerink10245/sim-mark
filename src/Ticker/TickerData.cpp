#include "TickerData.h"
#include "OrderBook.h"

#include <random>

TickerData::TickerData() : m_Price(0.0), m_Quantity(100000), m_Volume(0) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(1.00, 200.0);
    m_Price = dis(gen);
}

TickerData::~TickerData(){

}

void TickerData::TickerUpdate(const OrderBook& OrderBook){
    Price lastAsk = OrderBook.GetAsksMap().begin().front() ;
    Price lastBid = OrderBook.GetBidsMap().begin().front() ;
    m_Price = ((lastAsk + lastBid) / 2.00);
}

Price TickerData::GetPrice() const {return m_Price;}
Quantity TickerData::GetQuantity() const {return m_Quantity;}
Quantity TickerData::GetVolume() const {return m_Volume;}