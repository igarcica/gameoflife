GOL_PATH =$(HOME)/gameoflife #Project directory
INCLUDE_DIRS = -I$(GOL_PATH) #Include directory
BUILD_PATH=build #Objects directory

CC = gcc #Compiler to use
COMPILE_OPTS=-Wall #Compilation option
CFLAGS = $(COMPILE_OPTS) $(INCLUDE_DIRS) -I.
#LDFLAGS = -lncurses
DEPS = gol_rules.h #Dependencies
OBJ = main.o gol_rules.o #Targets

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<
gol_rules: $(OBJ)
	gcc -o $@ $^ $(LDFLAGS) $(CFLAGS)
clean :
	rm -f $(OBJ) gol_rules
