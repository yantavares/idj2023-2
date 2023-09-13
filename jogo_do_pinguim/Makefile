ifeq ($(OS),Windows_NT)
    # Windows
	CC=g++
	RM=del /Q
	OBJS=src/*.cpp
	COMPILER_FLAGS=-w
	LINKER_FLAGS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_mixer -lSDL2_image
	OBJ_NAME=game.exe
else
	# Linux
	CC=g++
	RM=rm -f
	OBJS=src/*.cpp
	COMPILER_FLAGS=-w
	LINKER_FLAGS=-lSDL2 -lSDL2_mixer -lSDL2_image
	OBJ_NAME=game
endif

all:$(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o src/$(OBJ_NAME)

run : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o src/$(OBJ_NAME)
	cd src && ./$(OBJ_NAME)

clean:
	$(RM) src/$(OBJ_NAME)