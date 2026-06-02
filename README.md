

Premise:
  Have 1 "market maker" serialzing.
    6 different individuals acting as buyers & sellers.
    Each individual acts on its own best interest
    Random generator of ticker price fluctuation to create voltaility
    Track overall performance every T seconds of 6 indiv and market makers margin.

    pline: Random generator of tickers w/ price data -> port network bus with TCP -> orderbook tracks synchronous data in vectors. 
  -> random generator of buyers and sellers --> matching bids & asks.


Structure:
  .hpp Class Asset
    virtual double priceinitilization() // initializes the original rpice
    virtual doulble priceFluc() // quantifid change in price 
    
    
  Class Orderbook
  Class Entity 
   Class MarketMaker : public Entity
   Class Individual : public Entity


  
    
