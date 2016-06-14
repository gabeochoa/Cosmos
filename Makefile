CC = clang++
CFLAGS := -std=c++11 -g -Wall -Wextra -Werror -Wpedantic
EXEC = cms
SRC_DIR = src
OBJ = obj/main.o obj/processor.o obj/parser.o obj/database.o

TESTEXEC = tests
TEST_DIR = test
GTEST_DIR = ~/googletest-release-1.7.0
TESTLINK = -lgtest
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h


all: $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

obj/main.o: src/main.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/processor.o: src/processor.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/parser.o: src/parser.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

obj/database.o: src/database.cpp
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TESTEXEC)
	
TEST_OBJECTS = test_parser.o

test_parser.o: $(TEST_DIR)/test_parser.cpp
	$(CC) $(TESTFLAGS) $(CFLAGS) -c $(TEST_DIR)/test_parser.cpp -o $@

$(TESTEXEC): $(TEST_OBJECTS) $(OBJS)
	$(CC) $(CFLAGS) $(TESTLINK) $^ -o $@

clean:
	-rm -rf obj/*.o src/*.gch cms

run:
	./cms base < notes/testparser.txt

runport:	
	./cms ext1 1234
