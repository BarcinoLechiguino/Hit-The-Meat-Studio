#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "MemLeaks.h"
#include "ModuleWelcomeScreen.h"
#include "ModuleSceneGuile.h"
#include "ModuleStartScreen.h"
#include "ModuleAudio.h"

ModuleStartScreen::ModuleStartScreen()
{
	start_screen.x = 0;
	start_screen.y = 0;
	start_screen.w = SCREEN_WIDTH;
	start_screen.h = SCREEN_HEIGHT;
}

ModuleStartScreen::~ModuleStartScreen()
{}

// Load assets
bool ModuleStartScreen::Start()
{
	LOG("Loading Welcome screen");
	graphics = App->textures->Load("Sprites/Start_Game.png");

	return true;
}

// UnLoad assets
bool ModuleStartScreen::CleanUp()
{
	LOG("Unloading Start Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleStartScreen::Update()
{
	App->render->Blit(graphics, 0, 0, &start_screen, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_1] == KEY_DOWN || App->input->game_pad[SDL_CONTROLLER_BUTTON_A][GAME_PAD_2] == KEY_DOWN) {

		App->fade->FadeToBlack(App->start_screen, App->scene_guile, 1.0f );

	}

	return UPDATE_CONTINUE;
}