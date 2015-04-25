# Makefile for Linux

INCLUDES=$(shell fltk-config --use-images --cflags)
LIBS=$(shell fltk-config --use-images --ldflags)
CXXFLAGS=-O3 -Wall $(INCLUDES)
CXX=g++
OBJ=Calc.o Gui.o

default: $(OBJ)
	$(CXX) -o joecalc Main.cxx $(OBJ) $(CXXFLAGS) $(LIBS)

%.o: %.cxx %.H
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f *.o joecalc
	@echo "Clean!"

