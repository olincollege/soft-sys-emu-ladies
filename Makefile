#TODO: put .o's and outputs in a folder

emu: main.o graphics.o cpu.o register.o
	g++ -Wall -g -o emu main.o screen.o graphics.o cpu.o register.o `sdl2-config --cflags --libs`

main.o: main.cpp
	g++ -Wall -c -o main.o main.cpp `sdl2-config --cflags --libs`

graphics.o: graphics.cpp
	g++ -Wall -c -o graphics.o graphics.cpp `sdl2-config --cflags --libs`

screen.o: screen.cpp
	g++ -Wall -c -o screen.o screen.cpp `sdl2-config --cflags --libs`

cpu.o: cpu.cpp
	g++ -Wall -c -o cpu.o cpu.cpp

test: register.o
	gcc -o testregisters unit_tests/test_registers.cpp register.cpp
	./testregisters

#TODO: why aren't the tests running?

register.o: register.cpp
	g++ -Wall -c -o register.o register.cpp
