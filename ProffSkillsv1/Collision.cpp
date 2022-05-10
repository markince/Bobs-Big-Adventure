// File:	      Collision.cpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#include "Collision.h"

// This function detects collision between a box and a sphere. The spheres old X and Y position, new X and Y position and radius
// are passed into the function as is the box X and Z and width and depth sizes that it is colliding with. The bounding box is then
// calculated and a check is done to see if the centre of the sphere is within the bounding box. Which ever side the sphere has collided
// with (x or z) is then returned to the main program.

collisionAxis Collision::Sphere2BoxCollision(float sphereOldX, float sphereOldZ, float sphereX, float sphereZ, float sphereRadius, float boxX,
	float boxZ, float halfBoxWidth, float halfBoxDepth, bool &PositionOfP)
{
	// Set up the bounding box
	float maxX = boxX + halfBoxWidth + sphereRadius;
	float minX = boxX - halfBoxWidth - sphereRadius;
	float maxZ = boxZ + halfBoxDepth + sphereRadius;
	float minZ = boxZ - halfBoxDepth - sphereRadius;

	// Check if centre of sphere is withing the bounding box

	if (sphereX > minX && sphereX < maxX && sphereZ > minZ && sphereZ < maxZ)
	{
		// Collision, test for axis of collision
		if (sphereOldX < minX)
		{
			PositionOfP = false;
			return XAXIS;
		}
		else if (sphereOldX > maxX)
		{
			PositionOfP = true;
			return XAXIS; // Colliding parallel to the x axis
		}
		else if (sphereOldZ < minZ)
		{
			PositionOfP = false;
			return ZAXIS;
		}
		else if (sphereOldZ > maxZ)
		{
			PositionOfP = true;
			return ZAXIS; // Colliding parallel to the Z axis
		}
	}
	else
		return NONE;
}

bool Collision::sphere2Box(float sphereXPos, float sphereZPos, float sphereRadius, float boxXPos, float boxZPos,
	float boxWidth, float boxDepth)
{
	float minX = boxXPos - boxWidth / 2 - sphereRadius;
	float maxX = boxXPos + boxWidth / 2 + sphereRadius;
	float minZ = boxZPos - boxDepth / 2 - sphereRadius;
	float maxZ = boxZPos + boxDepth / 2 + sphereRadius;

	return(sphereXPos > minX && sphereXPos < maxX && sphereZPos > minZ && sphereZPos < maxZ);

}

bool Collision::point2Box(float pointX, float pointZ, float boxXPos, float boxZPos, float boxDepth, float boxWidth)
{

	// calculate bounding area around the box used for collision detection
	float minX = boxXPos - boxWidth / 2;
	float maxX = boxXPos + boxWidth / 2;
	float minZ = boxZPos - boxDepth / 2;
	float maxZ = boxZPos + boxDepth / 2;

	return(pointX > minX && pointX < maxX && pointZ > minZ && pointZ < maxZ);
}