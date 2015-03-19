
INCLUDES=$(shell fltk-config --use-images --cflags)
LIBS=$(shell fltk-config --use-images --ldflags)
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

