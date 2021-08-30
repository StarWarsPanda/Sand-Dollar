#pragma once

#ifndef SDL_h_
#include "SDL2/SDL.h"
#endif

//#ifndef SDL_IMAGE_H_
//#include "SDL_image.h"
//#endif

#ifndef ENT_h_
#define ENT_h_
typedef struct
{
	float x, y; 
	int width, height;
}fRect;

typedef struct
{
	float x, y;
}Vector2;

class Entity
{
public:
	Vector2 speed, acceleration;

	Entity()
	{
		entity.x = 0;
		entity.y = 0;
		entity.width = 25;
		entity.height = 25;
		//texture = nullptr;
		debugColor.r = 200;
		debugColor.g = 200;
		debugColor.b = 200;
		debugColor.a = 255;
	}
	//Rect only
	Entity(int x, int y, int width, int height);
	//Rect with debug color seperated
	Entity(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int width, int height);
	//Rect with debug color
	Entity(int x, int y, int width, int height, SDL_Color color);
	//Rect with texture
	/*Entity(int x, int y, int width, int height, SDL_Renderer* window, const char* filePath);*/
	//Destructor
	~Entity();

	//Collision between two entities
	bool collision(Entity b);
	bool collisionLoop(Entity* eList, int eListLength);
	/*
	 Draws entity
			Note: Textures will override color drawing 
	* 
	*/
	void drawEntity(SDL_Renderer* window);
	void setPos(float x, float y);
	void movePos(float mx, float my);
	void moveEntityNoCollision();
	void changeColor(SDL_Color& color);
	void changeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
	void moveEntityWithCollision(Entity* eList, int eListLength);
	void moveEntityWithCollision(Entity* eList, int eListLength, int offset);

	Vector2 pos();
	Vector2 size();

	void print();


private:
	fRect entity;
	SDL_Rect box;
	/*SDL_Texture* texture;*/
	SDL_Color debugColor;

	bool bscCollision(Entity b);
};


	void drawEntityptr(Entity* eList, int eListLength, SDL_Renderer* window);

#endif

