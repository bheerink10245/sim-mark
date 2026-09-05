#include "Exchange.h"


Exchange::Exchange(const uint64_t& runs) 
    : m_Runs{runs}, 
    m_Clock{std::make_unique<Timer>(Timer(0))},
    m_TickerContainerPtr{std::make_shared<std::unordered_map<Symbol, std::shared_ptr<Ticker>>>()},
    m_PlayerContainerPtr{std::make_shared<std::unordered_map<Symbol, std::shared_ptr<Player>>>()},
    m_IdGenerator {std::make_shared<IdGenerator>()}



{ }


void Exchange::DependencyInits(){

}

void Exchange::TickerInit(uint8_t tickerNums){
    
    m_TickerContainerPtr->reserve(tickerNums);

    std::vector<Symbol> charset {"A","B","C","D","E","D","F","G"};

    static int t_count = 0;

    while(tickerNums >= t_count){

        //Key handled
        Symbol charName = charset.at(t_count);
        // Construct ticker value
        m_TickerContainerPtr->insert({charName, std::make_shared<Ticker>(charName)});
        t_count++;
    }
}



void Exchange::PlayerInit(uint32_t playerNums, std::vector<strategyFunction> functors){    
    
    m_PlayerContainerPtr->reserve(playerNums);

    std::vector<Symbol> charset {"A","B","C","D","E","D","F","G"};

    static int p_count = 0;

    while(playerNums >= p_count){

        //Key handled
        Symbol charName = charset.at(p_count);
        // Construct player value
        m_PlayerContainerPtr->insert({charName, std::make_unique<Player>(charName, functors.at(p_count))});
        p_count++;

    }
}

void Exchange::StartSimulation(){

    
    while(m_Clock->GetIterationCount() <= m_Runs){




        m_Clock->CLK();
    }
}
