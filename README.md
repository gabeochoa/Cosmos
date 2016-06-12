<p align="center">
  <img src="https://raw.githubusercontent.com/gabeochoa/BBG-CMS/master/notes/cosmos.png">
</p>


**C**os**M**o**S** is an electronic platform for trading commodities<sup>[1]</sup>

Description
-----

Cosmos is focused on making it easy to find, buy, and sell commodities contracts. 

------

When it comes to commodities, the current systems are reserved for financial experts and professionals. 

Cosmos is changing that by allowing the general public to make their own decisions in the trillion dollar industry that is commodities. 

Commodities date back to ancient Sumer. Trade wasn't complicated back then, and it shouldn't be now.

Cosmos is here to fix that. 


<sup>[1] This program was build as a warmup exercise for Bloomberg's FT Training Program.</sup>

Build/Run
-----

```bash
#To Compile and Run the Base Program
make
./cms base < notes/test2.txt
#Cleanup
make clean
```
```bash
#To Run Extention 1
./cms ext1 [port-num]
```
In another shell

```bash
cd client
make
./client localhost [port-num] < notes/test2.txt
```

Extensions
-----

####Extension 1
Modify the trading system to accept communication over a TCP socket. The port to listen on will be supplied as a command line argument. It should only accept 1 connection, and terminate when that connection is closed.

####Extension 2

Modify the trading system to handle more than one connection concurrently. It should remain idle until the first connection. Once all connections have been closed then the program should terminate. 

Implementation
------

- [x] Base Program
- [x] Extension 1
- [ ] Extension 2

Design
-----
####File Layout

- client/
	- contains sample client application
- notes/
	- Contains notes and basic tests
- obj/
	- should be empty, contains .o's
- src/
	- contains code for 'server' application
- makefile
	- run 'make' to compile  









