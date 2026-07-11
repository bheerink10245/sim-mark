#include "Aliases.cpp" 
#include "Maker.cpp"
#include "Player.cpp"
#include "Asset.cpp"
#include "Timer.cpp"



#include <random>
#include <string>
#include <queue> 

//Unique Functors

class Exchange{
public:
    //Exhcange is specific to machine
    //Avaiable Core count;
    Exchange(long long Runs) : m_Runs{Runs}
    { 

        // Create Tickers
        Ticker* A_Tick = new Ticker()
        //Create Particpants
        //Create Makers

        // Cycle Loop

        while(m_Clock->GetIterationCount() <= m_Runs)
        {
            // Every Ticker, Particpant, and MarketMaker needs to run
            // their performPerCLK. This has to be done in parallel.
            
            m_Clock->CLK();
        }


    }


    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    struct MarketData 
    {
    public:
        MarketData() : 
        {}


    };


private:

    Timer* m_Clock = new Timer{};
    long long m_Runs;

};