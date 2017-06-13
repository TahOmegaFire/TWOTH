#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "TexW.h"
#include "Utils.h"
#include "CollisionBox.h"
#include <fstream>
#include <istream>
#include <sstream>
#include <vector>
#include <cstring>
#include <cstdlib>


class Map
{
public:
    Map();
    ~Map();
	
    std::vector<std::vector<Tile> > m_Tiles;
	
	void CleanMap();
	void CreateTestMap();
	void LoadMap(std::string);
	void PrepareMap();
	void Render(Point2D);
	void Update();
	
	USI m_Width, m_Length;
	TexW floor1;
	
	Point2D spawnPoint;
	
	//Player m_Player;
};

#endif // MAP_H
