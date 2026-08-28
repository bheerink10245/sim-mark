
#include "ExchangeData.h"

#include "ExchangeData.h"

std::expected<std::reference_wrapper<const Ticker>, std::invalid_argument> ExchangeData::GetTickerObject(const Symbol& tickerSymbol) const {
    auto it = m_TickerContainer->find(tickerSymbol);
    if (it == m_TickerContainer->end()) {
        return std::unexpected(std::invalid_argument("Ticker not found for given symbol"));
    }
    return std::cref(it->first);
}