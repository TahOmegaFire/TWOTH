#include "Headers/Player.h"
#include <exception>

Player::Player()
{
    m_Texture.LoadTexture("Res/Img/Player/test.png", false);
    m_XVel = 0.0f;
    m_XAccel = 0.4f;
	m_YAccel = 20.0f;
    m_XFriction = 0.0f;
	collisionBox.m_W = m_Texture.m_Width;
	collisionBox.m_H = 64; //You'll have to eventually change this thing fam
	//UtilFn::Print2Values(collisionBox.m_W, collisionBox.m_H);
	isOnGround = true;
}

Player::~Player()
{

}

bool Player::LoadEntity(const char* path)
{
    return false; //TO DO: This shouldn't just be a return false function mate
}

void Player::Update(const Uint8* keys, const Map& map)
{
    //Movement
	int curTileX = collisionBox.m_X / 64;
	int curTileY = collisionBox.m_Y / 64;
	//if(keys[SDL_SCANCODE_SPACE])
		//UtilFn::Print2Values(curTileX, curTileY);
    MoveX(keys, map);
	MoveY(keys, map);
}

void Player::MoveX(const Uint8* keys, const Map& map)
{
	CollisionBox collider(collisionBox.m_X, collisionBox.m_Y, collisionBox.m_W, collisionBox.m_H);
	
	if(keys[SDL_SCANCODE_RIGHT])
	{
		if(m_XVel < 5)
			m_XVel += m_XAccel;
	}

	else if(keys[SDL_SCANCODE_LEFT])
	{
		if(m_XVel > -5)
			m_XVel -= m_XAccel;
	}

	else
	{
		if(m_XVel > 0)
		{
			if(m_XVel > 0.4f)
				m_XVel -= m_XAccel * 3 / 2;
			else
				m_XVel = 0;
		}

		else if(m_XVel < 0)
		{
			if(m_XVel < -0.4f)
				m_XVel += m_XAccel * 3 / 2;
			else
				m_XVel = 0;
		}
	}
	
	for(USI i = 0; i < 2; i++)
	{
			int curTileX = collisionBox.m_X / 64;
			int curTileY = collisionBox.m_Y / 64;
			if(map.m_Tiles[curTileX + i][curTileY].m_Type == Tile::TILE1)
			{
				if((i == 0 && m_XVel < 0) || (i == 1 && m_XVel > 0))
					m_XVel = 0;
				//if(keys[SDL_SCANCODE_SPACE])
					//std::cout << "Collision at " << curTileX + i << ", " << curTileY << std::endl;
				break;
			}
	}
	
	//std::cout << m_XVel << std::endl;

    collisionBox.m_X += m_XVel;
}

void Player::MoveY(const Uint8* keys, const Map& map)
{	
	if(!isOnGround)
	{
		if(!keys[SDL_SCANCODE_Z])
		{
			if(m_YVel < 0)
				m_YVel -= GRAVITY;
		}
		
		m_YVel -= GRAVITY;
	}
	
	else
	{
		if(keys[SDL_SCANCODE_Z])
		{
			if(!jumped)
			{
				m_YVel -= m_YAccel;
				isOnGround = false;
				jumped = true;
			}
		}
		
		else
			jumped = false;
	}
	
	int curTileX = collisionBox.m_X / 64;
	int curTileY = collisionBox.m_Y / 64;
	
	//for(int i = 0; i < 2; i++)
	//{
	if(map.m_Tiles[curTileX][curTileY].m_Type == Tile::TILE1)
	{
		if(m_YVel < 0)
			m_YVel = 0;
	}
	
	if(m_YVel > 0)
	{
		if(map.m_Tiles[curTileX + 1][curTileY + 1].m_Type == Tile::TILE1)
		{
			m_YVel = 0;
			collisionBox.m_Y = curTileY * 64;
			isOnGround = true;
		}
	}
	
	if(map.m_Tiles[curTileX][curTileY + 1].m_Type == Tile::TILE1)
	{
		if(m_YVel > 0)
		{
			m_YVel = 0;
			collisionBox.m_Y = curTileY * 64;
		}
		isOnGround = true;
	}

	else if(map.m_Tiles[curTileX][curTileY + 1].m_Type == Tile::EMPTY)
		isOnGround = false;
	//}
	
	if(keys[SDL_SCANCODE_SPACE])
		std::cout << m_YVel << std::endl;
	
	collisionBox.m_Y += m_YVel;
}

void Player::Render(Point2D camera_pos)
{
    m_Texture.Render(collisionBox.m_X - camera_pos.x, collisionBox.m_Y - camera_pos.y);
}
