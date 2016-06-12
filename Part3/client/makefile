COMPILER = g++
FLAGS = -std=c++11 -g -Wno-deprecated
OUTPUT_NAME = client
LDFLAGS := -I/usr/local/Cellar/boost/1.60.0_1/lib/ -lboost_system
CODE = client

all: $(CODE).o
	$(COMPILER) $(FLAGS) $(LDFLAGS) -o $(OUTPUT_NAME) $(CODE).o

$(CODE).o : $(CODE).cpp
	$(COMPILER) $(FLAGS) -c $(CODE).cpp

clean:
	rm -rf *.o *.gch $(OUTPUT_NAME)
