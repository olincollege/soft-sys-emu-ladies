#include "screen.h"
#include "graphics.h"
#include <cstdio>

int main() {
    Cpu cpu;
    Screen screen(&cpu);

    //TODO: this is test code and should be moved
    for (int i=0; i<160; i++) {
        for (int j = 0; j < 70; j++) {
            //window[i][j] = bit_color_to_SDL_color(3);
            screen.set_pixel(0, i, j);
        }
    }

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    // initialize the graphics
    init_graphics(&window, &renderer, &texture, SCREEN_WIDTH * SCALE,
                  SCREEN_HEIGHT * SCALE, SCREEN_WIDTH, SCREEN_HEIGHT);

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
