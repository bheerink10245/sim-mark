
#include "Ticker.h"
  




Ticker::Ticker(const Symbol& name, 
    std::shared_ptr<const Timer> timer, 
    IdGenerator& idGenerator)

    : m_Name{name}
    , m_SharedTimer{timer}
    , m_SharedIdGenerator{idGenerator}
    , m_OrderBookPtr{std::make_shared<OrderBook>()}
    , m_TickerQueuePtr{std::make_shared<MPSC>()}
    , m_DataPtr{std::make_unique<TickerData>()}
    , m_MakerOne{std::make_shared<Maker>("1", *(m_DataPtr), strat1, timer, idGenerator)}
    , m_MakerTwo{std::make_shared<Maker>("2", *(m_DataPtr), strat2, timer, idGenerator)}
{ }

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
    m_TradeLog.insert({timeS, OrderID});
}

void Ticker::LogOrder(const TimeStamp& timeS, const OrderId& OrderID){
    m_OrderLog.insert({timeS, OrderID});
}

std::expected<TradeInfo, std::invalid_argument> Ticker::GetTradeInfo(const OrderId& OrderID) const
{
    auto keyValue = m_TradeLog.find(OrderID);
    if (keyValue != m_TradeLog.end()){
        return keyValue->second;
    }

    return std::unexpected(std::invalid_argument("OrderID not found"));
}

std::expected<Order, std::invalid_argument> Ticker::GetOrderInfo(const OrderId& OrderID) const {
    auto keyValue = m_OrderLog.find(OrderID); 
    if(keyValue != m_OrderLog.end()){
        return keyValue->second;
    }
    return std::unexpected(std::invalid_argument("OrderID not found"));
    
}

