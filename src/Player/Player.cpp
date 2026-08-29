
#include "Player.h"


Player::Player(const Symbol& name, strategyFunction strategy)
    : Entity{name, 100000.00}
    , m_Strategy{std::move(strategy)}

{ }


Player::~Player(){
    
}

void Player::PerformPerCLK(const ExchangeData& Data){



}

