// ProffSkillsv1.cpp: A program using the TL-Engine
// File:	      ProffSkillsv1.cpp: A game written in C++ using the TL-Engine
// Author:	      Mark Ince, Ivaylo Ivanov, Brad Halsall
// Date:	      28-02-2019
// Last Edited:   01-05-2019

/*
Program (game) to meet the full specification of CO2403 Professional Skills group Assignment 2019
- An assignment that involves a working prototype/proof of concept of a game for implementation on the 
  PC in a team of 3 people.
*/

#include <TL-Engine.h>
#include <sstream>     
#include <math.h>
#include <string>
#include <iostream>
#include <time.h>
#include "CMasterModelCreator.h"
#include "CPlayer.hpp"
#include "CZombie.hpp"
#include "CKey.hpp"
#include "CDoor.hpp"
#include "CBook.hpp"
#include "CWalls.h"
#include "CBullet.hpp"

// SFML audio used for sound
// To get this to work, make sure you have linked the correct directories in the properties options
// (See Sound Effects with SFML worksheet for more info)
#include <SFML/Audio.hpp>

// -------------------------------------------------------------------------------//
// Class definitions                                                              //
// -------------------------------------------------------------------------------//

CMasterModelCreator* ModelCreator;                     // Model creator class
CPlayer*             player;                           // Player class
CZombie*             level1Zombies[kNumLevel1Zombies]; // Level 1 zombie class
CZombie*             level2Zombies[kNumLevel1Zombies]; // Level 1 zombie class

CKey*                level1Keys;                       // Keys class
CKey*                level2Keys;                       // Keys class
CDoor*               level1Doors;                      // Doors class
CDoor*               level2Doors;                      // Doors class
CBook*               level1Books;                      // Books class
CBook*               level2Books;                      // Books class
CWalls*              level1Walls;                      // Walls class
CWalls*              level2Walls;                      // Walls class
Collision*           collisionDetector;                // Collision detector
CBullet*             bullets;


// -------------------------------------------------------------------------------//
// Enums                                                                          //
// -------------------------------------------------------------------------------//
screenChoice   menuChoice         = START;
playerMovement bobMovement        = DOWN;
mainScreen     mainScreenMovement = MOVELEFT;
LevelState     level1State        = INTROSCREEN;
LevelState     level2State        = INTROSCREEN;
menuOption     level1Menu         = SOUNDMAIN;
FireBoltState  fireBolt           = FIREUP;
BossMovement   level2BossMovement = BOSSMOVINGUP;
BossFireMode   level1BossFire     = NOTFIRING;
// -------------------------------------------------------------------------------//
// Variables                                                                      //
// -------------------------------------------------------------------------------//

float titleMusicCounter   = 100.0f;
float backgroundMovement  = 0.0f;
float frameTime           = 0.0f;
float fps                 = 0.0f;
float oldXPos             = 0.0f;
float oldZPos             = 0.0f;
float distanceFromBall1   = 0.0f;
float particleXPos        = 0.0f;
float level1seconds       = 0.0f;
float level2seconds = 0.0f;
float fireBoltXMove = 0.0f;
float fireBoltZMove = 0.0f;
float boltMoveX[kNumBouncingFireBolts] = { 40.0f, 50.0f, 60.0f };
float boltMoveZ[kNumBouncingFireBolts] = { 40.0f, 50.0f, 60.0f };
float hBoltCollisionCounter     = 0.0f;
float vBoltCollisionCounter     = 0.0f;
float lightningCollisionCounter = 0.0f;
float fireBoltCollisionCounter = 0.0f;
float bossGunCounter = 0.0f;
float bouncingBoltsCounter = 0.0f;
float hBossCollisionCounter = 0.0f;
int   playerMoveCounter   = 0;
int   portalCounter       = 0;
int   loadCounter         = 0;
int   endOfLevelCounter   = 0;
int   particleCounter     = 0;
int   lightningCounter[kNumLightningBolts] = { 0,0 };
int   explosionCounter    = 0; // Explosion
int   level1minutes = 0;
int   level2minutes = 0;
int   bossFireCounter = 0;
int   healthCounterLvl1 = 10;
int   deathCounter = 0; 
int   bossLife = 0;
int   playerScore = 0;
bool  quitGame            = false;
bool  playPauseSound      = true;
bool  playMenuSound       = true;
bool  endOfLevelPlaySound = false;
bool  mainMenuDone        = false;
bool  endOfLevelMusicPlay = true;
bool  level1Complete      = false;
bool  level2Complete      = false;
bool  HlaserBoltCollison = false;
bool  VlaserBoltCollison = false;
bool fireShieldCollision = false;
bool fireShieldCollected = false;
bool lightningBoltCollision = false;
bool fireBoltCollision = false;
bool bossGunCollision = false;
bool bouncingFireBoltCollision = false;

int   zombie1MoveCounter[kNumLevel1Zombies]  = { 0,0,0,0 };
float enemyMovementSpeeds[kNumLevel1Zombies] = { 5.0f,15.0f,10.0f,20.0f };

// -------------------------------------------------------------------------------//
// Functions                                                                      //
// -------------------------------------------------------------------------------//

void CreateModel(I3DEngine* myEngine, IMesh* &mesh, IModel* &model, float startXPos, float startYPos, float startZPos, float rotateX, float rotateY, float rotateZ,
	             float scaleX, float scaleY, float scaleZ, string startSkin);

void CreateModelWithMesh(I3DEngine* myEngine, IMesh* &mesh, string meshFileName, IModel* &model, float startXPos, float startYPos, float startZPos,
	                     float rotateX, float rotateY, float rotateZ, string startSkinFileName);

void CreateSound(sf::SoundBuffer &buffer, sf::Sound &sound, string filename, float volume, float pitch, bool loop, sf::Vector3f position);

void SetListener(const float volume, sf::Vector3f position, sf::Vector3f direction, sf::Vector3f setUpVector);

void CreateFont(I3DEngine* myEngine, IFont* &font, string fontType, int size);

void CreateSprite(I3DEngine* myEngine, ISprite* &sprite, string &spriteFileName, float xPos, float yPos, float zPos);

void CreateCamera(I3DEngine* myEngine, ICamera* &camera, float startXPos, float startYPos, float startZPos, float rotateX, float rotateY, float rotateZ);

void DisplayText(string textToDisplay, IFont* font, int xPos, int yPos, const unsigned int colour);

void DisplayFloatAsText(float floatToDisplay, IFont* font, stringstream &stream, int xPos, int yPos, const unsigned int colour);

void DisplayIntAsText(int intToDisplay, IFont* font, stringstream &stream, int xPos, int yPos, const unsigned int colour);

void MoveBackgroundLeft(IModel* &backGround, float speed, const float backgroundLimitPosition, mainScreen &mainScreenMovement);

void MoveBackgroundRight(IModel* &backGround, float speed, const float backgroundLimitPosition, mainScreen &mainScreenMovement);

void NotificationFlash(int &counter, ISprite* &spriteToDisplay);

float DistanceFromPlayer(IModel* player, IModel* object);

float Random(int rangeMin, int rangeMax);

// -------------------------------------------------------------------------------//
// Model Definitions                                                              //
// -------------------------------------------------------------------------------//

// Engine
I3DEngine* myEngine;

//Fonts
IFont*     normalText;            // Output text for info panel
IFont*     keyBarText;            // Number of keys on hotbar text
IFont*    endOfLevelText;
IFont*     bookBarText;           // Number of books on hotbar text
IFont*     clockText;

// Main menu sprites
ISprite*   loading;               // Loading notification

// Main Game Sprites
ISprite*   infoPanel;              // Black info panel for data output
ISprite*   level1introScreen;      // Level 1 intro screen
ISprite*   level2introScreen;	   // Level 2 intro screen
ISprite*   mainBar[11];                // Player hotbar
ISprite*   paused;                 // Paused notification
ISprite*   mainMenuPanel;
ISprite*   soundOptionSelected;
ISprite*   controlsOptionSelected;
ISprite*   saveGameOptionSelected;
ISprite*   quitGameOptionSelected;
ISprite*   soundOptionNotSelected;
ISprite*   controlsOptionNotSelected;
ISprite*   saveGameOptionNotSelected;
ISprite*   quitGameOptionNotSelected;
ISprite*   soundMusicSelected;
ISprite*   soundSFXSelected;
ISprite*   soundBackSelected;
ISprite*   controlsUpSelected;
ISprite*   controlsDownSelected;
ISprite*   controlsLeftSelected;
ISprite*   controlsRightSelected;
ISprite*   controlsFireSelected;

ISprite*   controlsBackSelected;
ISprite*   fireShieldSprite;
ISprite*   gameOverScreen;


ISprite*   exitOpen;           // Exit open notification
ISprite*   levelComplete;      // End of level completed notification

// Meshes
IMesh*     modelMesh;           // Quad mesh
IMesh*     particleMesh;        // Particle Mesh
IMesh*     floorMesh;
IMesh*     flareMesh;

// Title screen models
IModel*    bob;                 // Main image of bob on title screen								
IModel*    menu;                // Main menu model
IModel*    background;          // Cartoony background in main menu


// Level 1 models
IModel*    laserUpDown;         // Gun Laser up down model
IModel*    laserLeftRight;      // Gun Laser gun left right model
IModel*    level1Background;    // Stary background
IModel*    level2Background;
IModel*    level1RotatingBG;
IModel*    level2RotatingBG;
IModel*    levelEndPortal;     // Level 1 portal particle model
IModel*    gunTurret[kNumLevel2Turrets];
IModel*    explosion1;
SParticle  particles[knumFireParticles];


// Level 2 Models
IModel* horizontolLaserBolt[5];
IModel* verticleLaserBolt[1];
IModel* fireBolts[1];
IModel* bouncingFireBolts[kNumBouncingFireBolts];
IModel* lightningBolt[kNumLightningBolts];
IModel* flare;
IModel* fireSheild;
IModel* lightningSheild;
IModel* level2MiniBoss;
IModel* level2MiniBossLaser;
IModel* fireParticlesDummy;

// Cameras
ICamera*   menuCamera;          // Main menu camera
ICamera*   gameCamera;          // Game camera

// -------------------------------------------------------------------------------//
// Set-up Sound Buffers and sounds                                                //
// -------------------------------------------------------------------------------//

// Declare sound buffers and sounds
sf::SoundBuffer mainTitleMusicBuffer;      // Main menu music
sf::Sound       mainTitleMusic;
sf::SoundBuffer menuSelectBuffer;          // Main menu select sound effect
sf::Sound       menuSelect;
sf::SoundBuffer level1MusicBuffer;         // Level 1 music
sf::Sound       level1Music;
sf::SoundBuffer laserShootBuffer;          // Gunfire sound effect
sf::Sound       laserShoot;
sf::SoundBuffer pauseOnBuffer;             // Pause on sound effect
sf::Sound       pauseOn;
sf::SoundBuffer pauseOffBuffer;            // Pause off sound effect
sf::Sound       pauseOff;
sf::SoundBuffer allBooksCollectedBuffer;   // Objective complete sound effect	
sf::Sound       allBooksCollected;
sf::SoundBuffer levelCompleteMusicBuffer;
sf::Sound       levelCompleteMusic;
sf::SoundBuffer particleFireBuffer;
sf::Sound       particleFire;
sf::SoundBuffer lightningShotBuffer;
sf::Sound       lightningShot;
sf::SoundBuffer laserBoltBuffer;
sf::Sound       laserBolt;



