// File:	      Collision.h
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#include "Definitions.h"

class Collision
{

public:
	collisionAxis Sphere2BoxCollision(float sphereOldX, float sphereOldZ, float sphereX, float sphereZ, float sphereRadius, float boxX,
		float boxZ, float halfBoxWidth, float halfBoxDepth, bool &PositionOfP);

	bool sphere2Box(float sphereXPos, float sphereZPos, float sphereRadius, float boxXPos, float boxZPos,
		float boxWidth, float boxDepth);

	bool point2Box(float pointX, float pointZ, float boxXPos, float boxZPos, float boxDepth, float boxWidth);
};