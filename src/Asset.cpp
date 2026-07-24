#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <memory>
#include <unordered_map>
#include <expected>
#include "OrderBook.cpp"
#include "Aliases.cpp"
#include "MPSC.cpp"

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using Trade = Aliases::Trade;





class Ticker {
public:

    Ticker(const Symbol& Name) : m_Name{Name}{


    }

    ~Ticker() {
        delete m_MatchingEnginePtr;
    }
    void PerformPerCLK(){
        m_MatchingEnginePtr->MatchOrder(m_TickerQueuePtr.pop());                        // Matching Engine Takes from MQSC
                                                                                        // Matching Engine Runs
                                                                                        // Returns from MatchingEngine 
        m_DataPtr->TickerUpdate();                                                      // Update TickerData
                                                                                        // Log Ticker changes
    } 




    class MatchingEngine{
    public:
        MatchingEngine()
        {}

        using m_AsksMap = m_OrderBookPtr->m_AsksMap;
        using m_BidsMap = m_OrderBookPtr->m_BidsMap;
        using m_OrdersMap = m_OrderBookPtr->m_OrdersMap;


        bool CanMatch(const Order& order){

            // Run through Tickers OrderBook and see if it can find a match

            if(order.GetOrderSide() == Side::Buy) // trying to buy, go to asks map
            {
                if(m_AsksMap.empty()) {return false;} // checks to see if asks map is empty or not
                const auto& [bestAsk,_] = *(m_AsksMap.begin()); // get iterator of the best Ask
                return order.GetOrderPrice() >= bestAsk; // if the price at which the order is trying to buy at is larger or equal to bestAsk, return true
            }
            else(order.GetOrderSide() == Side::Sell){
                if(m_BidsMap.empty()) {return false;} // see if anyone/bids to sell to
            
                const auto& [bestBid, _] = *(m_BidsMap.begin()); // get highed bid 
                return order.GetOrderPrice() <= bestBid; // check to see sell order price is lower or equal to bestBid
                
            }
        }   

        Trade MatchOrder(Order order){

            if(CanMatch(order)){ // order good, run order fullfillment and orderbook modification

                while (true){

                    auto& [bidPrice, bids] = *(m_BidsMap.begin());
                    auto& [askPrice, asks] = *(m_AsksMap.begin());
                    
                    if(bidPrice < askPrice)
                    {
                        break;
                    }

                    while (bids.size() && asks.size())
                    {
                        auto& bid = bids.front();
                        auto& ask = asks.front();

                        Quantity quantity = std::min(bid->GetRemainingQuantity(), ask->GetRemainingQuantity());
                        
                        bid->Fill(quantity);
                        ask->Fill(quantity);

                        if(bid->IsFilled())
                        {
                            bids.pop_front();
                            m_OrdersMap.erase(bid->GetOrderId());

                        }
                        if(ask->IsFilled())
                        {
                            asks.pop_front();
                            m_OrdersMap.erase(ask->GetOrderId);
                        }
                        if(bids.empty())
                        {
                            m_BidsMap.erase(bidPrice);

                        }
                        if (bids.empty())
                        {
                            m_AsksMap.erase(askPrice);
                        }

                        trades.push_back(Trade{
                            TradeInfo{bid->GetOrderId(), bid->GetPrice(), quantity},
                            TradeInfo{ask->GetOrderId(), ask->GetPrice(), quantity}
                        });
                    }
                
                if(!m_BidsMap.empty()){
                    auto& [_,bids] = *m_BidsMap.begin();
                    auto& order = bids.front();
                    if(order->GetOrderType() == OrderType::FillAndKill){
                        CancelOrder(order->GetOrderId());
                    
                }
                if(!m_AsksMap.empty()){
                    auto& [_,asks] = *asks.begin();
                    auto& order = asks,front();
                    if(order->GetOrderType() == OrderType::FillAndKill)
                        CancelOrder(order->GetOrderId());
                    
                }
            }
                return trades;
        }
            // Order cant be fullfilled 
    }
    };
    
    class TickerData {
    public:
        TickerData() :  m_Quantity{100000} { 
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(1.00, 200.0);
            m_Price{dis(gen)};
            
        }

        
        
        
        
        Price GetPrice() const {return m_Price;} 
        Quantity GetQuantity() const {return m_Quantity;}
        Quantity GetVolume() const {return m_Volume;}

        void TickerUpdate(const Price& priceChange, const Quantity& quantityChange, const Quantity& volumeChange) {
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
    std::unique_ptr<OrderBook::OrderBook> m_OrderBookPtr = std::make_unique<OrderBook::OrderBook>(new OrderBook::OrderBook);
    std::shared_ptr<MPSC> m_TickerQueuePtr = std::make_shared<MPSC>(new MPSC{});
    MatchingEngine* m_MatchingEnginePtr = new MatchingEngine{};
    

};
