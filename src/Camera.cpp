#include "Camera.h"
#include "Entity.h"

Vector2 Camera2d::pos()
{
	return cameraPos;
}

Camera2d::Camera2d()
{

}

Camera2d::~Camera2d()
{

}

void Camera2d::setPos(float x, float y)
{
	cameraPos = { x,y };
}

void Camera::drawEntityList(Camera2d camera, Entity* eList, int eListLength, SDL_Renderer* window)
{
	Vector2* bPos = (Vector2*)malloc(eListLength * sizeof Vector2);

	for (int i = 0; i < eListLength; i++)
	{
		bPos[i] = eList[i].pos();
		eList[i].setPos(eList[i].pos().x - camera.pos().x + 320, eList[i].pos().y - camera.pos().y + 240);
	}

	drawEntityptr(eList, eListLength, window);

	for (int i = 0; i < eListLength; i++)
	{
		eList[i].setPos(bPos[i].x, bPos[i].y);
	}

	delete[] bPos;
}