CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: SymmetricalTest

SymmetricalTest: $(BIN_DIR) $(BIN_DIR)/SymmetricalTest
	valgrind --leak-check=yes ./$(BIN_DIR)/SymmetricalTest

$(BIN_DIR)/SymmetricalTest: $(BIN_DIR)/SymmetricalTest.o $(BIN_DIR)/symmetrical.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/SymmetricalTest.o: $(TEST_DIR)/SymmetricalTest.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

$(BIN_DIR)/symmetrical.o: symmetrical.cpp symmetrical.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean

clean:
	rm -rf $(BIN_DIR)
