OBJ:=main
DEP:=main.o add.o sub.o
# wildcard 将当前的目录下查找
SRC:=$(wildcard *.c)
# patsubst 替换在SRC 中的.c 替换成.o文件
OBJS:=$(patsubst %.c,%o,$(SRC)) 
$(OBJ):$(DEP)
	gcc $^ -o $@
%.o:%.c
	gcc -c $^ -o $@

.phony:clean rebuild
rebuild:clean main
clean:
	$(RM) $(DEP) $(OBJ) 

