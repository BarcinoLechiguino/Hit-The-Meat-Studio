#include "Globals.h"
#include "Application.h"
#include "SDL/include/SDL.h"
#include "SDL_image/include/SDL_image.h"
#include "ModuleSceneHonda.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleSceneKen.h"
#include "MemLeaks.h"
#include "ModuleCongratScreen.h"


// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneHonda::ModuleSceneHonda()
{
	// ground
	ground = {8, 376, 848, 64};

	// roof
	roof = {91, 7, 765, 49};

	// foreground
	foreground = {164, 66, 336, 51};

	// Background / sky
	background = {120, 128, 671, 199};

	// flag animation
	water.PushBack({8, 447, 283, 9});
	water.PushBack({296, 447, 283, 12});
	water.PushBack({588, 447, 283, 18});
	water.speed = 0.02f;
}

ModuleSceneHonda::~ModuleSceneHonda()
{}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("honda_stage2.png");

	// TODO 5.1: Enable (and properly disable) the player module
	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	// Colliders ---
	/*App->collision->AddCollider({ 4, 0, 50, 400 }, COLLIDER_WALL);
	App->collision->AddCollider({ 340, 0, 50, 400 }, COLLIDER_WALL);*/
	
	return ret;
}

// Load assets
bool ModuleSceneHonda::CleanUp()
{
	// TODO 5.5: Remove all memory leaks
	LOG("Unloading honda stage");
	App->textures->Unload(graphics);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();

	return true;
}

// Update: draw background
update_status ModuleSceneHonda::Update()
{
	// Draw everything --------------------------------------	
	App->render->Blit(graphics, /*0*/-100, 160, &ground);
	App->render->Blit(graphics, /*50*/-25, -15, &background, 0.75f); // back of the room
	
	App->render->Blit(graphics, /*280*/180, 125, &foreground);
	App->render->Blit(graphics, /*305*/205, 136, &(water.GetCurrentFrame())); // water animation
	App->render->Blit(graphics, /*0*/-75, -16, &roof, 0.75f);

	// TODO 2: make so pressing SPACE the KEN stage is loaded
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1) {

		App->fade->FadeToBlack(App->scene_honda, App->congrat_screen,1.0f);

	}

	return UPDATE_CONTINUE;
}