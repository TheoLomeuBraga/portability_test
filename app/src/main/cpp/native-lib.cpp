
#include "../../../../src/main.h"

#define SDL_MAIN_USE_CALLBACKS
#include <../../../../libs/SDL/include/SDL3/SDL.h>
#include <../../../../libs/SDL/include/SDL3/SDL_main.h>
#include <../../../../libs/SDL/include/SDL3/SDL_init.h>

extern "C" SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]) {
    start();
    return SDL_APP_CONTINUE;
}

extern "C" SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event* event) {

    if(process_event(*event)){
        return SDL_APP_CONTINUE;
    }else{
        return SDL_APP_SUCCESS;
    }


}

extern "C" SDL_AppResult SDL_AppIterate(void *appstate) {

    main_loop();

    return SDL_APP_CONTINUE;
}

extern "C" void SDL_AppQuit(void* appstate, SDL_AppResult result) {
    end();
}
