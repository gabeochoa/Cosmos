<p align="center">
  <img src="http://ochoag.com/cosmos/img/logo.png">
</p>

**C**os**M**o**S** is an electronic platform for trading commodities<sup>[1]</sup>

Description
-----

Cosmos is focused on making it easy to find and trade commodities. 

------

When it comes to commodities, only financial experts and professionals can participate. **Cosmos** is changing that, by allowing anyone to trade in this trillion dollar industry. 

Commodities date back to ancient Sumer. Trade wasn't complicated back **then**, and it shouldn't be **now**.


####**Cosmos** is here to fix that. 


<sup>[1] This program was built as a warmup exercise for Bloomberg's FT Training Program. ie. not real</sup>

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

File Layout
-----

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









