SRC:=$(wildcard *.c)
OBJ:=$(patsubst %.c,%.o,$(SRC)) 
CC:=gcc
#$^ 是依赖项
# $@  是目标本身;	
server:$(OBJ)
	$(CC) $^ -o $@ -pthread -g
%.o:%.c
	$(CC) -c $^ -o $@   -g  
clean:
	$(RM) $(OBJ) server
rebuild:clean server
