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
        m_MatchingEnginePtr->MatchOrder(m_TickerQueuePtr.pop());                     
                                                                                        
        m_DataPtr->TickerUpdate();                                                     // Update TickerData
                                                                                        // Log Ticker changes
    } 




    class MatchingEngine{
    public:
        MatchingEngine()
        {}

        using m_AsksMap = m_OrderBookPtr->m_AsksMap;
        using m_BidsMap = m_OrderBookPtr->m_BidsMap;
        using m_OrdersMap = m_OrderBookPtr->m_OrdersMap;


        bool CanMatch(const Order& order) const {
            if (order.GetOrderSide() == Side::Buy)
            {
                if (m_AsksMap.empty()) return false;
                const auto& [bestAsk, _] = *m_AsksMap.begin();
                return order.GetOrderPrice() >= bestAsk;
            }
            else // sell side
            {
                if (m_BidsMap.empty()) return false;
                const auto& [bestBid, _] = *m_BidsMap.begin();
                return order.GetOrderPrice() <= bestBid;
            }
        }

        std::vector<Trade> MatchOrder(Order order)
        {
            std::vector<Trade> trades;

            if (!CanMatch(order))
                return trades;

            while (!m_BidsMap.empty() && !m_AsksMap.empty())
            {
                auto& [bidPrice, bids] = *m_BidsMap.begin();
                auto& [askPrice, asks] = *m_AsksMap.begin();

                if (bidPrice < askPrice)
                    break;

                while (!bids.empty() && !asks.empty())
                {
                    auto& bid = bids.front();
                    auto& ask = asks.front();

                    Quantity quantity = std::min(bid->GetRemainingQuantity(), ask->GetRemainingQuantity());

                    bid->Fill(quantity);
                    ask->Fill(quantity);

                    trades.emplace_back(
                        bid->GetOrderId(),
                        ask->GetOrderId(),
                        askPrice,        // convention: trade executes at the resting (ask) price
                        quantity,
                        Snapshot()

                    if (bid->IsFilled())
                    {
                        bids.pop_front();
                        m_OrdersMap.erase(bid->GetOrderId());
                    }
                    if (ask->IsFilled())
                    {
                        asks.pop_front();
                        m_OrdersMap.erase(ask->GetOrderId());
                    }
                }

                if (bids.empty())
                    m_BidsMap.erase(bidPrice);
                if (asks.empty())
                    m_AsksMap.erase(askPrice);
            }

            if (!m_BidsMap.empty())
            {
                auto& [_, bids] = *m_BidsMap.begin();
                auto& topBid = bids.front();
                if (topBid->GetOrderType() == OrderType::FillAndKill)
                    CancelOrder(topBid->GetOrderId());
            }

            if (!m_AsksMap.empty())
            {
                auto& [_, asks] = *m_AsksMap.begin();
                auto& topAsk = asks.front();
                if (topAsk->GetOrderType() == OrderType::FillAndKill)
                    CancelOrder(topAsk->GetOrderId());
            }

            return trades;
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

        void TickerUpdate(){
            Price lastAsk {*(m_OrderBookPtr->m_AsksMap.begin()) };
            Price lastBid {*(m_OrderBookPtr->m_BidsMap.begin()) };

            m_Price = ((lastAsk + lastBid) / 2.00);
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
