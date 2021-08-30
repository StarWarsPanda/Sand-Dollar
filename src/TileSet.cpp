#include "TileSet.h"
#include <fstream>

TileSet::TileSet::TileSet()
{
	mapLength = 1;
	map = (Uint8*)malloc(sizeof Uint8);
	pos = { 0,0 };
}

TileSet::TileSet::TileSet(int width, int height)
{
	mapLength = width * height;
	map = (Uint8*)malloc(mapLength * sizeof Uint8);
	pos = { 0, 0 };
}

TileSet::TileSet::~TileSet()
{
	delete[] map;
}

void TileSet::TileSet::generateSetFromFile(const char* filePath)
{
	char* txt = 0;

	int i = 0;

	std::ifstream Map;
	Map.open(filePath);

	while (Map.get(txt, mapLength))
	{
		map[i] = charToUint8(*txt);
		i++;
	}

	delete txt;
	Map.close();
}

void TileSet::TileSet::draw()
{

}

Uint8 TileSet::charToUint8(char& chr)
{
	switch (chr)
	{
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		default: return 255;
	}
}
