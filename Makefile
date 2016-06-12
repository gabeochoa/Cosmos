CC = clang++
CFLAGS := -std=c++11 -g
EXEC = cms
SRC_DIR = src
OBJ = obj/main.o obj/processor.o obj/parser.o obj/database.o

all:
	make clean
	make cms

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/processor.o: src/processor.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/parser.o: src/parser.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/database.o: src/database.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

clean:
	-rm -rf obj/*.o src/*.gch cms

run:
	./cms base < notes/testparser.txt

runport:	
	./cms ext1 1234
