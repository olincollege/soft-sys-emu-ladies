#include <cstdio>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_error.h>
#include <SDL_events.h>

#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define SCALE 1
#define ROW_SIZE sizeof(uint32_t) * SCREEN_WIDTH

void init_graphics(SDL_Window **window_pointer, SDL_Renderer **renderer_pointer,\
    SDL_Texture **texture_pointer, int windowWidth, int windowHeight, \
    int textureWidth, int textureHeight);

void update_graphics(SDL_Renderer **renderer, SDL_Texture **texture,\
    uint32_t **screen, int rowSize);

void quit_graphics(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);

int process_input();
