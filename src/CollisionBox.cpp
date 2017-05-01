#include "Headers/CollisionBox.h"

bool CollisionBox::TestCollision(CollisionBox& other)
{
	return !(this->Bottom() < other.Top() || this->Top() > other.Bottom()
		|| this->Left() > other.Right() || this->Right() < other.Left());
}

int CollisionBox::TestCollisionV(CollisionBox& other)
{
	if(TestCollision(other))
	{
		if(this->Top() > other.Bottom())
			return 1;
		else if(this->Bottom() < other.Top())
			return 2;
		//std::cout << "lmao";
	}
	return 0;
}

int CollisionBox::TestCollisionH(CollisionBox& other)
{
	if(TestCollision(other))
	{
		if(this->Left() < other.Right())
			return 1;
		else if(this->Right() > other.Left())
			return 2;
		//std::cout << "lmao";
	}
	return 0;
}