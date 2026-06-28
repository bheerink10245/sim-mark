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


    class MarketData 
    {
    public:
        MarketData() : 
        {}
    
        MarketData Exchange_Cycle_Update()
        {

        }

    };


private:
    size_t m_TickerNum;
    size_t m_MakerNum;
    size_t m_PlayerNum;

};