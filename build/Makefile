CC=g++
CXXFLAGS=-I$(IDIR) -std=c++11 -g

ODIR=../src
IDIR=../include


_OBJ = car.o terrain.o mediator.o path.o node.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

all:main

$(ODIR)/car.o: $(ODIR)/car.cpp  
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/terrain.o: $(ODIR)/terrain.cpp  
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/mediator.o: $(ODIR)/mediator.cpp  
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/path.o: $(ODIR)/path.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/node.o: $(ODIR)/node.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)

main.o: $(ODIR)/main.cpp
	$(CC) -c -o $@ $< $(CXXFLAGS)
	
main: $(OBJ)
	$(CC) -o $@ $^ $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o 
