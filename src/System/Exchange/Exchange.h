#pragma once

#include "Aliases.h"
#include "Time/Timer.h"
#include "Maker/Maker.h"
#include "Player/Player.h"
#include "Ticker/Ticker.h"
#include "ExchangeData.h"
#include "IdGenerator.h"

#include <unordered_map>
#include <thread> 
#include <random>
#include <string>
#include <queue> 
#include <vector>
#include <functional>

using strategyFunction = Aliases::strategyFunction;

class Exchange{

public:


    Exchange(const Exchange&) = delete;
    Exchange& operator=(const Exchange&) = delete;
    Exchange(Exchange&&) = delete;
    Exchange& operator=(Exchange&&) = delete;
    ~Exchange();

    Exchange(const uint64_t& runs);

    /**
     * @purpose: initilaize exchange dependencies
     */
    void DependencyInits();
    /**
     * 
     * @overview:Ticker number is machine based off of Processor arch
     * My Machine: Intel i7-14700K (20 Cores, 28 LP)
     * Based off my machine the most Tickers i should use is 8
     * TickerInit initializes a ticker from of name "A"
     * 2 makers to provide liquidity: "A1",  "A2"
     * @purpose: initlaizes all tickers and their respective liquidity. Constructs into object m_TickerContainer
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

    uint64_t m_Runs;
    std::unique_ptr<Timer> m_Clock;
    std::shared_ptr<std::unordered_map<Symbol, std::shared_ptr<Ticker>>> m_TickerContainerPtr;
    std::shared_ptr<std::unordered_map<Symbol, std::unique_ptr<Player>>> m_PlayerContainerPtr;
    std::shared_ptr<IdGenerator> m_IdGenerator;
    
};

