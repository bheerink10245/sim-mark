
#include "../Entity/Entity.h"
#include "Player.h"
#include "../Aliases/Signal.h"
#include "../Aliases/Order.h"
#include "../System/Exchange/ExchangeData.h"
#include "../System/IdGenerator/IdGenerator.h"

Player::Player(const Symbol& name
        , const Timer& timer
        , IdGenerator& generator
        , strategyFunction strategy)   
          
    : Entity{name , timer, generator, 1000000}
    , m_Strategy{std::move(strategy)}

{  }



Player::~Player(){
    
}

void Player::PerformPerCLK(const ExchangeData& data){

    Signal clk_signal = StrategyAPI(data);
    OrderPointer clk_build = OrderBuild(clk_signal);

}

Signal Player::StrategyAPI(const ExchangeData& data){
    return m_Strategy(data);
}

OrderPointer Player::OrderBuild(Signal signal){
    
    if(signal.GetSignalValidity() == false) { return nullptr;}
    

    OrderType type;
    OrderId ID;
    Side side;
    Price price;
    Quantity quantity;
    ActionFunction action;


    return std::make_shared<Order>(type, ID, side, price, quantity, action);
        
} 