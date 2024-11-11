
#include "../../../../src/main.h"

#include <../../../../libs/SDL/include/SDL3/SDL.h>
#include <../../../../libs/SDL/include/SDL3/SDL_main.h>

extern "C" int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
    /*
    if (!SDL_Init(SDL_INIT_EVENTS | SDL_INIT_VIDEO)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed (%s)", SDL_GetError());
        return 1;
    }

    if (!SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Hello World",
                                  "!! Your SDL project successfully runs on Android !!", NULL)) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_ShowSimpleMessageBox failed (%s)", SDL_GetError());
        return 1;
    }

    SDL_Quit();
    */
    start();
    return 0;
}