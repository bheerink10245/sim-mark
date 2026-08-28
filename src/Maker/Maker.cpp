
#include "Maker.h"


Maker::Maker(const Symbol& name) : m_Name{name}, m_InitCapital{10000000.00}{


}

Maker::~Maker(){

}

void Maker::PerformPerCLK(const ExchangeData& Data){

    // Process Exchange Data
    // Run against model for adjustive prices


}


static Signal Maker::SignalBuilder(const Ticker& ticker){
    
}
