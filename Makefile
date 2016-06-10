CC = clang++
CFLAGS := -std=c++11 -g 
EXEC = cms
SRC_DIR = src
OBJ = obj/main.o obj/processor.o obj/database.o

all: 
	make clean
	make cms

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $@ $<

obj/processor.o: src/processor.cpp
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $@ $<

obj/database.o: src/database.cpp
	$(CC) $(CFLAGS) $(CFLAGS) -c -o $@ $<

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXEC)

clean:
	-rm -rf obj/*.o cms

run:
	./cms base < foldertest/testparser.txt 