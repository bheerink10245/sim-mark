
#include "Maker.h"

#include "Entity/Entity.h"
#include "Ticker/Ticker.h"
#include "Ticker/TickerData.h"
#include "Aliases/Signal.h"
#include "System/IdGenerator/IdGenerator.h"
#include "System/Time/Timer.h"
#include "System/Time/TimeStamp.h"


Maker::Maker(const Symbol& name
    , const TickerData& tickerData
    , ModelFunction strategy
    , const Timer& timer
    , IdGenerator& generator)

    : Entity{name, 1000000.00 , timer, generator}
    , m_Strategy{std::move(strategy)}
    , m_Ticker{tickerData}

{ }

Maker::~Maker(){

}

void Maker::PerformPerCLK(const TickerData& ticker){

    // Process Exchange Data
    // Run against model for adjustive prices


}

Signal Maker::StrategyAPI(const TickerData& ticker){


}

OrderPointer Maker::OrderBuild(Signal signal){
    
    if(signal.GetSignalValidity() == false) { return nullptr;}
    

    OrderType type;
    OrderId ID;
    Side side;
    Price price;
    Quantity quantity;
    ActionFunction action;


    return std::make_shared<Order>(type, ID, side, price, quantity, action);
        
} 


