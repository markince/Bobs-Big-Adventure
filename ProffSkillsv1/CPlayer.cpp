// File:	      CPlayer.cpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#include "CPlayer.hpp"
//#include <math.h>

CPlayer::CPlayer() // Constructor
{

}


void CPlayer::CreateModel(IMesh* spriteMeshIn)
{
	playerModel = spriteMeshIn->CreateModel(85.0f, 15.0f, 85.0f);
	playerModel->RotateX(270.0f);
	playerModel->SetSkin("moveDown3.png");
	playerModel->Scale(1.2f);
}

void CPlayer::RemoveModel(IMesh* spriteMeshIn)
{
	spriteMeshIn->RemoveModel(playerModel);
}



IModel* CPlayer::GetModel()
{
	return playerModel;
}

void CPlayer::MoveUp(float speed, int &moveCounter)
{
	bobDirection = UP;
	moveCounter++;
	playerModel->MoveZ(speed);
	if      (moveCounter == 20) playerModel->SetSkin("moveUp1.png");
	else if (moveCounter == 40)  playerModel->SetSkin("moveUp2.png");
	else if (moveCounter == 60) playerModel->SetSkin("moveUp3.png");
	else if (moveCounter == 80) playerModel->SetSkin("moveUp4.png");
	else if (moveCounter == 100) playerModel->SetSkin("moveUp5.png");
	else if (moveCounter == 120) playerModel->SetSkin("moveUp6.png");
	else if (moveCounter == 140) playerModel->SetSkin("moveUp7.png");
	else if (moveCounter == 160) playerModel->SetSkin("moveUp8.png");
	else if (moveCounter == 180) playerModel->SetSkin("moveUp9.png");
	else if (moveCounter == 200) moveCounter = 19;
}



void CPlayer::MoveDown(float speed, int &moveCounter)
{
	bobDirection = DOWN;
	moveCounter++;
	playerModel->MoveZ(-speed);

	if      (moveCounter == 20) playerModel->SetSkin("moveDown1.png");
	else if (moveCounter == 40) playerModel->SetSkin("moveDown2.png");
	else if (moveCounter == 60) playerModel->SetSkin("moveDown3.png");
	else if (moveCounter == 80) playerModel->SetSkin("moveDown4.png");
	else if (moveCounter == 100) playerModel->SetSkin("moveDown5.png");
	else if (moveCounter == 120) playerModel->SetSkin("moveDown6.png");
	else if (moveCounter == 140) playerModel->SetSkin("moveDown7.png");
	else if (moveCounter == 160) playerModel->SetSkin("moveDown8.png");
	else if (moveCounter == 180) playerModel->SetSkin("moveDown9.png");
	else if (moveCounter == 200) moveCounter = 19;
}

void CPlayer::MoveLeft(float speed, int &moveCounter)
{
	bobDirection = LEFT;
	moveCounter++;
	playerModel->MoveX(-speed);
	if      (moveCounter == 20) playerModel->SetSkin("moveLeft1.png");
	else if (moveCounter == 40) playerModel->SetSkin("moveLeft2.png");
	else if (moveCounter == 60) playerModel->SetSkin("moveLeft3.png");
	else if (moveCounter == 80) playerModel->SetSkin("moveLeft4.png");
	else if (moveCounter == 100) playerModel->SetSkin("moveLeft5.png");
	else if (moveCounter == 120) playerModel->SetSkin("moveLeft6.png");
	else if (moveCounter == 140) playerModel->SetSkin("moveLeft7.png");
	else if (moveCounter == 160) playerModel->SetSkin("moveLeft8.png");
	else if (moveCounter == 180) playerModel->SetSkin("moveLeft9.png");
	else if (moveCounter == 200) moveCounter = 19;
}

