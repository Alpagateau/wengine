
test : tiles.o main.o game.o aliases.hpp luapi.o 
	echo Building [test]
	g++ main.o game.o tiles.o luapi.o -o ./build/91RueDesVignoles.out -L./lua54 -llua -lraylib -g -I./

main.o : main.cpp
	echo Building [main.cpp]
	g++ main.cpp -c main.o -I./ 

game.o : game.cpp
	echo Building [game.cpp]
	g++ game.cpp -c game.o -I./

luapi.o : luapi.cpp
	echo Building [luapi.cpp]
	g++ luapi.cpp -c game.o -I./

tiles.o : tiles.cpp 
	echo Building [tiles.cpp]
	g++ tiles.cpp -c tiles.o -I./
