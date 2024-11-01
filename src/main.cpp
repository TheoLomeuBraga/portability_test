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

#ifdef __EMSCRIPTEN__

#include <emscripten.h>

#endif

bool is_open = true;
SDL_Window *window;

float clear_color[3] = {0, 0, 0};

void main_loop()
{

  {
    SDL_Event e;
    while (SDL_PollEvent(&e))
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
        glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
      }
    }

    SDL_GL_SwapWindow(window);
  };

  glClearColor(clear_color[0], clear_color[1], clear_color[2], 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

int start()
{
  // SDL_Init(SDL_INIT_VIDEO);

  window = SDL_CreateWindow("test", 640, 480, SDL_WINDOW_OPENGL);

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
  SDL_GL_SetSwapInterval(0);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  SDL_GLContext glc = SDL_GL_CreateContext(window);

#ifdef __EMSCRIPTEN__
  emscripten_set_main_loop(main_loop, 0, true);
#else
  while (is_open)
    main_loop();
#endif

  return 0;
}

#ifdef __ANDROID__
#include <jni.h>
#include <thread>

extern "C"
{
  char msg[] = "greetings from C/C++";

  std::thread loopThread(start);
  loopThread.detach();

  JNIEXPORT void JNICALL Java_com_portabilitytest_game_MainActivity_start(JNIEnv *env, jobject thiz)
  {
    start();
    return env->NewStringUTF("OK");
  }
}

#else
int main(int argc, char **argv)
{
  return start();
}
#endif
