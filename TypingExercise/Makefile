CXX = g++
DBGFLAGS = -D_DEBUG -g
CFLAGS = -Wall -I. `pkg-config --cflags sdl2` 
LDFLAGS = `pkg-config --libs sdl2` -lSDL2_ttf
OUTDIR = obj
BINDIR = bin
BINNAME = TypingExercise

all: makedirs objects
	$(CXX) -o $(BINDIR)/$(BINNAME) $(OUTDIR)/main.o $(OUTDIR)/WordList.o $(OUTDIR)/SDLTextRenderer.o $(OUTDIR)/SDLInputHandler.o $(OUTDIR)/GameLogic.o $(LDFLAGS) 

makedirs:
	mkdir -p $(OUTDIR)
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OUTDIR)
	rm -rf $(BINDIR)

objects: main WordList SDLTextRenderer SDLInputHandler GameLogic

main:
	$(CXX) -o $(OUTDIR)/main.o -c main.cpp $(CFLAGS)

WordList:
	$(CXX) -o $(OUTDIR)/WordList.o -c WordList.cpp $(CFLAGS)

SDLTextRenderer:
	$(CXX) -o $(OUTDIR)/SDLTextRenderer.o -c SDLTextRenderer.cpp $(CFLAGS)

SDLInputHandler:
	$(CXX) -o $(OUTDIR)/SDLInputHandler.o -c SDLInputHandler.cpp $(CFLAGS)

GameLogic:
	$(CXX) -o $(OUTDIR)/GameLogic.o -c GameLogic.cpp $(CFLAGS)