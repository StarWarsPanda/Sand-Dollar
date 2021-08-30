#include "Entity.h"
#include <iostream>

Entity::Entity(int x, int y, int width, int height)
{
	entity.x = x;
	entity.y = y;
	entity.width = width;
	entity.height = height;
	//texture = nullptr;
	debugColor.r = 200;
	debugColor.g = 200;
	debugColor.b = 200;
	debugColor.a = 255;
}

Entity::Entity(Uint8 r, Uint8 g, Uint8 b, Uint8 a, int x, int y, int width, int height)
{
	entity.x = x;
	entity.y = y;
	entity.width = width;
	entity.height = height;
	//texture = nullptr;
	debugColor.r = r;
	debugColor.g = g;
	debugColor.b = b;
	debugColor.a = a;
}

Entity::Entity(int x, int y, int width, int height, SDL_Color color)
{
	entity.x = x;
	entity.y = y;
	entity.width = width;
	entity.height = height;
	//texture = nullptr;
	debugColor = color;
}

/*
Entity::Entity(int x, int y, int width, int height, SDL_Renderer* window, const char* filePath)
{
	entity.x = x;
	entity.y = y;
	entity.w = width;
	entity.h = height;
	texture = IMG_LoadTexture(window, filePath);
	debugColor = {0};
}
*/

Entity::~Entity()
{
	//if (texture) SDL_DestroyTexture(texture);
}

bool Entity::bscCollision(Entity b)
{
	return
	entity.x < b.entity.x + b.entity.width &&
	entity.x + entity.width > b.entity.x &&
	entity.y < b.entity.y + b.entity.height &&
	entity.y + entity.height > b.entity.y;
}

bool Entity::collision(Entity b)
{
	entity.x += 1.0f;
	if (bscCollision(b))
	{
		entity.x -= 1.0f;
		return true;
	}
	entity.x -= 2.0f;

	if (bscCollision(b))
	{
		entity.x += 1.0f;
		return true;
	}
	entity.x += 1.0f;

	entity.y += 1.0f;
	if (bscCollision(b))
	{
		entity.y -= 1.0f;
		return true;
	}
	entity.y -= 2.0f;

	if (bscCollision(b))
	{
		entity.y += 1.0f;
		return true;
	}
	entity.y += 1.0f;
	return false;
}

bool Entity::collisionLoop(Entity* eList, int eListLength)
{
	for (int i = 0; i < eListLength; i++)
	{
		if (collision(eList[i])) return true;
	}

	return false;
}

void Entity::drawEntity(SDL_Renderer* window)
{
	/*
	if (a.texture)
	{
		SDL_RenderCopy(window, a.texture, NULL, &a.entity);
		return;
	}
	*/

	SDL_Rect rect = {entity.x, entity.y, entity.width, entity.height};

	SDL_SetRenderDrawColor(window, debugColor.r, debugColor.g, debugColor.b, debugColor.a);
	SDL_RenderFillRect(window, &rect);
}

void drawEntityptr(Entity* eList, int eListLength, SDL_Renderer* window)
{
	for (int i = 0; i < eListLength; i++)
	{
		eList[i].drawEntity(window);
	}
}

Vector2 Entity::pos()
{
	return { entity.x, entity.y };
}

void Entity::moveEntityNoCollision()
{
	speed.x += acceleration.x;
	speed.y += acceleration.y;
	entity.x += speed.x;
	entity.y += speed.y;
}

void Entity::moveEntityWithCollision(Entity* eList, int eListLength)
{
	int i = 0;

	if (speed.x < 1.5f)
	{ 
		speed.x += acceleration.x;
	}
	else
	{
		speed.x = 1.5f;
	}

	if (speed.y < 1.5f)
{ 
		speed.y += acceleration.y;
	}
	else
	{
		speed.y = 1.5f;
	}

	entity.x += speed.x;

	for (i = 0; i < eListLength; i++)
	{
		if (collision(eList[i])) 
		{
			entity.x -= speed.x;
			speed.x = 0.0f;
			break;
		}
	}

	entity.y += speed.y;

	for (i = 0; i < eListLength; i++)
	{
		if (collision(eList[i]))
		{
			entity.y -= speed.y;
			if (speed.x > 0)
			{
				speed.x -= 0.001f;
			}
			if(speed.x < 0)
			{
				speed.x += 0.001f;
			}
			if (fabsf(speed.x) < 0.001f)
			{
				speed.x = 0.0f;
			}

			speed.y = 0.0f;
			break;
		}
	}
}

void Entity::moveEntityWithCollision(Entity* eList, int eListLength, int offset)
{
	int i = 0;

	if (speed.x < 1.5f)
	{
		speed.x += acceleration.x;
	}
	else
	{
		speed.x = 1.5f;
	}

	if (speed.y < 1.5f)
	{
		speed.y += acceleration.y;
	}
	else
	{
		speed.y = 1.5f;
	}

	entity.x += speed.x;

	for (i = offset; i < eListLength; i++)
	{
		if (collision(eList[i]))
		{
			entity.x -= speed.x;
			speed.x = 0.0f;
			break;
		}
	}

	entity.y += speed.y;

	for (i = offset; i < eListLength; i++)
	{
		if (collision(eList[i]))
		{
			entity.y -= speed.y;
			if (speed.x > 0)
			{
				speed.x -= 0.001f;
			}
			if (speed.x < 0)
			{
				speed.x += 0.001f;
			}
			if (fabsf(speed.x) < 0.001f)
			{
				speed.x = 0.0f;
			}

			speed.y = 0.0f;
			break;
		}
	}
}

void Entity::setPos(float x, float y)
{
	entity.x = x;
	entity.y = y;
}

void Entity::movePos(float mx, float my)
{
	entity.x += mx;
	entity.y += my;
}

Vector2 Entity::size()
{
	return { (float)entity.width, (float)entity.height };
}

void Entity::changeColor(SDL_Color& color)
{
	debugColor = color;
}

void Entity::changeColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	debugColor = { r,g,b,a };
}

void Entity::print()
{
	std::cout << "(" << entity.x << ", " << entity.y << ")" << std::endl;
}