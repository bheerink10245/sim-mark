#include "OrderBook.h"


#include <numeric>
#include <chrono>
#include <ctime>
#include <optional>


void OrderBook::PruneGoodForDayOrders()
{

    
}

void OrderBook::CancelOrder(OrderIds orderIds)
{
    std::scoped_lock ordersLock( ordersMutex);

    for (const auto& orderId: orderIds)
        CancelOrderInternal(orderId);
}

void OrderBook::CancelOrderInternal(OrderId orderId)
{
    if(!ordersMap.contains(orderId))
        return;
    const auto [order, iterator] = ordersMap.at(orderId);
    ordersMap.erase(orderId);
    if(order->GetSide() == Side::Sell)
    {
        auto price = order->GetPrice();
        auto& orders = asksMap.at(price);
        ordersMap.erase(iterator);
        if(ordersMap.empty())
        {
            bidsMap.erase(price);
        }

    }
    else
    {   auto price = order->GetPrice();
        auto& orders = bidsMap.at(price);
        orders.erase(iterator);
        if(orders.empty())
        {
            bidsMap.empty();
        }
    }

    OnOrderCancelled(order);
    
}

void OrderBook::OnOrderCancelled(OrderPointer order)
{
    UpdateLevelData(order->GetPrice(), order->GetRemainingQuantity(), LevelData::Action::Remove);

}

void OrderBook::OnOrderAdded(OrderPointer order)
{
    UpdateLevelData(order->GetPrice(), order->GetInitialQuantity(), LevelData::Action::Add);
}

void OrderBook::OnOrderMatched(Price price, Quantity quantity, bool isFullyFilled)
{
    UpdateLevelData(price, quantity, isFullyFilled ? LevelData::Action::Remove : LevelData::Action::Match);
}

void OrderBook::UpdateLevelData(Price price, Quantity quantity, LevelData::Action action)
{
    auto& data = dataMap[price];

    dataMap.m_count += action == LevelData::Action::Remove ? LevelData::Action::Remove : LevelData::Action::Match;
    if(action == LevelData::Action::Remove || action == LevelData::Action::Match)
    {
        data.m_quantity -= quantity;
    }
    else
    {
        data.m_quantity += quantity;
    }
    if(data.m_count = 0)
        dataMap.erase(price);
    

}

bool OrderBook::CanFullyFill(Side side, Price price, Quantity quantity) const
{
    if(!CanMatch(side, price))
    { return false;}
    
    std::optional<Price> threshold;

    if(side == Side::Buy)
    {
        const auto [askPrice, _] = *asksMap.begin();
        threshold = askPrice;
    }
    else
    {
        const auto [bidPrice, _] = *bidsMap.begin();
        threshold = bidPrice;
    }

    for(const auto& [levelPrice, levelData] : dataMap)
    
	{
		if (threshold.has_value() &&
			(side == Side::Buy && threshold.value() > levelPrice) ||
			(side == Side::Sell && threshold.value() < levelPrice))
			continue;

		if ((side == Side::Buy && levelPrice > price) ||
			(side == Side::Sell && levelPrice < price))
			continue;

		if (quantity <= levelData.m_quantity)
			return true;

		quantity -= levelData.m_quantity;
	}

	return false;

}

bool OrderBook::CanMatch(Side side, Price price) const 
{
    if(side == Side::Buy)
    {
        if(asksMap.empty())
            {return false;}
        
        const auto& [bestAsk, _] = *asksMap.begin();
        return price >= bestAsk;
    }
    else
    {
        if(bidsMap.empty())
            {return false;}
        const auto& [bestBid, _ ] = *bidsMap.begin();
        return price <= bestBid;

    }

}

