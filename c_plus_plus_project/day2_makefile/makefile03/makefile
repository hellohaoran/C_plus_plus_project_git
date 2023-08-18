SRC:=$(wildcard src/*.c)

OBJ:=$(patsubst src/%.c,objs/%.o,$(SRC))

OUT:=main
$(OUT):$(OBJ)
	gcc  $^ -o $@ 
 
objs/%.o:src/%.c
	gcc -c $^ -o $@ -I include include/
