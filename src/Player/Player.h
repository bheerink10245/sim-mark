#include "Aliases.h"
#include "Entity/Entity.h"
#include "Exchange/ExchangeData.h"

#include <functional>

using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using TradeInfo = Aliases::TradeInfo;
using Signal = Aliases::Signal;
using strategyFuntion = Aliases::strategyFunction;



class Player : public Entity {
    
public:

    Player(const Symbol& name, strategyFunction strategy);
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;
    ~Player();

    void PerformPerCLK(const ExchangeData& Data);


private:
    Symbol m_Name;
    strategyFunction m_Strategy;
};