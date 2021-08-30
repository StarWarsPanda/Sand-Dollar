#include "SDL2/SDL.h"
#include "Entity.h"
#include "Camera.h"
#include "SDL/SDL_image.h"
#include <iostream>

#define eKey e.key.keysym.sym

#define gravity 10.0f

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);

	SDL_Window * window = SDL_CreateWindow("Sand Dollar", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WindowFlags::SDL_WINDOW_ALLOW_HIGHDPI);

	SDL_Renderer* canvas = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	IMG_Init(IMG_INIT_PNG);

	SDL_Texture* buttonTestImage = NULL;

	SDL_Event e;

	Camera2d camera;

	camera.setPos(0.0f, 0.0f);

	const Uint8* keyState = SDL_GetKeyboardState(NULL);

	Entity* allEntitys = (Entity*)malloc(100 * sizeof Entity);

	allEntitys[0] = Entity(255,0,0,255,40 - 25,200 - 25,50,50);

#define player allEntitys[0]


#define platforms(num) allEntitys[1 + num]

	allEntitys[1] = Entity(15, 15, 225, 255, 0, 150, 7800, 400);
	allEntitys[2] = Entity(15, 15, 225, 255, -101, -3800, 100, 4000);

	player.acceleration = { 0.0f,0.0001f };
	player.speed = { 0.0f,0.0f };

	int64_t frame = 0;

	bool quit = false;

	SDL_Surface* img = IMG_Load("C:/Users/mgmus/Desktop/Projects/Sand_Dollar/Resc/Button/B_Up.png");
	buttonTestImage = SDL_CreateTextureFromSurface(canvas, img);
	SDL_FreeSurface(img);

	int w = 276, h = 110;

	SDL_Rect buttonRect = { 320,240,w,h };

	while (!quit)
	{
		frame++;

		while (SDL_PollEvent(&e))
		{
			switch (e.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
			}
		}

		if (keyState[SDL_SCANCODE_R]) 
		{ 
			player.speed = { 0.0f,0.0f };
			player.setPos(0, -5); 
		}
		if (keyState[SDL_SCANCODE_LEFT]) player.speed.x = -0.1f;
		if (keyState[SDL_SCANCODE_RIGHT]) player.speed.x = 0.1f;
		if (keyState[SDL_SCANCODE_UP] && player.speed.y == 0.0f) player.speed.y = -0.15f;
		if (keyState[SDL_SCANCODE_DOWN]) player.speed.x *= 0.1f;

		if (keyState[SDL_SCANCODE_LSHIFT])
		{
		}
		

		player.moveEntityWithCollision(allEntitys, 3, 1);
		
		camera.setPos(player.pos().x + ((int)(player.size().x) >> 1), player.pos().y + (((int)(player.size().y) >> 1)));

		SDL_SetRenderDrawColor(canvas, 12, 12, 24, 255);

		SDL_RenderClear(canvas);

		Camera::drawEntityList(camera, allEntitys, 3, canvas);
		
		if (SDL_RenderCopy(canvas, buttonTestImage, NULL, &buttonRect) == -1) 
		{
			std::cout << "Error: " << SDL_GetError() << " on frame " << frame << std::endl;
			if (!buttonTestImage) std::cout << "Error: Texture NULL" << std::endl;
		}

		SDL_RenderPresent(canvas);
	}

	SDL_DestroyTexture(buttonTestImage);
	
	IMG_Quit();

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(canvas);

	SDL_Quit();

	return 0;
}