void CPlayer::MoveRight(float speed, int &moveCounter)
{
	bobDirection = RIGHT;
	moveCounter++;
	playerModel->MoveX(speed);
	if      (moveCounter == 20) playerModel->SetSkin("moveRight1.png");
	else if (moveCounter == 40) playerModel->SetSkin("moveRight2.png");
	else if (moveCounter == 60) playerModel->SetSkin("moveRight3.png");
	else if (moveCounter == 80) playerModel->SetSkin("moveRight4.png");
	else if (moveCounter == 100) playerModel->SetSkin("moveRight5.png");
	else if (moveCounter == 120) playerModel->SetSkin("moveRight6.png");
	else if (moveCounter == 140) playerModel->SetSkin("moveRight7.png");
	else if (moveCounter == 160) playerModel->SetSkin("moveRight8.png");
	else if (moveCounter == 180) playerModel->SetSkin("moveRight9.png");
	else if (moveCounter == 200) moveCounter = 19;
}

void CPlayer::Death(int &moveCounter)
{
	moveCounter++;
	if      (moveCounter == 20) playerModel->SetSkin("die1.png");
	else if (moveCounter == 40) playerModel->SetSkin("die2.png");
	else if (moveCounter == 60) playerModel->SetSkin("die3.png");
	else if (moveCounter == 80) playerModel->SetSkin("die4.png");
	else if (moveCounter == 100) playerModel->SetSkin("die5.png");
	else if (moveCounter == 120) playerModel->SetSkin("die6.png");


}

void CPlayer::PlayerMovement(int &moveCounter)
{
	float movementSpeed = playerMoveSpeed * frameTime;
	if (myEngine->KeyHit(Key_M))
	{
		cout << "X:" << playerModel->GetX() << " Y:" << playerModel->GetY() << " Z:" << playerModel->GetZ() << endl;
		playerModel->SetPosition(145.0f, 15.0f, 310.0f);

	}
	// Player Movement
	int upDown = 0;
	int leftRight = 0;

	// Left & Right
	if (myEngine->KeyHeld(Key_A) && !myEngine->KeyHeld(Key_D))
	{
		leftRight = -1;
		--left;
	}
	else if (left < 0)
	{
		if (myEngine->KeyHeld(Key_D))
		{
			leftRight = 1;
			if (!myEngine->KeyHeld(Key_A))
			{
				left = 0;
			}
		}
		else
		{
			leftRight = 0;
			left = 0;
		}
	}

	if (myEngine->KeyHeld(Key_D) && !myEngine->KeyHeld(Key_A))
	{
		leftRight = 1;
		++right;
	}
	else if (right > 0)
	{
		if (myEngine->KeyHeld(Key_A))
		{
			leftRight = -1;
			if (!myEngine->KeyHeld(Key_D))
			{
				right = 0;
			}
		}
		else
		{
			leftRight = 0;
			right = 0;
		}
	}

	// Up & Down
	if (myEngine->KeyHeld(Key_S) && !myEngine->KeyHeld(Key_W))
	{
		upDown = -1;
		--up;
	}
	else if (up < 0)
	{
		if (myEngine->KeyHeld(Key_W))
		{
			upDown = 1;
			if (!myEngine->KeyHeld(Key_S))
			{
				up = 0;
			}
		}
		else
		{
			upDown = 0;
			up = 0;
		}
	}

	if (myEngine->KeyHeld(Key_W) && !myEngine->KeyHeld(Key_S))
	{
		upDown = 1;
		++down;
	}
	else if (down > 0)
	{
		if (myEngine->KeyHeld(Key_S))
		{
			upDown = -1;
			if (!myEngine->KeyHeld(Key_W))
			{
				down = 0;
			}
		}
		else
		{
			upDown = 0;
			down = 0;
		}
	}

	// Diagonal movement - Up/Left & Up/Right

	if (leftRight == -1 && upDown == 0)
	{
		MoveLeft(movementSpeed, moveCounter);
	}
	if (leftRight == 1 && upDown == 0)
	{
		MoveRight(movementSpeed, moveCounter);
	}
	if (leftRight == 0 && upDown == 1)
	{
		MoveUp(movementSpeed, moveCounter);
	}
	if (leftRight == 0 && upDown == -1)
	{
		MoveDown(movementSpeed, moveCounter);
	}

	if (leftRight == -1 && upDown == -1)
	{
		MoveDown(movementSpeed * cosf(45.0f), moveCounter);
		MoveLeft(movementSpeed * sinf(45.0f), moveCounter);
	}
	if (leftRight == 1 && upDown == -1)
	{
		MoveDown(movementSpeed * cosf(45.0f), moveCounter);
		MoveRight(movementSpeed * sinf(45.0f), moveCounter);
	}
	if (leftRight == -1 && upDown == 1)
	{
		MoveUp(movementSpeed * cosf(45.0f), moveCounter);
		MoveLeft(movementSpeed * sinf(45.0f), moveCounter);
	}
	if (leftRight == 1 && upDown == 1)
	{
		MoveUp(movementSpeed * cosf(45.0f), moveCounter);
		MoveRight(movementSpeed * sinf(45.0f), moveCounter);
	}
}


