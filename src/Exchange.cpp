// This simulation is run on a i7-14700K(Raptor Lake Refresh), 20 cores, 28 threads. 8 P-Cores, 12 E-Cores

#include "Aliases.cpp" 
#include "Maker.cpp"
#include "Player.cpp"
#include "Asset.cpp"
#include "Timer.cpp"


#include <thread> 
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
        Ticker* Ticker_A = new Ticker("A");
        Ticker* Ticker_B = new Ticker("B");
        Ticker* Ticker_C = new Ticker("C");
        Ticker* Ticker_D = new Ticker("D");


        //Create Makers

        // Cycle Loop

        void p_funcs();
        void m_funcs();
        void t_funcs();


        while(m_Clock->GetIterationCount() <= m_Runs)
        {
            // I have no idea if this works
            std::thread PlayerThread(p_funcs);
            std::thread MakerThread(m_funcs);
            std::thread TickerThread(t_funcs);


            PlayerThread.join();
            MakerThread.join();
            TickerThread.join();

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
    std::shared_ptr<std::vector<Ticker>> m_TickerContainer = new std::vector<Ticker>;
    long long m_Runs;

};