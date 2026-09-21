


#include "Exchange.h"

#include "../Time/Timer.h"
#include "../../Aliases/Signal.h"
#include "../../Maker/Maker.h"
#include "../../Player/Player.h"
#include "../../Ticker/Ticker.h"
#include "ExchangeData.h"
#include "../IdGenerator/IdGenerator.h"

#include <memory>


Exchange::Exchange(const uint64_t& runs) 
    : m_Runs{runs}
    , m_Clock{std::make_shared<Timer>(0)}
    , m_IdGenerator {std::make_shared<IdGenerator>()}
    , m_TickerContainer{}
    , m_PlayerContainer{}

{ }

Exchange::~Exchange(){

}

ExchangeData Exchange::GenerateExchangeData(){
    return ExchangeData(m_TickerContainer);    
}

void Exchange::TickerInit(uint8_t tickerNums){
    
    std::vector<Symbol> charset {"A","B","C","D","E","F","G"};
    m_PlayerContainer.reserve(tickerNums);
    size_t t_count = 0;

    while(tickerNums > t_count){

        Symbol charName = charset.at(t_count);
        m_TickerContainer.emplace_back(std::make_shared<Ticker>(charName, *(m_Clock) , *(m_IdGenerator) ));
        t_count++;
        
    }
    m_PlayerContainer.shrink_to_fit();
}



void Exchange::PlayerInit(uint32_t playerNums, std::vector<strategyFunction> functors){    
    
    std::vector<Symbol> charset {"A","B","C","D","E","F","G"};
    m_PlayerContainer.reserve(playerNums);
    size_t p_count = 0;

    while(playerNums > p_count){

        Symbol charName = charset.at(p_count);
        m_PlayerContainer.emplace_back(std::make_unique<Player>(charName,*(m_Clock), *(m_IdGenerator), std::move(functors.at(p_count))));
        p_count++;

    }
    m_PlayerContainer.shrink_to_fit();
}

void Exchange::StartSimulation(){

    
    while(m_Clock->GetIterationCount() < m_Runs){

        
        

        m_Clock->CLK();
    }
}
