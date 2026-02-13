CC      := gcc
CFLAGS  := -Wall -Wextra -std=c99 -O2

BIN     := simplewc

SRC     := main.c \
           fileStats.c \
           tests/wcStrUnits.c \
           tests/wcFileUnits.c

.PHONY: all clean run test fuzz

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN)

test: $(BIN)
	./$(BIN) -h >/dev/null
	@echo "Built and help works."

fuzz: $(BIN)
	tools/fuzzTest.sh ./$(BIN)

clean:
	rm -f $(BIN)