// Setup sound and listener positions
sf::Vector3f zeroPosition    (0.0f, 0.0f, 0.0f);
sf::Vector3f listenerPos     (0.0f, 0.0f, 0.0f);
sf::Vector3f listenerForward (0.0f, 0.0f, -1.0f);
sf::Vector3f listenerUp      (0.0f, 1.0f, 0.0f);

// -------------------------------------------------------------------------------//
// TitleScreen Gameloop Functions                                                 //
// -------------------------------------------------------------------------------//

void TitleScreenSetup()
{
	// ***** Load Models *****//

	// Main quad model
	modelMesh = myEngine->LoadMesh("Quad.x");

	// Clouds Background
	CreateModel(myEngine, modelMesh, background, kBackgroundStartX, 0.0f, 0.0f, kBackgroundRotateAmount, 0.0f, 0.0f, 
		        kBackgroundScale, 1.0f, 1.0f, kTitleScreenBackName);

	// Bob
	CreateModel(myEngine, modelMesh, bob, kBobTitleXPos, kBobTitleYPos, 0.0f, kBobTitleRotateAmount, 0.0f, 0.0f, kBobTitleScaleX, 
		        kBobTitleScaleY, 1.0f, "bob1.png");

	// Menu
	CreateModel(myEngine, modelMesh, menu, kMenuXPos, kMenuYPos, kMenuZPos, kMenuRotateAmount, 0.0f, 0.0f, kMenuRotateXScale, 
		        kMenuRotateYScale, 1.0f, kTitleMenuName);

	// Loading
	string loadScreenSprite = "loadingScreen.png";
	CreateSprite(myEngine, loading, loadScreenSprite, kLoadingXPos, kLoadingYPos, OFFSCREEN);

	// ***** Load Camera *****//
	CreateCamera(myEngine, menuCamera, 0.0f, kMenuCameraYPos, 0.0f, kMenuCameraRotateAmount, 0.0f, 0.0f);

	// ***** Load Music *****//
	CreateSound(mainTitleMusicBuffer, mainTitleMusic, "mainTitleMusic.wav", 100.0f, 1.0f, false, zeroPosition); 	// Main title music

	// ***** Load Sound Effects *****//
	CreateSound(menuSelectBuffer, menuSelect, "menuSelect.wav", 100.0f, 1.0f, false, zeroPosition); 	// Menu select sounds

	// Set the properties of the listener
	SetListener(kGlobalVolume, listenerPos, listenerForward, listenerUp);

	// Start the music playing 
	mainTitleMusic.play();

} // End of title screen setup function

void TitleScreenUpdate() 	// ***** Title screen Moving Background *****//
{
	backgroundMovement = kSecond * myEngine->Timer(); // Set movement speed

	switch (mainScreenMovement) // Which way it is moving?
	{
	case MOVELEFT:
	{
		MoveBackgroundLeft(background, backgroundMovement, kBackgroudLimitPos, mainScreenMovement);
		break;
	}
	case MOVERIGHT:
	{
		MoveBackgroundRight(background, backgroundMovement, kBackgroudResetPos, mainScreenMovement);
		break;
	}
	} // End of switch statment

	switch (menuChoice) 	// ***** Main Menu selection choice *****//
	{
	case START:
	{
		menu->SetSkin(kMenuScreenName1); // Starts with Play Game selected
		if (myEngine->KeyHit(kUpKey)) 
		{
			menuSelect.play();
			menuChoice = QUIT;
		}
		if (myEngine->KeyHit(kDownKey)) 
		{
			menuSelect.play();
			menuChoice = LOADGAME;
		}
		if (myEngine->KeyHit(Key_Return))
		{
			menuChoice = LOADING;
		}
		break;
	}
	case LOADGAME:
	{
		menu->SetSkin(kMenuScreenName2);
		if (myEngine->KeyHit(kUpKey))
		{
			menuSelect.play();
			menuChoice = START;
		}
		if (myEngine->KeyHit(kDownKey))
		{
			menuSelect.play();
			menuChoice = SCORES;
		}
		break;
	}
	case SCORES:
	{
		menu->SetSkin(kMenuScreenName3);
		if (myEngine->KeyHit(kUpKey))
		{
			menuSelect.play();
			menuChoice = LOADGAME;
		}
		if (myEngine->KeyHit(kDownKey))
		{
			menuSelect.play();
			menuChoice = OPTIONS;
		}
		break;
	}
	case OPTIONS:
	{
		menu->SetSkin(kMenuScreenName4);
		if (myEngine->KeyHit(kUpKey))
		{
			menuSelect.play();
			menuChoice = SCORES;
		}
		if (myEngine->KeyHit(kDownKey))
		{
			menuSelect.play();
			menuChoice = QUIT;
		}
		break;
	}
	case QUIT:
	{
		menu->SetSkin(kMenuScreenName5);
		if (myEngine->KeyHit(kUpKey))
		{
			menuSelect.play();
			menuChoice = OPTIONS;
		}
		else if (myEngine->KeyHit(kDownKey))
		{
			menuSelect.play();
			menuChoice = START;
		}

		if (myEngine->KeyHit(kSelectKey))
		{
			mainMenuDone = true;
			quitGame     = true;
		}

		break;
	}
	case LOADING:
	{
		menu->SetY(kMenuOffScreenPos);
		bob->SetY(kBobOffScreenPos);
		loading->SetZ(DISPLAYEDTOP);
		loadCounter++;

		if (loadCounter > 1)
		{
			if (titleMusicCounter > 1.0f)
			{
				titleMusicCounter = titleMusicCounter - 0.005f;
				mainTitleMusic.setVolume(titleMusicCounter);
			}
			else
			{
				mainMenuDone = true;
			}
		}
		break;
	}
	} // End of switch statment


} // End of TitleScreenUpdate function

void TitleScreenShutdown()
{
	// Remove all models from the game world
	myEngine->RemoveCamera(menuCamera);
	modelMesh->RemoveModel(menu);
	modelMesh->RemoveModel(bob);
	modelMesh->RemoveModel(background);
	myEngine->RemoveMesh(modelMesh);
	myEngine->RemoveSprite(loading);
	mainTitleMusic.stop();

} // End of titlescreen shutdown function

// -------------------------------------------------------------------------------//
// Level 1 Gameloop Functions                                                     //
// -------------------------------------------------------------------------------//

void LevelOneSetup()
{
	frameTime = myEngine->Timer(); // Call the Timer again and store it in a variable

	// ***** Load Models ***** //

	// Wall Cubes
	level1Walls = new CWalls();
	level1Walls->CreateLevel1Walls(ModelCreator->cubeMesh, ModelCreator->level1walls);

	// Keys
	level1Keys = new CKey();
	level1Keys->CreateLevel1Keys(ModelCreator->spriteMesh, ModelCreator->level1keyPosition);

	// Doors
	level1Doors = new CDoor();
	level1Doors->CreateLevel1Doors(ModelCreator->spriteMesh, ModelCreator->level1DoorPosition);

	// Books
	level1Books = new CBook();
	level1Books->CreateLevel1Books(ModelCreator->spriteMesh, ModelCreator->level1BookoPosition);

	// Player character
	player = new CPlayer();
	player->GetMyEngine(myEngine);
	player->CreateModel(ModelCreator->spriteMesh);

	// Explosion
	//CreateModelWithMesh(myEngine, particleMesh, "particle.x", explosion1, 85.0f, 10.0f, 85.0f, 90.0f, 0.0f, 0.0f, "explosion0.tga");

	// Bullets
	bullets = new CBullet(myEngine);
	bullets->CreateModel(ModelCreator->spriteMesh, player->GetModel(), ModelCreator->level1BulletDetails);

	// Enemies
	for (int i = 0; i < kNumLevel1Zombies; i++) // Place zombies in the world
	{
		level1Zombies[i] = new CZombie(frameTime);
		level1Zombies[i]->GetMyEngine(myEngine);
		level1Zombies[i]->CreateLevel1ZombieModel(ModelCreator->spriteMesh, ModelCreator->enemyPositions[i].xPos, ModelCreator->enemyPositions[i].yPos,
			ModelCreator->enemyPositions[i].zPos, i, ModelCreator->enemyStartSkins[i],
			ModelCreator->dummyWayPointsCooridnates);
	}

	// End portal
	CreateModelWithMesh(myEngine, particleMesh, "particle.x", levelEndPortal, 84.5f, 10.5f, 145.0f, 270.0f, 0.0f, 0.0f, "portal1TGA.tga");

	// Stone Background
	CreateModel(myEngine, ModelCreator->spriteMesh, level1Background, 85.0f, 10.0f, 85.0f, 270.0f, 0.0f, 0.0f, 15.0f, 15.0f, 1.0f, "stoneFloorLevel1.png");

	// Rotating star background
	CreateModelWithMesh(myEngine, floorMesh, "Floor.x", level1RotatingBG, 85.0f, 0.0f, 85.0f, 0.0f, 0.0f, 0.0f, "starBackground.jpg");

	
	// ***** Load Fonts *****//

	CreateFont(myEngine, normalText,     "Arial Bold", 20);
	CreateFont(myEngine, keyBarText,     "Arial",      70);
	CreateFont(myEngine, endOfLevelText, "Arial Bold", 150);

	CreateFont(myEngine, bookBarText,    "Arial",      60);
	CreateFont(myEngine, clockText,      "Arial Bold", 30);

	// ***** Load Sprites *****//

	// Level One Intro Screen
	string Level1TipsSprite = "Level1Tips.png";
	CreateSprite(myEngine, level1introScreen, Level1TipsSprite, 60, 25, OFFSCREEN);

	// *** These next panels are loaded but hidden off screen untill return is pressed ***//

	// Game bottom Hotbar
	string healthSystemLayersMain[] = { "mainHotBar0.png","mainHotBar1.png" ,"mainHotBar2.png" ,"mainHotBar3.png" ,"mainHotBar4.png" ,"mainHotBar5.png" ,"mainHotBar6.png" ,
	   "mainHotBar7.png" ,"mainHotBar8.png" ,"mainHotBar9.png" ,"mainHotBar10.png" };
	for (int i = 0; i < 11; i++)
	{
		CreateSprite(myEngine, mainBar[i], healthSystemLayersMain[i], 310, 920, OFFSCREEN);//y=920
	}
	// Paused Panel
	string pausedSprite = "paused.png";
	CreateSprite(myEngine, paused, pausedSprite, 660, 402, OFFSCREEN);

	// Escape key Menu Panels
	string mainMenuPanelSprite = "inGameMainMenu.png";
	CreateSprite(myEngine, mainMenuPanel, mainMenuPanelSprite,            641,   159, OFFSCREEN);
	string soundOptionsSprite = "soundOptionSelected.png";
	CreateSprite(myEngine, soundOptionSelected, soundOptionsSprite,       767,   500, OFFSCREEN);
	string controlOpsitonsSprite = "controlsOptionSelected.png";
	CreateSprite(myEngine, controlsOptionSelected, controlOpsitonsSprite,    823.5, 580, OFFSCREEN);
	string saveGameSpriteSelected = "saveGameOptionSelected.png";
	CreateSprite(myEngine, saveGameOptionSelected, saveGameSpriteSelected,    807,   660, OFFSCREEN);
	string quitGameOptionSprite = "quitGameOptionSelected.png";
	CreateSprite(myEngine, quitGameOptionSelected, quitGameOptionSprite,    884.5, 740, OFFSCREEN);
	string soundOptionsNonSprite = "soundOptionNotSelected.png";
	CreateSprite(myEngine, soundOptionNotSelected, soundOptionsNonSprite,    767,   500, OFFSCREEN);
	string controlsOptionsNonSprite = "controlsOptionNotSelected.png";
	CreateSprite(myEngine, controlsOptionNotSelected, controlsOptionsNonSprite, 823.5, 580, OFFSCREEN);
	string saveGaemOptionNonSprite = "saveGameOptionNotSelected.png";
	CreateSprite(myEngine, saveGameOptionNotSelected, saveGaemOptionNonSprite, 807,   660, OFFSCREEN);
	string quitGameNonSprite = "quitGameOptionNotSelected.png";
	CreateSprite(myEngine, quitGameOptionNotSelected, quitGameNonSprite, 884.5, 740, OFFSCREEN);
	string soundMusicSprite = "soundOptionsMusic.png";
	CreateSprite(myEngine, soundMusicSelected, soundMusicSprite,         460,   159, OFFSCREEN);
	string soundSFXSprite = "soundOptionsSFX.png";
	CreateSprite(myEngine, soundSFXSelected, soundSFXSprite,           460,   159, OFFSCREEN);
	string soundBackSprite = "soundOptionsBack.png";
	CreateSprite(myEngine, soundBackSelected, soundBackSprite,          460,   159, OFFSCREEN);
	string controlsUpSprite = "controlsOptionsUp.png";
	CreateSprite(myEngine, controlsUpSelected, controlsUpSprite,         546.5,  42, OFFSCREEN);
	string controlsDownSprite = "controlsOptionsDown.png";
	CreateSprite(myEngine, controlsDownSelected, controlsDownSprite,       546.5,  42, OFFSCREEN);
	string controlsLeftSprite = "controlsOptionsLeft.png";
	CreateSprite(myEngine, controlsLeftSelected, controlsLeftSprite,       546.5,  42, OFFSCREEN);
	string controlsRightSprite = "controlsOptionsRight.png";
	CreateSprite(myEngine, controlsRightSelected, controlsRightSprite,      546.5,  42, OFFSCREEN);
	string controlsFireSprite = "controlsOptionsFire.png";
	CreateSprite(myEngine, controlsFireSelected, controlsFireSprite,       546.5,  42, OFFSCREEN);
	string controlBackSprite = "controlsOptionsBack.png";
	CreateSprite(myEngine, controlsBackSelected, controlBackSprite,       546.5,  42, OFFSCREEN);
	string fireShieldSprite2 = "fireShield2.png";
	CreateSprite(myEngine, fireShieldSprite, fireShieldSprite2, 1535, 1000, OFFSCREEN);
	string gameOverString = "gameOver.png";
	CreateSprite(myEngine, gameOverScreen, gameOverString, 460, 205, OFFSCREEN);




	// Exit Open Panel
	string exitOpenSprite = "exitOpen.png";
	CreateSprite(myEngine, exitOpen, exitOpenSprite, 760, 780, OFFSCREEN);

	// Level complete and Score window
	string levelCompleteSprite = "levelComplete.png";
	CreateSprite(myEngine, levelComplete, levelCompleteSprite, 210, 118, OFFSCREEN);
	   	 
	// Black Info panel (used for debugging information)
	string infoPanelSprite = "infoPanel.png";
	CreateSprite(myEngine, infoPanel, infoPanelSprite, 1607, 867, OFFSCREEN);

	// ***** Load Camera *****//
	CreateCamera(myEngine, gameCamera, 0.0f, 0.0f, 80.0f, 180.0f, 0.0f, 0.0f);
	gameCamera->AttachToParent(player->GetModel());
	gameCamera->SetMovementSpeed(60.0f);
	gameCamera->SetRotationSpeed(30.0f);

	// ***** Load Music *****//
	CreateSound(level1MusicBuffer, level1Music, "level1Music.wav", 50.0f, 1.0f, true, zeroPosition);
	level1Music.play();

	// ***** Load Sound Effects *****//

	// Laser Gun
	CreateSound(laserShootBuffer, laserShoot, "laserGunShoot.wav", 50.0f, 1.0f, false, zeroPosition);

	// Pause on
	CreateSound(pauseOnBuffer, pauseOn, "pauseOn.wav", 80.0f, 1.0f, false, zeroPosition);

	// Pause off
	CreateSound(pauseOffBuffer, pauseOff, "pauseOff.wav", 80.0f, 1.0f, false, zeroPosition);

	// All keys collected sound
	CreateSound(allBooksCollectedBuffer, allBooksCollected, "allBooksCollected.wav", 100.0f, 1.0f, false, zeroPosition);

	// End of level jingle
	CreateSound(levelCompleteMusicBuffer, levelCompleteMusic, "levelComplete.wav", 100.0f, 1.0f, false, zeroPosition);


} // End of level one setup function

