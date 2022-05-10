// File:	      Definitions.hpp
// Date:	      04-02-2019
// Last Edited:   04-02-2019
//
// Type definitions and constants
//
#pragma once

const EKeyCode kQuitKey = Key_Escape; // Quit the game
const EKeyCode kUpKey = Key_W;      // Move player up
const EKeyCode kDownKey = Key_S;      // Move player down
const EKeyCode kLeftKey = Key_A;      // Move player left
const EKeyCode kRightKey = Key_D;      // Move player left
const EKeyCode kFireKey = Key_Space;

enum collision { NONE, XAXIS, ZAXIS };




// Constants
const float kSecond   = 1.0f;
const int   kNumWalls = 82;
const int   kNumKeys  = 8;
const int   kNumDoors = 8;
const int   kNumBooks = 11;

struct wallDetails
{
	float xPos;
	float yPos;
	float zPos;
};

wallDetails  level1walls[kNumWalls] = { {  55.0f, 1.0f,  15.0f },{  65.0f, 1.0f,  15.0f },{  75.0f, 1.0f,  15.0f },{  85.0f, 1.0f,  15.0f },
							          {  95.0f, 1.0f,  15.0f },{ 105.0f, 1.0f,  15.0f },{ 115.0f, 1.0f,  15.0f },{  55.0f, 1.0f,  25.0f },
                                      {  55.0f, 1.0f,  35.0f },{  55.0f, 1.0f,  45.0f },{  85.0f, 1.0f,  25.0f },{  85.0f, 1.0f,  35.0f },
                                      {  85.0f, 1.0f,  45.0f },{ 115.0f, 1.0f,  25.0f },{ 115.0f, 1.0f,  35.0f },{ 115.0f, 1.0f,  45.0f },
                                      {  15.0f, 1.0f,  55.0f },{  25.0f, 1.0f,  55.0f },{  35.0f, 1.0f,  55.0f },{  45.0f, 1.0f,  55.0f },
                                      {  55.0f, 1.0f,  55.0f },{  65.0f, 1.0f,  55.0f },{  85.0f, 1.0f,  55.0f },{ 105.0f, 1.0f,  55.0f },
                                      { 115.0f, 1.0f,  55.0f },{ 125.0f, 1.0f,  55.0f },{ 135.0f, 1.0f,  55.0f },{ 145.0f, 1.0f,  55.0f },
                                      { 155.0f, 1.0f,  55.0f },{  15.0f, 1.0f,  65.0f },{ 155.0f, 1.0f,  65.0f },{  15.0f, 1.0f,  75.0f },
                                      {  55.0f, 1.0f,  75.0f },{ 115.0f, 1.0f,  75.0f },{ 155.0f, 1.0f,  75.0f },{  15.0f, 1.0f,  85.0f },
                                      {  25.0f, 1.0f,  85.0f },{  35.0f, 1.0f,  85.0f },{  45.0f, 1.0f,  85.0f },{  55.0f, 1.0f,  85.0f },
                                      { 115.0f, 1.0f,  85.0f },{ 125.0f, 1.0f,  85.0f },{ 135.0f, 1.0f,  85.0f },{ 145.0f, 1.0f,  85.0f },
                                      { 155.0f, 1.0f,  85.0f },{  15.0f, 1.0f,  95.0f },{  55.0f, 1.0f,  95.0f },{ 115.0f, 1.0f,  95.0f },
                                      { 155.0f, 1.0f,  95.0f },{ 15.0f,  1.0f, 105.0f },{ 155.0f, 1.0f, 105.0f },{  15.0f, 1.0f, 115.0f },
                                      {  25.0f, 1.0f, 115.0f },{  35.0f, 1.0f, 115.0f },{  45.0f, 1.0f, 115.0f },{  55.0f, 1.0f, 115.0f },
                                      {  75.0f, 1.0f, 115.0f },{  95.0f, 1.0f, 115.0f },{ 115.0f, 1.0f, 115.0f },{ 125.0f, 1.0f, 115.0f },
                                      { 135.0f, 1.0f, 115.0f },{ 145.0f, 1.0f, 115.0f },{ 155.0f, 1.0f, 115.0f },{  35.0f, 1.0f, 125.0f },
                                      {  75.0f, 1.0f, 125.0f },{  95.0f, 1.0f, 125.0f },{ 135.0f, 1.0f, 125.0f },{  35.0f, 1.0f, 135.0f },
                                      {  75.0f, 1.0f, 135.0f },{  85.0f, 1.0f, 135.0f },{  95.0f, 1.0f, 135.0f },{ 135.0f, 1.0f, 135.0f },
                                      {  35.0f, 1.0f, 145.0f },{  45.0f, 1.0f, 145.0f },{  55.0f, 1.0f, 145.0f },{  65.0f, 1.0f, 145.0f },
                                      {  75.0f, 1.0f, 145.0f },{  95.0f, 1.0f, 145.0f },{ 105.0f, 1.0f, 145.0f },{ 115.0f, 1.0f, 145.0f },
                                      { 125.0f, 1.0f, 145.0f },{ 135.0f, 1.0f, 145.0f } };

struct keyDetails
{
	float xPos;
	float yPos;
	float zPos;
	int   colour;
};

keyDetails level1keyPosition[kNumKeys] = { { 105.0f, 10.0f,  75.0f, 1 },{ 105.0f, 10.0f,  95.0f, 1 }, {  65.0f, 10.0f, 75.0f, 2 },
                                         {  65.0f, 10.0f,  95.0f, 2 },{  75.0f, 10.0f,  25.0f, 3 }, {  95.0f, 10.0f, 25.0f, 3 },
                                         {  35.0f, 10.0f, 105.0f, 4 },{ 135.0f, 10.0f, 105.0f, 4 } };


struct doorDetails
{
	float xPos;
	float yPos;
	float zPos;
	int   colour;
};

keyDetails level1DoorPosition[kNumDoors] = { {  55.0f,  10.0f,  65.0f, 1 }, { 115.0f, 10.0f,  105.0f, 1 }, {  55.0f, 10.0f,  105.0f, 2 }, 
                                           { 115.0f,  10.0f,  65.0f, 2 }, {  65.0f, 10.0f,  115.0f, 3 }, { 105.0f, 10.0f,  115.0f, 3 },
                                           {  75.0f,  10.0f,  55.0f, 4 }, {  95.0f, 10.0f,  55.0f, 4 } };

struct bookDetails
{
	float xPos;
	float yPos;
	float zPos;
};

bookDetails level1BookoPosition[kNumBooks] = { {  55.0f,  10.0f,  125.0f }, {  115.0f,  10.0f,  125.0f },{   35.0f,  10.0f,  95.0f },
											   {  135.0f,  10.0f,  95.0f }, {   35.0f,  10.0f,   75.0f },{  135.0f,  10.0f,  75.0f }, 
											   {   85.0f,  10.0f,  65.0f }, {   75.0f,  10.0f,   35.0f },{   95.0f,  10.0f,  35.0f },
											   {   65.0f,  10.0f,  85.0f }, {  105.0f,  10.0f,  85.0f } };
