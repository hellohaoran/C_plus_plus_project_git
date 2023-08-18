SRC:=$(wildcard *.c)
OBJ:=$(patsubst %.c,%,$(SRC))
all:$(OBJ)
%:%.c
	gcc  $^ -o $@  -g -pthread
clean:
	$(RM) $(EXES)

