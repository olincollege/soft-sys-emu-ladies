#TODO: put .o's and outputs in a folder

emu: main.o graphics.o cpu.o register.o screen.o
	g++ -Wall -g -o emu main.o screen.o graphics.o cpu.o register.o `sdl2-config --cflags --libs`

main.o: main.cpp
	g++ -Wall -c -o main.o main.cpp `sdl2-config --cflags --libs`

graphics.o: graphics.cpp graphics.h
	g++ -Wall -c -o graphics.o graphics.cpp `sdl2-config --cflags --libs`

screen.o: screen.cpp screen.h
	g++ -Wall -c -o screen.o screen.cpp `sdl2-config --cflags --libs`

cpu.o: cpu.cpp cpu.h
	g++ -Wall -c -o cpu.o cpu.cpp

register.o: register.cpp register.h
	g++ -Wall -c -o register.o register.cpp

test:
	gcc -o testregisters unit_tests/test_registers.cpp register.cpp
	./testregisters

clean:
	rm *.o
