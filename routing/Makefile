all: router

CXX = g++
LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3
SRC_DIR = src

router: main.o parser.o route.o
	$(CXX) $(LINKFLAGS) main.o parser.o route.o -o router

main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/parser.h $(SRC_DIR)/route.h
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" $(SRC_DIR)/main.cpp -c

parser.o: $(SRC_DIR)/parser.cpp $(SRC_DIR)/parser.h
	$(CXX) $(LINKFLAGS) $(SRC_DIR)/parser.cpp -c

route.o: $(SRC_DIR)/route.cpp $(SRC_DIR)/route.h
	$(CXX) $(LINKFLAGS) $(SRC_DIR)/route.cpp -c

clean:
	rm -rf *.o router $(SRC_DIR)/*.gch