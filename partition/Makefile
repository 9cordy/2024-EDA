all: FM_partition

CXX = g++
LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3
SRC_DIR = v2

FM_partition: main.o parser.o FM.o
	$(CXX) $(LINKFLAGS) main.o parser.o FM.o -o FM_partition

main.o: $(SRC_DIR)/main.cpp $(SRC_DIR)/parser.h $(SRC_DIR)/FM.h
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" $(SRC_DIR)/main.cpp -c

parser.o: $(SRC_DIR)/parser.cpp $(SRC_DIR)/parser.h
	$(CXX) $(LINKFLAGS) $(SRC_DIR)/parser.cpp -c

FM.o: $(SRC_DIR)/FM.cpp $(SRC_DIR)/FM.h
	$(CXX) $(LINKFLAGS) $(SRC_DIR)/FM.cpp -c

clean:
	rm -rf *.o FM_partition $(SRC_DIR)/*.gch