#include "headers/Entity.h"

Entity::Entity()
{
    isPassable = false;
    isLoaded = false;
	entityType = "Null ent";
}

Entity::~Entity()
{
}

bool Entity::LoadEntity(const char* path)
{
    std::ifstream file;

    file.open(path, std::ifstream::in);

    if(file.is_open())
    {
        std::string line;
        while(getline(file, line))
        {
            if(line.substr(0, 3) == "img")
            {
                if(!m_Texture.LoadTexture(line.substr(6).c_str(), false))
                   return false;
			   
                std::cout << "YEAH LOADED HAHA\n";
				collisionBox.m_W = m_Texture.m_Width;
				collisionBox.m_H = m_Texture.m_Height;
            }

            else if(line.substr(0,3) == "pss")
            {
                if(line.substr(6) == "0")
                    isPassable = false;
                else
                    isPassable = true;
            }
			
			else if(line.substr(0, 3) == "tpe")
				entityType = line.substr(6);
        }
        file.close();

        isLoaded = true;
        return true;
    }

    return false;
}

void Entity::AssignEntity(const Entity& other)
{
    isPassable = other.isPassable;
    isLoaded = other.isLoaded;
    m_Texture.LoadTexture(other.m_Texture.imagePath.c_str(), false);
}

