#pragma once

#include "Aliases/Aliases.h"
#include <functional>
#include <memory>
#include <string>


using ModelFunction = std::function<Signal(const TickerData&)>;

class Entity;

class Order;
class Ticker;
class TickerData;
class Signal;
class IdGenerator;
class Timer;
class TimeStamp;



class Maker : public Entity {

public:

    Maker(const Symbol& name
        , const TickerData& tickerData
        , ModelFunction strategy
        , std::shared_ptr<const Timer> timer
        , IdGenerator generator);

    Maker(const Maker&) = delete;
    Maker& operator=(const Maker&) = delete;
    Maker(Maker&&) = delete;
    Maker& operator=(Maker&&) = delete;
    ~Maker();

    void PerformPerCLK(Ticker ticker);

    static Signal StrategyAPI(Ticker ticker){


    }

    OrderPointer OrderBuild(Signal signal){
        if(signal.GetSignalValidity() == false) { return nullptr;}
        

        OrderType type;
        OrderId ID;
        Side side;
        Price price;
        Quantity quantity;
        ActionFunction action;


        return std::make_shared<Order>(type, ID, side, price, quantity, action);
        
    } 


private:

    const TickerData& m_Ticker;
    ModelFunction m_Strategy;
};