void LevelOneUpdate()
{
	switch (level1State)
	{
	case INTROSCREEN: // ***** Level 1 tips screen *****//
	{
		frameTime = myEngine->Timer(); // Call the Timer again and store it in a variable

		level1introScreen->SetZ(DISPLAYEDTOP);

		// Wait for Return key press
		if (myEngine->KeyHit(kSelectKey)) level1State = GAMEACTIVE;

		break;

	} // End of INTROSCREEN option

	case GAMEACTIVE: // ***** Level 1 Gameplay Mode *****//
	{
		// ***** Set-up game timer *****//
		frameTime = myEngine->Timer(); // Call the Timer again and store it in a variable
		fps = kSecond / frameTime;     // Calculate the Frames per second

		// Hide UI elements
		level1introScreen->SetZ(OFFSCREEN); // Hide intro screen
		infoPanel->SetZ(DISPLAYEDBOTTOM); // Display info panel
		mainMenuPanel->SetZ(OFFSCREEN);
		paused->SetZ(OFFSCREEN);

		// ***** Game Timer/Stopwatch *****//

		// start the timer
		level1seconds = ((level1seconds + frameTime) / 1.0f);

		// Increase each minute and reset seconds counter
		if (level1seconds > 60.0f)
		{
			level1seconds = 0.0f;
			level1minutes++;
		}

		// ***** Stary Background *****//
		level1RotatingBG->RotateY(5.0f * frameTime); // Rotate the background


		// ***** Player Movement *****//

		// Get position of player character
		oldXPos = player->GetModel()->GetX();
		oldZPos = player->GetModel()->GetZ();

		// Check for player Movement
		player->GetFrameTime(frameTime);
		player->PlayerMovement(playerMoveCounter);

		// Lazer/Bullets
		bullets->Update(player->bobDirection, player->GetModel(), frameTime);

		// Player Death
		if (healthCounterLvl1 == 0)
		{
			level1State = GAMEOVER;
		}


		// ***** Enemy Movement *****//

		for (int i = 0; i < kNumLevel1Zombies; i++)
		{
			if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11 && !level1Zombies[i]->detectCollision)mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
			level1Zombies[i]->GenerateModelCoordinates(i);
			level1Zombies[i]->EnemyMovement(zombie1MoveCounter, ModelCreator->enemySkinsRight,
				ModelCreator->enemySkinsLeft, i, enemyMovementSpeeds[i],player);
			level1Zombies[i]->FollowPlayer(player, oldXPos, oldZPos,i);
			if (level1Zombies[i]->detectCollision)
			{
				level1Zombies[i]->detectCollision = false;
				if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11)
				{
					mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
					healthCounterLvl1--;
				}
				
			}
			
		}
		
		// ***** Collision detection ***** //

		collisionDetector = new Collision;
		level1Walls->level1WallCollision(player, oldXPos, oldZPos, ModelCreator->level1walls); // Walls
		level1Doors->Level1DoorCollision(player, oldXPos, oldZPos,ModelCreator->level1DoorPosition, playerScore);                            // Doors
		level1Keys->Level1KeyCollision(player,   oldXPos, oldZPos, playerScore);                            // Keys


		level1Books->Level1BookCollision(player, oldXPos, oldZPos, playerScore);		                       // Books

		for (int i = 0; i < kNumLevel1Zombies; i++)   // Enemy Collision With Player
		{
			level1Zombies[i]->enemyCollision(player, bullets, oldXPos, oldZPos, ModelCreator->level1walls, ModelCreator->level1DoorPosition, i);
		}

		// Bullet collision with walls
		bullets->level1WallCollision(ModelCreator->level1walls, player);
		bullets->level1DoorCollision(ModelCreator->level1DoorPosition, player);

		// ***** Player Score ***** //
		for (int i = 0; i < kNumLevel1Zombies; i++)
		{
			if (level1Zombies[i]->GetZombieState() == DEAD)
			{
				if (!level1Zombies[i]->GetScoreCalcualted())
				{
					playerScore += 100;
					level1Zombies[i]->SetScoreCalcualted(true);
				}
			}
		}



		// ***** End portal animation ***** //

		portalCounter++;

		for (int i = 0; i < kNumPortalSkinNames; i++) 
		{
			if (portalCounter == portalCounterValues[i]) levelEndPortal->SetSkin(portalSkinNames[i]);
			if (portalCounter == 151) portalCounter = 49;

		} // End of for loop

		// ***** Text output to screen ***** //

		stringstream frameTimeText, fpsText, minutesText, scoreText, secsText, numRedKeysText, numBlueKeysText, numGreenKeysText, numYellowKeysText,
			         numBooksText, totalBooksText, playerScoreText;
		
		// Bottom Right Info Panel 

		// FrameTime
		DisplayText("FrameTime: ", normalText, 1630, 890, kBlack);
		DisplayFloatAsText(frameTime, normalText, frameTimeText, 1800, 890, kBlack);

		// FPS
		DisplayText("FPS: ", normalText, 1630, 910, kBlack);
		DisplayFloatAsText(fps, normalText, fpsText, 1800, 910, kBlack);

		// Player Score
		DisplayText("Score: ", normalText, 1630, 930, kBlack);
	    DisplayFloatAsText(playerScore, normalText, playerScoreText, 1800, 930, kBlack);





		// Player hotbar

		// Output Number of Red Keys on hotbar
		DisplayIntAsText(player->GetNumLevel1RedKeys(), keyBarText, numRedKeysText, 1080, 1020, kRed);

		// Output Number of Blue Keys on hotbar
		DisplayIntAsText(player->GetNumLevel1BlueKeys(), keyBarText, numBlueKeysText, 1210, 1020, kBlue);

		// Output Number of green Keys on hotbar
		DisplayIntAsText(player->GetNumLevel1GreenKeys(), keyBarText, numGreenKeysText, 1340, 1020, kGreen);

		// Output Number of yellow Keys on hotbar
		DisplayIntAsText(player->GetNumLevel1YellowKeys(), keyBarText, numYellowKeysText, 1465, 1020, kYellow);

		// Output Number of Books on hotbar
		if (player->GetNumLevel1Books() < 10) DisplayIntAsText(player->GetNumLevel1Books(), bookBarText, numBooksText, 880, 1020, kWhite);
		else DisplayIntAsText(player->GetNumLevel1Books(), bookBarText, numBooksText, 855, 1020, kWhite);
		DisplayText("/", bookBarText, 920, 1020, kWhite);
		DisplayIntAsText(kNumLevel1Books, bookBarText, totalBooksText, 935, 1020, kWhite);

		// Timer/Clock
		DisplayIntAsText(level1minutes, clockText, minutesText, 492, 1001, kWhite);
		DisplayText(":", clockText, 510, 1000, kWhite);
		DisplayIntAsText(int(level1seconds), clockText, secsText, 520, 1001, kWhite);

		// Score
		DisplayIntAsText(playerScore, clockText, scoreText, 710, 1001, kWhite);




		// *************************************************************************************************************//
		// ***** THIS SECTION SHOWS HOW EXPLOSION ANIMATIONS WILL WORK SO THAT YOU CAN PUT THEM IN WHEN COLLISION ***** //
		// *****                             DETECTION IS WORKING CORRECTLY                                       ***** //        

		/*++explosionCounter;
		if (explosionCounter % 40 == 0)
		{
			int skinNo = (explosionCounter / 4) / 10; // Calculates the correct skin to use
			if (skinNo == 57) explosionCounter = 0, skinNo = 0; // Resets on last image
			stringstream ss;
			ss << "explosion";
			ss << skinNo;
			ss << ".tga";
			string tmp;
			ss >> tmp;
			explosion1->SetSkin(tmp);
		}*/

		// *************************************************************************************************************//


		// ***** End of level actions ***** //

		if (player->GetNumLevel1Books() == 17) // Has the player collected all 17 books?
		{
			if (!endOfLevelPlaySound) allBooksCollected.play(); // Play level complete sound
			endOfLevelPlaySound = true; // This is put into a boolean to stop the sound from repeating in the game loop

			// All books collection notification flash
			endOfLevelCounter++;
			NotificationFlash(endOfLevelCounter, exitOpen);

			// Remove exit block
			level1Walls->GetLevel1ExitCube()->SetX(-200.0f);
			ModelCreator->level1walls[kNumLevel1Walls - 1].xPos = -200.0f;

			// Check for collision with the exit portal
			Collision* portalCollison = new Collision;

			if (portalCollison->point2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 
				                          levelEndPortal->GetX(), levelEndPortal->GetZ(), 2.0f, 2.0f))
			{
				level1State = LEVELCOMPLETE;
			}



		} // End of if statment

		// ***** Check for in-game key presses ***** //


		// ******* Debug Key to complete level instantly ******* //
		if (myEngine->KeyHit(Key_L)) level1State = LEVELCOMPLETE;
		//*******************************************************//

		// Check for paused keypress
		if (myEngine->KeyHit(kPauseKey)) level1State = PAUSED;

		// Check for escape keypress
		if (myEngine->KeyHit(kMenuKey)) level1State = MAINMENU;

		break;

	} // End of GAMEACTIVE option

	case PAUSED: // ***** Level 1 Paused Screen *****//
	{
		level1Music.pause();
		if (playPauseSound)
		{
			pauseOn.play();
			playPauseSound = false;
		}

		paused->SetZ(DISPLAYEDTOP);

		if (myEngine->KeyHit(kPauseKey))
		{
			level1Music.play();
			level1State = GAMEACTIVE;
			if (!playPauseSound)
			{
				pauseOff.play();
				playPauseSound = true;
			}
		}
		frameTime = myEngine->Timer(); // Call the Timer again and store it in a variable
		break;
	
	} // End of PAUSED option

	case MAINMENU: 	// ***** Level 1 Main Menu Display *****//
	{
		level1Music.pause(); // Pause music

		// This next action is in an if statment with a bool to stop it from repeating in the game loop
		if (playPauseSound) 
		{
			pauseOn.play(); // Play pause notification sound
			playPauseSound = false;
		}

		mainMenuPanel->SetZ(DISPLAYEDBOTTOM);


		switch (level1Menu)
		{
		case SOUNDMAIN:
		{
			// Show and hide relevent menu option
			soundOptionSelected->SetZ(DISPLAYEDTOP);
			controlsOptionSelected->SetZ(OFFSCREEN);
			saveGameOptionSelected->SetZ(OFFSCREEN);
			quitGameOptionSelected->SetZ(OFFSCREEN);
			soundOptionNotSelected->SetZ(OFFSCREEN);
			controlsOptionNotSelected->SetZ(DISPLAYEDTOP);
			saveGameOptionNotSelected->SetZ(DISPLAYEDTOP);
			quitGameOptionNotSelected->SetZ(DISPLAYEDTOP);
			soundMusicSelected->SetZ(OFFSCREEN);
			soundSFXSelected->SetZ(OFFSCREEN);
			soundBackSelected->SetZ(OFFSCREEN);


			// Check for key input and change state
			if (myEngine->KeyHit(kUpKey)     || myEngine->KeyHit(Key_Up))   level1Menu = QUITGAMEMAIN;
			if (myEngine->KeyHit(kDownKey)   || myEngine->KeyHit(Key_Down)) level1Menu = CONTROLSMAIN;
			if (myEngine->KeyHit(kSelectKey))                               level1Menu = SOUNDMUSIC;
			// Play sound


			break;
		}
		case SOUNDMUSIC:
		{
			mainMenuPanel->SetZ(OFFSCREEN);
			soundOptionSelected->SetZ(OFFSCREEN);
			controlsOptionSelected->SetZ(OFFSCREEN);
			saveGameOptionSelected->SetZ(OFFSCREEN);
			quitGameOptionSelected->SetZ(OFFSCREEN);
			soundOptionNotSelected->SetZ(OFFSCREEN);
			controlsOptionNotSelected->SetZ(OFFSCREEN);
			saveGameOptionNotSelected->SetZ(OFFSCREEN);
			quitGameOptionNotSelected->SetZ(OFFSCREEN);

			soundMusicSelected->SetZ(DISPLAYEDTOP);
			soundSFXSelected->SetZ(OFFSCREEN);
			soundBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = SOUNDBACK;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = SOUNDSFX;
			if (myEngine->KeyHit(kSelectKey))                                {};

			break;
		}
		case SOUNDSFX:
		{
			soundMusicSelected->SetZ(OFFSCREEN);
			soundSFXSelected->SetZ(DISPLAYEDTOP);
			soundBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey) || myEngine->KeyHit(Key_Up))       level1Menu = SOUNDMUSIC;
			if (myEngine->KeyHit(kDownKey)   || myEngine->KeyHit(Key_Down)) level1Menu = SOUNDBACK;
			if (myEngine->KeyHit(kSelectKey))                               {};

			break;
		}
		case SOUNDBACK:
		{
			soundMusicSelected->SetZ(OFFSCREEN);
			soundSFXSelected->SetZ(OFFSCREEN);
			soundBackSelected->SetZ(DISPLAYEDTOP);
			if (myEngine->KeyHit(kUpKey)     || myEngine->KeyHit(Key_Up))   level1Menu = SOUNDSFX;
			if (myEngine->KeyHit(kDownKey)   || myEngine->KeyHit(Key_Down)) level1Menu = SOUNDMUSIC;
			if (myEngine->KeyHit(kSelectKey))                               level1Menu = SOUNDMAIN;


			break;
		}

		case CONTROLSMAIN:
		{
			if (!playMenuSound)
			{
				menuSelect.play();
				playMenuSound = true;
			}

			soundOptionSelected->SetZ(OFFSCREEN);
			controlsOptionSelected->SetZ(DISPLAYEDTOP);
			saveGameOptionSelected->SetZ(OFFSCREEN);
			quitGameOptionSelected->SetZ(OFFSCREEN);

			soundOptionNotSelected->SetZ(DISPLAYEDTOP);
			controlsOptionNotSelected->SetZ(OFFSCREEN);
			saveGameOptionNotSelected->SetZ(DISPLAYEDTOP);
			quitGameOptionNotSelected->SetZ(DISPLAYEDTOP);
			controlsBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = SOUNDMAIN;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = SAVEGAMEMAIN;
			if (myEngine->KeyHit(kSelectKey))                                level1Menu = CONTROLSUP;
			break;
		}
		case CONTROLSUP:
		{
			controlsOptionSelected->SetZ(OFFSCREEN);
			soundOptionSelected->SetZ(OFFSCREEN);
			controlsOptionSelected->SetZ(OFFSCREEN);
			saveGameOptionSelected->SetZ(OFFSCREEN);
			quitGameOptionSelected->SetZ(OFFSCREEN);
			soundOptionNotSelected->SetZ(OFFSCREEN);
			controlsOptionNotSelected->SetZ(OFFSCREEN);
			saveGameOptionNotSelected->SetZ(OFFSCREEN);
			quitGameOptionNotSelected->SetZ(OFFSCREEN);
			controlsUpSelected->SetZ(DISPLAYEDTOP);
			controlsDownSelected->SetZ(OFFSCREEN);
			controlsLeftSelected->SetZ(OFFSCREEN);
			controlsRightSelected->SetZ(OFFSCREEN);
			controlsFireSelected->SetZ(OFFSCREEN);
			controlsBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = CONTROLSBACK;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = CONTROLSDOWN;
			if (myEngine->KeyHit(kSelectKey))                                {};
			break;
		}
		case CONTROLSDOWN:
		{
			controlsUpSelected->SetZ(OFFSCREEN);
			controlsDownSelected->SetZ(DISPLAYEDTOP);
			controlsLeftSelected->SetZ(OFFSCREEN);
			controlsRightSelected->SetZ(OFFSCREEN);
			controlsFireSelected->SetZ(OFFSCREEN);
			controlsBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = CONTROLSUP;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = CONTROLSLEFT;
			if (myEngine->KeyHit(kSelectKey))                                {};
			break;

		}
		case CONTROLSLEFT:
		{
			controlsUpSelected->SetZ(OFFSCREEN);
			controlsDownSelected->SetZ(OFFSCREEN);
			controlsLeftSelected->SetZ(DISPLAYEDTOP);
			controlsRightSelected->SetZ(OFFSCREEN);
			controlsFireSelected->SetZ(OFFSCREEN);
			controlsBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = CONTROLSDOWN;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = CONTROLSRIGHT;
			if (myEngine->KeyHit(kSelectKey))                                {};
			break;
		}
		case CONTROLSRIGHT:
		{
			controlsUpSelected->SetZ(OFFSCREEN);
			controlsDownSelected->SetZ(OFFSCREEN);
			controlsLeftSelected->SetZ(OFFSCREEN);
			controlsRightSelected->SetZ(DISPLAYEDTOP);
			controlsFireSelected->SetZ(OFFSCREEN);
			controlsBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = CONTROLSLEFT;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = CONTROLSFIRE;
			if (myEngine->KeyHit(kSelectKey))                                {};
			break;

		}
		case CONTROLSFIRE:
		{
			controlsUpSelected->SetZ(OFFSCREEN);
			controlsDownSelected->SetZ(OFFSCREEN);
			controlsLeftSelected->SetZ(OFFSCREEN);
			controlsRightSelected->SetZ(OFFSCREEN);
			controlsFireSelected->SetZ(DISPLAYEDTOP);
			controlsBackSelected->SetZ(OFFSCREEN);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = CONTROLSRIGHT;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = CONTROLSBACK;
			if (myEngine->KeyHit(kSelectKey)) {};
			break;
		}
		case CONTROLSBACK:
		{
			controlsUpSelected->SetZ(OFFSCREEN);
			controlsDownSelected->SetZ(OFFSCREEN);
			controlsLeftSelected->SetZ(OFFSCREEN);
			controlsRightSelected->SetZ(OFFSCREEN);
			controlsFireSelected->SetZ(OFFSCREEN);
			controlsBackSelected->SetZ(DISPLAYEDTOP);

			if (myEngine->KeyHit(kUpKey)      || myEngine->KeyHit(Key_Up))   level1Menu = CONTROLSFIRE;
			if (myEngine->KeyHit(kDownKey)    || myEngine->KeyHit(Key_Down)) level1Menu = CONTROLSUP;
			if (myEngine->KeyHit(kSelectKey))                                level1Menu = CONTROLSMAIN;
			break;

		}
		case SAVEGAMEMAIN:
		{
			soundOptionSelected->SetZ(OFFSCREEN);
			controlsOptionSelected->SetZ(OFFSCREEN);
			saveGameOptionSelected->SetZ(DISPLAYEDTOP);
			quitGameOptionSelected->SetZ(OFFSCREEN);

			soundOptionNotSelected->SetZ(DISPLAYEDTOP);
			controlsOptionNotSelected->SetZ(DISPLAYEDTOP);
			saveGameOptionNotSelected->SetZ(OFFSCREEN);
			quitGameOptionNotSelected->SetZ(DISPLAYEDTOP);
			if (myEngine->KeyHit(kUpKey) || myEngine->KeyHit(Key_Up))
			{
				level1Menu = CONTROLSMAIN;
			}
			if (myEngine->KeyHit(kDownKey) || myEngine->KeyHit(Key_Down))
			{
				level1Menu = QUITGAMEMAIN;
			}
			break;
		}
		case QUITGAMEMAIN:
		{
			soundOptionSelected->SetZ(OFFSCREEN);
			controlsOptionSelected->SetZ(OFFSCREEN);
			saveGameOptionSelected->SetZ(OFFSCREEN);
			quitGameOptionSelected->SetZ(DISPLAYEDTOP);

			soundOptionNotSelected->SetZ(DISPLAYEDTOP);
			controlsOptionNotSelected->SetZ(DISPLAYEDTOP);
			saveGameOptionNotSelected->SetZ(DISPLAYEDTOP);
			quitGameOptionNotSelected->SetZ(OFFSCREEN);
			if (myEngine->KeyHit(kUpKey) || myEngine->KeyHit(Key_Up))
			{
				level1Menu = SAVEGAMEMAIN;
			}
			if (myEngine->KeyHit(kDownKey) || myEngine->KeyHit(Key_Down))
			{
				level1Menu = SOUNDMAIN;
			}
			if (myEngine->KeyHit(kSelectKey))
			{
				quitGame = true;
			}
			break;
		
		}
		}

		if (myEngine->KeyHit(kMenuKey))
		{
			if (!playPauseSound)
			{
				pauseOff.play();
				playPauseSound = true;
			}
			level1Music.play();

			soundOptionSelected->SetZ(OFFSCREEN);
			controlsOptionSelected->SetZ(OFFSCREEN);
			saveGameOptionSelected->SetZ(OFFSCREEN);
			quitGameOptionSelected->SetZ(OFFSCREEN);
			soundOptionNotSelected->SetZ(OFFSCREEN);
			controlsOptionNotSelected->SetZ(OFFSCREEN);
			saveGameOptionNotSelected->SetZ(OFFSCREEN);
			quitGameOptionNotSelected->SetZ(OFFSCREEN);
			soundMusicSelected->SetZ(OFFSCREEN);
			soundSFXSelected->SetZ(OFFSCREEN);
			soundBackSelected->SetZ(OFFSCREEN);
			controlsUpSelected->SetZ(OFFSCREEN);
			controlsDownSelected->SetZ(OFFSCREEN);
			controlsLeftSelected->SetZ(OFFSCREEN);
			controlsRightSelected->SetZ(OFFSCREEN);
			controlsFireSelected->SetZ(OFFSCREEN);
			controlsBackSelected->SetZ(OFFSCREEN);


			frameTime = myEngine->Timer();
			level1State = GAMEACTIVE;
		}
		break;

	} // End of MAINMENU option

	case LEVELCOMPLETE: // ***** Level 1 Complete actions *****//
	{
		level1Music.stop();



		if (endOfLevelMusicPlay)
		{
			levelCompleteMusic.play();
			endOfLevelMusicPlay = false;
		}

		exitOpen->SetZ(OFFSCREEN);
		levelComplete->SetZ(DISPLAYEDTOP);

		stringstream lv1minsastext, lv1secsastext, playerScoreStreamText;
		DisplayIntAsText(level1minutes, endOfLevelText, lv1minsastext, 1320, 460, kWhite);
		DisplayText(":", endOfLevelText, 1385, 455, kWhite);
		DisplayIntAsText(level1seconds, endOfLevelText, lv1secsastext, 1425, 460, kWhite);

		DisplayIntAsText(playerScore, endOfLevelText, playerScoreStreamText, 1320, 660, kWhite);


		if (myEngine->KeyHit(kSelectKey))
		{
			levelCompleteMusic.stop();

			level1Complete = true;
		}
	
		break;
	}
	case GAMEOVER:
	{
		deathCounter++;

		if      (deathCounter == 100)  player->GetModel()->SetSkin("die1.png");
		else if (deathCounter == 200)  player->GetModel()->SetSkin("die2.png");
		else if (deathCounter == 300)  player->GetModel()->SetSkin("die3.png");
		else if (deathCounter == 400)  player->GetModel()->SetSkin("die4.png");
		else if (deathCounter == 500) player->GetModel()->SetSkin("die5.png");
		else if (deathCounter == 600) player->GetModel()->SetSkin("die6.png");
		else if (deathCounter > 1500)
		{
			gameOverScreen->SetZ(DISPLAYEDTOP);

		}
		
		if (myEngine->KeyHit(kSelectKey)) myEngine->Stop();

		break;
	}


	} // End of switch statment

} // End of level one Update function

