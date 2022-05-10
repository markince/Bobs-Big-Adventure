// File:	      CBullet.cpp
// Date:	      03-02-2019
// Last Edited:   21-03-2019

#include "CBullet.hpp"

CBullet::CBullet(I3DEngine* engine)
{
	fireBulletBuffer.loadFromFile("laserGunShoot.wav");
	fireBullet.setBuffer(fireBulletBuffer);
	fireBullet.setVolume(30.0f); // 0 to 100
	fireBullet.setPitch(1.0f);
	fireBullet.setLoop(false);

	collisionBulletBuffer.loadFromFile("bulletHit.wav");
	collisionBullet.setBuffer(collisionBulletBuffer);
	collisionBullet.setVolume(30.0f); // 0 to 100
	collisionBullet.setPitch(1.0f);
	collisionBullet.setLoop(false);



	myEngine = engine;
}

void CBullet::CreateModel(IMesh* bulletMesh, IModel* player, bulletDetails level1BulletPosition[])
{
	for (int i = 0; i < kNumBullets; i++)
	{
		myBullets[i].Model = bulletMesh->CreateModel(level1BulletPosition[i].xPos, level1BulletPosition[i].yPos, level1BulletPosition[i].zPos);
		myBullets[i].Model->SetSkin("laser.png");
	}

}

void CBullet::DeleteModel(IMesh* bulletMesh)
{
	for (int i = 0; i < kNumBullets; i++)
	{
		bulletMesh->RemoveModel(myBullets[i].Model);
	}

}


void CBullet::Update(playerMovement currentDirection, IModel* player, float frameTime)
{
	if (myEngine->KeyHit(Key_Space))
	{
		Fire(currentDirection, player);
	}

	for (int i = 0; i < kNumBullets; ++i)
	{
		oldBulletX[i] = myBullets[i].Model->GetX();
		oldBulletZ[i] = myBullets[i].Model->GetZ();

		if (myBullets[i].fired == true)
		{
			switch (myBullets[i].firingDirection)
			{
			case UP:
				myBullets[i].Model->MoveZ(bulletSpeed * frameTime);
				break;
			case DOWN:
				myBullets[i].Model->MoveZ(-bulletSpeed * frameTime);
				break;
			case LEFT:
				myBullets[i].Model->MoveX(-bulletSpeed * frameTime);
				break;
			case RIGHT:
				myBullets[i].Model->MoveX(bulletSpeed * frameTime);
				break;
			}

		}
	}
	Reset();
}

void CBullet::Fire(playerMovement currentDirection, IModel* player)
{
	for (int i = 0; i < kNumBullets; ++i)
	{
		if (myBullets[i].fired == false)
		{
			myBullets[i].fired = true;

			float tmp[16];
			player->GetMatrix(tmp);
			myBullets[i].Model->SetMatrix(tmp);
			myBullets[i].Model->SetY(10.0f);
			myBullets[i].Model->SetZ(player->GetZ() - 4.4f);
			myBullets[i].Model->Scale(0.2f);

			myBullets[i].firingDirection = currentDirection;
			if (currentDirection == UP || currentDirection == DOWN)
			{
				myBullets[i].Model->RotateY(90.0f);
			}

			fireBullet.play();

			return;
		}
	}
}

void CBullet::Reset()
{
	/****************************************** temporary reset of bullets ************************************************/
	for (int i = 0; i < kNumBullets; ++i)
	{
		if (myBullets[i].Model->GetX() > 500.0f || myBullets[i].Model->GetX() < -500.0f)
		{
			myBullets[i].fired = false;
			myBullets[i].Model->SetY(-10.0f); // Move out of view
		}
		if (myBullets[i].Model->GetZ() > 500.0f || myBullets[i].Model->GetLocalZ() < -500.0f)
		{
			myBullets[i].fired = false;
			myBullets[i].Model->SetLocalY(10.0f); // Move out of view
			myBullets[i].Model->RotateY(-90.0f);
		}
		if (myBullets[i].Model->GetY() < 10.0f)
		{
			myBullets[i].fired = false;
			myBullets[i].Model->SetY(-10.0f);
		}
	}
	// Reset bullet when collision
}



void CBullet::level1WallCollision(wallDetails level1Walls[kNumLevel1Walls], CPlayer* player)
{
	for (int i = 0; i < kNumLevel1Walls; i++)
	{
		for (int j = 0; j < kNumBullets; j++)
		{
			if (collisionDetector->sphere2Box(myBullets[j].Model->GetX(), myBullets[j].Model->GetZ(), 1.0f, level1Walls[i].xPos,
				level1Walls[i].zPos, 10.0f, 10.0f))
			{
				myBullets[j].Model->SetPosition(player->GetModel()->GetX(), -11.0f, player->GetModel()->GetZ());
			}
		}
	}
}
void CBullet::level2WallCollision(wallDetails level2Walls[kNumLevel2Walls], CPlayer* player)
{
	for (int i = 0; i < kNumLevel2Walls; i++)
	{
		for (int j = 0; j < kNumBullets; j++)
		{
			if (collisionDetector->sphere2Box(myBullets[j].Model->GetX(), myBullets[j].Model->GetZ(), 1.0f, level2Walls[i].xPos,
				level2Walls[i].zPos, 10.0f, 10.0f))
			{
				myBullets[j].Model->SetPosition(player->GetModel()->GetX(), -11.0f, player->GetModel()->GetZ());
			}
		}
	}
}


void CBullet::level1DoorCollision(keyDetails level1DoorPosition[kNumLevel1Doors], CPlayer* player)
{
	for (int i = 0; i < kNumLevel1Doors; i++)
	{
		for (int j = 0; j < kNumBullets; j++)
		{
			if (collisionDetector->sphere2Box(myBullets[j].Model->GetX(), myBullets[j].Model->GetZ(), 1.0f, level1DoorPosition[i].xPos,
				level1DoorPosition[i].zPos, 10.0f, 10.0f))
			{
				myBullets[j].Model->SetPosition(player->GetModel()->GetX(), -11.0f, player->GetModel()->GetZ());
				Reset();

			}
		}
	}
}

void CBullet::level2DoorCollision(keyDetails level2DoorPosition[kNumLevel2Doors], CPlayer* player)
{
	for (int i = 0; i < kNumLevel2Doors; i++)
	{
		for (int j = 0; j < kNumBullets; j++)
		{
			if (collisionDetector->sphere2Box(myBullets[j].Model->GetX(), myBullets[j].Model->GetZ(), 1.0f, level2DoorPosition[i].xPos,
				level2DoorPosition[i].zPos, 10.0f, 10.0f))
			{
				myBullets[j].Model->SetPosition(player->GetModel()->GetX(), -11.0f, player->GetModel()->GetZ());
				Reset();

			}
		}
	}
}
