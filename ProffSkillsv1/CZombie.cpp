// File:	      CZombie.cpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#include "CZombie.hpp"
#include "Definitions.h"

CZombie::CZombie(float& frameTimeIn) :frameTime(frameTimeIn) // Constructor
{
	enemyMovement = MOVINGRIGHT;
	zombieCollisionResponse = false;
	playerPosition = false;
	zombieWallPosition = false;
	zombieDoorPosition = false;
	detectCollision = false;
	bulletHit = true;
	collisionCounter = 0.0f;
	hitCounter = 0;
	//frameTime = frameTimeIn;

	zombieDeathBuffer.loadFromFile("zombieDeath.wav");
	zombieDeath.setBuffer(zombieDeathBuffer);
	zombieDeath.setVolume(70.0f); // 0 to 100
	zombieDeath.setPitch(1.0f);
	zombieDeath.setLoop(false);
}

void CZombie::CreateLevel1ZombieModel(IMesh* spriteMeshIn, float startXPos, float startYPos, float startZPos, int zombieNum, string enemyStartSkins, enemyWaypoints dummyPoints[16])
{
	dummyMesh = myEngine->LoadMesh("dummy.x");
	for (int i = 0; i < kNumLevel1Zombies; i++)
	{
		dummyWaypoints[i] = dummyMesh->CreateModel(dummyPoints[i + (zombieNum * 4)].xPos, dummyPoints[i + (zombieNum * 4)].yPos, dummyPoints[i + (zombieNum * 4)].zPos);
		cout << dummyWaypoints[i]->GetX() << " " << dummyWaypoints[i]->GetY() << " " << dummyWaypoints[i]->GetZ() << endl;
	}
	cout << endl;

	zombieModel = spriteMeshIn->CreateModel(startXPos, startYPos, startZPos);

	zombieModel->RotateX(270.0f);
	zombieModel->SetSkin(enemyStartSkins);
	zombieModel->Scale(1.2f);
}

void CZombie::RemoveLevel1ZombieModel(IMesh* spriteMeshIn)
{

	for (int i = 0; i < kNumLevel1Zombies; i++)
	{
		spriteMeshIn->RemoveModel(zombieModel);
		dummyMesh->RemoveModel(dummyWaypoints[i]);
	}
}

