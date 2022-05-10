// File:	      Definitions.hpp
// Date:	      04-02-2019
// Last Edited:   04-02-2019
//
// Type definitions and constants
//
#pragma once
#ifndef _DEFINITION
#define _DEFINITION
#include "TL-Engine.h"
#include<iostream>

using namespace tle;


// -------------------------------------------------------------------------------//
// EKeyCode Constants                                                             //
// -------------------------------------------------------------------------------//

const EKeyCode kMenuKey   = Key_Escape; // Quit the game
const EKeyCode kUpKey     = Key_W;      // Move player up
const EKeyCode kDownKey   = Key_S;      // Move player down
const EKeyCode kLeftKey   = Key_A;      // Move player left
const EKeyCode kRightKey  = Key_D;      // Move player left
const EKeyCode kFirekey   = Key_Space;  // Fire Weapon
const EKeyCode kPauseKey  = Key_P;      // Pause Key
const EKeyCode kSelectKey = Key_Return; // Menu Select Key


// -------------------------------------------------------------------------------//
// Enum Constants                                                                 //
// -------------------------------------------------------------------------------//

enum collisionAxis  { NONE, XAXIS, ZAXIS };
enum screenChoice   { START, LOADGAME, SCORES, OPTIONS, QUIT, LOADING};
enum enemyMovementDef  { MOVINGUP, MOVINGDOWN, MOVINGLEFT, MOVINGRIGHT, COLLIDED, FOLLOW, DEAD, SCORECALCULATED };
enum playerMovement { UP, DOWN, LEFT, RIGHT };
enum menuOption     { SOUNDMAIN, SOUNDMUSIC, SOUNDSFX, SOUNDBACK, CONTROLSMAIN, CONTROLSUP, CONTROLSDOWN, CONTROLSLEFT, CONTROLSRIGHT, CONTROLSFIRE,
	                  CONTROLSBACK, SAVEGAMEMAIN, QUITGAMEMAIN };
enum mainScreen     { MOVELEFT, MOVERIGHT };
enum LevelState     { INTROSCREEN, GAMEACTIVE, PAUSED, MAINMENU, LEVELCOMPLETE, GAMEOVER};
enum gameState      { TITLESCREEN, LEVEL1, LEVEL2 };
enum FireBoltState  { FIREUP, FIREUPRIGHT, FIRERIGHT, FIREDOWNRIGHT, FIREDOWN, FIREDOWNLEFT, FIRELEFT, FIREUPLEFT };
enum BossMovement   { BOSSMOVINGUP, BOSSMOVINGDOWN, BOSSFIRING };
enum BossFireMode   { FIRING, NOTFIRING };
// -------------------------------------------------------------------------------//
// Constants                                                                      //
// -------------------------------------------------------------------------------//


// Constants
const int	kNumLevel1Zombies	 = 4;
const int	kNumLevel2Zombies = 4;

const int	kNumberOfFrames      = 17;
const int   kNumLevel1Walls      = 115;
const int   kNumLevel2Walls      = 404;
const int   kNumLevel1Keys       = 8;
const int   kNumLevel2Keys       = 11;
const int   kNumLevel1Doors      = 8;
const int   kNumLevel2Doors      = 11;
const int   kNumLevel1Books      = 17;
const int   kNumLevel2Books      = 52;
const int   kNumLevel2Turrets    = 16;
const int   kNumPortals          = 1;
const int   kLoadScreenStartXPos = 1920;
const int   kLoadScreenStartYPos = 1080;
const int   kNormalTextSize      = 90;
const int   kLoadingXPos         = 657;
const int   kLoadingYPos         = 472;
const int   kNumBullets          = 50;
const int   kNumLv1FloorCubes    = 272;
const int   kNumLv2FloorCubes    = 10000;
const int   kNumHLaserBolts       = 5;
const int   kNumVLaserBolts       = 1;

const int   OFFSCREEN            = -1;
const int   knumFireParticles    = 100;
const int   kNumPortalSkinNames  = 11;
const int   kNumLightningBolts = 2;
const int kNumBouncingFireBolts = 3;

const float DISPLAYEDTOP            = 0.0f;
const float DISPLAYEDBOTTOM         = 0.1f;
const float kSecond                 = 1.0f;
const float kBackgroundStartX       = 26.0f;
const float kBackgroundRotateAmount = 270.0f;
const float kBackgroundScale        = 7.0f;
const float kBobTitleXPos           = -4.0f;
const float kBobTitleYPos           = 1.0f;
const float kBobTitleRotateAmount   = 270.0f;
const float kBobTitleScaleX         = 0.4f;
const float kBobTitleScaleY         = 0.5f;
const float kMenuXPos               = 2.5f;
const float kMenuYPos               = 1.0f;
const float kMenuZPos               = 0.4f;
const float kMenuRotateAmount       = 270.0f;
const float kMenuRotateXScale       = 0.9f;
const float kMenuRotateYScale       = 0.8f;
const float kMenuCameraYPos         = 5.0f;
const float kMenuCameraRotateAmount = 90.0f;
const float kMainTitleMusicStart    = 100.0f;
const float kMainTitleMusicPitch    = 1.0f;
const float kMenuSelectVolume       = 100.0f;
const float kMenuSelectPitch        = 1.0f;
const float kGlobalVolume           = 50.0f;
const float kBackgroudLimitPos      = 0.415f;
const float kBackgroudResetPos      = 26.0f;
const float kMenuOffScreenPos       = -10.0f;
const float kBobOffScreenPos        = -10.0f;
const float kFireBoltMoveSpeed      = 50.0f;

const string kTitleScreenBackName = "grassBackground2.png";
const string kTitleMenuName       = "menuChoice1.png";
const string kLoadScreenName      = "loadingScreen.png";
const string kMenuScreenName1     = "menuChoice1.png";
const string kMenuScreenName2     = "menuChoice2.png";
const string kMenuScreenName3     = "menuChoice3.png";
const string kMenuScreenName4     = "menuChoice4.png";
const string kMenuScreenName5     = "menuChoice5.png";

const string portalSkinNames[11] = { "portal01.tga", "portal02.tga", "portal03.tga", "portal04.tga", "portal05.tga", "portal06.tga", "portal07.tga", "portal08.tga", 
                                     "portal09.tga", "portal10.tga" };
const int portalCounterValues[11] = { 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150 };

// -------------------------------------------------------------------------------//
// Structures                                                                     //
// -------------------------------------------------------------------------------//

struct wallDetails
{
	float xPos;
	float yPos;
	float zPos;
};

struct keyDetails
{
	float xPos;
	float yPos;
	float zPos;
	int   colour;
};

struct doorDetails
{
	float xPos;
	float yPos;
	float zPos;
	int   colour;
};

struct bookDetails
{
	float xPos;
	float yPos;
	float zPos;
};

struct bulletDetails
{
	float xPos;
	float yPos;
	float zPos;
};

struct enemyWaypoints
{
	float xPos;
	float yPos;
	float zPos;
	float wpWidth = 0.1f;
	float wpDepth = 0.1f;
};

struct portalDetails
{
	float xPos;
	float yPos;
	float zPos;
};

struct turretDetails
{
	float xPos;
	float yPos;
	float zPos;
	float rotation;
};

struct laserBoltHDetails
{
	float startXPos;
	float startYPos;
	float startZPos;
	float endXPos;
	float speed;
};

struct laserBoltVDetails
{
	float startXPos;
	float startYPos;
	float startZPos;
	float endZPos;
	float speed;
};

struct SParticle
{
	IModel* mModel;
	float speed;
	bool  mActive = false;
};

#endif