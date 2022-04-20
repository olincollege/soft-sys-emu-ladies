#include "graphics.h"

void init_graphics(SDL_Window **window_pointer, SDL_Renderer **renderer_pointer,\
    SDL_Texture **texture_pointer, int windowWidth, int windowHeight, \
    int textureWidth, int textureHeight) {

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
            SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
            SDL_Quit();
            exit(1);
        }
    // create window and renderer at the same time 
    // use the window_shown flag so we can query window info later
    if (SDL_CreateWindowAndRenderer(windowWidth, windowHeight,\
            SDL_WINDOW_SHOWN, window_pointer, renderer_pointer) != 0) 
    {
        SDL_Log("Unable to create window and renderer: %s", SDL_GetError());
        SDL_Quit();
        exit(1);
    }

    // create the texture 
    *texture_pointer = SDL_CreateTexture(*renderer_pointer, SDL_PIXELFORMAT_RGBA8888, \
            SDL_TEXTUREACCESS_STREAMING, textureWidth, textureHeight); 
}

void update_graphics(SDL_Renderer **renderer, SDL_Texture **texture,\
    uint32_t **screen, int rowSize) {
    SDL_UpdateTexture(*texture, NULL, *screen, rowSize);
    SDL_RenderClear(*renderer);
    SDL_RenderCopy(*renderer, *texture, NULL, NULL);
    SDL_RenderPresent(*renderer);
}

void quit_graphics(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture) {
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}