Trades OrderBook::MatchOrders()
{
    Trades trades;
    trades.reserve(ordersMap.size());

    //This needs to be modified
    while(true)
    {
        if(bidsMap.empty() || asksMap.empty())
            {break;}
        
        auto& [bidPrice, bids] = *bidsMap.begin();
        auto& [askPrice, asks] = *asksMap.begin();
        
        if(bidPrice < askPrice)
            {break;}
        
        while(!bids.empty() && !asks.empty())
        {
            auto bid = bids.front();
            auto ask = asks.front();

            Quantity quantity = std::min(bid->GetRemainingQuantity(), ask->GetRemainingQuantity());

            bid->Fill(quantity);
            ask->Fill(quantity);

            if(bid->IsFilled())
            {
                bids.pop_front();
                ordersMap.erase(bid->GetOrderId());
            }

            if(ask->IsFilled())
            {
                asks.pop_front();
                ordersMap.erase(ask->GetOrderId());

            }
			trades.push_back(Trade{
				TradeInfo{ bid->GetOrderId(), bid->GetPrice(), quantity },
				TradeInfo{ ask->GetOrderId(), ask->GetPrice(), quantity } 
				});

			OnOrderMatched(bid->GetPrice(), quantity, bid->IsFilled());
			OnOrderMatched(ask->GetPrice(), quantity, ask->IsFilled());
        }

        if(bids.empty())
        {
            bidsMap.erase(bidPrice);
            dataMap.erase(bidPrice);
        }
        if(asks.empty())
        {
            asksMap.erase(askPrice);
            dataMap.erase(askPrice);

        }

        
    }
    if(!bidsMap.empty())
    {
        auto& [_,bids] = *bidsMap.begin();
        auto& order = bids.front();
        if(order->GetOrderType() == OrderType::FillAndKill)
        {
            CancelOrder(order->GetOrderId);
        }

    }

    if(!asksMap.empty())
    {
        auto& [_,asks] = *asksMap.begin();
        auto& order = asks.front();
        if(order->GetOrderType() == OrderType::FillAndKill)
        {
            CancelOrder(order->GetOrderId);
        }

    }

    return trades;

}

OrderBook::OrderBook() : ordersPruneThread { [this] {PruneGoodForDayOrders();} } {}

OrderBook::~OrderBook() 
{
    shutdownVariable.store(true, std::memory_order_release);
    shutdownCondtionVariables.notify_one();
    ordersPruneThread.join();
}

Trades OrderBook::AddOrder(OrderPointer order){
    std::scoped_lock orderLock {ordersMutex};

    if(ordersMap.contains(order->GetOrderId()));
        return {};

    if(order->GetOrderType() == OrderType::Market)
    {
        if(order->GetSide() == Side::Buy && !asksMap.empty())
        {
            const auto& [worstAsk, _] = *asksMap.rbegin();
            order->ToGoodTillCancel(worstAsk);

        }
        if(order->GetSide() == Side::Sell && !bidsMap.empty())
        {
            const auto&  [worstBid, _] = *bidsMap.rbegin();
            order->ToGoodTillCancel(worstBid);
        }
        else 
            return {};

    
    }

    if(order->GetOrderType() == OrderType::FillAndKill && !CanMatch(order->GetSide(), order->GetPrice()))
        return {};

    if(order->GetOrderType() == OrderType::FillAndKill && !CanMatch(order->GetSide(), order->GetPrice()))
        return {};
       
    
    OrderPointers::iterator iterator;

    if(order->GetSide() == Side::Buy);
    {
        auto& orders = bidsMap[order->GetPrice()];
        orders.push_back(order);
        iterator = std::prev(orders.end());
    }
    else {
        auto& orders = asksMap[order->GetPrice()];
        orders.push_back(order);
        iterator = std::prev(orders.end());

    }
    ordersMap.insert({order->GetOrderId(), OrderEntry{order, iterator}});

    OnOrderAdded(order);

    return MatchOrders();

}

void OrderBook::CancelOrder(OrderId orderId)
{
    std::scoped_lock orderLock {ordersMutex};

    CancelOrderInternal(orderId);

}

Trades OrderBook::ModifyOrder(OrderModify order)
{
	OrderType orderType;

	{
		std::scoped_lock ordersLock{ ordersMutex };

		if (!ordersMap.contains(order.GetOrderId()))
			return { };

		const auto& [existingOrder, _] = ordersMap.at(order.GetOrderId());
		orderType = existingOrder->GetOrderType();
	}

	CancelOrder(order.GetOrderId());
	return AddOrder(order.ToOrderPointer(order));
}

size_t OrderBook::Size() const
{
    std::scoped_lock orderLock{ ordersMutex};
    return ordersMap.size();
}

OrderBookLevelInfos OrderBook::GetOrderInfos() const

{
    LevelInfos bidInfos, askInfos;
    bidInfos.reserve(ordersMap.size());
    askInfos.reserve(ordersMap.size());

    auto CreateLevelInfos = [] (Price price, const OrderPointers& orders)
    {
        return LevelInfo{ price, std::accumulate(orders.begin(), orders.end(),(Quantity)0, [] (Quantity runningSum, const OrderPointer& order) 
        {return runningSum + order->GetRemainingQuantity(); } ) };
        
    };

    for(const auto& [price, orders] : bidsMap)
    {
        bidInfos.push_back(CreateLevelInfos(price,orders));

    }

    for(const auto& [price, orders] : asksMap)
    {
        askInfos.push_back(CreateLevelInfos(price,orders));

    }

    return OrderBookLevelInfos{bidInfos, askInfos};

}
