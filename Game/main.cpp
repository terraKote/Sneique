#include <iostream>
#include <SDL.h>
#include <Tilengine.h>

#define WIDTH 640
#define HEIGHT 480

#define RENDER_WIDTH 160
#define RENDER_HEIGHT 120

#define UNIT_SIZE 8

int main(int argc, char* argv[]) {
    SDL_Rect dstrect = { 0 };
    dstrect.x = 0;
    dstrect.y = 0;
    dstrect.w = WIDTH;
    dstrect.h = HEIGHT;

    uint8_t* rt_pixels = { 0 };
    int rt_pitch = { 0 };

    TLN_Spriteset spriteset;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create a window
    SDL_Window* window = SDL_CreateWindow("Snake Game",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        SDL_WINDOW_SHOWN);

    if (window == nullptr) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED + SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture* backbuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, RENDER_WIDTH, RENDER_HEIGHT);

    // Main loop flag
    bool quit = false;
    SDL_Event event;

    TLN_Init(RENDER_WIDTH, RENDER_HEIGHT, 2, 64, 0);
    TLN_SetLoadPath("assets/sprites");

    spriteset = TLN_LoadSpriteset("snake");
    TLN_SetSpriteSet(0, spriteset);

    TLN_SetBGColor(0, 128, 238);

    // Main application loop
    while (!quit) {
        // Event processing
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_LockTexture(backbuffer, NULL, (void**)&rt_pixels, &rt_pitch);

        // Tilengine Draw Begin
        TLN_SetRenderTarget(rt_pixels, rt_pitch);

        TLN_SetSpritePicture(0, 0);

        TLN_UpdateFrame(0);
        // Tilengine Draw End

        SDL_UnlockTexture(backbuffer);
        SDL_RenderClear(renderer);
        SDL_SetTextureBlendMode(backbuffer, SDL_BLENDMODE_NONE);
        SDL_RenderCopy(renderer, backbuffer, NULL, &dstrect);
        SDL_RenderPresent(renderer);
    }

    TLN_DeleteSpriteset(spriteset);

    TLN_Deinit();

    // Destroy the window and quit SDL
    SDL_DestroyTexture(backbuffer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
