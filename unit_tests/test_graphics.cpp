// These tests would just be more complicated if we tried to use minunit
// to compile:
// 

#include "../screen.h"
#include "../graphics.h"
#include <stdint.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define SCALE 10 //TODO: this scale copied from EmuWars, IDK what it means -Emma
#define ROW_SIZE sizeof(uint8_t) * SCREEN_WIDTH

int main() {
    Screen screen;
    screen.set_pixel(0, 120, 120);

    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Texture *texture;

    // initialize the graphics
    init_graphics(&window, &renderer, &texture, SCREEN_WIDTH * SCALE,
                  SCREEN_HEIGHT * SCALE, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    while (1) {
        update_graphics(&renderer, &texture, *(screen.get_window()), ROW_SIZE);

        //TODO: break out of loop condition
    }

    quit_graphics(window, renderer, texture);
}