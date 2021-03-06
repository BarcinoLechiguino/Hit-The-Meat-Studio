#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "Animation.h"
#include "ModuleFonts.h"
#include "ModuleCollision.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayerII.h"
#include <stdio.h>


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

float speed = 2;
Uint8 alphaka= 255;
int groundLevel = 205;
int maxHeight = 120; 
bool airkick = true;
bool alreadyHit = false;


ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	graphics2 = NULL;
	current_animation = NULL;
	
	position.x = 100;
	position.y = 205;
	score = 0;

	health.x = 100;
	health.y = 400; 
	health.w = 200;
	health.h = 20;
	
	

	// idle animation (arcade sprite sheet)
	idle.PushBack({25, 54, 68, 98},0.05f);
	idle.PushBack({93, 54, 67, 98},0.05f);
	idle.PushBack({160, 54, 68, 98},0.05f);
	idle.PushBack({223, 54, 67, 98},0.005f);

	//Walk FORWARD Animation
	forward.PushBack({ 27,250, 66, 100 },0.5f);
	forward.PushBack({ 92, 250, 66, 100 },0.5f);
	forward.PushBack({ 160, 248, 70, 100 },0.5f);
	forward.PushBack({ 236, 250, 67, 100 },0.5f);
	forward.PushBack({ 306, 250, 67, 100 },0.5f);
	forward.PushBack({ 369, 250, 67, 100 },0.5f);
	forward.loop = true;

	//Walk backwards animation
	backward.PushBack({ 27, 155, 67, 100 },0.5f);
	backward.PushBack({ 97, 155, 67, 100 },0.5f);
	backward.PushBack({ 171, 155, 67, 100 },0.5f);
	backward.PushBack({ 239, 155, 60, 94 },0.5f);
	backward.PushBack({ 300, 155, 63, 100 },0.5f);
	backward.PushBack({ 362, 155, 67, 94 },0.5f);
	backward.loop = true;

	//Crouch Animation
	crouch.PushBack({ 519,156,67,95 },0.5f);
	crouch.PushBack({ 587,156,68,95 },0.5f);
	crouch.PushBack({ 654,156,68,95 },0.5f);
	crouch.loop = false;

	//Ryu jump
	jump.PushBack({ 17, 580, 63,105 },0.5f);
	jump.PushBack({ 80, 580, 62, 115 },0.5f);
	jump.PushBack({ 149, 580, 54, 100 },0.5f);
	jump.PushBack({ 207, 580, 61, 100 },0.5f);
	jump.PushBack({ 282, 580, 56,100 },0.5f);
	jump.PushBack({ 343, 580, 61,120 },0.5f);
	jump.loop = false;

	//Forward Jump Animation
	forwardjump.PushBack({ 13, 716, 62, 111  },0.5f);
	forwardjump.PushBack({ 75, 716, 65, 91 },0.5f);
	forwardjump.PushBack({ 140, 716, 112, 49 },0.5f);
	forwardjump.PushBack({ 420, 695, 58, 85 },0.5f);
	forwardjump.PushBack({ 140, 777, 129, 51 },0.5f);
	forwardjump.PushBack({ 328, 767, 77, 93 },0.5f);
	forwardjump.PushBack({ 343, 580, 61, 120 },0.5f);
	forwardjump.loop = false;

	//Backward Jump Animation
	backwardjump.PushBack({ 328, 767, 77, 93 },0.5f);
	backwardjump.PushBack({ 140, 777, 129, 51 },0.5f);
	backwardjump.PushBack({ 420, 695, 58, 85 },0.5f);
	backwardjump.PushBack({ 140, 716, 112, 49 },0.5f);
	backwardjump.PushBack({ 75, 716, 65, 91 },0.5f);
	backwardjump.PushBack({ 13, 716, 62, 111 },0.5f);
	backwardjump.loop = false;

	//Ryu Hadouken movement
	hadouken.PushBack({ 18, 870, 80, 95 },0.5f);
	hadouken.PushBack({ 100, 875, 90, 95 },0.5f);
	hadouken.PushBack({ 190, 875, 97, 95 },0.5f);
	hadouken.PushBack({ 290, 875, 110, 95 },0.5f);
	hadouken.loop = false;


	//Damaged Animation

	damaged.PushBack({ 499,900,84,108 },0.5f);
	damaged.PushBack({582,905,81,103},0.5f);
	damaged.PushBack({668,905,87,103},0.5f);
	damaged.PushBack({755,899,119,109},0.5f);
	damaged.loop = false;


	//Ryu light punch
	lightPunch.PushBack({ 34, 1368, 70, 96 },0.5f);
	lightPunch.PushBack({ 112, 1368, 101, 96 } ,0.5f);
	lightPunch.PushBack({ 34, 1368, 70, 96 },0.5f);
	lightPunch.loop = true;
 
	//Ryu light kick
	lightKick.PushBack({ 35, 1586, 69, 97 },0.5f);
	lightKick.PushBack({ 125, 1585, 120, 98 },0.5f);
	lightKick.loop = false;

	//punchcrouch Animation
	crouchpunch.PushBack({ 34, 2038, 90, 72 },0.5f);
	crouchpunch.PushBack({ 120, 2037, 105 , 73 },0.5f);
	crouchpunch.loop = false;

	//kickcrouch Animation
	crouchkick.PushBack({ 32, 2296, 80, 70 },0.5f);
	crouchkick.PushBack({ 109, 2296, 121, 70 },0.5f);
	crouchkick.loop = false;

	//Neutral punch jump Animation
	jumppunch.PushBack({ 259, 1693, 83, 91 },0.5f);
	jumppunch.PushBack({ 353, 1693, 200, 78 },0.5f);
	jumppunch.loop = false;

	//Neutral kick jump Animation
	jumpkick.PushBack({ 33, 1802, 82, 95 },0.5f);
	jumpkick.loop = false;

	//Jumpbackkick Animation
	jumpbackkick.PushBack({347, 1925, 80, 91},0.5f);
	jumpbackkick.PushBack({ 427, 1925, 135, 91 },0.5f);
	jumpbackkick.loop = false;
	
	
	
	//jumpbackpunch Animation
	jumpbackpunch.PushBack({ 23, 1689, 74, 91 },0.5f);
	jumpbackpunch.PushBack({ 99, 1689, 104, 92 },0.5f);
	jumpbackpunch.loop = false;
	

	//jumpfrontkick Animation
	jumpfrontkick.PushBack({ 347, 1925, 80, 91 },0.5f);
	jumpfrontkick.PushBack({ 427, 1925, 135, 91 },0.5f);
	jumpfrontkick.loop = false;
	
	
	// jumpfrontpunch Animation 
	jumpfrontpunch.PushBack({23, 1689, 74, 91},0.5f);
	jumpfrontpunch.PushBack({ 99, 1689, 104, 92 },0.5f);
	jumpfrontpunch.loop = false;
	


}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player textures");
	bool ret = true;
	graphics2 = App->textures->Load("Sprites/RyuP1_Inv.png"); // JA TE LA FOTO BONA
	graphics = App->textures->Load("Sprites/RyuP1_Def.png"); // JA TE LA FOTO BONA
	
	LightDamage_Sound = App->audio->LoadFx("Audios/FX/25H.wav");
	Hadoken_Sound = App->audio->LoadFx("Audios/Voices/Ryu&Ken hadouken.wav");

	position.x = 75;
	position.y = 205;


	//Player 2 stest collider
	player_collider = App->collision->AddCollider({ position.x , position.y - 100, 60, 93 }, COLLIDER_PLAYER, App->player);
	

	

	

	return ret;
}


