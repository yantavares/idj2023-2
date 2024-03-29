CXX = g++
CXXFLAGS = -w -lSDL2 -lSDL2_mixer -lSDL2_image
SRCDIR = jogo_do_pinguim/src
BINDIR = jogo_do_pinguim/bin
TARGET = $(BINDIR)/game
SRCS = $(shell find $(SRCDIR) -name "*.cpp")
CMD = $(CXX) $(SRCS) $(CXXFLAGS) -o $(TARGET)

all:
	mkdir -p $(BINDIR)
	$(CMD)

.PHONY: clean run

clean:
	rm -rf $(BINDIR)

run:
	mkdir -p $(BINDIR)
	$(CMD)
	cd $(BINDIR) && ./game

make play:
	cd $(BINDIR) && ./game