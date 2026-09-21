#pragma once

#include "../Aliases/Aliases.h"

#include <functional>
#include <memory>


class Entity;
class Signal;
class Order;
using OrderPointer = std::shared_ptr<Order>;
class ExchangeData;
class IdGenerator;
using strategyFunction = std::function<Signal(const ExchangeData&)>;





class Player : public Entity {
    
public:

    Player(const Symbol& name
        , const Timer& timer
        , IdGenerator& generator
        , strategyFunction strategy);
        
    Player(const Player&) = delete;
    void operator=(const Player&) = delete;
    Player(Player&&) = delete;
    void operator=(Player&&) = delete;
    ~Player();

    void PerformPerCLK(const ExchangeData& data);
    Signal StrategyAPI(const ExchangeData& data);
    OrderPointer OrderBuild(Signal signal);

        
    


private:

    strategyFunction m_Strategy;

};

