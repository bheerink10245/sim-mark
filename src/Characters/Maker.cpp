#include "Entity.hpp"
#include "OrderBook/Orderbook.cpp"

class Maker : public Entity {
public:

    /** 
     * Market maker has a complicated structure.
     * Each instance of a MarketMaker should own its own Orderbook.
     * APIs from the OrderBook follow:
     * OrderBook --> Maker --> Exchange --> Indviduals
     * Porting features from 
     * 
     * 
     * 
     */
    Maker(Price capital) : m_Capital{capital}
    {
        m_OrderBook = new Orderbook::OrderBook;
    }

    
    


private:
    Price m_Capital;
    Orderbook::OrderBook* m_OrderBook;


};