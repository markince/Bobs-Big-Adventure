// File:	      CPlayer.hpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CMasterModelCreator.h"

#ifndef _MYPLAYERFILE
#define _MYPLAYERFILE

class CPlayer : public CMasterModelCreator
{
private:
	I3DEngine*     myEngine;
	IMesh*         spritePlayerMesh;
	IModel*        playerModel;
	int            left = 0;
	int            right = 0;
	int            up = 0;
	int            down = 0;
	int            numLevel1RedKeys = 0;
	int            numLevel1BlueKeys = 0;
	int            numLevel1GreenKeys = 0;
	int            numLevel1YellowKeys = 0;
	int            numLevel1Books = 0;
	int            numLevel2RedKeys = 0;
	int            numLevel2BlueKeys = 0;
	int            numLevel2GreenKeys = 0;
	int            numLevel2YellowKeys = 0;
	int            numLevel2Books = 0;
	float          frameTime;
	float          playerMoveSpeed = 40.0f;
	enemyWaypoints enemyCoordinatesIn[kNumLevel1Zombies];

public:
	CPlayer(); // Constructor

	void GetMyEngine(I3DEngine* myEngineIn) { myEngine = myEngineIn; };
	void GetMesh(IMesh* spriteMeshIn) { spritePlayerMesh = spriteMeshIn; };
	void CreateModel(IMesh* spriteMeshIn);
	void RemoveModel(IMesh* spriteMeshIn);
	IModel* GetModel();
	void GetFrameTime(float frameTimeIn) { frameTime = frameTimeIn; };
	void PlayerMovement(int &moveCounter);
	void MoveUp(float speed, int &moveCounter);
	void MoveDown(float speed, int &moveCounter);
	void MoveLeft(float speed, int &moveCounter);
	void MoveRight(float speed, int &moveCounter);
	void Death(int &moveCounter);

	void CollectLevel1RedKey();
	void CollectLevel1BlueKey();
	void CollectLevel1GreenKey();
	void CollectLevel1YellowKey();
	void CollectLevel1Book();


	void CollectLevel2RedKey();
	void CollectLevel2BlueKey();
	void CollectLevel2GreenKey();
	void CollectLevel2YellowKey();
	void CollectLevel2Book();


	void UseLevel1RedKey();
	void UseLevel1BlueKey();
	void UseLevel1GreenKey();
	void UseLevel1YellowKey();

	void UseLevel2RedKey();
	void UseLevel2BlueKey();
	void UseLevel2GreenKey();
	void UseLevel2YellowKey();


	int GetNumLevel1RedKeys();
	int GetNumLevel1BlueKeys();
	int GetNumLevel1GreenKeys();
	int GetNumLevel1YellowKeys();
	int GetNumLevel1Books();

	int GetNumLevel2RedKeys();
	int GetNumLevel2BlueKeys();
	int GetNumLevel2GreenKeys();
	int GetNumLevel2YellowKeys();
	int GetNumLevel2Books();

	playerMovement bobDirection = DOWN;

};
#endif