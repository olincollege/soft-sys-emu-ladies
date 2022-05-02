#include "screen.h"
#include "graphics.h"
#include <cstdio>
#include <inttypes.h>

const int MAX_CYCLES = 5;

int main(int argc, char const *argv[]) {
    if (argc != 2) {
		fprintf(stderr, "Please provide a filename");
		exit(1);
	}

    char const* file_name = argv[1];

    Cpu cpu;
    Screen screen(&cpu);

    cpu.load_rom(file_name);
    for (int i=0; i<0x100; i++) {
        printf("%" PRIu8 "\n", cpu.read_memory(i));
    }

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    // initialize the graphics
    init_graphics(&window, &renderer, &texture, screen.width * SCALE,
                  screen.height * SCALE, screen.width, screen.height);

    uint32_t* screen_loc = screen.get_window();
    int quit = 0;
    int counter = 0;
    // while (!quit) {
    while (counter < 5) {
        quit = process_input();
        int cycles_this_update = 0;
        
        //while (cycles_this_update < MAX_CYCLES) {
            cycles_this_update += cpu.execute_next_opcode();
            printf("Cycles this update: %d\n", cycles_this_update);
            screen.draw_all_scanlines(cycles_this_update);
        //}

        update_graphics(&renderer, &texture, &screen_loc, ROW_SIZE);
        counter++;
    }

    quit_graphics(window, renderer, texture);

    return 0;
}
