#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"
#include "Utils.h"
#include "Map.h"

class Player : public Entity
{
public:

    Player();
    ~Player();

    bool LoadEntity(const char *path);

    void Update(const Uint8* keys, const Map& map);
    void Render(Point2D camera_pos);

	void MoveX(const Uint8* keys, const Map& map);
	void MoveY(const Uint8* keys, const Map& map);
	
    float m_XFriction, m_XVel, m_XAccel, m_YVel, m_YAccel;
	int curTileX1, curTileY, curTileX2;
	bool isOnGround, jumped;
};

#endif // PLAYER_H
