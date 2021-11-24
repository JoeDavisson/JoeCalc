# Makefile for Linux

INCLUDES=$(shell ./fltk-1.3.7/fltk-config --use-images --cflags)
LIBS=$(shell ./fltk-1.3.7/fltk-config --use-images --ldflags)
CXXFLAGS=-O3 -Wall $(INCLUDES)
CXX=g++
OBJ=Button.o ToggleButton.o Calc.o Gui.o

default: $(OBJ)
	$(CXX) -o joecalc Main.cxx $(OBJ) $(CXXFLAGS) $(LIBS)

fltk:
	@cd ./fltk-1.3.7; \
	make clean; \
	./configure --host=$(HOST) --enable-xft --enable-localjpeg --enable-localzlib --enable-localpng --disable-xdbe; \
	cd ..
	@echo "FLTK libs built!"

%.o: %.cxx %.H
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f *.o joecalc
	@echo "Clean!"

