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
	isOnGround = leftMovement = rightMovement = true;
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
	curTileX1 = collisionBox.m_X / 64;
	curTileY= collisionBox.m_Y / 64;
	curTileX2 = (collisionBox.m_X + collisionBox.m_W) / 64;
	//if(keys[SDL_SCANCODE_SPACE])
		//UtilFn::Print2Values(curTileX, curTileY);
    MoveX(keys, map);
	MoveY(keys, map);
}

void Player::MoveX(const Uint8* keys, const Map& map)
{	
	//std::cout << m_XVel << std::endl;
	if(keys[SDL_SCANCODE_RIGHT])
	{
		if(m_XVel < 5)
		{
			!isOnGround ? m_XVel += (m_XAccel * 2 / 3) : m_XVel += m_XAccel;
		}
		else
			m_XVel = 5;
	}

	else if(keys[SDL_SCANCODE_LEFT])
	{
		if(m_XVel > -5)
		{
			!isOnGround ? m_XVel -= (m_XAccel * 2 / 3) : m_XVel -= m_XAccel;
		}
		else
			m_XVel = -5;
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
	
	int nextTileX1 = (collisionBox.m_X + m_XVel) / 64;
	int nextTileX2 = (collisionBox.m_X + collisionBox.m_W + m_XVel) / 64;
	if(map.m_Tiles[nextTileX1][curTileY].m_Type == Tile::TILE1)
	{
		collisionBox.m_X = curTileX1 * 64;
		m_XVel = 0;
	}
	
	if(map.m_Tiles[nextTileX2][curTileY].m_Type == Tile::TILE1)
	{
		collisionBox.m_X = (curTileX1 + 1) * 64 - collisionBox.m_W; //What is this hack
		m_XVel = 0;
	}
	
	/*if(map.m_Tiles[curTileX1][curTileY].m_Type == Tile::TILE1)
	{
		if(m_XVel < 0)
			m_XVel = 0;
	}
	
	if(map.m_Tiles[curTileX2][curTileY].m_Type == Tile::TILE1)
	{
		if(m_XVel > 0)
			m_XVel = 0;
	}*/
	
	//Check for m_X + m_XVel

    collisionBox.m_X += m_XVel;
}

void Player::MoveY(const Uint8* keys, const Map& map)
{	
	if(map.m_Tiles[curTileX1][curTileY].m_Type == Tile::TILE1 || map.m_Tiles[curTileX2][curTileY].m_Type == Tile::TILE1)
	{
		if(m_YVel < 0)
			m_YVel = 0;
	}
	
	if(map.m_Tiles[curTileX1][curTileY + 1].m_Type == Tile::TILE1 || map.m_Tiles[curTileX2][curTileY + 1].m_Type == Tile::TILE1)
	{
		m_YVel = 0;
		collisionBox.m_Y = curTileY * 64;
		isOnGround = true;
	}

	else if(map.m_Tiles[curTileX1][curTileY + 1].m_Type == Tile::EMPTY && map.m_Tiles[curTileX2][curTileY + 1].m_Type == Tile::EMPTY)
			isOnGround = false;
	
	if(!isOnGround)
	{
		if(!keys[SDL_SCANCODE_Z])
		{
			if(m_YVel < 0)
				m_YVel -= GRAVITY * 2;
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
	
	if(keys[SDL_SCANCODE_SPACE])
		std::cout << isOnGround << std::endl;
	
	collisionBox.m_Y += m_YVel;
}

void Player::Render(Point2D camera_pos)
{
    m_Texture.Render(collisionBox.m_X - camera_pos.x, collisionBox.m_Y - camera_pos.y);
}
