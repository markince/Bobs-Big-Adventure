// File:	      CBullet.hpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CMasterModelCreator.h"
#include <SFML/Audio.hpp>
#include "CPlayer.hpp"


#ifndef _MYBULLETFILE
#define _MYBULLETFILE

struct bullet
{
	IModel* Model;
	bool fired = false;
	playerMovement firingDirection;

};
class CBullet :public CMasterModelCreator
{
private:
	float bulletSpeed = 100.0f;
	Collision*      collisionDetector;
	sf::SoundBuffer fireBulletBuffer;
	sf::Sound       fireBullet;
	sf::SoundBuffer collisionBulletBuffer;
	sf::Sound       collisionBullet;

	I3DEngine* myEngine;

	void Fire(playerMovement currentDirection, IModel* player);
	void Reset();

public:
	bullet myBullets[kNumBullets];
	float oldBulletX[kNumBullets];
	float oldBulletZ[kNumBullets];

	CBullet(I3DEngine* engine);
	void CreateModel(IMesh* bulletMesh, IModel* player, bulletDetails level1BulletPosition[]);
	void DeleteModel(IMesh* bulletMesh);
	void Update(playerMovement currentDirection, IModel* player, float frameTime);

	void level1WallCollision(wallDetails level1Walls[kNumLevel1Walls], CPlayer* player);
	void level1DoorCollision(keyDetails level1DoorPosition[kNumLevel1Doors], CPlayer* player);

	void level2WallCollision(wallDetails level2Walls[kNumLevel2Walls], CPlayer* player);
	void level2DoorCollision(keyDetails level2DoorPosition[kNumLevel2Doors], CPlayer* player);


	//void level1ZombieCollision(wallDetails level1Walls[kNumLevel1Walls]);



};

#endif