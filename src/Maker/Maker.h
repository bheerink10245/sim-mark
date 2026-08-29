#pragma once

#include "Aliases.h"
#include "System/Time/Timer.h"
#include "System/Exchange/Exchange.h"
#include "Entity/Entity.h"

#include <map>
#include <cmath>


using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using TradeInfo = Aliases::TradeInfo;
using ModelFunction = std::function<Signal(Ticker ticker)>;



class Maker : public Entity {

public:

    Maker(const Symbol& name, const Ticker* ticker, ModelFunction strategy);
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

    Ticker* m_OwningTicker;
    ModelFunction m_Strategy;
};


/**
 * INHERITED:
 *  Symbol m_Name;
    std::unique_ptr<std::map<TimeStamp, OrderId, std::greater<OrderId>>> m_TradeLog;
    std::unique_ptr<std::map<TimeStamp, OrderId, std::greater<OrderId>>> m_OrderLog;
    strategyFunction m_Strategy;
    Price m_InitCapital;
    Price m_RemainingCapital;
 */