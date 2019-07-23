#pragma once
#include <SDL.h>
#include <SDL_image.h>

typedef SDL_Texture			Texture;
typedef SDL_Rect			Rect;
typedef SDL_Point			Point;

bool fwInit(int widht, int height);
void fwSetFPS(int fps);
void fwLoop();

void fwRegisterUpdateCallback(void(*fnUpdate)(float dt));
void fwRegisgerRenderCallback(void(*fnRender)());
void fwRegisterOnKeyDownCallback(void(*fnKeyDown)(int key));
void fwRegisterOnKeyUpCallback(void(*fnKeyUp)(int key));

bool fwLoadTexture(const char* file, Texture*& tex, int& width, int& height);
void fwDestroyTexture(Texture* tex);
void fwRenderTexture(Texture* tex, Rect* src, Rect* des);
void fwRenderTextureEx(Texture* tex, Rect* src, Rect* des, const double angle);

void fwRenderPoint(int x, int y);
void fwRenderRect(int x, int y, int w, int h);
void fwFillRect(Rect &rect, SDL_Color &color);

void fwTerminate();

bool fwIsRectOverlap(const Rect* r1, const Rect* r2);

bool fwLoadTextFont(const char *text, TTF_Font *font, Texture*& tex, int& width, int& height);