#pragma once

#include "Aliases.h"
#include "Exchange.h"


#include <unordered_map>
#include <vector>
#include <expected>
#include <stdexcept>
#include <functional>


class ExchangeData {

public:

    ExchangeData(const Exchange& exchange);
`
    std::expected<Ticker, std::invalid_arguement> FindSpecificTicker(const Symbol& name);
    const Ticker& GetSpecifcTicker(const Ticker& ticker);
    Price GetSpecficTickerPrice(const Symbol& tickerName);
    Quantity GetSpecificTickerQuantity(const Symbol& tickerName);
    Quantity GetSpecificTickerVolume(const Symbol& tickerName);

    
};