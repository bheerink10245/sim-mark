#include "Exchange.h"


Exchange::Exchange(const uint64_t& runs) 
    : m_Runs{runs}, 
    m_Clock{std::make_shared<Timer>(Timer(0))},
    m_IdGenerator {std::make_shared<IdGenerator>()},
    m_TickerContainerPtr{std::make_shared<std::unordered_map<Symbol, std::shared_ptr<Ticker>>>()},
    m_PlayerContainerPtr{std::make_shared<std::unordered_map<Symbol, std::shared_ptr<Player>>>()}

{ }

Exchange::~Exchange(){


};

ExchangeData Exchange::GenerateExchangeData(){


    
}

void Exchange::TickerInit(uint8_t tickerNums){
    

    std::vector<Symbol> charset {"A","B","C","D","E","D","F","G"};

    size_t t_count = 0;

    while(tickerNums > t_count){

        //Key handled
        Symbol charName = charset.at(t_count);
        // Construct ticker value
        m_TickerContainerPtr->emplace(charName, std::make_shared<Ticker>(charName));
        t_count++;
        
    }
}



void Exchange::PlayerInit(uint32_t playerNums, std::vector<strategyFunction> functors){    
    
    std::vector<Symbol> charset {"A","B","C","D","E","D","F","G"};

    size_t p_count = 0;

    while(playerNums > p_count){

        //Key handled
        Symbol charName = charset.at(p_count);
        //value constructed
        auto player = std::make_unique<Player>(charName, functors.at(p_count));
        m_PlayerContainerPtr->emplace(charName, std::move(player));
        p_count++;

    }
}

void Exchange::StartSimulation(){

    
    while(m_Clock->GetIterationCount() <= m_Runs){

        
        

        m_Clock->CLK();
    }
}