void CZombie::EnemyMovement(int zombie1MoveCounter[], string enemyRightSkins[kNumLevel1Zombies][kNumberOfFrames], string enemyLeftSkins[kNumLevel1Zombies][kNumberOfFrames],
	int enemyNum, float enemySpeed, CPlayer*player)
{
	enemyMovementSpeed = enemySpeed * frameTime;
	switch (enemyMovement)
	{
	case MOVINGRIGHT:
	{
		zombieModel->LookAt(dummyWaypoints[1]);
		zombieModel->MoveLocalZ(enemyMovementSpeed);
		zombieModel->ResetOrientation();
		zombieModel->RotateX(270.0f);

		zombie1MoveCounter[enemyNum]++;
		if (zombie1MoveCounter[enemyNum] == 50)  zombieModel->SetSkin(enemyRightSkins[enemyNum][0]);
		else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyRightSkins[enemyNum][1]);
		else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyRightSkins[enemyNum][2]);
		else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyRightSkins[enemyNum][3]);
		else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyRightSkins[enemyNum][4]);
		else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyRightSkins[enemyNum][5]);
		else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyRightSkins[enemyNum][6]);
		else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyRightSkins[enemyNum][7]);
		else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyRightSkins[enemyNum][8]);
		else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyRightSkins[enemyNum][9]);
		else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyRightSkins[enemyNum][10]);
		else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyRightSkins[enemyNum][11]);
		else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyRightSkins[enemyNum][12]);
		else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyRightSkins[enemyNum][13]);
		else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyRightSkins[enemyNum][14]);
		else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyRightSkins[enemyNum][15]);
		else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyRightSkins[enemyNum][16]);
		else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;
		bool zombieCollisionResponse = collisionDetector->point2Box(dummyWaypoints[1]->GetX(), dummyWaypoints[1]->GetZ(), zombieModel->GetX(), zombieModel->GetZ(), 2.0f, 2.0f);
		if (zombieCollisionResponse)
		{
			enemyMovement = MOVINGDOWN;
		}
		break;
	}
	case MOVINGLEFT:
	{
		zombieModel->LookAt(dummyWaypoints[3]);
		zombieModel->MoveLocalZ(enemyMovementSpeed);
		zombieModel->ResetOrientation();
		zombieModel->RotateX(270.0f);
		bool zombieCollisionResponse = collisionDetector->point2Box(dummyWaypoints[3]->GetX(), dummyWaypoints[3]->GetZ(), zombieModel->GetX(), zombieModel->GetZ(), 2.0f, 2.0f);
		if (zombieCollisionResponse)
		{
			enemyMovement = MOVINGUP;
		}
		zombie1MoveCounter[enemyNum]++;
		if (zombie1MoveCounter[enemyNum] == 50) zombieModel->SetSkin(enemyLeftSkins[enemyNum][0]);//1
		else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyLeftSkins[enemyNum][1]);//2
		else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyLeftSkins[enemyNum][2]);//3
		else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyLeftSkins[enemyNum][3]);//4
		else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyLeftSkins[enemyNum][4]);//5
		else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyLeftSkins[enemyNum][5]);//6
		else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyLeftSkins[enemyNum][6]);//7
		else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyLeftSkins[enemyNum][7]);//8
		else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyLeftSkins[enemyNum][8]);//9
		else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyLeftSkins[enemyNum][9]);//10
		else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyLeftSkins[enemyNum][10]);//11
		else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyLeftSkins[enemyNum][11]);//12
		else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyLeftSkins[enemyNum][12]);//13
		else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyLeftSkins[enemyNum][13]);//14
		else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyLeftSkins[enemyNum][14]);//15
		else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyLeftSkins[enemyNum][15]);//16
		else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyLeftSkins[enemyNum][16]);//17
		else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;

		break;
	}
	case MOVINGDOWN:
	{
		zombieModel->LookAt(dummyWaypoints[2]);
		zombieModel->MoveLocalZ(enemyMovementSpeed);
		zombieModel->ResetOrientation();
		zombieModel->RotateX(270.0f);
		zombie1MoveCounter[enemyNum]++;
		if (zombie1MoveCounter[enemyNum] == 50)  zombieModel->SetSkin(enemyRightSkins[enemyNum][0]);
		else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyRightSkins[enemyNum][1]);
		else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyRightSkins[enemyNum][2]);
		else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyRightSkins[enemyNum][3]);
		else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyRightSkins[enemyNum][4]);
		else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyRightSkins[enemyNum][5]);
		else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyRightSkins[enemyNum][6]);
		else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyRightSkins[enemyNum][7]);
		else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyRightSkins[enemyNum][8]);
		else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyRightSkins[enemyNum][9]);
		else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyRightSkins[enemyNum][10]);
		else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyRightSkins[enemyNum][11]);
		else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyRightSkins[enemyNum][12]);
		else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyRightSkins[enemyNum][13]);
		else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyRightSkins[enemyNum][14]);
		else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyRightSkins[enemyNum][15]);
		else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyRightSkins[enemyNum][16]);
		else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;

		bool zombieCollisionResponse = collisionDetector->point2Box(dummyWaypoints[2]->GetX(), dummyWaypoints[2]->GetZ(), zombieModel->GetX(), zombieModel->GetZ(), 2.0f, 2.0f);
		if (zombieCollisionResponse)
		{
			enemyMovement = MOVINGLEFT;
		}

		break;
	}
	case MOVINGUP:
	{
		zombieModel->LookAt(dummyWaypoints[0]);
		zombieModel->MoveLocalZ(enemyMovementSpeed);
		zombieModel->ResetOrientation();
		zombieModel->RotateX(270.0f);
		bool zombieCollisionResponse = collisionDetector->point2Box(dummyWaypoints[0]->GetX(), dummyWaypoints[0]->GetZ(), zombieModel->GetX(), zombieModel->GetZ(), 2.0f, 2.0f);
		if (zombieCollisionResponse)
		{
			enemyMovement = MOVINGRIGHT;
		}
		zombie1MoveCounter[enemyNum]++;
		if (zombie1MoveCounter[enemyNum] == 50) zombieModel->SetSkin(enemyLeftSkins[enemyNum][0]);//1
		else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyLeftSkins[enemyNum][1]);//2
		else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyLeftSkins[enemyNum][2]);//3
		else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyLeftSkins[enemyNum][3]);//4
		else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyLeftSkins[enemyNum][4]);//5
		else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyLeftSkins[enemyNum][5]);//6
		else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyLeftSkins[enemyNum][6]);//7
		else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyLeftSkins[enemyNum][7]);//8
		else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyLeftSkins[enemyNum][8]);//9
		else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyLeftSkins[enemyNum][9]);//10
		else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyLeftSkins[enemyNum][10]);//11
		else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyLeftSkins[enemyNum][11]);//12
		else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyLeftSkins[enemyNum][12]);//13
		else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyLeftSkins[enemyNum][13]);//14
		else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyLeftSkins[enemyNum][14]);//15
		else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyLeftSkins[enemyNum][15]);//16
		else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyLeftSkins[enemyNum][16]);//17
		else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;
		break;

	}
	case FOLLOW:
	{

		zombieModel->LookAt(player->GetModel());
		if (player->GetModel()->GetZ() < zombieModel->GetZ() && player->GetModel()->GetX() < zombieModel->GetX())
		{
			zombieModel->MoveLocalZ(enemyMovementSpeed);
			zombieModel->ResetOrientation();
			zombieModel->RotateX(270.0f);
			zombie1MoveCounter[enemyNum]++;
			if (zombie1MoveCounter[enemyNum] == 50) zombieModel->SetSkin(enemyLeftSkins[enemyNum][0]);//1
			else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyLeftSkins[enemyNum][1]);//2
			else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyLeftSkins[enemyNum][2]);//3
			else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyLeftSkins[enemyNum][3]);//4
			else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyLeftSkins[enemyNum][4]);//5
			else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyLeftSkins[enemyNum][5]);//6
			else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyLeftSkins[enemyNum][6]);//7
			else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyLeftSkins[enemyNum][7]);//8
			else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyLeftSkins[enemyNum][8]);//9
			else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyLeftSkins[enemyNum][9]);//10
			else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyLeftSkins[enemyNum][10]);//11
			else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyLeftSkins[enemyNum][11]);//12
			else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyLeftSkins[enemyNum][12]);//13
			else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyLeftSkins[enemyNum][13]);//14
			else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyLeftSkins[enemyNum][14]);//15
			else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyLeftSkins[enemyNum][15]);//16
			else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyLeftSkins[enemyNum][16]);//17
			else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;
		}
		else if (player->GetModel()->GetZ() > zombieModel->GetZ() && player->GetModel()->GetX() < zombieModel->GetX())
		{
			zombieModel->MoveLocalZ(enemyMovementSpeed);
			zombieModel->ResetOrientation();
			zombieModel->RotateX(270.0f);
			zombie1MoveCounter[enemyNum]++;
			if (zombie1MoveCounter[enemyNum] == 50) zombieModel->SetSkin(enemyLeftSkins[enemyNum][0]);//1
			else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyLeftSkins[enemyNum][1]);//2
			else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyLeftSkins[enemyNum][2]);//3
			else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyLeftSkins[enemyNum][3]);//4
			else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyLeftSkins[enemyNum][4]);//5
			else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyLeftSkins[enemyNum][5]);//6
			else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyLeftSkins[enemyNum][6]);//7
			else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyLeftSkins[enemyNum][7]);//8
			else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyLeftSkins[enemyNum][8]);//9
			else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyLeftSkins[enemyNum][9]);//10
			else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyLeftSkins[enemyNum][10]);//11
			else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyLeftSkins[enemyNum][11]);//12
			else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyLeftSkins[enemyNum][12]);//13
			else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyLeftSkins[enemyNum][13]);//14
			else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyLeftSkins[enemyNum][14]);//15
			else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyLeftSkins[enemyNum][15]);//16
			else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyLeftSkins[enemyNum][16]);//17
			else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;
		}
		else if (player->GetModel()->GetZ() < zombieModel->GetZ() && player->GetModel()->GetX() > zombieModel->GetX())
		{
			zombieModel->MoveLocalZ(enemyMovementSpeed);
			zombieModel->ResetOrientation();
			zombieModel->RotateX(270.0f);
			zombie1MoveCounter[enemyNum]++;
			if (zombie1MoveCounter[enemyNum] == 50)  zombieModel->SetSkin(enemyRightSkins[enemyNum][0]);
			else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyRightSkins[enemyNum][1]);
			else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyRightSkins[enemyNum][2]);
			else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyRightSkins[enemyNum][3]);
			else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyRightSkins[enemyNum][4]);
			else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyRightSkins[enemyNum][5]);
			else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyRightSkins[enemyNum][6]);
			else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyRightSkins[enemyNum][7]);
			else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyRightSkins[enemyNum][8]);
			else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyRightSkins[enemyNum][9]);
			else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyRightSkins[enemyNum][10]);
			else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyRightSkins[enemyNum][11]);
			else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyRightSkins[enemyNum][12]);
			else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyRightSkins[enemyNum][13]);
			else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyRightSkins[enemyNum][14]);
			else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyRightSkins[enemyNum][15]);
			else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyRightSkins[enemyNum][16]);
			else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;
		}
		else if (player->GetModel()->GetZ() > zombieModel->GetZ() && player->GetModel()->GetX() > zombieModel->GetX())
		{
			zombieModel->MoveLocalZ(enemyMovementSpeed);
			zombieModel->ResetOrientation();
			zombieModel->RotateX(270.0f);
			zombie1MoveCounter[enemyNum]++;
			if (zombie1MoveCounter[enemyNum] == 50)  zombieModel->SetSkin(enemyRightSkins[enemyNum][0]);
			else if (zombie1MoveCounter[enemyNum] == 100) zombieModel->SetSkin(enemyRightSkins[enemyNum][1]);
			else if (zombie1MoveCounter[enemyNum] == 150) zombieModel->SetSkin(enemyRightSkins[enemyNum][2]);
			else if (zombie1MoveCounter[enemyNum] == 200) zombieModel->SetSkin(enemyRightSkins[enemyNum][3]);
			else if (zombie1MoveCounter[enemyNum] == 250) zombieModel->SetSkin(enemyRightSkins[enemyNum][4]);
			else if (zombie1MoveCounter[enemyNum] == 300) zombieModel->SetSkin(enemyRightSkins[enemyNum][5]);
			else if (zombie1MoveCounter[enemyNum] == 350) zombieModel->SetSkin(enemyRightSkins[enemyNum][6]);
			else if (zombie1MoveCounter[enemyNum] == 400) zombieModel->SetSkin(enemyRightSkins[enemyNum][7]);
			else if (zombie1MoveCounter[enemyNum] == 450) zombieModel->SetSkin(enemyRightSkins[enemyNum][8]);
			else if (zombie1MoveCounter[enemyNum] == 500) zombieModel->SetSkin(enemyRightSkins[enemyNum][9]);
			else if (zombie1MoveCounter[enemyNum] == 550) zombieModel->SetSkin(enemyRightSkins[enemyNum][10]);
			else if (zombie1MoveCounter[enemyNum] == 600) zombieModel->SetSkin(enemyRightSkins[enemyNum][11]);
			else if (zombie1MoveCounter[enemyNum] == 650) zombieModel->SetSkin(enemyRightSkins[enemyNum][12]);
			else if (zombie1MoveCounter[enemyNum] == 700) zombieModel->SetSkin(enemyRightSkins[enemyNum][13]);
			else if (zombie1MoveCounter[enemyNum] == 750) zombieModel->SetSkin(enemyRightSkins[enemyNum][14]);
			else if (zombie1MoveCounter[enemyNum] == 800) zombieModel->SetSkin(enemyRightSkins[enemyNum][15]);
			else if (zombie1MoveCounter[enemyNum] == 850) zombieModel->SetSkin(enemyRightSkins[enemyNum][16]);
			else if (zombie1MoveCounter[enemyNum] == 900) zombie1MoveCounter[enemyNum] = 49;
		}
		else
		{
			zombieModel->MoveLocalZ(enemyMovementSpeed);
			zombieModel->ResetOrientation();
			zombieModel->RotateX(270.0f);
		}
		break;
	}
	case COLLIDED:
	{
		//Do magic with sprites animations heree
		enemyMovement = oldMove;

		break;
	}
	case DEAD:
	{
		//++explosionCounter;
		//if (explosionCounter % 40 == 0)
		//{
		//	int skinNo = (explosionCounter / 4) / 10; // Calculates the correct skin to use
		//	if (skinNo == 57) explosionCounter = 0, skinNo = 0; // Resets on last image
		//	stringstream ss;
		//	ss << "explosion";
		//	ss << skinNo;
		//	ss << ".tga";
		//	string tmp;
		//	ss >> tmp;
			//zombieModel->Scale(1.5f);
		//	zombieModel->SetSkin(tmp);
		//}
		//else if (explosionCounter > 900)
		//{
			zombieModel->SetX(-500.0f);
			if (!playDeathSound) zombieDeath.play();
			playDeathSound = true;

		//}

		break;
	}
	}
	collisionCounter -= frameTime;

}

