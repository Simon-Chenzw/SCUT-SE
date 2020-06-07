TARGET = 2048

BIN = bin
INC = inc
SRC = src
OBJ = obj

SRCS = $(wildcard $(SRC)/*.cpp)
OBJS = $(patsubst $(SRC)/%cpp, $(OBJ)/%o, $(SRCS))

INCLUDE = -I $(INC)
FLAGS = -W -O3 -std=c++17


# 链接时候指定库文件目录及库文件名
$(BIN)/$(TARGET): $(OBJS)
	@if [ ! -e $(BIN) ]; then mkdir $(BIN); fi;
	g++ -o $@ $^ 
 
# 编译时候指定头文件目录
$(OBJ)/%o: $(SRC)/%cpp
	@if [ ! -e $(OBJ) ]; then mkdir $(OBJ); fi;
	g++ -c -o $@ $^ $(INCLUDE) $(FLAGS) 

.PHONY: clean
clean:
	if [ -e $(BIN) ]; then rm -rf $(BIN); fi;
	if [ -e $(OBJ) ]; then rm -rf $(OBJ); fi;
