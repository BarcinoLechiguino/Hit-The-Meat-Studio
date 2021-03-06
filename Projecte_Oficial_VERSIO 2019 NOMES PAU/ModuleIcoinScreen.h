#pragma once
#ifndef __MODULEICOINSCREEN_H__
#define __MODULEICOINSCREEN_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

struct SDL_Texture;

class ModuleIcoinScreen : public Module
{
public:
	ModuleIcoinScreen();
	~ModuleIcoinScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics = nullptr;
	SDL_Rect icoin_screen;

};

#endif // __MODULEICOINSCREEN_H__#pragma once
