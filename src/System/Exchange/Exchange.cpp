#include "Exchange.h"


Exchange::Exchange(const uint64_t& RUNS) 
    : m_Runs{RUNS}, 
    m_Clock{std::make_unique<Timer>(new Timer(0))},
    m_TickerContainer{std::make_shared<std::unordered_map<Ticker, std::vector<Maker>, TickerHash, TickerEqual>>()}
    m_Player{std::make_shared<std::vector<Player>>(new std::vector<Player>>)}



{ }


void Exchange::TickerInit(uint32_t tickerNums){
    

    Symbol charset[] = ["A","B","C","D","E","D","F","G","H","I","J"];
    static int t_count = 0;
    static int m_count = 0;
    m_TickerContainer->reserve(tickerNums);

    while(tickerNums >= t_count){

        Symbol strip = static_cast<Symbol>(t_count);
        Symbol entityName = charset[t_count] + strip;


    }

}


void Exchange::PlayerInit(uint32_t playerNums, const std::vector<strategyFunction>& functors){    
    
    Symbol charset[] = ["A","B","C","D","E","D","F","G","H","I","J"];
    static int p_count = 0;
    m_PlayerContainer->reserve(playerNums);
    
    while(playerNums >= p_count){

        Symbol strip = static_cast<Symbol>(p_count);
        Symbol entityName = charset[p_count] + strip;

        m_PlayerContainer->emplace({entityName,functors.at(p_count)});
        p_count++;
    }

}

void Exchange::Start(){

    
    while(m_Clock->GetIterationCount() <= m_Runs){




        m_Clock->CLK();
    }
}
