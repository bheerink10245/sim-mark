#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <memory>
#include <unordered_map>
#include "Orderbook.cpp"
#include "Aliases.cpp"
#

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using TradeInfo = Orderbook::TradeInfo;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;




class Ticker {
public:

    Ticker(const Symbol& Name) : m_Name{Name}
    {


    }




    void PerformPerCLK()
    {
        // Matching Engine Takes from MQSC
        // Matching Engine Runs through OrderBook
        // Returns from MatchingEngine 
        // Update TickerData
        m_DataPtr->TickerUpdate();
        
        
    }





    class TickerData {
    public:
        TickerData() : m_Price{}, m_Quantity{100000}
        { //Intilaize Random Price
                 

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
        float GetVolatility() const
        {
            return m_Volatility;
        }

        
        
        
        void TickerUpdate(const Price& priceChange,
                            const Quantity& quantityChange,
                            const Quantity& volumeChange,
                            const float& volatilityChange) 
        {

            m_Price = m_Price + priceChange;
            m_Quantity = m_Quantity + quantityChange;
            m_Volume = m_Volume + volumeChange;
            m_Volatility = m_Volatility + volatilityChange;
        }


    private:

        Price m_Price;
        Quantity m_Quantity;
        Quantity m_Volume;
        float m_Volatility;
    };




private:

    Symbol m_Name;
    std::unique_ptr<TickerData> m_DataPtr = new TickerData;
    std::unique_ptr<Orderbook::OrderBook> m_OrderBookPtr = new OrderBook;



};
