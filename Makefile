CC=clang
BIN=main.exe
SRC=main.c rstrlib.c
DEBUGGER=gdb
COMPILER_FLAGS=-Wall -Wextra -g -std=c11 -Wno-unused-parameter

all: 
	$(CC) $(SRC) $(COMPILER_FLAGS) -o $(BIN)

run: all
	$(BIN)

debug: all
	$(DEBUGGER) $(BIN)

clean:
	del *.exe *.o *.ilk *.pdb