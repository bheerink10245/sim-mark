#pragma once

#include "Aliases/Aliases.h"


#include <unordered_map>
#include <vector>
#include <expected>
#include <stdexcept>
#include <functional>


class Exchange;
class Ticker;
class Player;


class ExchangeData {

public:

    ExchangeData(const Exchange& exchange);
    
    bool IsTickerExist(const Symbol& name);
    const Ticker& GetTicker(const Ticker& ticker);
    Price GetTickerPrice(const Ticker& ticker);
    Quantity GetTickerQuantity(const Ticker& ticker);
    Quantity GetTickerVolume(const Ticker& ticker);
private:

    std::unordered_map<Symbol, std::shared_ptr<Ticker>> m_TickerContainer;
    std::unordered_map<Symbol, std::unique_ptr<Player>> m_PlayerContainer

};