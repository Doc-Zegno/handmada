INCLUDE_DIRS = include $(wildcard include/**) \
	include/util/prefab include/misc/literal
INCLUDE = $(addprefix -I, $(INCLUDE_DIRS))

CC = g++
FLAGS = -Wall -Werror -std=gnu++11 --coverage
DEPFLAGS = -MMD -MP
LIB = -lpthread -pthread lib/gtest_main.a

SRC = $(wildcard src/**/*.cpp) $(wildcard src/**/**/*.cpp)
SRC_ADMIN = src/AdminMain.cpp
SRC_USER = src/UserMain.cpp
SRC_SERVER = src/Server.cpp
SRC_FOR_BUILD = $(SRC) $(SRC_ADMIN) $(SRC_USER) $(SRC_SERVER)
TESTS = $(wildcard tests/*.cpp)

OBJ_USER = $(patsubst src/%.cpp, obj/%.o, $(SRC_USER))
OBJ_ADMIN = $(patsubst src/%.cpp, obj/%.o, $(SRC_ADMIN))
OBJ_SERVER = $(patsubst src/%.cpp, obj/%.o, $(SRC_SERVER))

.PHONY: clean coverage time
.SILENT: dirs

all: dirs semiuser semiadmin semiserver semitest test

semiuser: $(SRC:src/%.cpp=obj/%.o) $(OBJ_USER)
	$(CC) $(FLAGS) $^ -o bin/User
	
semiadmin: $(SRC:src/%.cpp=obj/%.o) $(OBJ_ADMIN)
	$(CC) $(FLAGS) $^ -o bin/Admin
	
semiserver: $(SRC:src/%.cpp=obj/%.o) $(OBJ_SERVER)
	$(CC) $(FLAGS) $^ -o bin/Server -pthread
	
	
semitest: $(SRC:src/%.cpp=obj/%.o) $(TESTS:%.cpp=obj/%.o)
	$(CC) $(FLAGS) $(LIB) $^ -o bin/TestAll

	
user: semiuser
	valgrind bin/User localhost 50000
	
admin: semiadmin
	valgrind bin/Admin localhost 50000
	
server: semiserver
	valgrind bin/Server 50000
	
build: dirs semiuser semiadmin semiserver
	
	
test:
	valgrind bin/TestAll
	
time:
	touch $(SRC_FOR_BUILD) $(TESTS) $(wildcard include/**/*.h) $(wildcard include/**/**/*.h)


$(SRC_FOR_BUILD:src/%.cpp=obj/%.o) : obj/%.o :
		$(CC) $(FLAGS) $(DEPFLAGS) $(INCLUDE) src/$*.cpp -c -o obj/$*.o
		
$(TESTS:%.cpp=obj/%.o) : obj/%.o :
		$(CC) $(FLAGS) $(DEPFLAGS) $(INCLUDE) $*.cpp -c -o obj/$*.o

dirs:
	mkdir -p bin
	mkdir -p $(patsubst src/%, obj/%, $(dir $(SRC)))
	mkdir -p obj/tests
	
clean:
	rm -rf bin obj dump lcov-out
	
coverage:
	lcov --capture --no-external --directory . --output-file coverage.info
	genhtml coverage.info --output-directory lcov-out


-include $(SRC_FOR_BUILD:src/%.cpp=obj/%.d)
-include $(TESTS:%.cpp=obj/%.d)
