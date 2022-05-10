// File:	      CWalls.cpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CWalls.h"

CWalls::CWalls()
{
	collisionDetector = new Collision;
}


// ****** Level 1 *********

void CWalls::CreateLevel1Walls(IMesh* wallMesh, wallDetails level1Walls[kNumLevel1Walls])
{


	for (int i = 0; i < kNumLevel1Walls; i++)
	{
		level1WallsModel[i] = wallMesh->CreateModel(level1Walls[i].xPos, level1Walls[i].yPos, level1Walls[i].zPos);
		if (i < kNumLevel1Walls - 1) level1WallsModel[i]->SetSkin("wallSkin2.png");
		else level1WallsModel[i]->SetSkin("exitSkin.png");

	}
}

void CWalls::RemoveLevel1Walls(IMesh* wallMesh)
{
	for (int i = 0; i < kNumLevel1Walls; i++)
	{
		level1WallsModel[i]->~IModel();

	}

}



void CWalls::level1WallCollision(CPlayer* player, float oldXPos, float oldZPos, wallDetails level1Walls[kNumLevel1Walls])
{
	for (int i = 0; i < kNumLevel1Walls; i++)
	{
		wallsCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level1Walls[i].xPos, level1Walls[i].zPos, 5.0f, 5.0f, filler);
		if (wallsCollisionResponse == XAXIS) player->GetModel()->SetX(oldXPos);
		if (wallsCollisionResponse == ZAXIS) player->GetModel()->SetZ(oldZPos);
	}
}

void CWalls::level2WallCollision(CPlayer* player, float oldXPos, float oldZPos, wallDetails level2Walls[kNumLevel2Walls])
{
	for (int i = 0; i < kNumLevel2Walls; i++)
	{
		wallsCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level2Walls[i].xPos, level2Walls[i].zPos, 5.0f, 5.0f, filler);
		if (wallsCollisionResponse == XAXIS) player->GetModel()->SetX(oldXPos);
		if (wallsCollisionResponse == ZAXIS) player->GetModel()->SetZ(oldZPos);
	}

}





//
IModel* CWalls::GetLevel1ExitCube()
{
	return level1WallsModel[kNumLevel1Walls - 1];
}



// ****** Level 2 *********

void CWalls::CreateLevel2Walls(IMesh* wallMesh, wallDetails level2Walls[kNumLevel2Walls])
{

	for (int i = 0; i < kNumLevel2Walls; i++)
	{
		level2WallsModel[i] = wallMesh->CreateModel(level2Walls[i].xPos, level2Walls[i].yPos, level2Walls[i].zPos);
		if (i < kNumLevel2Walls - 1) level2WallsModel[i]->SetSkin("wallSkin2.png");
		else level2WallsModel[i]->SetSkin("exitSkin.png");
	}


}

IModel* CWalls::GetLevel2ExitCube()
{
	return level2WallsModel[kNumLevel2Walls - 1];
}

