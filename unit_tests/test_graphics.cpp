// These tests would just be more complicated if we tried to use minunit
// to compile:
// g++ test_graphics.cpp ../graphics.cpp ../screen.cpp `sdl2-config --cflags --libs`

#include "../screen.h"
#include "../graphics.h"
#include <stdint.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define SCALE 1 //TODO: this scale copied from EmuWars, IDK what it means -Emma
#define ROW_SIZE sizeof(uint8_t) * SCREEN_WIDTH //TODO: basically same ^

// putting this function here temporarily just so we can cleanly break out 
// of the loop

int process_input() {
    int quit = 0;

    SDL_Event event;
    
    // handle quitting, later this can handle other keypresses
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: 
                quit = 1;
                break;
            case SDL_KEYDOWN:
                // check if we hit escape
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        quit = 1;
                        break;
                }
        }
    }

    return quit;
}

int main() {
    Screen screen;
    screen.set_pixel(3, 120, 120);

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
        update_graphics(&renderer, &texture, &screen_loc, ROW_SIZE);

        //TODO: break out of loop condition
    }

    quit_graphics(window, renderer, texture);
}