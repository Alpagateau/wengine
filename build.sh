#/usr/bin/zsh
g++ main.cpp game.cpp tiles.cpp luapi.cpp -o ./build/test -L./lua54 -llua -lraylib -g -I./

