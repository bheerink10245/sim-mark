
#include "src/System/Exchange/Exchange.h"

#include <vector>
#include <functional>

int main() {

    std::vector<std::function<Signal(const ExchangeData&)>> PLAYER_FUNCTIONS;

    //------------ DECLARE ALL STRATEGY FUNCTIONS HERE ----------- // 











    // -----------SET ALL ENTITY NUBMERS -----------------------------//
    size_t Ticker_Number = 8;
    size_t Player_Number = 4;
    uint64_t EXCHANGE_RUNS = 10000000000000000; 

    
    Exchange* EXCHANGE = new Exchange(EXCHANGE_RUNS);

    EXCHANGE->TickerInit(Ticker_Number);
    EXCHANGE->PlayerInit(Player_Number, PLAYER_FUNCTIONS);


    EXCHANGE->StartSimulation();


}