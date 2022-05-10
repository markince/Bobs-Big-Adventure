// File:	      CKey.cpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#include "CKey.hpp"

CKey::CKey()
{
	pickUpKeyBuffer.loadFromFile("keyPickUp.wav");
	pickUpKey.setBuffer(pickUpKeyBuffer);
	pickUpKey.setVolume(100.0f); // 0 to 100
	pickUpKey.setPitch(1.0f);
	pickUpKey.setLoop(false);
}

void CKey::CreateLevel1Keys(IMesh* keyMesh, keyDetails level1keyPosition[kNumLevel1Keys])
{
	for (int i = 0; i < kNumLevel1Keys; i++)
	{
		level1KeyModels[i] = keyMesh->CreateModel(level1keyPosition[i].xPos, level1keyPosition[i].yPos, level1keyPosition[i].zPos);
		level1KeyModels[i]->RotateX(270.0f);
		level1KeyModels[i]->Scale(0.8f);
		switch (level1keyPosition[i].colour)
		{
		case 1:
		{
			level1KeyModels[i]->SetSkin("redKey.png");
			level1KeyColour[i] = 1;
			break;
		}
		case 2:
		{
			level1KeyModels[i]->SetSkin("blueKey.png");
			level1KeyColour[i] = 2;

			break;
		}
		case 3:
		{
			level1KeyModels[i]->SetSkin("greenKey.png");
			level1KeyColour[i] = 3;

			break;
		}
		case 4:
		{
			level1KeyModels[i]->SetSkin("yellowKey.png");
			level1KeyColour[i] = 4;
			break;
		}
		}
	}
}

void CKey::CreateLevel2Keys(IMesh* keyMesh, keyDetails level2keyPosition[kNumLevel2Keys])
{
	for (int i = 0; i < kNumLevel2Keys; i++)
	{
		level2KeyModels[i] = keyMesh->CreateModel(level2keyPosition[i].xPos, level2keyPosition[i].yPos, level2keyPosition[i].zPos);
		level2KeyModels[i]->RotateX(270.0f);
		level2KeyModels[i]->Scale(0.8f);
		switch (level2keyPosition[i].colour)
		{
		case 1:
		{
			level2KeyModels[i]->SetSkin("redKey.png");
			level2KeyColour[i] = 1;
			break;
		}
		case 2:
		{
			level2KeyModels[i]->SetSkin("blueKey.png");
			level2KeyColour[i] = 2;

			break;
		}
		case 3:
		{
			level2KeyModels[i]->SetSkin("greenKey.png");
			level2KeyColour[i] = 3;

			break;
		}
		case 4:
		{
			level2KeyModels[i]->SetSkin("yellowKey.png");
			level2KeyColour[i] = 4;
			break;
		}
		}
	}
}




void CKey::RemoveLevel1Keys(IMesh* keyMesh)
{
	for (int i = 0; i < kNumLevel1Keys; i++)
	{
		level1KeyModels[i]->~IModel();

	}

}

void CKey::Level1KeyCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore)
{
	for (int i = 0; i < kNumLevel1Keys; i++)
	{
		keysCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level1KeyModels[i]->GetX(), level1KeyModels[i]->GetZ(), 1.0f, 1.0f, filler);
		if (keysCollisionResponse == XAXIS || keysCollisionResponse == ZAXIS)
		{
			level1KeyModels[i]->SetX(-200.0f);
			pickUpKey.play();
			playerScore += 10;

			if (level1KeyColour[i] == 1) player->CollectLevel1RedKey();
			if (level1KeyColour[i] == 2) player->CollectLevel1BlueKey();
			if (level1KeyColour[i] == 3) player->CollectLevel1GreenKey();
			if (level1KeyColour[i] == 4) player->CollectLevel1YellowKey();
		}
	}
}

void CKey::Level2KeyCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore)
{
	for (int i = 0; i < kNumLevel2Keys; i++)
	{
		keysCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level2KeyModels[i]->GetX(), level2KeyModels[i]->GetZ(), 1.0f, 1.0f, filler);
		if (keysCollisionResponse == XAXIS || keysCollisionResponse == ZAXIS)
		{
			level2KeyModels[i]->SetX(-200.0f);
			pickUpKey.play();
			playerScore += 10;
			if (level2KeyColour[i] == 1) player->CollectLevel2RedKey();
			if (level2KeyColour[i] == 2) player->CollectLevel2BlueKey();
			if (level2KeyColour[i] == 3) player->CollectLevel2GreenKey();
			if (level2KeyColour[i] == 4) player->CollectLevel2YellowKey();
		}
	}
}