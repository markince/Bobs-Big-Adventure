// File:	      CMasterModelCreator.hpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "Definitions.h"
#include "Collision.h"
class CMasterModelCreator
{
public:
	//Variables
	I3DEngine*       myEngine;
	IMesh*           spriteMesh;
	IMesh*           spriteMeshCopy;
	IMesh*           cubeMesh;
	wallDetails      level1walls[kNumLevel1Walls];
	wallDetails      level2walls[kNumLevel2Walls];
	keyDetails       level1keyPosition[kNumLevel1Keys];
	keyDetails       level2keyPosition[kNumLevel2Keys];
	keyDetails       level1DoorPosition[kNumLevel1Doors];
	keyDetails       level2DoorPosition[kNumLevel2Doors];
	bookDetails      level1BookoPosition[kNumLevel1Books];
	bookDetails      level2BookoPosition[kNumLevel2Books];
	turretDetails    level2TurretPosition[kNumLevel2Turrets];
	laserBoltHDetails level2LaserBoltHPosition[kNumHLaserBolts];
	laserBoltVDetails level2LaserBoltVPosition[kNumVLaserBolts];


	bulletDetails    level1BulletDetails[kNumBullets];
	enemyWaypoints   enemyPositions[kNumLevel1Zombies];
	enemyWaypoints   enemyPositionsTwo[kNumLevel1Zombies];
	enemyWaypoints   dummyWayPointsCooridnates[kNumLevel1Zombies * 4];
	enemyWaypoints   dummyWayPointsTwoCooridnates[16];

	string           enemyStartSkins[kNumLevel1Zombies];
	string           enemySkinsLeft[kNumLevel1Zombies][kNumberOfFrames];
	string           enemySkinsRight[kNumLevel1Zombies][kNumberOfFrames];
	string			 healthSystemLayers[11];
	//Functions 
	CMasterModelCreator();
	void GetMyEngine(I3DEngine* myEngineIn) { myEngine=myEngineIn; };
	void LoadMediaFolders();
	void LoadModelMeshes();
	void GenerateModelCoordinates();
};

