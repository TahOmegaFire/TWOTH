#include "Headers/Map.h"

Map::Map()
{
	m_Width = m_Length = 20;
	
	floor1.LoadTexture("Res/Img/Tiles/ye.png", false);
	
	CleanMap();
	std::cout << "ass\n";
}

Map::~Map()
{
	
}

void Map::CleanMap()
{
	m_Tiles.clear();
	for(USI i = 0; i < m_Width + 2; i++)
	{
		std::vector<Tile> nVector;
		
		for(USI j = 0; j < m_Length + 2; j++)
		{
			Tile nTile;
			nTile.m_Type = Tile::EMPTY;
			nTile.x = i;
			nTile.y = j;
			nVector.push_back(nTile);
		}
		
		m_Tiles.push_back(nVector);
	}
}

void Map::CreateTestMap()
{
	for(USI i = 1; i < 20; i++)
	{
		std::cout << i << std::endl;
		m_Tiles[1][i].m_Type = Tile::TILE1;
		m_Tiles[i][1].m_Type = Tile::TILE1;
		m_Tiles[m_Width - 1][i].m_Type = Tile::TILE1;
		m_Tiles[i][m_Length - 1].m_Type = Tile::TILE1;
	}
	std::cout << "hh";
	
	m_Tiles[4][18].m_Type = Tile::TILE1;
	m_Tiles[6][18].m_Type = Tile::TILE1;
	m_Tiles[6][17].m_Type = Tile::TILE1;
	//m_Tiles[8][18].m_Type = Tile::TILE1;
	//m_Tiles[8][17].m_Type = Tile::TILE1;
	m_Tiles[8][16].m_Type = Tile::TILE1;
	m_Tiles[11][18].m_Type = Tile::TILE1;
	m_Tiles[13][17].m_Type = Tile::TILE1;
	m_Tiles[15][16].m_Type = Tile::TILE1;
	m_Tiles[16][17].m_Type = Tile::TILE1;
	
	m_Tiles[9][18].m_Entity.LoadEntity("Res/Data/Ent/SpawnPoint.ent");
	//TO DO: Make collisions
}

void Map::PrepareMap()
{
	for(USI i = 0; i < m_Width; i++)
	{	
		for(USI j = m_Length - 1; j > 0; j--)
		{
			if(m_Tiles[i][j].m_Entity.entityType == "SpawnPoint")
			{
				spawnPoint.x = TILESIZE * i;
				spawnPoint.y = TILESIZE * j;
			}
		}
	}
}

std::vector<Tile> Map::GetCollidingTiles(CollisionBox col_box) const
{
	const int firstRow = col_box.Bottom() / TILESIZE;
	const int lastRow = col_box.Top() / TILESIZE;
	const int firstCol = col_box.Left() / TILESIZE;
	const int lastCol = col_box.Right() / TILESIZE;
	std::vector<Tile> colTiles;
	//UtilFn::Print2Values(firstRow, lastRow);
	//UtilFn::Print2Values(firstCol, lastCol);
	
	for(int i = firstCol; i <= lastCol; i++)
	{
		//std::cout << "rooolling FAAAAAAAAAAAAAAAAAAAAAAAA";
		for(int j = firstRow; j <= lastRow; j++) //FIRST ROW LST ROW IS BAD SEND HELPO
		{
			//UtilFn::Print2Values(i, j);
			
			colTiles.push_back(m_Tiles[i][j]);
			//std::cout << "AAAAAAAAAAAAST";
		}
		//std::cout << std::endl;
	}
	
	return colTiles;
}

std::vector<CollisionBox> Map::GetCollidingTilesF(CollisionBox col_box) const
{
	const int firstRow = col_box.Bottom() / TILESIZE;
	const int lastRow = col_box.Top() / TILESIZE;
	const int firstCol = col_box.Left() / TILESIZE;
	const int lastCol = col_box.Right() / TILESIZE;
	std::vector<CollisionBox> colTiles;
	//UtilFn::Print2Values(firstRow, lastRow);
	//UtilFn::Print2Values(firstCol, lastCol);
	
	for(int i = firstCol; i <= lastCol + 1; i++)
	{
		//std::cout << "rooolling FAAAAAAAAAAAAAAAAAAAAAAAA";
		for(int j = firstRow; j <= lastRow + 1; j++) //FIRST ROW LST ROW IS BAD SEND HELPO
		{
			//UtilFn::Print2Values(i, j);
			
			if(m_Tiles[i][j].m_Type == Tile::TILE1)
			{
				CollisionBox nBox(i * TILESIZE, j * TILESIZE, TILESIZE, TILESIZE);
				
				colTiles.push_back(nBox);
			}
			//std::cout << "AAAAAAAAAAAAST";
		}
		//std::cout << std::endl;
	}
	
	return colTiles;
}


/*std::vector<Tile&> Map::GetCollidingTilesF(CollisionBox col_box) const
{
	const int firstRow = col_box.Bottom() / TILESIZE;
	const int lastRow = col_box.Top() / TILESIZE;
	const int firstCol = col_box.Left() / TILESIZE;
	const int lastCol = col_box.Right() / TILESIZE;
	std::vector<Tile&> colTiles;
	//UtilFn::Print2Values(firstRow, lastRow);
	//UtilFn::Print2Values(firstCol, lastCol);
	
	for(int i = firstCol; i <= lastCol; i++)
	{
		//std::cout << "rooolling FAAAAAAAAAAAAAAAAAAAAAAAA";
		for(int j = firstRow; j <= lastRow; j++) //FIRST ROW LST ROW IS BAD SEND HELPO
		{
			colTiles.push_back(&m_Tiles[i][j]);
			//UtilFn::Print2Values(i, j);
			//std::cout << "AAAAAAAAAAAAST";
		}
		//std::cout << std::endl;
	}
	
	return colTiles;	
}*/

void Map::Render(Point2D camera_pos)
{
	for(USI i = 0; i < m_Width; i++)
    {
        for(USI j = 0; j < m_Length; j++)
        {
            if(m_Tiles[i][j].m_Type == Tile::TILE1)
			{
                floor1.Render(TILESIZE * i - camera_pos.x, TILESIZE * j - camera_pos.y);
			}
        }
    }
}

void Map::Update()
{
	
}