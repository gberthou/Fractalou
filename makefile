BINDIR=bin
OBJDIR=obj

BINNAME=Fractals
BIN=$(BINDIR)/$(BINNAME)
CLEAN=clean

DEBUGDIR=Debug
RELEASEDIR=Release

DEBUG=debug
RELEASE=release

GPP=g++
CFLAGS=-Wall -Wextra -Wmissing-braces -pedantic -Werror
INCLUDE=-I"./" -I"./core" -I"./view" -I"./network"

COREDIR=core/
COREFILES=Quaternion.cpp QuaternionSuite.cpp FractalPart.cpp Fractal.cpp

FRACTALSDIR=core/fractals/
FRACTALSFILES=QS_Julia.cpp

VIEWDIR=view/
VIEWFILES=

NETWORKDIR=network/
NETWORKFILES=

MAINFILE=main.cpp

CPPFILES=$(MAINFILE) $(addprefix $(COREDIR),$(COREFILES)) $(addprefix $(FRACTALSDIR),$(FRACTALSFILES)) $(addprefix $(VIEWDIR),$(VIEWFILES)) $(addprefix $(NETWORKDIR),$(NETWORKFILES))

OBJ=$(CPPFILES:.cpp=.o)
OBJABS=$(addprefix $(OBJDIR)/,$(OBJ))

OBJDEBUG=$(addprefix $(DEBUGDIR)/,$(OBJABS))
OBJRELEASE=$(addprefix $(RELEASEDIR)/,$(OBJABS))

BINDEBUG=$(addprefix $(DEBUGDIR)/,$(BIN))
BINRELEASE=$(addprefix $(RELEASEDIR)/,$(BIN))

FLAGSDEBUG=-g -pg
FLAGSRELEASE=-O2

LIBS=-lsfml-system -lsfml-window -lsfml-graphics

$(DEBUG): $(OBJDEBUG)
	$(GPP) $(LIBS) -o $(BINDEBUG) $(OBJDEBUG)

$(RELEASE): $(OBJRELEASE)
	$(GPP) $(LIBS) -o $(BINRELEASE) $(OBJRELEASE)

$(CLEAN):
	rm -f $(BINDEBUG) $(BINRELEASE) $(OBJDEBUG) $(OBJRELEASE)

$(DEBUGDIR)/$(OBJDIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) $(FLAGSDEBUG) $(INCLUDE) -c -o $@ $<

$(RELEASEDIR)/$(OBJDIR)/%.o: %.cpp
	$(GPP) $(CFLAGS) $(FLAGSRELEASE) $(INCLUDE) -c -o $@ $<

