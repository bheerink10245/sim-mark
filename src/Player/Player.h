#pragma once

#include "Aliases/Aliases.h"

#include <functional>
#include <memory>

using strategyFunction = std::functional<Signal(const ExchangeData&)>;

class Entity;
class Signal;
class Order;
class ExchangeData;
class IdGenerator;




class Player : public Entity {
    
public:

    Player(const Symbol& name, strategyFunction strategy);
    Player(const Player&) = delete;
    Player& operator=(const Player&) = delete;
    Player(Player&&) = delete;
    Player& operator=(Player&&) = delete;
    ~Player();

    void PerformPerCLK(const ExchangeData& Data);

    static Signal StrategyAPI(const ExchangeData& data){


    }

    OrderPointer OrderBuild(Signal signal , IdGenerator& id_gen){
        if(signal.GetSignalValidity() == false) { return nullptr;}
        
        OrderType type;
        OrderId ID = id_gen.GenerateId();
        Side side = signal.GetSignalSide();
        Price price;
        Quantity quantity;
        ActionFunction action;

        return std::make_shared<Order>(type, ID, side, price, quantity, action);
        
    } 



private:

    strategyFunction m_Strategy;

};

