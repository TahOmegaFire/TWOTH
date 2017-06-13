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
	std::vector<UtilFn::Attribute> tiles;
	std::vector<UtilFn::Attribute> entities;

	if(f_Map.good())
	{
		//CleanMap();
		bool startMap = false;
		USI jay = 0;
		while(getline(f_Map, s_Map))
		{
//			std::cout << s_Map << std::endl;
			if(!startMap)
			{
				char name = s_Map[0];
				std::cout << name << std::endl;
				switch(name)
				{
				case '#': //Width
					m_Width = atoi(s_Map.substr(3).c_str());
					std::cout << "Width = " << m_Width << std::endl;
					break;

				case '$': //Length
					m_Length = atoi(s_Map.substr(3).c_str());
					std::cout << "Length = " << m_Length << std::endl;
					break;

				case 't':
				{
					UtilFn::Attribute nAtt = UtilFn::ParseMapAttribute(s_Map.substr(1));
					tiles.push_back(nAtt);
					std::cout << nAtt.name << " = " << nAtt.value << std::endl;
					break;
				}
				case 'e':
				{
					UtilFn::Attribute nAtt = UtilFn::ParseMapAttribute(s_Map.substr(1));
					entities.push_back(nAtt);
					std::cout << nAtt.name << " = " << nAtt.value << std::endl;
					break;
				}

				case '[':
					if(strcmp(s_Map.c_str(), "[MAP]") == 0)
					{
						startMap = true; //Yee
						CleanMap();
					}

				default:
					break;
				}
				
			}
			else
			{
				//Read map struct data
				for(USI i = 0; i < s_Map.length(); i++)
				{
					bool put = false;
					for(USI j = 0; j < tiles.size(); j++)
					{
						if(s_Map[i] == tiles[j].name[0])
						{
							m_Tiles[i][jay].tileType = tiles[j].value;
							put = true;
							break;
						}
					}

					if(!put)
					{
						for(USI j = 0; j < entities.size(); j++)
						{
							if(s_Map[i] == entities[j].name[0])
							{
								m_Tiles[i][jay].tileType = "floor0";
								std::string path = "Res/Data/Ent/";
								path.append(entities[j].value);
								path.append(".ent");
								m_Tiles[i][jay].m_Entity.LoadEntity(path.c_str());
								put = true;
								break;
							}
						}
					}

					if(!put)
						std::cout << "Sad reacts only\n";
				}
				jay++;
			}
		}
	}
	else
		std::cout << "Bad filename" << std::endl;
	
	f_Map.close();
}

void Map::PrepareMap()
{
	bool put = false;
	for(USI i = 0; i < m_Width; i++)
	{	
		for(USI j = m_Length - 1; j > 0; j--)
		{
			if(UtilFn::SearchAttributeValue("tpe", m_Tiles[i][j].m_Entity.m_Attributes) == "SpawnPoint")
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
            if(m_Tiles[i][j].tileType == "floor1") //change to strcmp?
			{
                floor1.Render(TILESIZE * i - camera_pos.x, TILESIZE * j - camera_pos.y);
			}
        }
    }
}

void Map::Update()
{
	
}
