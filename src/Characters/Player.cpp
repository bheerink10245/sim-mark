#include "Entity.hpp"




class Player : public Entity {
public:
    template <typename Strategy>
    Player(Symbol name, Strategy strategy_function ) : m_Name{name}
    {}

    








private:

    Symbol m_Name;
    Price m_Capital {100000.00}; // 100 Thousand
    



};