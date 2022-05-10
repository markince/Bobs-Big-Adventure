// File:	      CBook.hpp
// Date:	      05-02-2019
// Last Edited:   21-03-2019

#pragma once
#include "CMasterModelCreator.h"
#include "CPlayer.hpp"
#include <SFML/Audio.hpp>


#ifndef _MYBOOKFILE
#define _MYBOOKFILE


class CBook : public CMasterModelCreator
{
private:
	IModel*         level1BookModels[kNumLevel1Books];
	IModel*         level2BookModels[kNumLevel2Books];
	Collision*      collisionDetector;
	collisionAxis       booksCollisionResponse;
	sf::SoundBuffer pickUpBookBuffer;
	sf::Sound       pickUpBook;

	bool filler = false;

public:
	CBook();
	void CreateLevel1Books(IMesh* bookMesh, bookDetails level1BookoPosition[kNumLevel1Books]);
	void CreateLevel2Books(IMesh* bookMesh, bookDetails level2BookoPosition[kNumLevel2Books]);
	void RemoveLevel1Books(IMesh* bookMesh);
	void RemoveLevel2Books(IMesh* bookMesh);

	void Level1BookCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore);
	void Level2BookCollision(CPlayer* player, float oldXPos, float oldZPos, int &playerScore);

	IModel* GetLevel1BookModel(int index);
	IModel* GetLevel2BookModel(int index);

};











#endif