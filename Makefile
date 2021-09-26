CC = gcc
CPP = g++
LD = g++

INC = 
CFLAGS = -O2
LIBDIR = 
LIB = -lglut -lGLU -lGL -lm

OBJDIR = objs
OUT = bin/main

OBJ = $(OBJDIR)/main.o $(OBJDIR)/glExtension.o $(OBJDIR)/render.o 

all: default

default: $(OUT)

$(OUT): $(OBJ)
	test -d ../bin || mkdir -p ../bin
	$(LD) -o $(OUT) $(OBJ) $(LIB)

$(OBJDIR)/main.o: main.cpp
	test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$(CPP) $(CFLAGS) $(INC) -c -o $(OBJDIR)/main.o main.cpp

$(OBJDIR)/glExtension.o: libgl/glExtension.cpp
	test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$(CPP) $(CFLAGS) $(INC) -c -o $(OBJDIR)/glExtension.o libgl/glExtension.cpp

$(OBJDIR)/render.o: libgl/render.cpp
	test -d $(OBJDIR) || mkdir -p $(OBJDIR)
	$(CPP) $(CFLAGS) $(INC) -c -o $(OBJDIR)/render.o libgl/render.cpp



clean:
	rm -f $(OBJ) $(OUT)

run: default
	bin/main

.PHONY: clean

