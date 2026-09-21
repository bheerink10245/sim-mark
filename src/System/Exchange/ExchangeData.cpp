


#include "../../Aliases/Aliases.h"
#include "../../Ticker/Ticker.h"
#include "ExchangeData.h"

#include <algorithm>



ExchangeData::ExchangeData(const TickerContainer& tContainer)
    : tempTicker{tContainer}
{ } 


// IMPLEMENT LATER
bool ExchangeData::IsTickerExist(const Symbol& name){
    if(name == "X"){
    return true;}
    return false;
}


std::expected<Price, TickerError> ExchangeData::GetTickerPrice(const Ticker& ticker){
    if(!IsTickerExist(ticker.GetName())){
       return std::unexpected(TickerError::Invalid);
    }
    return ticker.GetTickerPrice();
}

std::expected<Quantity, TickerError> ExchangeData::GetTickerQuantity(const Ticker& ticker){
    if(!IsTickerExist(ticker.GetName())){
       return std::unexpected(TickerError::Invalid);
    }
    return ticker.GetTickerQuantity();
}

std::expected<Quantity, TickerError> ExchangeData::GetTickerVolume(const Ticker& ticker){
    if(!IsTickerExist(ticker.GetName())){
       return std::unexpected(TickerError::Invalid);
    }
    return ticker.GetTickerVolume();
}

