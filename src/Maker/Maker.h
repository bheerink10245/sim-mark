#pragma once

#include "Aliases/Aliases.h"
#include "Entity/Entity.h"
#include <functional>
#include <memory>


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
        , const Timer& timer
        , IdGenerator& generator);

    Maker(const Maker&) = delete;
    Maker& operator=(const Maker&) = delete;
    Maker(const Maker&&) = delete;
    Maker&& operator=(const Maker&&) = delete;
    ~Maker();

    void PerformPerCLK(const TickerData& ticker);
    Signal StrategyAPI(const TickerData& ticker);
    OrderPointer OrderBuild(Signal signal);


private:
    
    const TickerData& m_Ticker;
    ModelFunction m_Strategy;
};