bool ModulePlayer::CleanUp()
{
	LOG("Unloading Player");

	App->textures->Unload(graphics);
	App->audio->UnLoadFX(LightDamage_Sound);
	App->audio->UnLoadFX(Hadoken_Sound);

	return true;
}


update_status ModulePlayer::PreUpdate() {

	  
	//MOVE BACKWARD
	inputplayer1.A_active = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
	//MOVE FORWARD
	inputplayer1.D_active = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
	//CROUCH
	inputplayer1.S_active = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
	//JUMP
	inputplayer1.W_active = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
	//LIGHT PUNCH
	inputplayer1.Punch1_active = App->input->keyboard[SDL_SCANCODE_C] == KEY_DOWN;
	//LIGHT KICK
	inputplayer1.Kick1_active = App->input->keyboard[SDL_SCANCODE_V] == KEY_DOWN;
	//HADOKEN
	inputplayer1.Special1_active = App->input->keyboard[SDL_SCANCODE_B] == KEY_DOWN;

	{



		if (currentstate == damagedstate) {
			
				if (current_animation->Finished()) {
					currentstate = idlestate;
					damaged.Reset();
				}
			
		}







		//}

		if (currentstate == punchlight) {
			if(!App->player->flip){
				if (current_animation->Finished()) {

					attack_collider->to_delete = true;
					currentstate = idlestate;
					alreadyHit = false;
					lightPunch.Reset();
					LOG("PUNCH TO IDLE");
				}
			}
			if(App->player->flip){
				if (App->player2->lightPunch2.Finished()) {

					attack_collider->to_delete = true;
					currentstate = idlestate;
					alreadyHit = false;
					App->player2->lightPunch2.Reset();
					LOG("PUNCH TO IDLE");
				}
			}
			LOG("PUNCH");
		}

		if (currentstate == kicklight) {
			if (!App->player->flip) {
				if (current_animation->Finished()) {
					currentstate = idlestate;
					attack_collider->to_delete = true;
					alreadyHit = false;
					lightKick.Reset();
					LOG("KICK TO IDLE");
				}
			}
			if (App->player->flip) {
				if (App->player2->lightKick2.Finished()) {

					attack_collider->to_delete = true;
					currentstate = idlestate;
					alreadyHit = false;
					App->player2->lightKick2.Reset();
					LOG("PUNCH TO IDLE");

				}
			}
		}

		if (currentstate == jumpstate) {
			if (!flip) {
				if (airkick) {
					if (inputplayer1.Punch1_active) {
						attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 80 ,35 ,40 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
						currentstate = jumppunchstate;
					}
					if (inputplayer1.Kick1_active) {
						attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 90 ,35 ,40 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
						currentstate = jumpkickstate;
					}
				}
			}
			if (flip) {
				if (airkick) {
					if (inputplayer1.Punch1_active) {
						attack_collider = App->collision->AddCollider({ position.x -20 ,position.y - 80 ,35 ,40 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
						currentstate = jumppunchstate;
					}
					if (inputplayer1.Kick1_active) {
						attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 90 ,35 ,40 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
						currentstate = jumpkickstate;
					}
				}
			}
		}

		if (currentstate == hadoukenstate) {

			if (!flip) {
				if (current_animation->Finished()) {
					App->particles->hadouken.speed.x = 5;
					App->particles->hadouken.life = 2000;
					App->particles->AddParticle(App->particles->hadouken, position.x + 25, position.y - 70, COLLIDER_PLAYER_SHOT);
					currentstate = idlestate;
					hadouken.Reset();
				}
			}
			if (flip) {
				if (App->player2->hadouken2.Finished()) {

					App->particles->hadouken2.speed.x = -5;
					App->particles->hadouken2.life = 2000;
					App->particles->AddParticle(App->particles->hadouken2, position.x -20, position.y - 70, COLLIDER_PLAYER_SHOT);
					currentstate = idlestate;
					App->player2->hadouken2.Reset();
					LOG("PUNCH TO IDLE");

				}
			}
		}
		
		if (currentstate == idlestate) {
			if (inputplayer1.A_active) {
				currentstate = backwardstate;
				LOG("IDLE TO BACK");
			}
			if (inputplayer1.D_active) {
				currentstate = forwardstate;
				LOG("IDLE TO forward");
			}
			if (inputplayer1.S_active) {
				currentstate = crouched;
				LOG("IDLE to CROUCH");
			}

			if (!flip) {
				if (inputplayer1.Punch1_active) {
					currentstate = punchlight;
					attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO PUNCH");
				}
				if (inputplayer1.Kick1_active) {
					currentstate = kicklight;
					attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO KICK");
				}
			}
			if (flip) {
				if (inputplayer1.Punch1_active) {
					currentstate = punchlight;
					attack_collider = App->collision->AddCollider({ position.x -35,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO PUNCH");
				}
				if (inputplayer1.Kick1_active) {
					currentstate = kicklight;
					attack_collider = App->collision->AddCollider({ position.x -35,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO KICK");
				}
			}
			if (inputplayer1.Special1_active) {
				App->audio->PlayFx(Hadoken_Sound); //PONER HADOUKEN SOUNDS 
				currentstate = hadoukenstate;
				LOG("IDLE TO hadouken");
			}
			if (inputplayer1.W_active) {
				currentstate = jumpstate;
				LOG("IDLE TO jump");
				current_animation = &jump;
			}
		}

		if (currentstate == backwardstate) {
			if (!inputplayer1.A_active) {
				currentstate = idlestate;
				LOG("BACK TO IDLE");
			}
			if (!flip) {
				if (inputplayer1.Punch1_active) {
					currentstate = punchlight;
					attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO PUNCH");
				}
				if (inputplayer1.Kick1_active) {
					currentstate = kicklight;
					attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO KICK");
				}
			}
			if (flip) {
				if (inputplayer1.Punch1_active) {
					currentstate = punchlight;
					attack_collider = App->collision->AddCollider({ position.x ,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO PUNCH");
				}
				if (inputplayer1.Kick1_active) {
					currentstate = kicklight;
					attack_collider = App->collision->AddCollider({ position.x ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO KICK");
				}



			}
			if (inputplayer1.W_active) {
				currentstate =jumpbackward;
				LOG("BACK TO JUMP");
			}
			
			if (inputplayer1.S_active) {
				currentstate = crouched;
				LOG("BACK TO KICK");
			}
		}

		if (currentstate == forwardstate) {
			if (!inputplayer1.D_active) {
				LOG("FORWARD TO IDLE");
				currentstate = idlestate;
			}
			if (!flip) {
				if (inputplayer1.Punch1_active) {
					currentstate = punchlight;
					attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO PUNCH");
				}
				if (inputplayer1.Kick1_active) {
					currentstate = kicklight;
					attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO KICK");
				}
			}
			if (flip) {
				if (inputplayer1.Punch1_active) {
					currentstate = punchlight;
					attack_collider = App->collision->AddCollider({ position.x ,position.y - 80 ,35 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO PUNCH");
				}
				if (inputplayer1.Kick1_active) {
					currentstate = kicklight;
					attack_collider = App->collision->AddCollider({ position.x ,position.y - 100 ,50 ,50 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					LOG("BACK TO KICK");
				}
			}
			if (inputplayer1.W_active) {
				currentstate = jumpforward; 
				LOG("FORWARD TO JUMP");
			}
			if (inputplayer1.S_active) {
				currentstate = crouched;
				LOG("BACK TO KICK");
			}
		}

		if (currentstate == jumpbackward) {
			LOG("BACKWARDJUMP TO IDLE"); 
			if (!flip) {
				if (airkick) {
					if (inputplayer1.Punch1_active) {
						attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 65 ,35 ,30 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
						currentstate = jumpbackwardpunch;
						LOG("BACKWARDJUMP TO BACKWARDJUMPPUNCH");
					}
					if (inputplayer1.Kick1_active) {
						attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 50 ,60 ,30 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS 
						currentstate = jumpbackwardkick;
						LOG("BACKWARDJUMP TO BACKWARDJUMPKICK");
					}
				}
			}
			if (flip) {
				if (airkick) {
					if (inputplayer1.Punch1_active) {
						attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 65 ,35 ,30 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
						currentstate = jumpbackwardpunch;
						LOG("BACKWARDJUMP TO BACKWARDJUMPPUNCH");
					}
					if (inputplayer1.Kick1_active) {
						attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 50 ,60 ,30 }, COLLIDER_PLAYER_ATTACK, App->player);
						App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS 
						currentstate = jumpbackwardkick;
						LOG("BACKWARDJUMP TO BACKWARDJUMPKICK");
					}
				}
			}
		}
		if (currentstate == jumpforward) {
			LOG("FORWARDJUMP TO IDLE");
			if (airkick) {
			if (inputplayer1.Punch1_active) {
				attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 65 ,35 ,30 }, COLLIDER_PLAYER_ATTACK, App->player);
				App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
				currentstate = jumpforwardpunch;
				LOG("FORWARDJUMP TO FORWARDJUMPPUNCH");
			}
			if (inputplayer1.Kick1_active) {
				attack_collider = App->collision->AddCollider({ position.x + 65 ,position.y - 50 ,60 ,30 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound); //PONER SOUNDS
					currentstate = jumpforwardkick;
					LOG("FORWARDJUMP TO FORWARDJUMPKICK");
				}
			}
		}

		if (currentstate == jumpbackwardkick) {	
			LOG("BACKWARDJUMPKICK TO JUMP");
			if (jumpbackkick.Finished()) {
				attack_collider->to_delete = true;
				currentstate = jumpbackward;
				airkick = false;
				alreadyHit = false;
				jumpbackkick.Reset();
			}
			if (App->player2->jumpfrontkick2.Finished()) {
				currentstate = jumpbackward;
				airkick = false;
				alreadyHit = false;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
				App->player2->jumpfrontkick2.Reset();
			}
		}
		
		if (currentstate == jumpbackwardpunch) {
			LOG("BACKWARDJUMPPUNCH TO JUMP");
		}

		if (airkick) {
			if (currentstate == jumpforwardkick) {
				if (jumpfrontkick.Finished()) {
					LOG("FORWARDJUMPKICK TO JUMPFORWARD")
					attack_collider->to_delete = true;
					App->player2->jump2.Reset();
					currentstate = jumpforward;
					airkick = false;
					alreadyHit = false;
				}
				if (App->player2->jumpbackkick2.Finished()) {
					LOG("FORWARDJUMPKICK TO JUMPFORWARD")
					App->player2->jump2.Reset();
					currentstate = jumpforward;
					airkick = false;
					alreadyHit = false;
					if (attack_collider != nullptr) {
						attack_collider->to_delete = true;
					}

				}
			}
		}

		if (currentstate == jumpforwardpunch) {
			LOG("FORWARDJUMPPUNCH TO JUMPFORWARD");
		}
		if (currentstate == punchcrouch) {
			LOG("CROUCH TO CROUCHPUNCH");
			if (current_animation->Finished()) {
				attack_collider->to_delete = true;
				currentstate = crouched;
				alreadyHit = false;
				App->player2->crouchpunch2.Reset();
				crouchpunch.Reset();
			}
		}

		if (currentstate == kickcrouch) {
			LOG("CROUCH TO KICKCROUCH");
			if (current_animation->Finished()) {
				attack_collider->to_delete = true;
				alreadyHit = false;
				currentstate = crouched;
				crouchkick.Reset();
				App->player2->crouchkick2.Reset();
			}
		}
		
		if (currentstate == crouched) {
			if (flip) {
				if (inputplayer1.Punch1_active) {
					attack_collider = App->collision->AddCollider({ position.x - 30 ,position.y - 60 ,38 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound);
					currentstate = punchcrouch;
				}
				if (inputplayer1.Kick1_active) {
					attack_collider = App->collision->AddCollider({ position.x - 40 ,position.y - 24 ,50 ,25 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound);
					currentstate = kickcrouch;
				}
			}

			if (!flip) {
				if (inputplayer1.Punch1_active) {
					attack_collider = App->collision->AddCollider({ position.x +65 ,position.y - 60 ,38 ,20 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound);
					currentstate = punchcrouch;
				}
				if (inputplayer1.Kick1_active) {
					attack_collider = App->collision->AddCollider({ position.x +65 ,position.y - 24 ,50 ,25 }, COLLIDER_PLAYER_ATTACK, App->player);
					App->audio->PlayFx(LightDamage_Sound);
					currentstate = kickcrouch;
				}
			}
			if (!flip) {
				if (!inputplayer1.S_active) {
					crouch.Reset();
					currentstate = idlestate;
					LOG("CROUCH TO IDLE");
				}
			}
			if (flip) {
				if (!inputplayer1.S_active) {
					App->player2->crouch2.Reset();
					currentstate = idlestate;
					LOG("CROUCH TO IDLE");
				}
			}
		}
	
		if (currentstate == jumpkickstate) {
			LOG("KICKJUMP TO IDLE");
			if (!flip) {
				if (jumpkick.Finished()) {
					currentstate = jumpstate;
					airkick = false;
					attack_collider->to_delete = true;
					alreadyHit = false;
				}
			}
			if (flip) {
				if (App->player2->jumpkick2.Finished()) {
					currentstate = jumpstate;
					airkick = false;
					if (attack_collider != nullptr) {
						attack_collider->to_delete = true;
					}
				}
			}
		}
	
		if (currentstate == jumppunchstate) {
			LOG("PUNCHJUMP ACTIVE");
			if (current_animation->Finished()&& (position.y == groundLevel)) {
				currentstate = jumpstate;
				jumpbackpunch.Reset();
			}
		}
		
		if (currentstate == jumpfalling) {
			if (current_animation->Finished()); {
				currentstate = idlestate;
				jump.Reset();
			}
		}




	}
	return UPDATE_CONTINUE;
}

float gravity = 1;

update_status ModulePlayer::Update()
{
	if (!flip) {
		switch (currentstate) {

		case jumpfalling:

			current_animation = &jump;
			position.y -= speed * gravity;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				jump.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				attack_collider->to_delete = true;
			}
			LOG("JUMPFALLING ANIMATION ACTIVE");
			break;

		case jumpbackwardkick:

			current_animation = &jumpbackkick;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x -= speed;
			position.y -= speed * gravity;

			attack_collider->rect.y = position.y-50;
			attack_collider->rect.x = position.x - App->render->camera.x+65;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				jump.Reset();
				jumpbackkick.Reset();
				backwardjump.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				attack_collider->to_delete = true;
				alreadyHit = false;
			}
			LOG("JUMPBACKKICK ANIMATION ACTIVE");
			break;

		case jumpbackwardpunch:

			current_animation = &jumpbackpunch;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x -= speed;
			position.y -= speed * gravity;
			attack_collider->rect.y = position.y - 65;
			attack_collider->rect.x =  65 - App->render->camera.x + position.x;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				jump.Reset();
				airkick = true;
				jumpbackpunch.Reset();
				backwardjump.Reset();
				currentstate = idlestate;
				gravity = 1;
				attack_collider->to_delete = true;
				alreadyHit = false;
			}
			LOG("JUMPBACKPUNCH ANIMATION ACTIVE");
			break;

		case jumpforwardkick:

			current_animation = &jumpfrontkick;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x += speed;
			position.y -= speed * gravity;
			attack_collider->rect.y = position.y -50;
			attack_collider->rect.x = position.x +65 - App->render->camera.x;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				jump.Reset();
				airkick = true;
				jumpfrontkick.Reset();
				currentstate = idlestate;
				gravity = 1;
				forwardjump.Reset();
				attack_collider->to_delete = true;
				alreadyHit = false;
			}
			LOG("JUMPFRONTKICK ANIMATION ACTIVE");
			break;

		case  jumpforwardpunch:

			current_animation = &jumpfrontpunch;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x += speed;
			position.y -= speed * gravity;
			attack_collider->rect.y -= speed * gravity;
			attack_collider->rect.x += speed;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				jumpfrontpunch.Reset();
				jump.Reset();
				forwardjump.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				attack_collider->to_delete = true;
				alreadyHit = false;
			}
			LOG("JUMPFRONTPUNCH ANIMATION ACTIVE");
			break;

		case damagedstate:

			current_animation = &damaged;
			LOG("DAMAGED ANIMATION ACTIVE");
			break;

		case jumpforward:
			position.x += speed;
			position.y -= speed * gravity;
			current_animation = &forwardjump;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			
			if (position.y <= maxHeight)
			{
				gravity = -1;
			}
			else if (position.y == groundLevel) {
				jump.Reset();
				airkick = true;
				currentstate = idlestate;
				jumpfrontkick.Reset();
				gravity = 1;
				forwardjump.Reset();
				if (attack_collider != nullptr){
					attack_collider->to_delete = true;
				}
			}
			LOG("FORWARD JUMP ANIMATION ACTIVE");
			break;

		case jumpbackward:
			
			current_animation = &backwardjump;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x -= speed;
			position.y -= speed * gravity;
			
			if (position.y <= maxHeight)
			{
				gravity = -1;
			}
			else if (position.y == groundLevel) {
				jump.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				jumpbackkick.Reset();
				backwardjump.Reset();
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
			}
			LOG("backward JUMP ANIMATION ACTIVE");
			break;

		case punchcrouch:

			current_animation = &crouchpunch;
			

			LOG("CROUCH PUNCH ANIMATION ACTIVE")
				break;

		case kickcrouch:

			current_animation = &crouchkick;
			LOG("CROUCH KICK ANIMATION ACTIVE");
			break;

		case idlestate:
			player_collider->rect.h = 93;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			current_animation = &idle;
			LOG("IDLE ANIMATION ACTIVE");
			break;

		case backwardstate:
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			current_animation = &backward;
			position.x -= speed;
			LOG("BACKWARD ANIMATION ACTIVE");
			break;

		case forwardstate:
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			current_animation = &forward;
			position.x += speed;
			LOG("FORWARD ANIMATION ACTIVE");
			break;

		case jumpstate:

			current_animation = &jump;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.y -= speed * gravity;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				
				jump.Reset();
				airkick = true;
				jumpkick.Reset();
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
				
			}
			LOG("JUMP ANIMATION ACTIVE");
			break;

		case punchlight:
			current_animation = &lightPunch;

			LOG("PUNCH ANIMATION ACTIVE");
			break;

		case kicklight:

			current_animation = &lightKick;
			LOG("KICK ANIMATION ACTIVE");
			break;

		case crouched:

			current_animation = &crouch;
			player_collider->rect.h = 65;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 68 - App->render->camera.y);
			LOG("CROUCHED ANIMATION ACTIVE");
			break;

		case hadoukenstate:

			current_animation = &hadouken;
			LOG("KADOUKEN ANIMATION ACTIVE");
			break;

		case jumpkickstate:

			current_animation = &jumpkick;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.y -= speed * gravity;
			attack_collider->rect.y -= speed * gravity;

			if (position.y <= maxHeight)
			{
				gravity = -1;

			}
			else if (position.y == groundLevel) {
				jump.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				backwardjump.Reset();
				attack_collider->to_delete = true;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
			}
			LOG("JUMP KICK ACTIVE");
			break;

		case jumppunchstate:
			current_animation = &jumpbackpunch;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			attack_collider->rect.y -= speed * gravity;
			position.y -= speed * gravity;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}
			else if (position.y == groundLevel) {
				jump.Reset();
				jumppunch.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				backwardjump.Reset();
				attack_collider->to_delete = true;
				alreadyHit = false;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}

			}
			LOG("JUMP PUNCH ACTIVE");
			break;
		}
	}
	if (flip) { // FLIP HERE AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
		switch (currentstate) {

		case jumpfalling:

			current_animation = &jump;
			position.y -= speed * gravity;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				jump.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
			}
			LOG("JUMPFALLING ANIMATION ACTIVE");
			break;

		case jumpbackwardkick:

			current_animation = &App->player2->jumpfrontkick2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x -= speed;
			position.y -= speed * gravity;

			attack_collider->rect.y = position.y - 40;
			attack_collider->rect.x = position.x - App->render->camera.x - 50;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				
				App->player2->jump2.Reset();
				App->player2->jumpfrontkick2.Reset();
				App->player2->jumpfrontpunch2.Reset();
				App->player2->forwardjump2.Reset();

				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
			}
			LOG("JUMPBACKKICK ANIMATION ACTIVE");
			break;

		case jumpbackwardpunch:

			current_animation = &App->player2->jumpfrontpunch2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x -= speed;
			position.y -= speed * gravity;

			attack_collider->rect.y = position.y - 60;
			attack_collider->rect.x = position.x - App->render->camera.x -20;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {

				App->player2->jumpfrontpunch2.Reset();
				App->player2->forwardjump2.Reset();
				App->player2->jumpfrontkick2.Reset();

				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
			}
			LOG("JUMPBACKPUNCH ANIMATION ACTIVE");
			break;

		case jumpforwardkick:

			current_animation = &App->player2->jumpbackkick2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x += speed;
			position.y -= speed * gravity;

			attack_collider->rect.y = position.y - 40;
			attack_collider->rect.x = position.x - App->render->camera.x -50;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				

				App->player2->jump2.Reset();
				App->player2->jumpbackkick2.Reset();
				App->player2->jumpbackpunch2.Reset();
				App->player2->backwardjump2.Reset();

				airkick = true;
				
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
				
			}
			LOG("JUMPFRONTKICK ANIMATION ACTIVE");
			break;

		case  jumpforwardpunch:

			current_animation = &App->player2->jumpbackpunch2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x += speed;
			position.y -= speed * gravity;

			attack_collider->rect.y = position.y - 60;
			attack_collider->rect.x = position.x - App->render->camera.x -20;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {

				App->player2->jump2.Reset();
				App->player2->jumpbackkick2.Reset();
				App->player2->jumpbackpunch2.Reset();
				App->player2->backwardjump2.Reset();



				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
			}
			LOG("JUMPFRONTPUNCH ANIMATION ACTIVE");
			break;

		case damagedstate:

			current_animation = &damaged;
			LOG("DAMAGED ANIMATION ACTIVE");
			break;

		case jumpforward:
			position.x += speed;
			position.y -= speed * gravity;

			current_animation = &App->player2->backwardjump2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			if (position.y <= maxHeight)
			{
				gravity = -1;
			}
			else if (position.y == groundLevel) {
				
				App->player2->jump2.Reset();
				App->player2->jumpbackkick2.Reset();
				App->player2->jumpbackpunch2.Reset();
				App->player2->backwardjump2.Reset();

				airkick = true;
				currentstate = idlestate;
				
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
				
			}
			LOG("FORWARD JUMP ANIMATION ACTIVE");
			break;

		case jumpbackward:

			current_animation = &App->player2->forwardjump2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.x -= speed;
			position.y -= speed * gravity;
			if (position.y <= maxHeight)
			{
				gravity = -1;
			}
			else if (position.y == groundLevel) {
				App->player2->jumpfrontkick2.Reset();
				App->player2->jumpfrontpunch2.Reset();
				App->player2->forwardjump2.Reset();
				App->player2->jump2.Reset();

				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
			}
			LOG("backward JUMP ANIMATION ACTIVE");
			break;

		case punchcrouch:

			current_animation = &App->player2->crouchpunch2;
			LOG("CROUCH PUNCH ANIMATION ACTIVE")
				break;

		case kickcrouch:

			current_animation = &App->player2->crouchkick2;
			LOG("CROUCH KICK ANIMATION ACTIVE");
			break;

		case idlestate:
			
			
			player_collider->rect.h = 93;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);

			current_animation = &App->player2->idle2;
			LOG("IDLE ANIMATION ACTIVE");
			break;

		case backwardstate:
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			current_animation = &App->player2->forward2;
			position.x -= speed;
			LOG("BACKWARD ANIMATION ACTIVE");
			break;

		case forwardstate:
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			current_animation = &App->player2->backward2;
			position.x += speed;
			LOG("FORWARD ANIMATION ACTIVE");
			break;

		case jumpstate:

			current_animation = &App->player2->jump2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.y -= speed * gravity;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}

			else if (position.y == groundLevel) {
				
				App->player2->jump2.Reset();
				App->player2->jumppunch2.Reset();
				App->player2->jumpkick2.Reset();
				
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
			}
			LOG("JUMP ANIMATION ACTIVE");
			break;

		case punchlight:
			current_animation = &App->player2->lightPunch2;

			LOG("PUNCH ANIMATION ACTIVE");
			break;

		case kicklight:

			current_animation = &App->player2->lightKick2;
			LOG("KICK ANIMATION ACTIVE");
			break;

		case crouched:

			current_animation = &App->player2->crouch2;
			player_collider->rect.h = 65;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 68 - App->render->camera.y);
			LOG("CROUCHED ANIMATION ACTIVE");
			break;

		case hadoukenstate:

			current_animation = &App->player2->hadouken2;
			LOG("KADOUKEN ANIMATION ACTIVE");
			break;

		case jumpkickstate:

			current_animation = &App->player2->jumpkick2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.y -= speed * gravity;
			attack_collider->rect.x = position.x - 20 - App->render->camera.x;
			attack_collider->rect.y = position.y - 90;
			if (position.y <= maxHeight)
			{
				gravity = -1;

			}
			else if (position.y == groundLevel) {
				App->player2->jump2.Reset();
				App->player2->jumppunch2.Reset();
				App->player2->jumpkick2.Reset();

				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
				
			}
			LOG("JUMP KICK ACTIVE");
			break;

		case jumppunchstate:
			current_animation = &App->player2->jumpfrontpunch2;
			player_collider->SetPos(position.x - App->render->camera.x + 5, position.y - 93 - App->render->camera.y);
			position.y -= speed * gravity;
			attack_collider->rect.x = position.x - 20 - App->render->camera.x;
			attack_collider->rect.y = position.y - 70;

			if (position.y <= maxHeight)
			{
				gravity = -1;
			}
			else if (position.y == groundLevel) {
				App->player2->jump2.Reset();
				App->player2->jumppunch2.Reset();
				App->player2->jumpkick2.Reset();
				airkick = true;
				currentstate = idlestate;
				gravity = 1;
				if (attack_collider != nullptr) {
					attack_collider->to_delete = true;
				}
				
			}
			LOG("JUMP PUNCH ACTIVE");
			break;
		}
	}
	//Limits ben fets
	if (position.x <= (App->render->camera.x-10) /SCREEN_SIZE)
	{
		position.x = (App->render->camera.x -10) / SCREEN_SIZE;
	}
	if (position.x >= (SCREEN_WIDTH +App->render->camera.x ) / SCREEN_SIZE +127) 
	{ 
		position.x = (SCREEN_WIDTH +App->render->camera.x ) / SCREEN_SIZE +127;
	}
	/*if (position.y < groundLevel + 20) {
		position.y = groundLevel;
	}*/
	if (position.x > App->player2->position.x +75) {
		flip = true;
	}
	else {
		flip = false;
	}
	

	SDL_Rect r = current_animation->GetCurrentFrame();
	if (!flip) {
		App->render->Blit(graphics, position.x, position.y - r.h, &r);
	}
	if (flip) {
		App->render->Blit(graphics2, position.x - 87, position.y - r.h, &r);
	}
	return UPDATE_CONTINUE;
}

//TODO 7.4: Detect collision with a wall. If so, go back to intro screen.
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (!alreadyHit) {
		if (c1->type == COLLIDER_PLAYER_ATTACK) {
			
			App->scene_ryu->health2.w -= App->scene_ryu->damage;
			alreadyHit = true;
			
				
			
		}
	}

}