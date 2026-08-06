#include "Ticker.h"
   
Ticker::Ticker(const Symbol& Name) 
    : m_Name{Name}, 
    m_OrderBookPtr{new OrderBook},
    m_TickerQueuePtr{new MPSC},
    m_DataPtr{new TickerData}
{}

Ticker::~Ticker() {}

void Ticker::PerformPerCLK(){
    OrderPointer NXT_Order = m_TickerQueuePtr->pop();
    PerformOrderMatch(NXT_Order, *(m_OrderBookPtr));       
    //Add Logging Data and Feedback from PerformOrderMatch                                                        
    m_DataPtr->TickerUpdate(*(m_OrderBookPtr));                                                                                                                                  
} 

void Ticker::PerformOrderMatch(const OrderPointer& order, OrderBook& OrderBook){
    OrderBook->OrderBook::AddOrder(order);
}

Price Ticker::GetTickerPrice() const {return m_DataPtr->GetPrice();}
Quantity Ticker::GetTickerQuantity() const {return m_DataPtr->GetQuantity();}
Quantity Ticker::GetTickerVolume() const {return m_DataPtr->GetVolume();}

void Ticker::LogTrade(const OrderId& OrderID, const TradeInfo& Info){
    TradeLog.insert({OrderID,Info});
}

void Ticker::LogOrder(const OrderId& OrderID, const Order& Info){
    OrderLog.insert({OrderID,Info});
}

TradeInfo Ticker::GetTradeInfo(const OrderId& OrderID) const {
    auto keyValue = TradeLog.find(OrderID);
    if(keyValue != TradeLog.end()){
        return keyValue->second;
    };
    return NULL;
}

Order Ticker::GetOrderInfo(const OrderId& OrderID) const {
    auto keyValue = OrderLog.find(OrderID);
    if(keyValue != OrderLog.end()){
        return keyValue->second;
    };
    return NULL;
}
