#include "Signal.h"




Signal::Signal(bool validity, Side orderside, Price sigprice)
: m_Valid{validity}
, m_SignalSide{orderside}
, m_SignalPrice{sigprice} 

{ }

bool Signal::GetSignalValidity() const {return m_Valid;}
Side Signal::GetSignalSide() const {return m_SignalSide;}
Price Signal::GetSignaPrice() const {return m_SignalPrice;}


