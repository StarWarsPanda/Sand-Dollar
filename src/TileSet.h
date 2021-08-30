#pragma once

#ifndef ENT_h_
#include "Entity.h"

namespace TileSet
{

	class TileSet
	{
	public:

		TileSet();
		TileSet(int width, int height);
		~TileSet();

		void generateSetFromFile(const char* filePath);
		void draw();

	private:
		Uint8* map;
		int mapLength;
		Vector2 pos;
	};

	Uint8 charToUint8(char& chr);
}
#endif
