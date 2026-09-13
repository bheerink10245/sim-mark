
#include "Entity/Entity.h"
#include "Player.h"
#include "Aliases/Signal.h"
#include "Aliases/Order.h"
#include "System/Exchange/ExchangeData.h"
#include "System/IdGenerator/IdGenerator.h"

Player::Player(const Symbol& name, strategyFunction strategy)
    : Entity{name, 100000.00}
    , m_Strategy{std::move(strategy)}

{ }


Player::~Player(){
    
}

void Player::PerformPerCLK(const ExchangeData& Data){



}

