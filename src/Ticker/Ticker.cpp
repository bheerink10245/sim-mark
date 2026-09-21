
#include "Ticker.h"

#include "../Maker/Maker.h"
#include "../MPSC/MPSC.h"
#include "../System/Time/Timer.h"
#include "../System/Time/TimeStamp.h"
#include "../System/IdGenerator/IdGenerator.h"
#include "../Aliases/Order.h"
#include "../Aliases/Trade.h"
#include "../Aliases/OrderModify.h"
#include "TickerData.h"
#include "OrderBook/OrderBook.h"




Ticker::Ticker(const Symbol& name
    , const Timer& timer
    , IdGenerator& idGenerator)

    : m_Name{name}
    , m_Timer{timer}
    , m_IdGenerator{idGenerator}
    , m_OrderBookPtr{std::make_unique<OrderBook>()}
    , m_TickerQueuePtr{std::make_shared<MPSC>()}
    , m_DataPtr{std::make_unique<TickerData>()}
    , m_MakerOne{std::make_shared<Maker>("1", timer, idGenerator , *(m_DataPtr), strat1)}
    , m_MakerTwo{std::make_shared<Maker>("2", timer, idGenerator , *(m_DataPtr), strat2)}
    , m_TradeLog{}
    , m_OrderLog{}
{ }

Ticker::~Ticker() {}

void Ticker::PerformPerCLK(){
    OrderPointer NEXT_Order = m_TickerQueuePtr->pop();
    // Makers need to be fed data 
    //Makers need to make liquidity adjustment
    //Allow makers into Queue
    auto status = PerformOrderMatch(NEXT_Order, *(m_OrderBookPtr));   
    // Respond to exchange with status update. Exchange handles owner comms
    //Add Logging Data and Feedback from PerformOrderMatch                                                        
    m_DataPtr->TickerUpdate(*(m_OrderBookPtr));                                                                                                                                  
} 

OrderStatus Ticker::PerformOrderMatch(const std::shared_ptr<Order>& order, OrderBook& OrderBook){
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

void Ticker::LogTrade(const OrderId& ID, const TimeStamp& ts){
    m_TradeLog.insert({ID , ts});
}

void Ticker::LogOrder(const OrderId& ID, const TimeStamp& ts){
    m_OrderLog.insert({ID, ts});
}

std::expected<OrderId, TickerError> Ticker::GetTradeInfo(const OrderId& ID) const
{
    auto keyValue = m_TradeLog.find(ID);
    if (keyValue != m_TradeLog.end()){
        return keyValue->first;
    }

    return std::unexpected(TickerError::Invalid);
}

std::expected<OrderId, TickerError> Ticker::GetOrderInfo(const OrderId& ID) const {
    auto keyValue = m_OrderLog.find(ID); 
    if(keyValue != m_OrderLog.end()){
        return keyValue->first;
    }
    return std::unexpected(TickerError::Invalid);
    
}


OrderStatus Ticker::TickerEnqueue(OrderPointer order){
    

    
}
