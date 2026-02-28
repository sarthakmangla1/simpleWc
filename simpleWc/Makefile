CC      := gcc
CFLAGS  := -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -O2

BIN     := simplewc

SRC     := main.c \
           fileStats.c \
           tests/wcStrUnits.c \
           tests/wcFileUnits.c

.PHONY: all clean run test fuzz gtest

all: $(BIN)

$(BIN): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(BIN)

run: $(BIN)
	./$(BIN)

test: $(SRC)
	$(CC) $(CFLAGS) -DRUN_TESTS $(SRC) -o $(BIN)-test
	./$(BIN)-test
	rm -f $(BIN)-test
	@echo "All tests passed."

fuzz: $(BIN)
	./fuzzTest.sh ./$(BIN)

clean:
	rm -f $(BIN)

GTEST_FLAGS := $(shell pkg-config --cflags --libs gtest_main)
GTEST_CXXFLAGS := -Wall -Wextra -std=c++17 -D_POSIX_C_SOURCE=200809L -O2

gtest: fileStats.c tests/gtests.cpp
	$(CC) $(CFLAGS) -c fileStats.c -o fileStats_gtest.o
	g++ $(GTEST_CXXFLAGS) tests/gtests.cpp fileStats_gtest.o \
		$(GTEST_FLAGS) -o simplewc-gtest
	./simplewc-gtest
	rm -f simplewc-gtest fileStats_gtest.o