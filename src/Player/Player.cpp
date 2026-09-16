
#include "Entity/Entity.h"
#include "Player.h"
#include "Aliases/Signal.h"
#include "Aliases/Order.h"
#include "System/Exchange/ExchangeData.h"
#include "System/IdGenerator/IdGenerator.h"

Player::Player(const Symbol& name
            , strategyFunction strategy
            , const Timer& timer
            , IdGenerator& generator)
            
    : Entity{name, 100000.00 , timer, generator}
    , m_Strategy{std::move(strategy)}

{  }



Player::~Player(){
    
}

void Player::PerformPerCLK(const ExchangeData& data){



}

Signal Player::StrategyAPI(const ExchangeData& data){

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