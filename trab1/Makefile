CC=g++
CFLAGS=-w -lSDL2 -lSDL2_mixer -lSDL2_image
SRCDIR=src
BINDIR=bin
EXECUTABLE=$(BINDIR)/game

SOURCES=$(wildcard $(SRCDIR)/*.cpp)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)