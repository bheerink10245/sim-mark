
#include "Aliases.h"
#include "ExchangeData.h"






bool ExchangeData::IsTickerExist(const Symbol& name){

    if(!(m_TickerContainer.contains(name)) ){
        return false;
    }
    auto keyValue = m_TickerContainer.find(name);
    if (keyValue != m_TickerContainer.end()){
        return true;
    }
    return false;
}

const Ticker& ExchangeData::GetTicker(const Ticker& ticker){
    if(!IsTickerExist(ticker.m_Name));

}

Price ExchangeData::GetTickerPrice(const Ticker& ticker){
    return ticker.GetTickerPrice();
}

Quantity ExchangeData::GetTickerQuantity(const Ticker& ticker){
    return ticker.GetTickerQuantity();
}

Quantity ExchangeData::GetTickerVolume(const Ticker& ticker){
    return ticker.GetTickerVolume();
}