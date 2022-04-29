#include "screen.h"
#include "graphics.h"
#include <cstdio>
#include <inttypes.h>

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


    /*
    //TODO: this is test code and should be moved
    for (int i=0; i<160; i++) {
        for (int j = 0; j < 70; j++) {
            //window[i][j] = bit_color_to_SDL_color(3);
            screen.set_pixel(0, i, j);
        }
    }
    */

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    // initialize the graphics
    init_graphics(&window, &renderer, &texture, screen.width * SCALE,
                  screen.height * SCALE, screen.width, screen.height);

    uint32_t* screen_loc = screen.get_window();
    int quit = 0;
    while (!quit) {
        quit = process_input();
        screen.draw_all_scanlines(456);
        update_graphics(&renderer, &texture, &screen_loc, ROW_SIZE);
    }

    quit_graphics(window, renderer, texture);

    return 0;
}
