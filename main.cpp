#include "cpu.h"
#include "graphics.h"
#include <cstdio>


int main() {
    Cpu cpu;
    printf("stack pointer: %x\n", cpu.AF.get_all());

    return 0;  
}