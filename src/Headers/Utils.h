#ifndef UTILS_H
#define UTILS_H

struct SDL_Rect;

typedef unsigned short int USI;
struct Point2D {int x, y;};

const short int TILESIZE = 64;
const float GRAVITY = -0.8;

namespace UtilFn
{
	inline bool SimpleCollisionDetection(SDL_Rect f, SDL_Rect s)
	{
		int leftA, leftB; 
		int rightA, rightB; 
		int topA, topB; 
		int bottomA, bottomB; 
		
		leftA = f.x; 
		rightA = f.x + f.w; 
		topA = f.y; 
		bottomA = f.y + f.h; 
		leftB = s.x; 
		rightB = s.x + s.w; 
		topB = s.y; 
		bottomB = s.y + s.h;
		
		if(bottomA <= topB || topA >= bottomB || rightA <= leftB || leftA >= rightB) 
			return false;
		
		return true;
	}
	
	inline void Print2Values(int f, int s)
	{
		std::cout << f << " | " << s << std::endl;
	}
}
#endif //UTILS_H