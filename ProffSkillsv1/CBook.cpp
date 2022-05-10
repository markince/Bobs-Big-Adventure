// File:	      CBook.cpp
// Date:	      03-02-2019
// Last Edited:   21-03-2019

#include "CBook.hpp"

CBook::CBook()
{
	pickUpBookBuffer.loadFromFile("bookPickUp2.wav");
	pickUpBook.setBuffer(pickUpBookBuffer);
	pickUpBook.setVolume(100.0f); // 0 to 100
	pickUpBook.setPitch(1.0f);
	pickUpBook.setLoop(false);

}

void CBook::CreateLevel1Books(IMesh* bookMesh, bookDetails level1BookoPosition[kNumLevel1Books])
{
	for (int i = 0; i < kNumLevel1Books; i++)
	{
		level1BookModels[i] = bookMesh->CreateModel(level1BookoPosition[i].xPos, level1BookoPosition[i].yPos, level1BookoPosition[i].zPos);
		level1BookModels[i]->RotateX(270.0f);
		level1BookModels[i]->Scale(0.7f);
		level1BookModels[i]->SetSkin("book2.png");
	}
}

void CBook::CreateLevel2Books(IMesh* bookMesh, bookDetails level2BookoPosition[kNumLevel2Books])
{
	for (int i = 0; i < kNumLevel2Books; i++)
	{
		level2BookModels[i] = bookMesh->CreateModel(level2BookoPosition[i].xPos, level2BookoPosition[i].yPos, level2BookoPosition[i].zPos);
		level2BookModels[i]->RotateX(270.0f);
		level2BookModels[i]->Scale(0.7f);
		level2BookModels[i]->SetSkin("book1.png");
	}
}

void CBook::RemoveLevel1Books(IMesh* wallMesh)
{
	for (int i = 0; i < kNumLevel1Books; i++)
	{
		wallMesh->RemoveModel(level1BookModels[i]);

	}
}

void CBook::RemoveLevel2Books(IMesh* wallMesh)
{
	for (int i = 0; i < kNumLevel2Books; i++)
	{
		wallMesh->RemoveModel(level2BookModels[i]);

	}
}

void CBook::Level1BookCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore)
{
	for (int i = 0; i < kNumLevel1Books; i++)
	{

		booksCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level1BookModels[i]->GetX(), level1BookModels[i]->GetZ(), 1.0f, 1.0f, filler);

		if (booksCollisionResponse == XAXIS || booksCollisionResponse == ZAXIS)
		{
			level1BookModels[i]->SetX(-200.0f);
			pickUpBook.play();
			player->CollectLevel1Book();
			playerScore += 50;

		}
	}
}

void CBook::Level2BookCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore)
{
	for (int i = 0; i < kNumLevel2Books; i++)
	{

		booksCollisionResponse = collisionDetector->Sphere2BoxCollision(oldXPos, oldZPos, player->GetModel()->GetX(),
			player->GetModel()->GetZ(), 4.0f, level2BookModels[i]->GetX(), level2BookModels[i]->GetZ(), 1.0f, 1.0f, filler);

		if (booksCollisionResponse == XAXIS || booksCollisionResponse == ZAXIS)
		{
			level2BookModels[i]->SetX(-200.0f);
			pickUpBook.play();
			player->CollectLevel2Book();
			playerScore += 50;
		}
	}
}


IModel* CBook::GetLevel1BookModel(int index)
{
	return level1BookModels[index];
}

IModel* CBook::GetLevel2BookModel(int index)
{
	return level2BookModels[index];
}