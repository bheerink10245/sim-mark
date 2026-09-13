#pragma once

#include <cstdint>

using Price = std::int32_t;

enum class Side;

class Signal {
private:

    bool m_Valid;
    Side m_SignalSide;    
    Price m_SignalPrice;

public:

    Signal(bool validity, Side orderside, Price sigprice);
    

    bool GetSignalValidity() const;
    Side GetSignalSide() const;
    Price GetSignaPrice() const;

};