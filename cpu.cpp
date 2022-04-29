#include "cpu.h"

Cpu::Cpu() {
    AF.set_all(0x01B0);
    BC.set_all(0x0013);
    DE.set_all(0x00D8);
    HL.set_all(0x014D);

    PC = 0x0100;
    SP = 0xFFFE;

    
    memory[0xFF05] = 0x00;
    memory[0xFF06] = 0x00;
    memory[0xFF07] = 0x00;
    memory[0xFF10] = 0x80;
    memory[0xFF11] = 0xBF;
    memory[0xFF12] = 0xF3;
    memory[0xFF14] = 0xBF;
    memory[0xFF16] = 0x3F;
    memory[0xFF17] = 0x00;
    memory[0xFF19] = 0xBF;
    memory[0xFF1A] = 0x7F;
    memory[0xFF1B] = 0xFF;
    memory[0xFF1C] = 0x9F;
    memory[0xFF1E] = 0xBF;
    memory[0xFF20] = 0xFF;
    memory[0xFF21] = 0x00;
    memory[0xFF22] = 0x00;
    memory[0xFF23] = 0xBF;
    memory[0xFF24] = 0x77;
    memory[0xFF25] = 0xF3;
    memory[0xFF26] = 0xF1;
    memory[0xFF40] = 0x91;
    memory[0xFF42] = 0x00;
    memory[0xFF43] = 0x00;
    memory[0xFF45] = 0x00;
    memory[0xFF47] = 0xFC;
    memory[0xFF48] = 0xFF;
    memory[0xFF49] = 0xFF;
    memory[0xFF4A] = 0x00;
    memory[0xFF4B] = 0x00;
    memory[0xFFFF] = 0x00;
    

    // TODO: initialize all other values to 0? or random like gameboy?
}

void Cpu::load_rom(const char* filename) {
    FILE* game;

    game = fopen(filename, "rb");

    if (NULL == game) {
        fprintf(stderr, "Unable to open game: %s\n", filename);
        //exit(1);
    }
    // Read the game data into memory starting at address 0x200
    fread(&memory[0], 1, 0x10000, game);

    fclose(game);
}

uint16_t Cpu::get_PC(){
    return PC;
}

uint16_t Cpu::get_SP() {
    return SP;
}

void Cpu::set_PC(uint16_t bytes){
    PC = bytes;
}

void Cpu::set_SP(uint16_t bytes){
    SP = bytes;
}

int Cpu::write_memory(uint16_t address, uint8_t data) {
    if (address < 0x8000) {
        fprintf(stderr, "Tried to write to read-only memory");
        return 0;

    } else if ((address >= 0xE000) && (address < 0xFE00)) {
        memory[address] = data;
        write_memory(address-0x2000, data);
        return 1;

    } else if ((address >= 0xFEA0) && (address < 0xFEFF)) {
        fprintf(stderr, "Tried to write to restricted memory");
        return 0;

    } else {
        memory[address] = data;
        return 1;
    }
}

uint8_t Cpu::read_memory(uint16_t address) {
    return memory[address];
    // TODO: we don't know if restricted memory is readable
}
