#pragma once

#include "../../Aliases/Aliases.h"

#include <set>
#include <memory>
#include <thread> 
#include <random>
#include <string>
#include <queue> 
#include <vector>
#include <functional>


class ExchangeData;
class IdGenerator;
class Player;
class Ticker;
class Signal;
class Timer;
class TimeStamp;
using strategyFunction = std::function<Signal(const ExchangeData&)>;


class Exchange{

public:

    
    Exchange(const uint64_t& runs);
    Exchange(const Exchange&) = delete;
    Exchange& operator=(const Exchange&) = delete;
    Exchange(Exchange&&) = delete;
    Exchange& operator=(Exchange&&) = delete;
    ~Exchange();


    ExchangeData GenerateExchangeData();

    /**
     * 
     * @overview:Ticker number is machine based off of Processor arch
     * My Machine: Intel i7-14700K (20 Cores, 28 LPs)
     * @purpose: initlaizes all tickers and thei respective liquidity. Constructs into object m_TickerContainer
     * @param: tickerNums, number of tickers you want to create
     */
    void TickerInit(uint8_t tickerNums);
    /**
     * @overiew: Creates players and their unique strategy functors
     * Players are initalized as" Player: "A", "B", "C"... etc.
     * @purpose:Initliazes all the Players 
     * @param: numbers of plays you want in simulation
     * @param: vector containing all the strategy functions
     */
    void PlayerInit(uint32_t playerNums, std::vector<strategyFunction> functors);

    void StartSimulation();




private:

    //INTERFACEs
    uint64_t m_Runs;

    //DEPENDNCIES
    std::shared_ptr<Timer> m_Clock;
    std::shared_ptr<IdGenerator> m_IdGenerator;
    
    //INITALIZATIONS
    std::vector<Player> m_TickerContainer;
    std::vector<Player> m_PlayerContainer;
    
    std::vector<std::thread> m_Threads;
};

