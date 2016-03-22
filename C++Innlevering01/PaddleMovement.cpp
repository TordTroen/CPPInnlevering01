#include "PaddleMovement.h"
#include "SDLWrapper.h"
#include "Vector2D.h"


PaddleMovement::PaddleMovement()
{
}


PaddleMovement::~PaddleMovement()
{
}

void PaddleMovement::Update()
{
	// TODO Make IOmanager and Time a singleton
	//Vector2D velocity = Vector2D(io.GetAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT), 0);// , io.GetAxis(SDL_SCANCODE_DOWN, SDL_SCANCODE_UP));
	//float speed = 10;
	//velocity = velocity * time.DeltaTime() * speed;
	//player->GetTransform()->Translate(velocity, true);
}
