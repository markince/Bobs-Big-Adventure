// File:	      CWalls.h
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CMasterModelCreator.h"
#include "CPlayer.hpp"

class CWalls : public CMasterModelCreator
{
private:
	IModel*    level1WallsModel[kNumLevel1Walls];
	IModel*    level2WallsModel[kNumLevel2Walls];
	Collision* collisionDetector;
	collisionAxis  wallsCollisionResponse;
	bool filler = false;

public:
	CWalls();
	void CreateLevel1Walls(IMesh* wallMesh, wallDetails level1Walls[kNumLevel1Walls]);
	void RemoveLevel1Walls(IMesh* wallMesh);
	void level1WallCollision(CPlayer* player, float oldXPos, float oldZPos, wallDetails level1Walls[kNumLevel1Walls]);
	void level2WallCollision(CPlayer* player, float oldXPos, float oldZPos, wallDetails level2Walls[kNumLevel2Walls]);

	IModel* GetLevel1ExitCube();
	IModel* GetLevel2ExitCube();

	void CWalls::CreateLevel2Walls(IMesh* wallMesh, wallDetails level2Walls[kNumLevel2Walls]);




};