void LevelOneShutdown()
{
	levelComplete->SetZ(OFFSCREEN);

	level1Walls->RemoveLevel1Walls(ModelCreator->cubeMesh);
	level1Keys->RemoveLevel1Keys(ModelCreator->spriteMesh);
	level1Doors->RemoveLevel1Doors(ModelCreator->spriteMesh);
	level1Books->RemoveLevel1Books(ModelCreator->spriteMesh);

	ModelCreator->spriteMesh->RemoveModel(level1Background);

	floorMesh->RemoveModel(level1RotatingBG);

	for (int i = 0; i < kNumLevel1Zombies; i++) // Place zombies in the world
	{
		level1Zombies[i]->GetModel()->SetX(-100.0f);
	}

}

// -------------------------------------------------------------------------------//
// Level 2 Gameloop Functions                                                     //
// -------------------------------------------------------------------------------//

void LevelTwoSetup()
{
	// ***** Load Models ***** //

	// Walls and floor
	level2Walls = new CWalls();
	level2Walls->CreateLevel2Walls(ModelCreator->cubeMesh, ModelCreator->level2walls);

	// Keys
	level2Keys = new CKey();
	level2Keys->CreateLevel2Keys(ModelCreator->spriteMesh, ModelCreator->level2keyPosition);

	// Books
	level2Books = new CBook();
	level2Books->CreateLevel2Books(ModelCreator->spriteMesh, ModelCreator->level2BookoPosition);

	// Doors
	level2Doors = new CDoor();
	level2Doors->CreateLevel2Doors(ModelCreator->spriteMesh, ModelCreator->level2DoorPosition);


	// Position player Character
	//player->GetModel()->SetPosition(195.0f, 15.0f, 325.0f);
	player->GetModel()->SetPosition(25.0f, 15.0f, 25.0f);
	player->GetModel()->SetSkin("moveDown3.png");

	// Position End portal
	levelEndPortal->SetPosition(185.0f, 10.5f, 125.0f);

	// Stone Background
	CreateModel(myEngine, ModelCreator->spriteMesh, level2Background, 200.0f, 10.0f, 200.0f, 270.0f, 0.0f, 0.0f, 40.0f, 40.0f, 1.0f, "stoneFloorLevel2.png");

	// Level Two Intro Screen
	string Level2Tips = "Level2Tips.png";
	CreateSprite(myEngine, level2introScreen, Level2Tips, 60, 25, OFFSCREEN);
	// Rotating background
	CreateModelWithMesh(myEngine, floorMesh, "Floor.x", level2RotatingBG, 200.0f, 0.0f, 200.0f, 0.0f, 0.0f, 0.0f, "starBackground.jpg");

	// Hotbars

	healthCounterLvl1 = 10;
	for (int i = 0; i < 11; i++)
	{
		mainBar[i]->SetZ(OFFSCREEN);
	}


	// Turrets
	for (int i = 0; i < kNumLevel2Turrets; i++)
	{
		CreateModel(myEngine, ModelCreator->spriteMesh, gunTurret[i], ModelCreator->level2TurretPosition[i].xPos, ModelCreator->level2TurretPosition[i].yPos,
			ModelCreator->level2TurretPosition[i].zPos, 270.0f, ModelCreator->level2TurretPosition[i].rotation, 0.0f,
			0.7f, 0.7f, 1.0f, "turret.png");
	} 

	// Shield collectables
	CreateModel(myEngine, ModelCreator->spriteMesh, fireSheild, 64.0f, 12.0f, 205.0f, 270.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.8f, "fireShield.png");

	// Particles

	// Laser Bolts

	// Horizontol
	for (int i = 0; i < kNumHLaserBolts; i++)
	{
		CreateModel(myEngine, particleMesh, horizontolLaserBolt[i], ModelCreator->level2LaserBoltHPosition[i].startXPos, 
			ModelCreator->level2LaserBoltHPosition[i].startYPos, ModelCreator->level2LaserBoltHPosition[i].startZPos, 
			270.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "particle6.tga");
	}

	// Vertical
	for (int i = 0; i < kNumVLaserBolts; i++)
	{
		CreateModel(myEngine, particleMesh, verticleLaserBolt[i], ModelCreator->level2LaserBoltVPosition[i].startXPos,
			ModelCreator->level2LaserBoltVPosition[i].startYPos, ModelCreator->level2LaserBoltVPosition[i].startZPos,
			270.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "particle6.tga");
	}

	// Lightning
	CreateModel(myEngine, particleMesh, lightningBolt[0], 45.0f, 0.0f, 175.0f, 270.0f, 90.0f, 0.0f, 2.9f, 1.5f, 1.0f, "lightning.tga");
	CreateModel(myEngine, particleMesh, lightningBolt[1], 65.0f, 0.0f, 175.0f, 270.0f, 90.0f, 0.0f, 2.9f, 1.5f, 1.0f, "lightning.tga");

	// Fire Particles
	for (int i = 0; i < knumFireParticles; i++)
	{
		particleXPos = Random(80, 130);
		CreateModel(myEngine, particleMesh, particles[i].mModel, float(particleXPos), 3.0f, 12.0f, 90.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, "010_tlxadd.tga");
	}

	// Flare
	CreateModelWithMesh(myEngine, flareMesh, "Flare.x", flare, 145.0f, 10.0f, 115.0f, 0.0f, 0.0f, 0.0f, "Fire.jpg");
	flare->Scale(3.0f);

	// FireBolts
	CreateModel(myEngine, particleMesh, fireBolts[0], 145.0f, 2.0f, 115.0f, 90.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f, "particle4.tga");

	// Bouncing Fire Bolts

	CreateModel(myEngine, particleMesh, bouncingFireBolts[0], 195.0f, 12.0f, 325.0f, 90.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f, "particle5.tga");
	CreateModel(myEngine, particleMesh, bouncingFireBolts[1], 265.0f, 12.0f, 375.0f, 90.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f, "particle1.tga");
	CreateModel(myEngine, particleMesh, bouncingFireBolts[2], 345.0f, 12.0f, 325.0f, 90.0f, 0.0f, 0.0f, 0.8f, 0.8f, 0.0f, "particle3.tga");

	//Zombies
	for (int i = 0; i < kNumLevel2Zombies; i++) // Place zombies in the world
	{
		level2Zombies[i] = new CZombie(frameTime);
		level2Zombies[i]->GetMyEngine(myEngine);
		level2Zombies[i]->CreateLevel1ZombieModel(ModelCreator->spriteMesh, ModelCreator->enemyPositionsTwo[i].xPos, ModelCreator->enemyPositionsTwo[i].yPos,
			ModelCreator->enemyPositionsTwo[i].zPos, i, ModelCreator->enemyStartSkins[i],
			ModelCreator->dummyWayPointsTwoCooridnates);
	}
	

	// ***** Load Sound Effects *****//

	// Particle bolt shoot sound
	CreateSound(particleFireBuffer, particleFire, "particlefire.wav", 80.0f, 1.0f, false, zeroPosition);

	// Lightning strike sound
	CreateSound(lightningShotBuffer, lightningShot, "lightningShot.wav", 80.0f, 1.0f, false, zeroPosition);

	// Laser Bolt sound
	CreateSound(laserBoltBuffer, laserBolt, "LaserBoltShot.wav", 80.0f, 1.0f, false, zeroPosition);

	// MiniBoss
	CreateModel(myEngine, ModelCreator->spriteMesh, level2MiniBoss,     65.0f, 12.5f, 325.0f, 270.0f, 180.0f, 0.0f, 2.0f, 2.0f, 1.0f, "Cacodemon_tlxcutout.png");
	CreateModel(myEngine, ModelCreator->spriteMesh, level2MiniBossLaser, 0.0f,  0.0f,   0.0f, 270.0f,  0.0f, 0.0f, 1.2f, 0.5f, 1.0f, "bossLaser.png");
	
	deathCounter = 0;

	// Play Music
	level1Music.play();

}

