// File:	      CDoor.hpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CMasterModelCreator.h"
#include "CPlayer.hpp"
#include <SFML/Audio.hpp>

#ifndef _MYDOORFILE
#define _MYDOORFILE

class CDoor : public CMasterModelCreator
{
private:
	int             Level1DoorColour[kNumLevel1Doors];
	IModel*         level1DoorModels[kNumLevel1Doors];
	int             Level2DoorColour[kNumLevel2Doors];
	IModel*         level2DoorModels[kNumLevel2Doors];
	int             collisionCount = 0;
	bool            doorOpen = false;
	int             doorsCollisionResponse;
	Collision*      collisionDetector;
	sf::SoundBuffer unlockDoorBuffer;
	sf::Sound       unlockDoor;
	bool filler = false;

public:
	CDoor();
	void CreateLevel1Doors(IMesh* doorMesh, keyDetails level1DoorPosition[kNumLevel1Doors]);
	void CreateLevel2Doors(IMesh* doorMesh, keyDetails level2DoorPosition[kNumLevel2Doors]);
	void RemoveLevel1Doors(IMesh* doorMesh);
	void RemoveLevel2Doors(IMesh* doorMesh);

	//IModel* GetModel();
	void Level1DoorCollision(CPlayer* player, float oldXPos, float oldZPos, keyDetails level1DoorPosition[kNumLevel1Doors], int &playerScore);
	void Level2DoorCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore);

};


#endif