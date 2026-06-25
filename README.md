This is a simplified local exchange market. You initliaze the number of tickers # you want there to exist, the number of market makers can be custom or based off of the "optimal" amount based off Player and Ticker counter. Players are inintialize each withe their own strategy, which they use to "maximize" their profits. 

The goal of this project is NOT to create profitable/efficient trading strategies on the player or the efficiency of the market. 
Rather my project aims to optimize the efficiency of exchange communication and actions using the C++ 23 Concurrency Library. 

Source file "Main" contains the main function.
Outside of the main function:
|Create functors for each players unique strategy
|Other benchmarking stuff, etc.

In the main function:
Create a single exchange object contiang:
|Iinitialize the amount of Tickers you want to exist (they are all assigned random Tickers)
|Intiailize the amount of Market Makers, if you choose.
|Intialize the number of players with their unique strategy functor.