void LevelTwoUpdate(int &moveCounter)
{

	switch (level2State)
	{
	case INTROSCREEN: // ***** Level 2 tips screen *****//
	{
		frameTime = myEngine->Timer(); // Call the Timer again and store it in a variable

		level2introScreen->SetZ(DISPLAYEDTOP);
		mainBar[11]->SetZ(OFFSCREEN);
		infoPanel->SetZ(OFFSCREEN);

		// Reset Counters
		portalCounter = 0;
		endOfLevelPlaySound = false;
		endOfLevelCounter = 0;

		// Wait for Return key press
		if (myEngine->KeyHit(kSelectKey)) level2State = GAMEACTIVE;

		break;

	} // End of INTROSCREEN option

	case GAMEACTIVE: // ***** Level 2 Gameplay Mode *****//
	{
		// ***** Set-up game timer *****
		frameTime = myEngine->Timer(); // Call the Timer again and store it in a variable
		fps = kSecond / frameTime;     // Calculate the Frames per second

		// Hide UI elements
		level2introScreen->SetZ(OFFSCREEN);
		infoPanel->SetZ(DISPLAYEDTOP);
		mainBar[11]->SetZ(DISPLAYEDTOP);
		mainMenuPanel->SetZ(OFFSCREEN);
		paused->SetZ(OFFSCREEN);

		// ***** Game Timer/Stopwatch *****//

		// start the timer
		level2seconds = ((level2seconds + frameTime) / 1.0f);

		// Increase each minute and reset seconds counter
		if (level2seconds > 60.0f)
		{
			level2seconds = 0.0f;
			level2minutes++;
		}

		// ***** Stary Background *****//
		level2RotatingBG->RotateY(5.0f * frameTime); // Rotate the background

		// ***** Player Movement *****//

		// Get position of player character
		oldXPos = player->GetModel()->GetX();
		oldZPos = player->GetModel()->GetZ();

		// Check for player Movement
		player->GetFrameTime(frameTime);
		player->PlayerMovement(playerMoveCounter);

		// Lazer/Bullets
		bullets->Update(player->bobDirection, player->GetModel(), frameTime);

		// Player Death
		if (healthCounterLvl1 == 0)
		{
			level2State = GAMEOVER;
		}

		//Enemies 
		if (healthCounterLvl1 == 0)mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
		for (int i = 0; i < kNumLevel2Zombies; i++)
		{
			if (healthCounterLvl1 > 0 && healthCounterLvl1 < 11
				&& !level2Zombies[i]->detectCollision)mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
			level2Zombies[i]->GenerateModelCoordinates(i);
			level2Zombies[i]->EnemyMovement(zombie1MoveCounter, ModelCreator->enemySkinsRight,
				ModelCreator->enemySkinsLeft, i, enemyMovementSpeeds[i], player);
			level2Zombies[i]->FollowPlayer(player, oldXPos, oldZPos, i);
			if (level2Zombies[i]->detectCollision)
			{
				level2Zombies[i]->detectCollision = false;
				if (healthCounterLvl1 > 0 && healthCounterLvl1 < 11)
				{
					mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
					healthCounterLvl1--;
				}

			}

		}
		for (int i = 0; i < kNumLevel2Zombies; i++)   // Enemy Collision With Player
		{
			level2Zombies[i]->enemyCollisionTwo(player, bullets, oldXPos, oldZPos, ModelCreator->level2walls, ModelCreator->level2DoorPosition, i);
		}
		// ******************************************* Level 2 Collision detection ******************************************* //

		// Walls, books doors and keys collision

		collisionDetector = new Collision;
		level2Walls->level2WallCollision(player, oldXPos, oldZPos, ModelCreator->level2walls); // Walls
		level2Books->Level2BookCollision(player, oldXPos, oldZPos, playerScore);		                       // Books
		level2Doors->Level2DoorCollision(player, oldXPos, oldZPos, playerScore);
		level2Keys->Level2KeyCollision(player, oldXPos, oldZPos, playerScore);                            // Keys

		// Bullets collision

		bullets->level2WallCollision(ModelCreator->level2walls, player);
		bullets->level2DoorCollision(ModelCreator->level2DoorPosition, player);

		// Fire sheild Collision
		fireShieldCollision = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f, fireSheild->GetX(),
			fireSheild->GetZ(), 2.0f, 2.0f);

		if (fireShieldCollision)
		{
			fireSheild->SetY(-10.0f);
			fireShieldCollected = true;
			fireShieldSprite->SetZ(DISPLAYEDTOP);
		}

		// Horizontal laser bolt collision

		hBoltCollisionCounter -= frameTime;

		for (int i = 0; i < kNumHLaserBolts; i++)
		{
			HlaserBoltCollison = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f, horizontolLaserBolt[i]->GetX(),
				horizontolLaserBolt[i]->GetZ(), 1.0f, 1.0f);
			if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
			if (HlaserBoltCollison)
			{
				if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11 && hBoltCollisionCounter <= 0.0f)
				{
					mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
					healthCounterLvl1--;
					hBoltCollisionCounter = 3.0f;
					vBoltCollisionCounter = 3.0f;
					lightningCollisionCounter = 3.0f;
					fireBoltCollisionCounter = 3.0f;
					bossGunCounter = 1.0f;
					bouncingBoltsCounter = 1.0f;

				}
			}
		}

		// Verical laser bolt collision

		vBoltCollisionCounter -= frameTime;

		for (int i = 0; i < kNumVLaserBolts; i++)
		{
			VlaserBoltCollison = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f,
				verticleLaserBolt[i]->GetX(), verticleLaserBolt[i]->GetZ(), 1.0f, 1.0f);
			if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
			if (VlaserBoltCollison)
			{
				if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11 && vBoltCollisionCounter <= 0.0f)
				{
					mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
					healthCounterLvl1--;
					hBoltCollisionCounter = 3.0f;
					vBoltCollisionCounter = 3.0f;
					lightningCollisionCounter = 3.0f;
					fireBoltCollisionCounter = 3.0f;
					bossGunCounter = 1.0f;
					bouncingBoltsCounter = 1.0f;
				}
			}
		}

		// lightning bolt collision

		lightningCollisionCounter -= frameTime;

		for (int i = 0; i < kNumLightningBolts; i++)
		{
			lightningBoltCollision = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f,
				lightningBolt[i]->GetX(), lightningBolt[i]->GetZ(), 1.0f, 20.0f);
			if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
			if (lightningBoltCollision)
			{
				if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11 && lightningCollisionCounter <= 0.0f)
				{
					mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
					healthCounterLvl1--;
					hBoltCollisionCounter = 3.0f;
					vBoltCollisionCounter = 3.0f;
					lightningCollisionCounter = 3.0f;
					fireBoltCollisionCounter = 3.0f;
					bossGunCounter = 1.0f;
					bouncingBoltsCounter = 1.0f;
				}

			}
		}

		// Firebolts


		fireBoltCollisionCounter -= frameTime;

		fireBoltCollision = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f,
			fireBolts[0]->GetX(), fireBolts[0]->GetZ(), 2.0f, 2.0f);
		if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
		if (fireBoltCollision)
		{
			if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11 && fireBoltCollisionCounter <= 0.0f)
			{
				mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
				healthCounterLvl1--;
				hBoltCollisionCounter = 3.0f;
				vBoltCollisionCounter = 3.0f;
				lightningCollisionCounter = 3.0f;
				fireBoltCollisionCounter = 3.0f;
				bossGunCounter = 1.0f;
				bouncingBoltsCounter = 1.0f;
			}


		}

		// boss gun

		bossGunCounter -= frameTime;

		bossGunCollision = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f,
			level2MiniBossLaser->GetX(), level2MiniBossLaser->GetZ(), 1.0f, 2.0f);
		if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
		if (bossGunCollision)
		{
			if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11 && bossGunCounter <= 0.0f)
			{
				mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
				healthCounterLvl1--;
				hBoltCollisionCounter = 3.0f;
				vBoltCollisionCounter = 3.0f;
				lightningCollisionCounter = 3.0f;
				fireBoltCollisionCounter = 3.0f;
				bossGunCounter = 1.0f;
				bouncingBoltsCounter = 1.0f;
			}


		}

		// Bouncing bolts

		bouncingBoltsCounter -= frameTime;

		for (int i = 0; i < kNumBouncingFireBolts; i++)
		{
			bouncingFireBoltCollision = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f,
				                                                      bouncingFireBolts[i]->GetX(), bouncingFireBolts[i]->GetZ(), 1.0f, 1.0f);
			if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);
			if (bouncingFireBoltCollision)
			{
				if (healthCounterLvl1 > -1 && healthCounterLvl1 < 11 && bouncingBoltsCounter <= 0.0f)
				{
					mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
					healthCounterLvl1--;
					hBoltCollisionCounter = 3.0f;
					vBoltCollisionCounter = 3.0f;
					lightningCollisionCounter = 3.0f;
					fireBoltCollisionCounter = 3.0f;
					bossGunCounter = 1.0f;
					bouncingBoltsCounter = 1.0f;
				}


			}


		}



		// ******************************************************************************************************************** //



		// ***** End portal animation ***** //

		portalCounter++;

		for (int i = 0; i < kNumPortalSkinNames; i++)
		{
			if (portalCounter == portalCounterValues[i]) levelEndPortal->SetSkin(portalSkinNames[i]);
			if (portalCounter == 151) portalCounter = 49;

		} // End of for loop


		// ***** Laser bolts (that fire out of the turrets) *****//

		particleCounter++;

		// Horizontal

		for (int i = 0; i < kNumHLaserBolts; i++)
		{
			horizontolLaserBolt[i]->MoveX(ModelCreator->level2LaserBoltHPosition[i].speed * frameTime);
			if (horizontolLaserBolt[i]->GetX() > ModelCreator->level2LaserBoltHPosition[i].endXPos)
			{
				horizontolLaserBolt[i]->SetX(ModelCreator->level2LaserBoltHPosition[i].startXPos);
				if ((DistanceFromPlayer(player->GetModel(), horizontolLaserBolt[i]) < 70.0f)) particleFire.play();
			}



		}

		// Verticle
		for (int i = 0; i < kNumVLaserBolts; i++)
		{
			verticleLaserBolt[i]->MoveZ(ModelCreator->level2LaserBoltVPosition[i].speed * frameTime);
			if (verticleLaserBolt[i]->GetZ() > ModelCreator->level2LaserBoltVPosition[i].endZPos)
			{
				verticleLaserBolt[i]->SetZ(ModelCreator->level2LaserBoltVPosition[i].startZPos);
				if ((DistanceFromPlayer(player->GetModel(), verticleLaserBolt[i]) < 70.0f)) particleFire.play();
			}

		}

		// ***** Lightning Beams *****//

		for (int i = 0; i < kNumLightningBolts; i++)  lightningCounter[i]++;

		for (int i = 0; i < kNumLightningBolts; i++)
		{

			if (lightningCounter[i] == 100)
			{
				lightningBolt[i]->SetY(15.0f);
				if ((DistanceFromPlayer(player->GetModel(), lightningBolt[i]) < 60.0f)) lightningShot.play();

			}
			else if (lightningCounter[i] == 125)
			{
				lightningBolt[i]->SetY(-20.0f);

			}
			else if (lightningCounter[i] == 150)
			{
				lightningBolt[i]->SetY(15.0f);
				if ((DistanceFromPlayer(player->GetModel(), lightningBolt[i]) < 60.0f)) lightningShot.play();
			}
			else if (lightningCounter[i] == 175
				)
			{
				lightningBolt[i]->SetY(-20.0f);
				lightningCounter[i] = 0;
			}
		}

		// ***** Fire particles *****//

		for (int i = 0; i < knumFireParticles; i++)
		{
			// check if active
			if (particles[i].mActive)
			{
				particles[i].mModel->MoveZ(particles[i].speed * frameTime);

				if (particles[i].mModel->GetZ() > 30.0f)
				{
					particles[i].mModel->SetZ(10.0f);
					particles[i].mActive = false;
				}
			}

			if (particles[i].mActive == false)
			{
				// activate and skip rest
				particles[i].speed = Random(10, 40);
				particles[i].mActive = true;
				break;
			}
		}

		// ***** 6 Way firebolt *****//

		switch (fireBolt)
		{
		case FIREUP:
		{
			fireBolts[0]->MoveZ(kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetZ() > 150.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIREUPRIGHT;
			}
			break;
		}
		case FIREUPRIGHT:
		{
			fireBolts[0]->MoveX(kFireBoltMoveSpeed * frameTime);
			fireBolts[0]->MoveZ(kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetX() > 175.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIRERIGHT;
			}
			break;
		}
		case FIRERIGHT:
		{
			fireBolts[0]->MoveX(kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetX() > 175.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIREDOWNRIGHT;
			}
			break;
		}
		case FIREDOWNRIGHT:
		{
			fireBolts[0]->MoveX(kFireBoltMoveSpeed * frameTime);
			fireBolts[0]->MoveZ(-kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetX() > 175.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIREDOWN;
			}
			break;
		}
		case FIREDOWN:
		{
			fireBolts[0]->MoveZ(-kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetZ() < 80.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIREDOWNLEFT;
			}
			break;
		}
		case FIREDOWNLEFT:
		{
			fireBolts[0]->MoveX(-kFireBoltMoveSpeed * frameTime);
			fireBolts[0]->MoveZ(-kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetX() < 115.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIRELEFT;
			}
			break;
		}
		case FIRELEFT:
		{
			fireBolts[0]->MoveX(-kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetX() < 115.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIREUPLEFT;
			}
			break;
		}
		case FIREUPLEFT:
		{
			fireBolts[0]->MoveX(-kFireBoltMoveSpeed * frameTime);
			fireBolts[0]->MoveZ(kFireBoltMoveSpeed * frameTime);
			if (fireBolts[0]->GetX() < 115.0f)
			{
				fireBolts[0]->SetPosition(145.0f, 6.0f, 115.0f);
				if ((DistanceFromPlayer(player->GetModel(), fireBolts[0]) < 60.0f)) laserBolt.play();
				fireBolt = FIREUP;
			}
			break;
		}
		}

		// ***** Mini Boss *****//

		// Boss Movement
		switch (level2BossMovement)
		{
		case BOSSMOVINGUP:
		{
			level2MiniBoss->MoveZ(40.0f * frameTime);
			if (level2MiniBoss->GetZ() > 380.0f) level2BossMovement = BOSSMOVINGDOWN;
			break;
		}
		case MOVINGDOWN:
		{
			level2MiniBoss->MoveZ(-40.0f * frameTime);
			if (level2MiniBoss->GetZ() < 320.0f) level2BossMovement = BOSSMOVINGUP;
			break;
		}
		}

		// Boss firing laser
		bossFireCounter++;
		switch (level1BossFire)
		{
		case FIRING:
		{
			level2MiniBossLaser->MoveX(100.0f * frameTime);
			if (level2MiniBossLaser->GetX() > 175.0f) level1BossFire = NOTFIRING;
			break;
		}
		case NOTFIRING:
		{
			level2MiniBossLaser->SetPosition(level2MiniBoss->GetX(), level2MiniBoss->GetY() - 0.5f, level2MiniBoss->GetZ());
			if ((DistanceFromPlayer(player->GetModel(), level2MiniBoss) < 100.0f)) laserBolt.play();
			level1BossFire = FIRING;
			break;
		}
		}
		bool bossHitsPlayer = collisionDetector->sphere2Box(player->GetModel()->GetX(), player->GetModel()->GetZ(), 4.0f, level2MiniBossLaser->GetX(), level2MiniBossLaser->GetZ(), 10.0f, 5.0f);

		hBossCollisionCounter -= frameTime;
		if (bossHitsPlayer && hBossCollisionCounter <= 0.0f)
		{
			if (healthCounterLvl1 > 0 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
			healthCounterLvl1 -= 2;
			//if(healthCounterLvl1==1)mainBar[healthCounterLvl1]->SetZ(OFFSCREEN);
			hBossCollisionCounter = 5.0f;
		}
		if (healthCounterLvl1 > 0 && healthCounterLvl1 < 11) mainBar[healthCounterLvl1]->SetZ(DISPLAYEDBOTTOM);

		for (int i = 0; i < kNumBullets; i++)
		{
			bool playerHitsBoss = collisionDetector->sphere2Box(bullets->myBullets[i].Model->GetX(), bullets->myBullets[i].Model->GetZ(), 1.0f, level2MiniBoss->GetX(), level2MiniBoss->GetZ(), 10.0f, 10.0f);
			if (playerHitsBoss)
			{
				bossLife++;
				bullets->myBullets[i].Model->SetPosition(-500.0f, 0.0f, -500.0f);
				if (bossLife == 20)
				{

					level2MiniBoss->SetPosition(-500.0f, 0.0f, -500.0f);
				}
			}
		}
		// Bouncing bolts


		for (int i = 0; i < kNumBouncingFireBolts; i++)
		{
			bouncingFireBolts[i]->MoveX(boltMoveX[i] * frameTime);
			bouncingFireBolts[i]->MoveZ(boltMoveZ[i] * frameTime);

			if ((bouncingFireBolts[i]->GetZ() > 385.0f) || (bouncingFireBolts[i]->GetZ() < 322.0f))
			{
				if (bouncingFireBolts[i]->GetZ() > 385.0f) bouncingFireBolts[i]->SetZ(bouncingFireBolts[i]->GetZ() - 0.5f);
				if (bouncingFireBolts[i]->GetZ() < 322.0f) bouncingFireBolts[i]->SetZ(bouncingFireBolts[i]->GetZ() + 0.5f);

				if ((DistanceFromPlayer(player->GetModel(), bouncingFireBolts[i]) < 100.0f)) laserBolt.play();
				boltMoveZ[i] = -boltMoveZ[i];
			}
			if ((bouncingFireBolts[i]->GetX() > 354.0f) || (bouncingFireBolts[i]->GetX() < 185.0f))
			{
				if (bouncingFireBolts[i]->GetX() > 354.0f) bouncingFireBolts[i]->SetX(bouncingFireBolts[i]->GetX() - 0.5f);
				if (bouncingFireBolts[i]->GetX() < 322.0f) bouncingFireBolts[i]->SetX(bouncingFireBolts[i]->GetX() + 0.5f);

				if ((DistanceFromPlayer(player->GetModel(), bouncingFireBolts[i]) < 100.0f)) laserBolt.play();
				boltMoveX[i] = -boltMoveX[i];
			}
		}










		// ***** Text output to screen ***** //


		stringstream frameTimeTextlv2, fpsTextlv2, numRedKeysTextlv2, numBlueKeysTextlv2, numGreenKeysTextlv2, numYellowKeysTextlv2,
			         numBooksTextlv2, totalBooksTextlv2, lightningCounterTextlv2, minutesTextlv2, secsTextlv2, healthCounterText, hBoltCollisionText, scoreText2;

		// Bottom Right Info Panel 

		// FrameTime
		DisplayText("FrameTime: ", normalText, 1630, 890, kBlack);
		DisplayFloatAsText(frameTime, normalText, frameTimeTextlv2, 1800, 890, kBlack);

		// FPS
		DisplayText("FPS: ", normalText, 1630, 910, kBlack);
		DisplayFloatAsText(fps, normalText, fpsTextlv2, 1800, 910, kBlack);

		// healthCounterLvl1
		DisplayText("hCounterLvl1: ", normalText, 1630, 930, kBlack);
		DisplayFloatAsText(healthCounterLvl1, normalText, healthCounterText, 1800, 930, kBlack);

		// laser bolt counter
		DisplayText("hBoltCollCounter: ", normalText, 1630, 950, kBlack);
		DisplayFloatAsText(hBoltCollisionCounter, normalText, hBoltCollisionText, 1800, 950, kBlack);



		// Player hotbar

		// Output Number of Red Keys on hotbar
		DisplayIntAsText(player->GetNumLevel2RedKeys(), keyBarText, numRedKeysTextlv2, 1080, 1020, kRed);

		// Output Number of Blue Keys on hotbar
		DisplayIntAsText(player->GetNumLevel2BlueKeys(), keyBarText, numBlueKeysTextlv2, 1210, 1020, kBlue);

		// Output Number of green Keys on hotbar
		DisplayIntAsText(player->GetNumLevel2GreenKeys(), keyBarText, numGreenKeysTextlv2, 1340, 1020, kGreen);

		// Output Number of yellow Keys on hotbar
		DisplayIntAsText(player->GetNumLevel2YellowKeys(), keyBarText, numYellowKeysTextlv2, 1465, 1020, kYellow);

		// Output Number of Books on hotbar
		if (player->GetNumLevel2Books() < 10) DisplayIntAsText(player->GetNumLevel2Books(), bookBarText, numBooksTextlv2, 880, 1020, kWhite);
		else DisplayIntAsText(player->GetNumLevel2Books(), bookBarText, numBooksTextlv2, 855, 1020, kWhite);
		DisplayText("/", bookBarText, 920, 1020, kWhite);
		DisplayIntAsText(kNumLevel2Books, bookBarText, totalBooksTextlv2, 935, 1020, kWhite);

		// Timer/Clock
		DisplayIntAsText(level2minutes, clockText, minutesTextlv2, 492, 1001, kWhite);
		DisplayText(":", clockText, 510, 1000, kWhite);
		DisplayIntAsText(int(level2seconds), clockText, secsTextlv2, 520, 1001, kWhite);

		// Score
		DisplayIntAsText(playerScore, clockText, scoreText2, 710, 1001, kWhite);



		// ***** End of level actions ***** //
		if (player->GetNumLevel2Books() == 52) // Has the player collected all 52 books?
		{
			if (!endOfLevelPlaySound) allBooksCollected.play(); // Play level complete sound
			endOfLevelPlaySound = true; // This is put into a boolean to stop the sound from repeating in the game loop

			// All books collection notification flash
			endOfLevelCounter++;
			NotificationFlash(endOfLevelCounter, exitOpen);


			
			// END OF LEVEL BOSS CODE GOES HERE

		}

		// ***** Check for in-game key presses ***** //

		// Check for paused keypress
		if (myEngine->KeyHit(kPauseKey)) level2State = PAUSED;

		// Check for escape keypress
		if (myEngine->KeyHit(kMenuKey)) level2State = MAINMENU;


		break;
	}

	case PAUSED: // ***** Level 2 Paused Screen *****//
	{
		level1Music.pause();
		if (playPauseSound)
		{
			pauseOn.play();
			playPauseSound = false;
		}

		paused->SetZ(DISPLAYEDTOP);

		if (myEngine->KeyHit(kPauseKey))
		{
			level1Music.play();
			level2State = GAMEACTIVE;
			if (!playPauseSound)
			{
				pauseOff.play();
				playPauseSound = true;
			}
		}
		frameTime = myEngine->Timer(); // Call the Timer again and store it in a variable
		break;

	}
	case MAINMENU: // ***** Level 2 Main Menu Display *****//
	{

		break;
	}

	case LEVELCOMPLETE: // ***** Level 2 Complete actions *****//
	{

		break;
	}
	case GAMEOVER:
	{
		deathCounter++;

		if      (deathCounter == 100)  player->GetModel()->SetSkin("die1.png");
		else if (deathCounter == 200)  player->GetModel()->SetSkin("die2.png");
		else if (deathCounter == 300)  player->GetModel()->SetSkin("die3.png");
		else if (deathCounter == 400)  player->GetModel()->SetSkin("die4.png");
		else if (deathCounter == 500) player->GetModel()->SetSkin("die5.png");
		else if (deathCounter == 600) player->GetModel()->SetSkin("die6.png");
		else if (deathCounter > 1500)
		{
			gameOverScreen->SetZ(DISPLAYEDTOP);

		}

		if (myEngine->KeyHit(kSelectKey)) myEngine->Stop();

		break;
	}
	}

	// Debug quit key
	if (myEngine->KeyHit(kMenuKey)) myEngine->Stop();
}

