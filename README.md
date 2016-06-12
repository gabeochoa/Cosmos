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









