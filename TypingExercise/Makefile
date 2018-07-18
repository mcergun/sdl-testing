CXX = g++
CFLAGS = -I. -I`pkg-config --cflags sdl2`
OUTDIR = out
BINDIR = bin

all: makedirs WordList SDLTextRenderer SDLInputHandler

makedirs:
	mkdir -p $(OUTDIR)
	mkdir -p $(BINDIR)

clean:
	rm -rf $(OUTDIR)
	rm -rf $(BINDIR)

WordList:
	$(CXX) -o $(OUTDIR)/WordList.o -c WordList.cpp $(CFLAGS)

SDLTextRenderer:
	$(CXX) -o $(OUTDIR)/SDLTextRenderer.o -c SDLTextRenderer.cpp $(CFLAGS)

SDLInputHandler:
	$(CXX) -o $(OUTDIR)/SDLInputHandler.o -c SDLInputHandler.cpp $(CFLAGS)