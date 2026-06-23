#include "Aliases.cpp" 
#include <random>
#include "Player.cpp"
#include "Maker.cpp"
#include "TickerChars/Asset.cpp"
#include <string>

class Exchange{
public:
    Exchange(size_t Tickers, size_t Makers, size_t Players) 
    : m_TickerNum{Tickers}, m_MakerNum{Makers}, m_PlayerNum{Players}
    {
        for(size_t i {}; i < m_TickerNum < ++i)
        {
            std::random_device RandomDevice;
            std::mt19937    Engine(RandomDevice);
            std::uniform_int_distribution<int>  distr(0, 10000);




        }

        for(size_t i {}; i < m_MakerNum; ++i)
        {
            std::random_device RandomDevice;
            std::mt19937    Engine(RandomDevice);
            std::uniform_int_distribution<int>  distr(0, 10000);  

            


        }

        for(size_t i {}; i < m_PlayerNum; ++i)
        {
            std::random_device RandomDevice;
            std::mt19937    Engine(RandomDevice);
            std::uniform_int_distribution<int>  distr(0, 10000);  
            Symbol NumericalString{distr(Engine)};
            m_PlayerVector.emplace_back(NumericalString, 100000);


        }
        

    }




    


private:
    size_t m_TickerNum;
    size_t m_MakerNum;
    size_t m_PlayerNum;
    std::vector<Player> m_PlayerVector;
    std::vector<Maker> m_MakerVector;
    std::vector<Ticker> m_TickerVector;
};