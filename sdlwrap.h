#ifndef SDLWRAP_H_INCLUDED
#define SDLWRAP_H_INCLUDED

/* forward declarations begin */
struct SDL_Renderer;
struct SDL_Window;
/* forward declarations end */

unsigned const maxFps = 60;
unsigned const minSpf = 1000/maxFps; // 16.6 milliseconds per frame

int& screenWidth();
int& screenHeight();

SDL_Renderer*& renderer();

#endif // SDLWRAP_H_INCLUDED
