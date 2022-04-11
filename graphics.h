#include <stdio.h>
#include <SDL.h>
#include <SDL_video.h>
#include <SDL_render.h>
#include <SDL_error.h>
#include <SDL_events.h>

void init_graphics(SDL_Window **window_pointer, SDL_Renderer **renderer_pointer,\
    SDL_Texture **texture_pointer, int windowWidth, int windowHeight, \
    int textureWidth, int textureHeight);

void update_graphics(SDL_Renderer **renderer, SDL_Texture **texture,\
    uint8_t **screen, int rowSize);

void quit_graphics(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture);