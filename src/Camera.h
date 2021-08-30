#pragma once

#include "Entity.h"

class Camera2d
{
public:
	Camera2d();
	~Camera2d();
	Vector2 pos();
	void setPos(float x, float y);

private:
	Vector2 cameraPos;

};

namespace Camera
{
	void drawEntityList(Camera2d camera, Entity* eList, int eListLength, SDL_Renderer* window);
}

