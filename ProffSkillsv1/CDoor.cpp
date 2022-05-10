// File:	      CDoor.cpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#include "CDoor.hpp"

CDoor::CDoor()
{
	collisionDetector = new Collision;
	unlockDoorBuffer.loadFromFile("doorUnlock.wav");
	unlockDoor.setBuffer(unlockDoorBuffer);
	unlockDoor.setVolume(100.0f); // 0 to 100
	unlockDoor.setPitch(1.0f);
	unlockDoor.setLoop(false);

}

void CDoor::CreateLevel1Doors(IMesh* doorMesh, keyDetails level1DoorPosition[kNumLevel1Doors])
{
	for (int i = 0; i < kNumLevel1Doors; i++)
	{
		level1DoorModels[i] = doorMesh->CreateModel(level1DoorPosition[i].xPos, level1DoorPosition[i].yPos, level1DoorPosition[i].zPos);
		level1DoorModels[i]->RotateX(270.0f);
		level1DoorModels[i]->Scale(0.9f);

		switch (level1DoorPosition[i].colour)
		{
		case 1:
		{
			level1DoorModels[i]->SetSkin("redDoor.png");
			Level1DoorColour[i] = 1;
			break;
		}
		case 2:
		{
			level1DoorModels[i]->SetSkin("blueDoor.png");
			Level1DoorColour[i] = 2;

			break;
		}
		case 3:
		{
			level1DoorModels[i]->SetSkin("greenDoor.png");
			Level1DoorColour[i] = 3;

			break;
		}
		case 4:
		{
			level1DoorModels[i]->SetSkin("yellowDoor.png");
			Level1DoorColour[i] = 4;

			break;
		}
		}
	}
}

void CDoor::CreateLevel2Doors(IMesh* doorMesh, keyDetails level2DoorPosition[kNumLevel2Doors])
{
	for (int i = 0; i < kNumLevel2Doors; i++)
	{
		level2DoorModels[i] = doorMesh->CreateModel(level2DoorPosition[i].xPos, level2DoorPosition[i].yPos, level2DoorPosition[i].zPos);
		level2DoorModels[i]->RotateX(270.0f);
		level2DoorModels[i]->Scale(0.9f);

		switch (level2DoorPosition[i].colour)
		{
		case 1:
		{
			level2DoorModels[i]->SetSkin("redDoor.png");
			Level2DoorColour[i] = 1;
			break;
		}
		case 2:
		{
			level2DoorModels[i]->SetSkin("blueDoor.png");
			Level2DoorColour[i] = 2;

			break;
		}
		case 3:
		{
			level2DoorModels[i]->SetSkin("greenDoor.png");
			Level2DoorColour[i] = 3;

			break;
		}
		case 4:
		{
			level2DoorModels[i]->SetSkin("yellowDoor.png");
			Level2DoorColour[i] = 4;

			break;
		}
		}
	}
}

void CDoor::RemoveLevel1Doors(IMesh* keyMesh)
{
	for (int i = 0; i < kNumLevel1Keys; i++)
	{
		level1DoorModels[i]->~IModel();

	}

}

void CDoor::Level1DoorCollision(CPlayer* player, float oldXPos, float oldZPos, keyDetails level1DoorPosition[kNumLevel1Doors], int &playerScore)
{
	for (int i = 0; i < kNumLevel1Doors; i++)
	{
		doorsCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level1DoorModels[i]->GetX(), level1DoorModels[i]->GetZ(), 5.0f, 5.0f, filler);

		if (doorsCollisionResponse == XAXIS) player->GetModel()->SetX(oldXPos);
		if (doorsCollisionResponse == ZAXIS) player->GetModel()->SetZ(oldZPos);
		if (doorsCollisionResponse == XAXIS || doorsCollisionResponse == ZAXIS)
		{

			if (Level1DoorColour[i] == 1 && player->GetNumLevel1RedKeys() > 0)
			{
				level1DoorModels[i]->SetX(-200.0f);
				player->UseLevel1RedKey();
				unlockDoor.play();
				playerScore += 10;

			}
			if (Level1DoorColour[i] == 2 && player->GetNumLevel1BlueKeys() > 0)
			{
				level1DoorModels[i]->SetX(-200.0f);
				player->UseLevel1BlueKey();
				unlockDoor.play();
				playerScore += 10;


			}
			if (Level1DoorColour[i] == 3 && player->GetNumLevel1GreenKeys() > 0)
			{
				level1DoorModels[i]->SetX(-200.0f);
				player->UseLevel1GreenKey();
				unlockDoor.play();
				playerScore += 10;

			}
			if (Level1DoorColour[i] == 4 && player->GetNumLevel1YellowKeys() > 0)
			{
				level1DoorModels[i]->SetX(-200.0f);
				player->UseLevel1YellowKey();
				unlockDoor.play();
				playerScore += 10;

			}

		}
		level1DoorPosition[i] = { level1DoorModels[i]->GetX(),level1DoorModels[i]->GetY(),level1DoorModels[i]->GetZ() };
	}
}

void CDoor::Level2DoorCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore)
{
	for (int i = 0; i < kNumLevel2Doors; i++)
	{
		doorsCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level2DoorModels[i]->GetX(), level2DoorModels[i]->GetZ(), 5.0f, 5.0f, filler);

		if (doorsCollisionResponse == XAXIS) player->GetModel()->SetX(oldXPos);
		if (doorsCollisionResponse == ZAXIS) player->GetModel()->SetZ(oldZPos);
		if (doorsCollisionResponse == XAXIS || doorsCollisionResponse == ZAXIS)
		{
			if (Level2DoorColour[i] == 1 && player->GetNumLevel2RedKeys() > 0)
			{
				level2DoorModels[i]->SetX(-200.0f);
				player->UseLevel2RedKey();
				unlockDoor.play();
				playerScore += 10;
			}
			if (Level2DoorColour[i] == 2 && player->GetNumLevel2BlueKeys() > 0)
			{
				level2DoorModels[i]->SetX(-200.0f);
				player->UseLevel2BlueKey();
				unlockDoor.play();
				playerScore += 10;

			}
			if (Level2DoorColour[i] == 3 && player->GetNumLevel2GreenKeys() > 0)
			{
				level2DoorModels[i]->SetX(-200.0f);
				player->UseLevel2GreenKey();
				unlockDoor.play();
				playerScore += 10;

			}
			if (Level2DoorColour[i] == 4 && player->GetNumLevel2YellowKeys() > 0)
			{
				level2DoorModels[i]->SetX(-200.0f);
				player->UseLevel2YellowKey();
				unlockDoor.play();
				playerScore += 10;

			}

		}
	}
}


