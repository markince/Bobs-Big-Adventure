// File:	      CZombie.hpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CMasterModelCreator.h"
#include <vector>
#include "CPlayer.hpp"
#include "CBullet.hpp"
#include <sstream>
#ifndef _MYENEMYFILE
#define _MYENEMYFILE


class CZombie : public CMasterModelCreator
{
private:
	I3DEngine*    myEngine;
	IMesh*        zombiePlayerMesh;
	IModel*       zombieModel;
	float&        frameTime;
	//enemyState    currentState;
	IModel*       dummyWaypoints[4];
	IMesh*        dummyMesh;
	bool          zombieCollisionResponse;
	Collision*    collisionDetector;
	float         enemyMovementSpeed;
	bool		  playerPosition;
	bool zombieWallPosition;
	bool zombieDoorPosition;
	collisionAxis DoorCollision;
	collisionAxis WallCollision;
	collisionAxis BulletCollision;
	bool bulletHit;
	int hitCounter;
	enemyMovementDef oldMove;
	float oldEnemyX[kNumLevel1Zombies];
	float oldEnemyZ[kNumLevel1Zombies];
	float distancePos[kNumLevel1Zombies];
	float collisionCounter;
	float momentum;
	int numOfZombiesKilled = 0;
	bool scoreCalcualted = false;
	int explosionCounter = 0;
	sf::SoundBuffer zombieDeathBuffer;
	sf::Sound       zombieDeath;
	bool playDeathSound = false;

public:
	bool detectCollision;
	void CalMomentum(CBullet* bullets, int bulletNum);
	//CZombie() { frameTime = (*new float(0)) ; }
	CZombie(float& frameTimeIn);
	enemyMovementDef enemyMovement;
	void GetMyEngine(I3DEngine* myEngineIn) { myEngine = myEngineIn; };
	void GetMesh(IMesh* spriteMeshIn) { zombiePlayerMesh = spriteMeshIn; };
	void CreateLevel1ZombieModel(IMesh* spriteMeshIn, float startXPos, float startYPos, float startZPos, int zombieNum, string enemyStartSkins, enemyWaypoints dummyPoints[16]);
	void RemoveLevel1ZombieModel(IMesh* spriteMeshIn);
	void EnemyMovement(int zombie1MoveCounter[], string enemyRightSkins[kNumLevel1Zombies][kNumberOfFrames], string enemyLeftSkins[kNumLevel1Zombies][kNumberOfFrames], int enemyNum, float enemySpeed, CPlayer*player);
	IModel* GetModel();
	void FollowPlayer(CPlayer* player, float &oldXPos, float &oldZPos, int zombieNum);
	void GenerateModelCoordinates(int zombieNum);
	//void GetFrameTime(float &frameTimeIn) { frameTime = frameTimeIn; };
	void enemyCollision(CPlayer* player, CBullet* bullets, float &oldXPos, float &oldZPos, wallDetails wallCoordinates[kNumLevel1Walls], keyDetails doorCoordinates[kNumLevel1Doors], int zombieNum);
	void enemyCollisionTwo(CPlayer* player, CBullet* bullets, float &oldXPos, float &oldZPos, wallDetails wallCoordinates[kNumLevel2Walls], keyDetails doorCoordinates[kNumLevel2Doors], int zombieNum);
	enemyMovementDef GetZombieState();

	bool GetScoreCalcualted();
	void SetScoreCalcualted(bool trueorfalse);

};

#endif