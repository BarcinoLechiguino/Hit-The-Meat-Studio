
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleInput.h"
#include "SDL/include/SDL.h"
#include "ModuleSceneHonda.h"
#include "ModuleSceneryu.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"
#include "ModulePlayerII.h"
ModuleRender::ModuleRender() : Module()
{
	camera.x = camera.y = 0;
	camera.w = SCREEN_WIDTH;
	camera.h = SCREEN_HEIGHT;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;
	Uint32 flags = 0;

	if(REN_VSYNC == true)
	{
		flags |= SDL_RENDERER_PRESENTVSYNC;
	}

	renderer = SDL_CreateRenderer(App->window->window, -1, flags);
	
	if(renderer == NULL)
	{
		LOG("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleRender::PreUpdate()
{
	SDL_RenderClear(renderer);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::Update()	
{
	int speed = 2;
	int still = 0;

	if (App->collision->debug) {
		if (App->input->keyboard[SDL_SCANCODE_KP_2] == KEY_REPEAT)
		{
			if (App->scene_honda->IsEnabled() || App->scene_ryu->IsEnabled())
			{
				camera.y += speed;
			}
			else
			{
				camera.y += still;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_KP_8] == KEY_REPEAT)
		{
			if (App->scene_honda->IsEnabled() || App->scene_ryu->IsEnabled())
			{
				camera.y -= speed;
			}
			else
			{
				camera.y -= still;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_KP_4] == KEY_REPEAT)
		{
			if (App->scene_honda->IsEnabled() || App->scene_ryu->IsEnabled())
			{
				camera.x -= speed;
			}
			else
			{
				camera.x -= still;
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_KP_6] == KEY_REPEAT)
		{
			if (App->scene_honda->IsEnabled() || App->scene_ryu->IsEnabled())
			{
				camera.x += speed;
			}
			else
			{
				camera.x += still;
			}
		}
	} 
	
	if (camera.x <= -225) {
		camera.x = -225;
	}

	if (camera.x >= 235) {
		camera.x = 235;
	}

	



	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_RenderPresent(renderer);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");
	if(renderer != NULL)
	{
		SDL_DestroyRenderer(renderer);
	}

	return true;
}

// Blit to screen
bool ModuleRender::Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed, bool use_camera)
{
	
		bool ret = true;
		SDL_Rect rect;

		if (use_camera)
		{
			rect.x = (int)(-camera.x * speed) + x * SCREEN_SIZE;
			rect.y = (int)(-camera.y * speed) + y * SCREEN_SIZE;
		}
		else
		{
			rect.x = x * SCREEN_SIZE;
			rect.y = y * SCREEN_SIZE;
		}

		if (section != NULL)
		{
			rect.w = section->w;
			rect.h = section->h;
		}
		else
		{
			SDL_QueryTexture(texture, NULL, NULL, &rect.w, &rect.h);
		}

		rect.w *= SCREEN_SIZE;
		rect.h *= SCREEN_SIZE;

		if (SDL_RenderCopy(renderer, texture, section, &rect) != 0)
		{
			LOG("Cannot blit to screen. SDL_RenderCopy error: %s", SDL_GetError());
			ret = false;
		}

		return ret;
	
}

//Renders the collision quads
bool ModuleRender::DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera)
{
	bool ret = true;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer, r, g, b, a);

	SDL_Rect rec(rect);
	if (use_camera)
	{
		rec.x = (int)(camera.x + rect.x * SCREEN_SIZE);
		rec.y = (int)(camera.y + rect.y * SCREEN_SIZE);
		rec.w *= SCREEN_SIZE;
		rec.h *= SCREEN_SIZE;
	}

	if (SDL_RenderFillRect(renderer, &rec) != 0)
	{
		LOG("Cannot draw quad to screen. SDL_RenderFillRect error: %s", SDL_GetError());
		ret = false;
	}

	return ret;
}

