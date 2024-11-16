#include <exception>
#include <functional>

#include <SDL3/SDL.h>


#include <SDL3/SDL_opengles2.h>

#include <random>
std::default_random_engine rng;
float randon()
{
  std::uniform_real_distribution<double> dist(0.0, 1.0);
  return dist(rng);
}



bool is_open = true;
SDL_Window *window;

float clear_color[3] = {0, 0, 0};

SDL_GLContext glc;

void start()
{
  SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_OPENGL);

  // SDL_SetHint(SDL_HINT_OPENGL_ES_DRIVER, "1");
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

  glc = SDL_GL_CreateContext(window);

  SDL_GL_MakeCurrent(window, glc);

  SDL_GL_SetSwapInterval(1);
}

bool process_event(SDL_Event e)
{
  if (e.type == SDL_EVENT_QUIT)
  {
    is_open = false;
  }

  if (e.type == SDL_EVENT_MOUSE_BUTTON_DOWN || e.type == SDL_EVENT_KEY_DOWN || e.type == SDL_EVENT_FINGER_DOWN)
  {
    clear_color[0] = randon();
    clear_color[1] = randon();
    clear_color[2] = randon();
  }
  return is_open;
}

void main_loop()
{

#ifndef __ANDROID__
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    process_event(e);
  }
#endif

  glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  SDL_GL_SwapWindow(window);
}

void end()
{
  is_open = false;
  // SDL_GL_DeleteContext(glc);
  SDL_DestroyWindow(window);
  SDL_Quit();
}




#ifndef __ANDROID__
#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>

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


#endif

