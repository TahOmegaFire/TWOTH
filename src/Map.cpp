#include "Headers/Map.h"

Map::Map()
{
	m_Width = m_Length = 20;
	
	floor1.LoadTexture("Res/Img/Tiles/ye.png", false);
	
	CleanMap();
}

Map::~Map()
{
	
}

void Map::CleanMap()
{
	m_Tiles.clear();
	for(USI i = 0; i < m_Width; i++)
	{
		std::vector<Tile> nVector;
		
		for(USI j = 0; j < m_Length; j++)
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

void Map::LoadMap(std::string map_dir)
{
	std::ifstream f_Map;
	f_Map.open(map_dir.c_str(), std::ifstream::in);
	std::string s_Map;
	USI len = 0;
	USI wid = 0;
	
	while(getline(f_Map, s_Map))
	{
		std::cout << s_Map << std::endl;
		++len;
		if(s_Map.size() > wid)
		{
			if(wid != 0)
				std::cout << "Warning: Variable size in map file" << std::endl;
			wid = s_Map.size();
		}
	}
	
	m_Length = len;
	m_Width = wid;
	//check what values are m_Len and m_Wid
	
	CleanMap();
	std::cout << "We good nig\n";
	
	f_Map.clear();
	f_Map.seekg(0, f_Map.beg);

	std::cout << "We stiil good\n";
	
	len = 0;
	wid = 0;

	char c;
	while(f_Map >> std::noskipws >> c)
	{

		std::cout << "Once again good\n";

		if(c == 'F')
			m_Tiles[wid][len].m_Type = Tile::EMPTY;
		else if(c == 'S')
		{
			m_Tiles[wid][len].m_Type = Tile::EMPTY;
			spawnPoint.x = TILESIZE * wid;
			spawnPoint.y = TILESIZE * len;
		}
		else
			m_Tiles[wid][len].m_Type = Tile::TILE1;

		wid++;
		if(wid == m_Width) //Maybe change to m_Width - 1?
			len++;
	}
	
	std::cout << "We aren't supposed to be this good nigga\n";

	f_Map.close();
	
	//PrepareMap();
}

void Map::PrepareMap()
{
	bool put = false;
	for(USI i = 0; i < m_Width; i++)
	{	
		for(USI j = m_Length - 1; j > 0; j--)
		{
			if(m_Tiles[i][j].m_Entity.entityType == "SpawnPoint")
			{
				spawnPoint.x = TILESIZE * i;
				spawnPoint.y = TILESIZE * j;
				put = true;
			}
		}
	}

	if(!put)
		std::cout << "Could not automatically put spawn point\n";
}

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
