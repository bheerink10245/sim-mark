#pragma once

#include "../../Aliases/Aliases.h"
#include "Exchange.h"

#include <vector>
#include <memory>
#include <expected>
#include <functional>


class Exchange;
class Ticker;
class Player;
using TickerContainer = std::vector<std::shared_ptr<Ticker>>;
using PlayerContainer = std::vector<std::unique_ptr<Player>>;

class ExchangeData {

public:

    ExchangeData() = delete;
    ExchangeData(const TickerContainer& tContainer);
    
    bool IsTickerExist(const Symbol& name);
    std::expected<Price, TickerError> GetTickerPrice(const Ticker& ticker);
    std::expected<Quantity, TickerError> GetTickerQuantity(const Ticker& ticker);
    std::expected<Quantity, TickerError> GetTickerVolume(const Ticker& ticker);

private:
    std::vector<std::shared_ptr<Ticker>> tempTicker; 

};