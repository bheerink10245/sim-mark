
#include "Orderbook.cpp"
#include "Entity.hpp"


class Maker : public Entity {
public:

    Maker(const Symbol& name, const std::vector<Symbol>& Service_Tickers) : m_Name{name} 
    {
        
    }



    
    


private:
    Price m_Capital {1000000000.00};// 10 million 
    Symbol m_Name;


};