#pragma once

#include "Aliases.h"
#include "Exchange.h"


#include <unordered_map>
#include <vector>
#include <expected>
#include <stdexcept>
#include <functional>


class ExchangeData {


    ExchangeData(const Exchange& exchange);

    
    std::expected<std::reference_wrapper<const Ticker>, std::invalid_argument> GetTickerObject(const Symbol& tickerSymbol) const;
    

    
    
};