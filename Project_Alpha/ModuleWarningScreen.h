#pragma once
#ifndef __MODULEWARNINGSCREEN_H__
#define __MODULEWARNINGSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleWarningScreen : public Module
{
public:
	ModuleWarningScreen();
	~ModuleWarningScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	Uint32 timeLimitWrng = 0;
	Uint32 deltaTimeWrng = SDL_GetTicks() / 1000;;
	Uint32 startTimeWrng = 0;

	SDL_Texture* graphics = nullptr;
	SDL_Rect warning_screen;
	SDL_Rect black;
	

};

#endif // __MODULEWARNINSCREEN_H__