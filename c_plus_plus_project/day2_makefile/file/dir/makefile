SRC:=$(wildcard *c)
OBJ:=$(patsubst %.c,%,$(SRC))
all:$(OBJ)
%:%.c
	gcc  $^ -o  $@