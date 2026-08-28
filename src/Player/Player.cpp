
#include "Player.h"


Player::Player(const Symbol& name, strategyFunction strategy)
    : m_Name(name), m_Strategy(std::move(strategy))
{}

Player::~Player(){
    
}

void Player::PerformPerCLK(const ExchangeData& Data){
    Signal returnSig = m_Strategy(Data);
}

