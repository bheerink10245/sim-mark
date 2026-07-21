#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <memory>
#include <unordered_map>
#include <expected>
#include "OrderBook.cpp"
#include "Aliases.cpp"
#

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;




class Ticker {
public:

    Ticker(const Symbol& Name) : m_Name{Name}{


    }

    void PerformPerCLK(){
        // Matching Engine Takes from MQSC
        // Matching Engine Runs
        // Returns from MatchingEngine 
        m_DataPtr->TickerUpdate();// Update TickerData
        // Log Ticker changes
    } 




    class MatchingEngine{
    public:
        MatchingEngine()
        {

        }

        

        bool CanMatch(const Order& order){

            // Run through Tickers OrderBook and see if it can find a match

            if(order.OrderSide == Side::Buy)
            {
                if(m_OrderBookPtr->MEM_ASKS.empty()) {return false;}
                const auto& [bestAsk,_] = *m_OrderBookPtr->MEM_ASKS.begin();
                return order.OrderPrice >= bestAsk;
            }
            else{
                if(m_OrderBookPtr->MEM_BIDS.empty()) {return false;}
            } 
            const auto& [bestBid, _] = *(m_OrderBookPtr->MEM_BIDS.begin());
            return order.OrderPrice <= bestBid;
        }
        // I acutally dont know if this return type is right, will do 
        Trade MatchOrder(const Order& order){
            //Match Success, Build and fullfill order
            if(CanMatch(order)){

                while (true){

                    if(MEM_BIDS.empty() || MEM_ASKS.empty())
                    {
                        break;
                    }
                    auto& [bidPrice, bids] = *MEM_BIDS.begin();
                    auto& [askPrice, asks] = *MEM_ASKS.begin();
                    
                    if(bidPrice < askPrice)
                    {
                        break;
                    }

                    while (bids.size() && asks.size())
                    {
                        auto& bid = bids.front();
                        auto& ask = asks.front();

                        Quantity quantity = std::min(bid->GetRemainingQuantity, ask->GetRemainingQuantity());
                        
                        bid->Fill(quantity);
                        ask->Fill(quantity);

                        if(bid->IsFilled())
                        {
                            bids.pop_front();
                            ORDERS.erase(bid->GetOrderId());

                        }
                        if(ask->IsFilled())
                        {
                            asks.pop_front();
                            ORDERS.erase(ask->GetOrderId);
                        }
                        if(bids.empty())
                        {
                            MEM_BIDS.erase(bidPrice);

                        }
                        if (bids.empty())
                        {
                            MEM_ASKS.erase(askPrice);
                        }

                        trades.push_back(Trade{
                            TradeInfo{bid->GetOrderId(), bid->GetPrice(), quantity},
                            TradeInfo{ask->GetOrderId(), ask->GetPrice(), quantity}
                        });
                    }
                
                if(!MEM_BIDS.empty()){
                    auto& [_,bids] = *MEM_BIDS.begin();
                    auto& order = bids.front();
                    if(order->GetOrderType() == OrderType::FillAndKill){
                        CancelOrder(order->GetOrderId());
                    
                    }
                    if(!.empty()){
                        auto& [_,asks] = *asks.begin();
                        auto& order = asks,front();
                        if(order->GetOrderType() == OrderType::FillAndKill)
                            CancelOrder(order->GetOrderId());
                        
                    }
                }
                return trades;
            }
            // Order cant be fullfilled 
            else{
                // Destroy order accordingly. Return unexpected
            }
        }
    }
    };
    
    class TickerData {
    public:
        TickerData() :  m_Quantity{100000}
        { 
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(1.00, 200.0);
            m_Price{dis(gen)};
            
        }

        
        
        
        
        Price GetPrice() const
        {
            return m_Price;
        }
        Quantity GetQuantity() const
        {
            return m_Quantity;
        }
        Quantity GetVolume() const 
        {
            return m_Volume;
        }


        
        
        
        void TickerUpdate(const Price& priceChange,
                            const Quantity& quantityChange,
                            const Quantity& volumeChange) 
        {

            m_Price +=  priceChange;
            m_Quantity += quantityChange;
            m_Volume += volumeChange;
        }


    private:
        Price m_Price;
        Quantity m_Quantity;
        Quantity m_Volume;
    };

 


private:

    Symbol m_Name;
    std::unique_ptr<TickerData> m_DataPtr = std::make_unique<TickerData>(new TickerData{});
    std::unique_ptr<OrderBook::OrderBook> m_OrderBookPtr = std::make_unique<OrderBook::OrderBook>(new OrderBook::OrderBook{});



};
