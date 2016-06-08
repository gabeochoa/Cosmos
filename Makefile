CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := 
CC_FLAGS := -std=c++11 -g 

main.exe: $(OBJ_FILES)
	clang++ $(LD_FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	clang++ $(CC_FLAGS) -c -o $@ $<

clean:
	rm obj/*.o main.exe