void CZombie::enemyCollision(CPlayer* player, CBullet* bullets, float &oldXPos, float &oldZPos,
	wallDetails wallCoordinates[kNumLevel1Walls], keyDetails doorCoordinates[kNumLevel1Doors], int zombieNum)
{
	float bounceBack = 5.0f;
	collisionAxis enemyCollision = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(), player->GetModel()->GetZ(), 0.0f, zombieModel->GetX(), zombieModel->GetZ(), 4.0f, 4.0f, playerPosition);
	if ((enemyCollision == XAXIS || enemyCollision == ZAXIS) && !detectCollision)
	{
		enemyMovement = COLLIDED;
		//if (collisionCounter >= 4.9f)
		if (collisionCounter <= 0.0f)
		{
			player->GetModel()->SetPosition(oldXPos, 15.0f, oldZPos);
			detectCollision = true;
			collisionCounter = 5.0f;
		}
	}

	for (int i = 0; i < kNumBullets; i++)
	{
		BulletCollision = collisionDetector->Sphere2BoxCollision(bullets->oldBulletX[i], bullets->oldBulletZ[i], bullets->myBullets[i].Model->GetX(),
			bullets->myBullets[i].Model->GetZ(), 1.0f, zombieModel->GetX(), zombieModel->GetZ(), 4.0f, 4.0f, bulletHit);
		if (BulletCollision == ZAXIS || BulletCollision == XAXIS)
		{
			float moveBack = 3.0f;
			hitCounter++;
			bullets->myBullets[i].Model->SetPosition(-500.0f, bullets->myBullets[i].Model->GetY(), -500.0f);
			if (BulletCollision == ZAXIS && bulletHit) zombieModel->SetZ(oldEnemyZ[zombieNum] - moveBack);
			if (BulletCollision == ZAXIS && !bulletHit)zombieModel->SetZ(oldEnemyZ[zombieNum] + moveBack);
			if (BulletCollision == XAXIS && !bulletHit)zombieModel->SetX(oldEnemyX[zombieNum] + moveBack);
			if (BulletCollision == XAXIS && bulletHit)zombieModel->SetX(oldEnemyX[zombieNum] - moveBack);


			if (hitCounter == 5)
			{
				enemyMovement = DEAD;
			}
		}
	}

	for (int i = 0; i < kNumLevel1Doors; i++)
	{
		DoorCollision = collisionDetector->Sphere2BoxCollision(oldEnemyX[zombieNum], oldEnemyZ[zombieNum], zombieModel->GetX(), zombieModel->GetZ(), 4.0f,
			doorCoordinates[i].xPos, doorCoordinates[i].zPos, 5.0f, 5.0f, zombieDoorPosition);

		if (DoorCollision == XAXIS)zombieModel->SetX(oldEnemyX[zombieNum]);
		if (DoorCollision == ZAXIS)zombieModel->SetZ(oldEnemyZ[zombieNum]);
	}
	for (int i = 0; i < kNumLevel1Walls; i++)
	{
		WallCollision = collisionDetector->Sphere2BoxCollision(oldEnemyX[zombieNum], oldEnemyZ[zombieNum], zombieModel->GetX(), zombieModel->GetZ(), 4.0f,
			wallCoordinates[i].xPos, wallCoordinates[i].zPos, 5.0f, 5.0f, zombieWallPosition);

		if (WallCollision == XAXIS)zombieModel->SetX(oldEnemyX[zombieNum]);
		if (WallCollision == ZAXIS)zombieModel->SetZ(oldEnemyZ[zombieNum]);

	}


}
void CZombie::enemyCollisionTwo(CPlayer* player, CBullet* bullets, float &oldXPos, float &oldZPos,
	wallDetails wallCoordinates[kNumLevel2Walls], keyDetails doorCoordinates[kNumLevel2Doors], int zombieNum)
{
	float bounceBack = 5.0f;
	collisionAxis enemyCollision = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(), player->GetModel()->GetZ(), 0.0f, zombieModel->GetX(), zombieModel->GetZ(), 4.0f, 4.0f, playerPosition);
	if ((enemyCollision == XAXIS || enemyCollision == ZAXIS) && !detectCollision)
	{
		enemyMovement = COLLIDED;
		//if (collisionCounter >= 4.9f)
		if (collisionCounter <= 0.0f)
		{
			player->GetModel()->SetPosition(oldXPos, 15.0f, oldZPos);
			detectCollision = true;
			collisionCounter = 5.0f;
		}
	}
	for (int i = 0; i < kNumBullets; i++)
	{
		BulletCollision = collisionDetector->Sphere2BoxCollision(bullets->oldBulletX[i], bullets->oldBulletZ[i], bullets->myBullets[i].Model->GetX(),
			bullets->myBullets[i].Model->GetZ(), 1.0f, zombieModel->GetX(), zombieModel->GetZ(), 4.0f, 4.0f, bulletHit);
		if (BulletCollision == ZAXIS || BulletCollision == XAXIS)
		{
			float moveBack = 3.0f;
			hitCounter++;
			bullets->myBullets[i].Model->SetPosition(-500.0f, bullets->myBullets[i].Model->GetY(), -500.0f);
			if (BulletCollision == ZAXIS && bulletHit) zombieModel->SetZ(oldEnemyZ[zombieNum] - moveBack);
			if (BulletCollision == ZAXIS && !bulletHit)zombieModel->SetZ(oldEnemyZ[zombieNum] + moveBack);
			if (BulletCollision == XAXIS && !bulletHit)zombieModel->SetX(oldEnemyX[zombieNum] + moveBack);
			if (BulletCollision == XAXIS && bulletHit)zombieModel->SetX(oldEnemyX[zombieNum] - moveBack);


			if (hitCounter == 5)
			{

				enemyMovement = DEAD;

			}
		}
	}

	for (int i = 0; i < kNumLevel2Doors; i++)
	{
		DoorCollision = collisionDetector->Sphere2BoxCollision(oldEnemyX[zombieNum], oldEnemyZ[zombieNum], zombieModel->GetX(), zombieModel->GetZ(), 4.0f,
			doorCoordinates[i].xPos, doorCoordinates[i].zPos, 5.0f, 5.0f, zombieDoorPosition);

		if (DoorCollision == XAXIS)zombieModel->SetX(oldEnemyX[zombieNum]);
		if (DoorCollision == ZAXIS)zombieModel->SetZ(oldEnemyZ[zombieNum]);
	}
	for (int i = 0; i < kNumLevel2Walls; i++)
	{
		WallCollision = collisionDetector->Sphere2BoxCollision(oldEnemyX[zombieNum], oldEnemyZ[zombieNum], zombieModel->GetX(), zombieModel->GetZ(), 4.0f,
			wallCoordinates[i].xPos, wallCoordinates[i].zPos, 5.0f, 5.0f, zombieWallPosition);

		if (WallCollision == XAXIS)zombieModel->SetX(oldEnemyX[zombieNum]);
		if (WallCollision == ZAXIS)zombieModel->SetZ(oldEnemyZ[zombieNum]);

	}


}
void CZombie::FollowPlayer(CPlayer* player, float &oldXPos, float &oldZPos, int zombieNum)
{
	if (enemyMovement != COLLIDED && collisionCounter <= 0.0f)
	{
		distancePos[zombieNum] = fabs(sqrt(((zombieModel->GetX() - player->GetModel()->GetX())*(zombieModel->GetX() - player->GetModel()->GetX()))
			+ ((zombieModel->GetZ() - player->GetModel()->GetZ())*(zombieModel->GetZ() - player->GetModel()->GetZ()))));
		if (enemyMovement != FOLLOW && enemyMovement != COLLIDED)oldMove = enemyMovement;
		if (distancePos[zombieNum] < 20.0f)
		{
			enemyMovement = FOLLOW;
		}
		else if (distancePos[zombieNum] > 20.0f) enemyMovement = oldMove;
	}
}
void CZombie::GenerateModelCoordinates(int zombieNum)
{
	oldEnemyX[zombieNum] = zombieModel->GetX();
	oldEnemyZ[zombieNum] = zombieModel->GetZ();
}
void CZombie::CalMomentum(CBullet* bullets, int bulletNum)
{
	float distanceX = zombieModel->GetX() - bullets->myBullets[bulletNum].Model->GetX();
	float distanceZ = zombieModel->GetZ() - bullets->myBullets[bulletNum].Model->GetZ();

	float distance = fabs(sqrt((distanceX * distanceX) + (distanceZ * distanceZ)));
	distanceX /= distance;
	distanceZ /= distance;
	momentum = (zombieModel->GetX() * distanceX + zombieModel->GetZ()*distanceZ) + (bullets->myBullets[bulletNum].Model->GetX()*distanceX + bullets->myBullets[bulletNum].Model->GetZ()*distanceZ);


}

IModel* CZombie::GetModel()
{
	return zombieModel;
}

enemyMovementDef CZombie::GetZombieState()
{
	return oldMove;
}


bool CZombie::GetScoreCalcualted()
{
	return scoreCalcualted;
}

void CZombie::SetScoreCalcualted(bool trueorfalse)
{
	scoreCalcualted = trueorfalse;
}

