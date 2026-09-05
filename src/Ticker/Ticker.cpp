
#include "Ticker.h"
  

ModelFunction strat1;
ModelFunction strat2;


Ticker::Ticker(const Symbol& Name) 
    : m_Name{Name}, 
    m_OrderBookPtr{std::make_unique<OrderBook>()},
    m_TickerQueuePtr{std::make_shared<MPSC>()},
    m_DataPtr{std::make_unique<TickerData>()},
    m_MakerOne{std::make_unique<Maker>("1", this, strat1)},
    m_MakerTwo{std::make_unique<Maker>("2", this, strat2)}
{}

Ticker::~Ticker() {}

void Ticker::PerformPerCLK(){
    OrderPointer NEXT_Order = m_TickerQueuePtr->pop();
    // Makers need to be fed data 
    //Makers need to make liquidity adjustment
    //Allow makers into Queue
    PerformOrderMatch(NEXT_Order, *(m_OrderBookPtr));   
    // Respond to exchange with status update. Exchange handles owner comms
    //Add Logging Data and Feedback from PerformOrderMatch                                                        
    m_DataPtr->TickerUpdate(*(m_OrderBookPtr));                                                                                                                                  
} 

void Ticker::PerformOrderMatch(const OrderPointer& order, OrderBook& OrderBook){
    ActionFunction action = order->GetOrderAction();
    if(action == ActionFunction::AddOrder){
        OrderBook.AddOrder(order);
    }
    else if(action == ActionFunction::CancelOrder){
        OrderBook.CancelOrder(order->GetOrderId());
    }
    else if(action == ActionFunction::ModifyOrder){
        OrderModify modOrder = OrderModify(order->GetOrderId(), order->GetOrderSide(), order->GetOrderPrice(), order->GetFilledQuantity());
        OrderBook.ModifyOrder(modOrder);
    }

}

Symbol Ticker::GetName() const {return m_Name;}
Price Ticker::GetTickerPrice() const {return m_DataPtr->GetPrice();}
Quantity Ticker::GetTickerQuantity() const {return m_DataPtr->GetQuantity();}
Quantity Ticker::GetTickerVolume() const {return m_DataPtr->GetVolume();}

void Ticker::LogTrade(const TimeStamp& timeS,const OrderId& OrderID){
    TradeLog.insert({timeS, OrderID});
}

void Ticker::LogOrder(const TimeStamp& timeS, const OrderId& OrderID){
    OrderLog.insert({timeS, OrderID});
}

std::expected<TradeInfo, std::invalid_argument> Ticker::GetTradeInfo(const OrderId& OrderID) const
{
    auto keyValue = TradeLog.find(OrderID);
    if (keyValue != TradeLog.end()){
        return keyValue->second;
    }

    return std::unexpected(std::invalid_argument("OrderID not found"));
}

std::expected<Order, std::invalid_argument> Ticker::GetOrderInfo(const OrderId& OrderID) const {
    auto keyValue = OrderLog.find(OrderID); 
    if(keyValue != OrderLog.end()){
        return keyValue->second;
    }
    return std::unexpected(std::invalid_argument("OrderID not found"));
    
}

