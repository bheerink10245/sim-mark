#pragma once

#include "Aliases/Aliases.h"
#include "Entity/Entity.h"
#include <functional>
#include <memory>



class Entity;
class Order;
class Ticker;
class TickerData;
class Signal;
using ModelFunction = std::function<Signal(const TickerData&)>;
class IdGenerator;
class Timer;
class TimeStamp;
using OrderPointer = std::shared_ptr<Order>;


class Maker : public Entity {

public:

    Maker(const Symbol& name
        , const Timer& timer
        , IdGenerator& generator
        , const TickerData& tickerData
        , ModelFunction strategy);

    Maker(const Maker&) = delete;
    void operator=(const Maker&) = delete;
    Maker(Maker&&) = delete;
    void operator=(Maker&&) = delete;
    ~Maker();

    void PerformPerCLK(const TickerData& ticker);
    Signal StrategyAPI(const TickerData& ticker);
    OrderPointer OrderBuild(Signal signal);


private:
    
    const TickerData& m_Ticker;
    ModelFunction m_Strategy;
    
};


