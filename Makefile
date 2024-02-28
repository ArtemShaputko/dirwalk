PROJECT = dirwalk
COMPILER = gcc

PREFIX_SRC = ./src/
PREFIX_OBJ = ./obj/

SRC = $(wildcard $(PREFIX_SRC)*.c)
OBJ = $(patsubst $(PREFIX_SRC)%.c, $(PREFIX_OBJ)%.o, $(SRC))

$(PROJECT) : $(OBJ)
	$(COMPILER) $(OBJ) -o  $(PROJECT) -g

$(PREFIX_OBJ)%.o : $(PREFIX_SRC)%.c
	$(COMPILER) -c $< -o $@ -g

clean :
	rm $(PROJECT) $(PREFIX_OBJ)*.o