
#include "Maker.h"

#include "../Entity/Entity.h"
#include "../Ticker/Ticker.h"
#include "../Ticker/TickerData.h"
#include "../Aliases/Signal.h"
#include "../Aliases/Order.h"
#include "../System/IdGenerator/IdGenerator.h"
#include "../System/Time/Timer.h"
#include "../System/Time/TimeStamp.h"


Maker::Maker(const Symbol& name
        , const Timer& timer
        , IdGenerator& generator
        , const TickerData& tickerData
        , ModelFunction strategy)

    : Entity{name, timer, generator, 10000000}
    , m_Ticker{tickerData}
    , m_Strategy{std::move(strategy)}
{ }

Maker::~Maker(){

}

void Maker::PerformPerCLK(const TickerData& ticker){

    Signal clk_signal = StrategyAPI(ticker);
    OrderPointer clk_build = OrderBuild(clk_signal);

    // Run against model for adjustive prices


}

Signal Maker::StrategyAPI(const TickerData& ticker){

    return m_Strategy(ticker); 
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