//***************************************************************************************

void CPlayer::CollectLevel1RedKey()
{
	numLevel1RedKeys++;
}

void CPlayer::CollectLevel1BlueKey()
{
	numLevel1BlueKeys++;
}

void CPlayer::CollectLevel1GreenKey()
{
	numLevel1GreenKeys++;
}

void CPlayer::CollectLevel1YellowKey()
{
	numLevel1YellowKeys++;
}

void CPlayer::CollectLevel1Book()
{
	numLevel1Books++;

}

//***************************************************************************************

void CPlayer::CollectLevel2RedKey()
{
	numLevel2RedKeys++;
}

void CPlayer::CollectLevel2BlueKey()
{
	numLevel2BlueKeys++;
}

void CPlayer::CollectLevel2GreenKey()
{
	numLevel2GreenKeys++;
}

void CPlayer::CollectLevel2YellowKey()
{
	numLevel2YellowKeys++;
}


void CPlayer::CollectLevel2Book()
{
	numLevel2Books++;

}

//***************************************************************************************


void CPlayer::UseLevel1RedKey()
{
	numLevel1RedKeys--;
}

void CPlayer::UseLevel1BlueKey()
{
	numLevel1BlueKeys--;
}
void CPlayer::UseLevel1GreenKey()
{
	numLevel1GreenKeys--;
}
void CPlayer::UseLevel1YellowKey()
{
	numLevel1YellowKeys--;
}

//***************************************************************************************


void CPlayer::UseLevel2RedKey()
{
	numLevel2RedKeys--;
}

void CPlayer::UseLevel2BlueKey()
{
	numLevel2BlueKeys--;
}
void CPlayer::UseLevel2GreenKey()
{
	numLevel2GreenKeys--;
}
void CPlayer::UseLevel2YellowKey()
{
	numLevel2YellowKeys--;
}

//***************************************************************************************


int CPlayer::GetNumLevel1RedKeys()
{
	return numLevel1RedKeys;
}


int CPlayer::GetNumLevel1BlueKeys()
{
	return numLevel1BlueKeys;
}

int CPlayer::GetNumLevel1GreenKeys()
{
	return numLevel1GreenKeys;
}

int CPlayer::GetNumLevel1YellowKeys()
{
	return numLevel1YellowKeys;
}

int CPlayer::GetNumLevel1Books()
{
	return numLevel1Books;
}

//***************************************************************************************


int CPlayer::GetNumLevel2RedKeys()
{
	return numLevel2RedKeys;
}


int CPlayer::GetNumLevel2BlueKeys()
{
	return numLevel2BlueKeys;
}

int CPlayer::GetNumLevel2GreenKeys()
{
	return numLevel2GreenKeys;
}

int CPlayer::GetNumLevel2YellowKeys()
{
	return numLevel2YellowKeys;
}

int CPlayer::GetNumLevel2Books()
{
	return numLevel2Books;
}