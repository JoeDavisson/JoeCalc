
INCLUDES=$(shell fltk-config --cflags)
LIBS=$(shell fltk-config --ldflags)
CFLAGS=-O3 -Wall $(INCLUDES)
LDFLAGS=$(LIBS)
CPP=g++
OBJECTS=Calc.o Gui.o

default: $(OBJECTS)
	g++ -o joecalc Main.cxx \
	   $(OBJECTS) \
	   $(CFLAGS) \
	   $(LDFLAGS)

%.o: %.cxx %.H
	$(CPP) -c $< $(CFLAGS)

clean:
	@rm -f *.o joecalc

