Gabriel Ochoa 

Cosmos
An electronic platform for trading commodities contracts

base program and extensions one and two implemented

Design:

All user input is passed through a recursive descent parser for validation and then gets passed to our singleton processor. 

The processor breaks down the commands and handles the interface with our 'database'.

While running, the database logs all output and passes it back up to the processor which in turn passes it back up for output to the user. 

no known bugs, but I have not idea how sound the socket stuff is, especially ext2 as its practically magic

#To Compile and Run the Base Program
mkdir build
cd build
cmake ..
make
./cms base < ../notes/test2.txt


#To Run Extention 1/2
./cms ext1 [port-num]
or
./cms ext2 [port-num]

In another shell
cd ../client
make
./client localhost [port-num] < ../notes/test2.txt

#Cleanup
cd ..
rm -rf build

**More Info in README.md**
