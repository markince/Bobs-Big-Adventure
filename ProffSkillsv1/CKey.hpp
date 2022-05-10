// File:	      CKey.hpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CMasterModelCreator.h"
#include "CPlayer.hpp"
#include <SFML/Audio.hpp>

#ifndef _MYKEYFILE
#define _MYKEYFILE

class CKey : public CMasterModelCreator
{
private:
	int             level1KeyColour[kNumLevel1Keys];
	int             level2KeyColour[kNumLevel2Keys];
	Collision*      collisionDetector;
	IModel*         level1KeyModels[kNumLevel1Keys];
	IModel*         level2KeyModels[kNumLevel2Keys];
	collisionAxis       keysCollisionResponse;
	sf::SoundBuffer pickUpKeyBuffer;
	sf::Sound       pickUpKey;
	bool filler = false;

public:
	CKey();
	void CreateLevel1Keys(IMesh* keyMesh, keyDetails level1keyPosition[kNumLevel1Keys]);
	void CreateLevel2Keys(IMesh* keyMesh, keyDetails level2keyPosition[kNumLevel2Keys]);
	void RemoveLevel1Keys(IMesh* keyMesh);
	void RemoveLevel2Keys(IMesh* keyMesh);
	void Level1KeyCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore);
	void Level2KeyCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore);

};


#endif