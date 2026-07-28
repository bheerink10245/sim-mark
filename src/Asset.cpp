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
using Trades = Aliases::Trades;


class Ticker {
public:

    Ticker(const Symbol& Name) : m_Name{Name}{


    }

    ~Ticker() {}
    void PerformPerCLK(){
        m_MatchingEnginePtr->MatchOrder(m_TickerQueuePtr.pop());                     
                                                                                        
        m_DataPtr->TickerUpdate();                                                     // Update TickerData
                                                                                        // Log Ticker changes
    } 
 
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

    

};
