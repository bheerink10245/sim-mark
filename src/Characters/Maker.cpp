#include "Entity.hpp"
#include "OrderBook/Orderbook.cpp"

class Maker : public Entity {
public:

    /** 
     * 
     * Market maker has a complicated structure.
     * Each instance of a MarketMaker should own its own Orderbook.
     * APIs from the OrderBook follow:
     * OrderBook --> Maker --> Exchange --> Indviduals
     * Porting features from 
     * 
     * 
     * 
     */
    Maker(Price capital, Symbol name) : m_Capital{capital}, m_Name{name}
    {
    m_OrderBook = new Orderbook::OrderBook;



    }

    
    


private:
    Price m_Capital;
    Symbol m_Name;
    Orderbook::OrderBook* m_OrderBook;


};