#include "screen.h"
#include "graphics.h"
#include <cstdio>


int main() {
    Cpu cpu;
    Screen screen(&cpu);
    screen.load_tile(5, 1);
    printf("stack pointer: %x\n", cpu.AF.get_all());
    printf("ahhh\n");

    return 0;  
}