COMPILER = g++
FLAGS = -std=c++11 -g -Wno-deprecated
OUTPUT_NAME = client
CODE = client

all: $(CODE).o
	$(COMPILER) $(FLAGS) -o $(OUTPUT_NAME) $(CODE).o

$(CODE).o : $(CODE).cpp
	$(COMPILER) $(FLAGS) -c $(CODE).cpp

clean:
	rm -rf *.o *.gch $(OUTPUT_NAME)
