#include "Aliases.cpp" 
#include "Maker.cpp"
#include "Player.cpp"
#include "TickerChars\Asset.cpp"


#include <random>
#include <string>
#include <queue> 



class Exchange{
public:
    Exchange(size_t Tickers, size_t Makers, size_t Players) 
    : m_TickerNum{Tickers}, m_MakerNum{Makers}, m_PlayerNum{Players}
    {
        
        

    }

    /**
    * Contains all of the data of exchange
    * Data Included 
    * 1. Each Ticker and all of its public data member (Price, TradeLog, Volume, Quantity on Market, Quantity Owned...)
    * 2. Each Players' trades from the Cycle Update (Trade Log)
    * 3. Market Makers exchanges and with whom, 
    *
    */
    class MarketData 
    {
    public:
        MarketData() : 
        {}


    };

    MarketData Exchange_Cycle_Update()
    {

    }
    


private:
    size_t m_TickerNum;
    size_t m_MakerNum;
    size_t m_PlayerNum;
    std::vector<Player> m_PlayerVector;
    std::vector<Maker> m_MakerVector;
    std::vector<Ticker> m_TickerVector;
};