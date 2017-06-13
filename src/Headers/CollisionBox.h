#ifndef COL_BOX_H
#define COL_BOX_H

#include <iostream>

class CollisionBox
{
public:

	enum COLTYPE {NONE, TOP, BOTTOM, LEFT, RIGHT};
	
	CollisionBox() {m_X = m_Y = m_W = m_H = 0;}
	CollisionBox(int x, int y, int width, int height) :
		m_X(x),
		m_Y(y),
		m_W(width),
		m_H(height) {}
	~CollisionBox() {}
		
	int m_X, m_Y, m_W, m_H;	
	
	int Left() const {return m_X;}
	int Right() const {return m_X + m_W;}
	int Top() const {return m_Y;}
	int Bottom() const {return m_Y + m_H;}
	
	int Width() const {return m_W;}
	int Height() const {return m_H;}
	
	bool TestCollision(CollisionBox& other);
	int TestCollisionV(CollisionBox& other);
	int TestCollisionH(CollisionBox& other);
};


#endif //COL_BOX_H