void LevelTwoShutdown()
{

}

// -------------------------------------------------------------------------------//
// Main Function                                                                  //
// -------------------------------------------------------------------------------//

void main()
{
	// ***** Create a 3D engine (using TLX engine) and open a window for it *****//
	myEngine = New3DEngine( kTLX );
	myEngine->StartWindowed(1920, 1080);

	// ***** Add default folder for meshes and other media *****//
	ModelCreator = new CPlayer;
	ModelCreator->GetMyEngine(myEngine);
	ModelCreator->LoadMediaFolders();
	ModelCreator->LoadModelMeshes();

	// ***** Call the timer at the start of the game loop *****//
	myEngine->Timer();

	// ---------------------------------------------------------------------------//
	// Title Screen                                                               //
	// ---------------------------------------------------------------------------//

	// ***** Title screen Set-up  *****
	TitleScreenSetup();

	//// ***** Title screen update loop  *****
	while (myEngine->IsRunning())
	{
		if (!mainMenuDone)
		{
			// Draw the scene
			myEngine->DrawScene();
			myEngine->StopMouseCapture();

			TitleScreenUpdate();
		}
		else
		{
			break;
		}

	} // End of Title screen game loop

	// ***** Title screen Shutdown  *****
	TitleScreenShutdown();

	// ---------------------------------------------------------------------------//
	// Level 1                                                                    //
	// ---------------------------------------------------------------------------//

	// ***** Level 1 Set-up  *****
	LevelOneSetup();

	// ***** Level 1 Update Loop  *****
	while (myEngine->IsRunning())
	{
		if (!quitGame && !level1Complete)
		{
			// Draw the scene
			myEngine->DrawScene();
			myEngine->StopMouseCapture();

			LevelOneUpdate();

			// *** Debug key to quit straight out of program ***
			if (myEngine->KeyHit(Key_Numpad0)) myEngine->Stop(); 

			// *************************************************
		}
		else
		{
			break;
		}

	} // End of main game loop

	// ***** Level 1 Shutdown  *****
	LevelOneShutdown();

	// ---------------------------------------------------------------------------//
	// Level 2                                                                    //
	// ---------------------------------------------------------------------------//
	
	// ***** Level 2 Set-up  *****
	LevelTwoSetup();

	// ***** Level 2 Update Loop  *****
	while (myEngine->IsRunning())
	{
		if (!quitGame && !level2Complete)
		{
			// Draw the scene
			myEngine->DrawScene();
			myEngine->StopMouseCapture();

			LevelTwoUpdate(playerMoveCounter);
		}
		else
		{

			return;
		
		}

	}
	
	// ***** Level 2 Shutdown  *****
	LevelTwoShutdown();

	// Delete the 3D engine now we are finished with it

	//myEngine->Delete();
}
	
