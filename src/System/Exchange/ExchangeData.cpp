
#include "ExchangeData.h"


std::expected<Ticker, std::invalid_arguement> ExchangeData::FindSpecificTicker(const Symbol& name){

    if(!(*m_TickerContainer).contains(name)){
        return std::invalid_arguement("Ticker: " name " does not exist in exchange.");
    }

    auto keyValue = (*m_TickerContainer)->find(name);
    if(keyValue != (*m_TickerContainer)->end()){
        return keyValue->second;
    }
}

const Ticker& ExchangeData::GetSpecifcTicker(const Symbol& name );
