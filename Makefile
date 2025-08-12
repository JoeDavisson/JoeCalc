# JoeCalc
# Makefile for Linux

VERSION=0.1.2
SRC_DIR=src
INCLUDES=$(shell fltk-config --use-images --cflags)
LIBS=$(shell fltk-config --use-images --ldflags)
CXXFLAGS=-O3 -Wall -DPACKAGE_STRING=\"$(VERSION)\" $(INCLUDES)
CXX=g++

OBJ= \
  $(SRC_DIR)/Button.o \
  $(SRC_DIR)/ToggleButton.o \
  $(SRC_DIR)/Calc.o \
  $(SRC_DIR)/Gui.o

default: $(OBJ)
	$(CXX) -o joecalc $(SRC_DIR)/Main.cxx $(OBJ) $(CXXFLAGS) $(LIBS)

%.o: %.cxx %.H
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@rm -f $(SRC_DIR)/*.o
	@rm -f ./joecalc
	@echo "Clean!"

