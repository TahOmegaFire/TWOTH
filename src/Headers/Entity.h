#ifndef ENTITY_H
#define ENTITY_H

#include <fstream>
#include "TexW.h"
#include "CollisionBox.h"

class Entity
{
public:
	Entity();
	~Entity();

	//Entity operator=(const Entity& other);
	std::string entityType;

	virtual bool LoadEntity(const char* path);
	void AssignEntity(const Entity& other);

	bool isPassable, isLoaded;
	CollisionBox collisionBox;
	TexW m_Texture;
};


#endif //ENTITY_H
