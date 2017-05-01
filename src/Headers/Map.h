#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include "TexW.h"
#include "Utils.h"
//#include "Player.h"
#include "CollisionBox.h"
#include <vector>

class Map
{
public:
    Map();
    ~Map();
	
    std::vector<std::vector<Tile> > m_Tiles;
	std::vector<Tile> GetCollidingTiles(CollisionBox) const;
	std::vector<CollisionBox> GetCollidingTilesF(CollisionBox) const;
	//std::vector<Tile&> GetCollidingTilesF(CollisionBox) const;
	
	void CleanMap();
	void CreateTestMap();
	void PrepareMap();
	void Render(Point2D);
	void Update();
	
	USI m_Width, m_Length;
	TexW floor1;
	
	Point2D spawnPoint;
	
	//Player m_Player;
};

#endif // MAP_H
