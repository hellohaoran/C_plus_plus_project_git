SRC:=$(wildcard *.c)
OBJ:=$(patsubst %.c,%,$(SRC))
all:$(OBJ)
%:%.c
	gcc  $^ -o $@   -g -pthread -l mysqlclient  -lcrypt
clean:
	$(RM) $(EXEC)
