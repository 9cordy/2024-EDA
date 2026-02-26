all: ROBDD

CXX = g++
LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3
SRC_DIR = src

ROBDD: main.o parser.o
	$(CXX) $(LINKFLAGS) main.o parser.o -o ROBDD

main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/parser.h
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" $(SRC_DIR)/main.cpp -c

parser.o: $(SRC_DIR)/parser.cpp $(SRC_DIR)/parser.h
	$(CXX) $(LINKFLAGS) $(SRC_DIR)/parser.cpp -c

clean:
	rm -rf *.o ROBDD $(SRC_DIR)/*.gch