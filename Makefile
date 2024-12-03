lib = -llua -lraylib 
libdir = -L./lua54 -L./raylib/build/raylib
idir = -I./
opts = -g -static-libstdc++
filename = ./build/91RueDesVignoles.out

test : tiles.o main.o game.o aliases.hpp luapi.o 
	echo Building [test]
	g++ main.o game.o tiles.o luapi.o -o $(filename) $(libdir) $(lib) $(opts) $(idir)

main.o : main.cpp
	echo Building [main.cpp]
	g++ main.cpp -c main.o -I./ $(opts)

game.o : game.cpp
	echo Building [game.cpp]
	g++ game.cpp -c game.o -I./ $(opts)

luapi.o : luapi.cpp
	echo Building [luapi.cpp]
	g++ luapi.cpp -c game.o -I./ $(opts)

tiles.o : tiles.cpp 
	echo Building [tiles.cpp]
	g++ tiles.cpp -c tiles.o -I./ $(opts)