// ---------------------------------------------------------------------------//
// Functions                                                                  //
// ---------------------------------------------------------------------------//

void CreateModel(I3DEngine* myEngine, IMesh* &mesh, IModel* &model, float startXPos, float startYPos, float startZPos, 
	float rotateX, float rotateY, float rotateZ, float scaleX, float scaleY, float scaleZ, string startSkin)
{
	model = mesh->CreateModel(startXPos, startYPos, startZPos);
	model->RotateX(rotateX);
	model->RotateY(rotateY);
	model->RotateZ(rotateZ);
	model->ScaleX(scaleX);
	model->ScaleY(scaleY);
	model->ScaleZ(scaleZ);
	model->SetSkin(startSkin);
}

void CreateModelWithMesh(I3DEngine* myEngine, IMesh* &mesh, string meshFileName, IModel* &model, float startXPos, 
	float startYPos, float startZPos, float rotateX, float rotateY, float rotateZ, string startSkinFileName)
{
	mesh = myEngine->LoadMesh(meshFileName);
	model = mesh->CreateModel(startXPos, startYPos, startZPos);
	model->RotateX(rotateX);
	model->RotateY(rotateY);
	model->RotateZ(rotateZ);
	model->SetSkin(startSkinFileName);
}

void CreateSound(sf::SoundBuffer &buffer, sf::Sound &sound, string filename, float volume, float pitch, bool loop, 
	             sf::Vector3f position)
{
	buffer.loadFromFile(filename);
	sound.setBuffer(buffer);
	sound.setVolume(volume);
	sound.setPitch(pitch);
	sound.setLoop(loop);
	sound.setPosition(position);
}

