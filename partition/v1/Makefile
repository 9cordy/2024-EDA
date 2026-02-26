all: FM_partition

CXX = g++
LINKFLAGS = -pedantic -Wall -fomit-frame-pointer -funroll-all-loops -O3

FM_partition: main.o parser.o FM.o
	$(CXX) $(LINKFLAGS) main.o parser.o FM.o -o FM_partition

main.o: main.cpp
	$(CXX) $(LINKFLAGS) -DCOMPILETIME="\"`date`\"" main.cpp -c

parser.o: parser.cpp parser.h
	$(CXX) $(LINKFLAGS) parser.cpp -c

FM.o: FM.cpp FM.h
	$(CXX) $(LINKFLAGS) FM.cpp -c

clean:
	rm -rf *.o *.gch FM_partition