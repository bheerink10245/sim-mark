
#include "Maker.h"




Maker::Maker(const Symbol& name, const Ticker* ticker, ModelFunction strategy)
    : Entity{name, 1000000.00}
    , m_Strategy{std::move(strategy)}
    , m_OwningTicker{ticker}

{ }

Maker::~Maker(){

    delete m_OwningTicker;
}



void Maker::PerformPerCLK(Ticker ticker){

    // Process Exchange Data
    // Run against model for adjustive prices


}


