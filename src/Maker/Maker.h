#include "Aliases.h"
#include "System/Time/Timer.h"
#include "System/Exchange/Exchange.h"
#include "Entity/Entity.h"

#include <map>
#include <cmath>


using Price = Aliases::Price;
using Quantity = Aliases::Quantity;
using OrderId = Aliases::OrderId;
using Symbol = Aliases::Symbol;
using Side = Aliases::Side;
using Order = Aliases::Order;
using TradeInfo = Aliases::TradeInfo;


class Maker : public Entity{
public:


    Maker(const Symbol& name);
    Maker(const Maker&) = delete;
    void operator=(const Maker&) = delete;
    Maker(Maker&&) = delete;
    void operator=(Maker&&) = delete;
    ~Maker();

    void PerformPerCLK(const ExchangeData& Data) override;

    static Signal SignalBuilder(const Ticker& ticker);

};