void SetListener(const float volume, sf::Vector3f position, sf::Vector3f direction, sf::Vector3f setUpVector)
{
	sf::Listener::setGlobalVolume(volume);
	sf::Listener::setPosition(position);
	sf::Listener::setDirection(direction);
	sf::Listener::setUpVector(setUpVector);
}

void CreateFont(I3DEngine* myEngine, IFont* &font, string fontType, int size)
{
	font = myEngine->LoadFont(fontType, size);
}

void CreateSprite(I3DEngine* myEngine, ISprite* &sprite, string &spriteFileName, float xPos, float yPos, float zPos)
{
	sprite = myEngine->CreateSprite(spriteFileName, xPos, yPos);
	sprite->SetZ(zPos);
}

void CreateCamera(I3DEngine* myEngine, ICamera* &camera, float startXPos, float startYPos, float startZPos, float rotateX, 
	              float rotateY, float rotateZ)
{
	camera = myEngine->CreateCamera(kManual);
	camera->SetPosition(startXPos, startYPos, startZPos);
	camera->RotateX(rotateX);
	camera->RotateY(rotateY);
	camera->RotateZ(rotateZ);
}

void DisplayText(string textToDisplay, IFont* font, int xPos, int yPos, const unsigned int colour)
{
	font->Draw(textToDisplay, xPos, yPos, colour, kLeft, kVCentre);
}

void DisplayFloatAsText(float floatToDisplay, IFont* font, stringstream &stream, int xPos, int yPos, 
	                    const unsigned int colour)
{
	stream << floatToDisplay;
	font->Draw(stream.str(), xPos, yPos, colour, kLeft, kVCentre);
}

void DisplayIntAsText(int intToDisplay, IFont* font, stringstream &stream, int xPos, int yPos, const unsigned int colour)
{
	stream << intToDisplay;
	font->Draw(stream.str(), xPos, yPos, colour, kLeft, kVCentre);
}

void MoveBackgroundLeft(IModel* &backGround, float speed, const float backgroundLimitPosition, mainScreen &mainScreenMovement)
{
	backGround->MoveX(-speed); // Move left
	if (backGround->GetX() <= backgroundLimitPosition) mainScreenMovement = MOVERIGHT; // Change direction
}

void MoveBackgroundRight(IModel* &backGround, float speed, const float backgroundLimitPosition, mainScreen &mainScreenMovement)
{
	backGround->MoveX(speed); // Move left
	if (backGround->GetX() > backgroundLimitPosition) mainScreenMovement = MOVELEFT;
}

void NotificationFlash(int &counter, ISprite* &spriteToDisplay)
{
	if (counter == 200)  spriteToDisplay->SetZ(DISPLAYEDTOP);
	else if (counter == 400)  spriteToDisplay->SetZ(OFFSCREEN);
	else if (counter == 600) spriteToDisplay->SetZ(DISPLAYEDTOP);
	else if (counter == 800) spriteToDisplay->SetZ(OFFSCREEN);
	else if (counter == 1000) spriteToDisplay->SetZ(DISPLAYEDTOP);
	else if (counter == 1200) spriteToDisplay->SetZ(OFFSCREEN);
}

float DistanceFromPlayer(IModel* player, IModel* object)
{
	float distanceX = object->GetX() - player->GetX();
	float distanceY = object->GetY() - player->GetY();
	float distanceZ = object->GetZ() - player->GetZ();

	float distance = sqrt((distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ));

	return distance;

}

float Random(int rangeMin, int rangeMax)
{
	float result = (float)rand() / (float)(RAND_MAX + 1);
	result *= (float)(rangeMax - rangeMin);
	result += rangeMin;

	return result;
}



