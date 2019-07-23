#include "Framework.h"

SDL_Window*		gWindow		= NULL;
SDL_Renderer*	gRenderer	= NULL;
Uint32			gFPS		= 0;
Uint32			gFrameTime	= 0;
Uint32			gDeltaTime	= 0;

void (*gFnUpdate)(float)	= NULL;
void (*gFnRender)()			= NULL;
void (*gFnKeyDown)(int)		= NULL;
void (*gFnKeyUp)(int)		= NULL;

bool fwInit(int width, int height)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		SDL_Log("SDL Init failed - %d", SDL_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("Framework 2D", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, 0);
	if (gWindow == NULL)
	{
		SDL_Log("SDL create window failed - %d", SDL_GetError());
		return false;
	}

	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
	if (gRenderer == NULL)
	{
		SDL_Log("SDL create renderer failed - %d", SDL_GetError());
		return false;
	}
	SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND);

	int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if ((initted & flags) != flags)
	{	
		SDL_Log("IMG_Init: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

void fwSetFPS(int fps)
{
	gFPS = fps;
	gFrameTime = 1000 / gFPS;
	gDeltaTime = gFrameTime;
}

void fwLoop()
{
	bool isRunning = true;
	SDL_Event e;

	while (isRunning)
	{
		Uint32 startTime = SDL_GetTicks();

		while (SDL_PollEvent(&e) != 0)
        {
			switch (e.type)
			{
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				gFnKeyDown(e.key.keysym.sym);
				break;
			case SDL_KEYUP:
				gFnKeyUp(e.key.keysym.sym);
				break;
			}
        }

		if (gFnUpdate != NULL)
			gFnUpdate(gDeltaTime / 1000.0f);
		
		if (gFnRender != NULL)
		{
			SDL_RenderClear(gRenderer);
			gFnRender();
			SDL_RenderPresent(gRenderer);
		}
				
		gDeltaTime = SDL_GetTicks() - startTime;
		int sleepTime = gFrameTime - gDeltaTime;

		if (sleepTime > 0)
		{
			SDL_Delay(sleepTime);
			gDeltaTime += sleepTime;
		}
	}
}

void fwRegisterUpdateCallback(void(*fnUpdate)(float dt))
{
	gFnUpdate = fnUpdate;
}

void fwRegisgerRenderCallback(void(*fnRender)())
{
	gFnRender = fnRender;
}

void fwRegisterOnKeyDownCallback(void(*fnKeyDown)(int key))
{
	gFnKeyDown = fnKeyDown;
}

void fwRegisterOnKeyUpCallback(void(*fnKeyUp)(int key))
{
	gFnKeyUp = fnKeyUp;
}

bool fwLoadTexture(const char* file, Texture*& tex, int& width, int& height)
{
	SDL_Log("Texture load - File: %s", file);
	tex = IMG_LoadTexture(gRenderer, file);
	if (tex == NULL)
	{
		SDL_Log("Texture load failed - File: %s", file);
		return false;
	}

	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
	return true;
}

void fwDestroyTexture(Texture* tex)
{
	SDL_DestroyTexture(tex);
}

void fwRenderTexture(Texture* tex, Rect* src, Rect* des)
{
	SDL_RenderCopy(gRenderer, tex, src, des);
}

void fwRenderTextureEx(Texture * tex, Rect * src, Rect * des, const double angle)
{
	SDL_RenderCopyEx(gRenderer, tex, src, des, angle, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
}

void fwRenderPoint(int x, int y)
{
	SDL_RenderDrawPoint(gRenderer, x, y);
}

void fwRenderRect(int x, int y, int w, int h)
{
	Rect drawRect;
	drawRect.x = x;
	drawRect.y = y;
	drawRect.w = w;
	drawRect.h = h;
	SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(gRenderer, &drawRect);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}

void fwFillRect(Rect &rect, SDL_Color &color)
{
	SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderFillRect(gRenderer, &rect);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
}

void fwTerminate()
{
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	IMG_Quit();
	SDL_Quit();
}

bool fwIsRectOverlap(const Rect* r1, const Rect* r2)
{
	return r1->x < (r2->x + r2->w) && (r1->x + r1->w) > r2->x &&
			r1->y < (r2->y + r2->h) && (r1->y + r1->h) > r2->y;
}


bool fwLoadTextFont(const char *text, TTF_Font *font, Texture*& tex, int& width, int& height) {
	SDL_Surface *surface;
	SDL_Color textColor = { 255, 255, 255, 0 };

	surface = TTF_RenderText_Solid(font, text, textColor);
	tex = SDL_CreateTextureFromSurface(gRenderer, surface);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);

	if (tex == NULL)
	{
		SDL_Log("text font load failed - File: %s", text);
		return false;
	}
	SDL_QueryTexture(tex, NULL, NULL, &width, &height);
	return true;
}