#pragma once

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

    static Signal StrategyAPI(const ExchangeData& data){


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

    strategyFunction m_Strategy;

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