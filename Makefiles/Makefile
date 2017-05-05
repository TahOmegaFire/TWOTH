SRCDIR = ../src/
SRC = $(addprefix ../src/, Main.cpp Log.cpp TexW.cpp Entity.cpp Player.cpp Map.cpp CollisionBox.cpp)
CC = g++

CFLAGS = -Wall #Add -Wl,-subsystem,windows for stopping console
LFLAGS = -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

IDIR = ../lib/i686-w64-mingw32/include/SDL2
LDIR = ../lib/i686-w64-mingw32/lib

BINDIR = ../bin/OverTheHeaven

all : $(SRC)
	$(CC) $(SRC) -I$(IDIR) -L$(LDIR) $(CFLAGS) $(LFLAGS) -o $(BINDIR)