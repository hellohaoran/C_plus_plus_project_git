SRC:=$(wildcard *.c)
OBJ:=$(patsubst %.c,%,$(SRC))
all:$(OBJ)
#通配符
%:%.c
	gcc  $^ -o $@  -g  

