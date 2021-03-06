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
#include "ModuleIcoinScreen.h"
#include "ModuleStartScreen.h"
#include "Animation.h"
#include "ModuleSceneKen.h"

ModuleIcoinScreen::ModuleIcoinScreen()
{
	icoin_screen.x = 0;
	icoin_screen.y = 0;
	icoin_screen.w = SCREEN_WIDTH;
	icoin_screen.h = SCREEN_HEIGHT;
}

ModuleIcoinScreen::~ModuleIcoinScreen()
{

}

// Load assets
bool ModuleIcoinScreen::Start()
{
	LOG("Loading Welcome screen");
	graphics = App->textures->Load("StartScreenIII_II.png");
	return true;
}

// UnLoad assets
bool ModuleIcoinScreen::CleanUp()
{
	LOG("Unloading Introduce coin Screen");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleIcoinScreen::Update()
{
	//Animation* current_animation = &idle;

	App->render->Blit(graphics, 0, 0, &icoin_screen, 0.75f);
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->icoin_screen, App->scene_ken, 1.0f);

	}
	return UPDATE_CONTINUE;
}