#pragma once

#include "Aliases/Aliases.h"
#include "Entity/Entity.h"
#include <functional>
#include <memory>

using strategyFunction = std::function<Signal(const ExchangeData&)>;

class Entity;
class Signal;
class Order;
class ExchangeData;
class IdGenerator;




class Player : public Entity {
    
public:

    Player(const Symbol& name
            , strategyFunction strategy
            , const Timer& timer
            , IdGenerator& generator);
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player&& operator=(Player&&) = delete;
    ~Player();

    void PerformPerCLK(const ExchangeData& data);
    Signal StrategyAPI(const ExchangeData& data);
    OrderPointer OrderBuild(Signal signal);

        
    


private:

    strategyFunction m_Strategy;

};

