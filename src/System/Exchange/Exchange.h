#include "Aliases.h"
#include "Time/Timer.h"
#include "Maker/Maker.h"
#include "Player/Player.h"
#include "Ticker/Ticker.h"
#include "ExchangeData.h"

#include <thread> 
#include <random>
#include <string>
#include <queue> 
#include <vector>
#include <functional>

using strategyFunction = Aliases::strategyFunction;

class Exchange{
public:
    Exchange(const uint64_t& RUNS);


    void TickerInit(uint32_t tickerNums);
    void PlayerInit(uint32_t playerNums, const std::vector<strategyFunction> functors);
    void Start();

    



private:

    uint64_t m_Runs;
    std::unique_ptr<Timer> m_Clock;
    std::shared_ptr<std::unordered_map<Ticker, std::vector<Maker>, TickerHash, TickerEqual>> m_TickerContainer;
    std::shared_ptr<std::vector<Player>> m_PlayerContainer;
    
};

