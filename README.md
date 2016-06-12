<p align="center">
  <img src="https://raw.githubusercontent.com/gabeochoa/BBG-CMS/master/notes/cosmos.png">
</p>


#**C**os**M**o**S**

Description
-----

Your task is to create an electronic platform for trading commodities contracts. This platform will allow dealers to list the contracts they have available to buy or sell (we shall refer to this as posting orders) and allow other dealers to trade these orders (we shall refer to this as aggressing on orders). The system will allow dealers to modify and revoke their orders, and will also allow querying of available orders. 

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









