// File:	      CMasterModelCreator.CPP
// Date:	      05-02-2019
// Last Edited:   21-03-2019


#include "CMasterModelCreator.h"
CMasterModelCreator::CMasterModelCreator()
{
	spriteMesh     = NULL;
	cubeMesh       = NULL;
	spriteMeshCopy = NULL;
};

void CMasterModelCreator::LoadMediaFolders()
{
	myEngine->AddMediaFolder("C:\\ProgramData\\TL-Engine\\Media");
	myEngine->AddMediaFolder(".\\media");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Backgrounds");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Bob");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Collectable_Items");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Doors");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Explosions");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Floors");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Models");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Particles");
	myEngine->AddMediaFolder(".\\media\\Graphics\\User_Interface");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Walls");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Zombies");
	myEngine->AddMediaFolder(".\\media\\Graphics\\Other");
}

void CMasterModelCreator::LoadModelMeshes()
{
	spriteMesh = myEngine->LoadMesh("quad.x");
	cubeMesh = myEngine->LoadMesh("cube.x");
	GenerateModelCoordinates();
}

void CMasterModelCreator::GenerateModelCoordinates()
{
	// Level 1
	string healthSystemLayers2[] = { "mainHotBar0.png","mainHotBar1.png" ,"mainHotBar2.png" ,"mainHotBar3.png" ,"mainHotBar4.png" ,"mainHotBar5.png" ,"mainHotBar6.png" ,
	   "mainHotBar7.png" ,"mainHotBar8.png" ,"mainHotBar9.png" ,"mainHotBar10.png" };
	for (int i = 0; i < 10; i++)
	{
		healthSystemLayers[i] = healthSystemLayers2[i];
	}                  
	bookDetails level1BookoPosition2[kNumLevel1Books] = { {  55.0f, 10.0f, 135.0f }, { 110.0f, 10.0f, 135.0f },{  35.0f, 10.0f,  95.0f },
												          { 135.0f, 10.0f,  95.0f }, {  35.0f, 10.0f,  75.0f },{ 135.0f, 10.0f,  65.0f },
												          {  85.0f, 10.0f,  65.0f }, {  65.0f, 10.0f,  35.0f },{  95.0f, 10.0f,  35.0f },
												          {  65.0f, 10.0f,  85.0f }, { 105.0f, 10.0f,  85.0f },{  65.0f, 10.0f,  25.0f },
												          {  25.0f, 10.0f,  35.0f }, { 145.0f, 10.0f,  45.0f },{ 135.0f, 10.0f,  25.0f },
												          {  25.0f, 10.0f, 135.0f }, { 145.0f, 10.0f, 135.0f } };


	keyDetails  level1keyPosition2[kNumLevel1Keys]   = { { 105.0f, 10.0f,  75.0f, 1 },{ 105.0f, 10.0f,  95.0f, 1 },{  65.0f, 10.0f,  75.0f, 2 },
											            {  65.0f, 10.0f,  95.0f, 2 },{  25.0f, 10.0f,  25.0f, 3 },{ 145.0f, 10.0f,  25.0f, 3 },
											            {  15.0f, 10.0f,  95.0f, 4 },{ 155.0f, 10.0f, 105.0f, 4 } };


	keyDetails level1DoorPosition2[kNumLevel1Doors] = { {  55.0f, 10.0f,  65.0f, 1 },{ 115.0f, 10.0f, 105.0f, 1 },{  55.0f, 10.0f, 105.0f, 2 },
												        { 115.0f, 10.0f,  65.0f, 2 },{  65.0f, 10.0f, 115.0f, 3 },{ 105.0f, 10.0f, 115.0f, 3 },
												        {  75.0f, 10.0f,  55.0f, 4 },{  95.0f, 10.0f,  55.0f, 4 } };


	// Level 2

	bookDetails level2BookoPosition2[kNumLevel2Books] = { {  15.0f, 10.5f,  65.0f },{  15.0f, 10.5f, 105.0f },{  15.0f, 10.5f, 175.0f },
                                                          { 105.0f, 10.5f, 185.0f },{  55.0f, 10.5f, 145.0f },{ 105.0f, 10.5f, 145.0f },
                                                          { 105.0f, 10.5f,  85.0f },{  55.0f, 10.5f,  15.0f },{ 145.0f, 10.5f,  15.0f },
                                                          { 165.0f, 10.5f,  75.0f },{ 125.0f, 10.5f,  85.0f },{ 125.0f, 10.5f, 145.0f },
                                                          { 165.0f, 10.5f, 145.0f },{ 165.0f, 10.5f, 165.0f },{ 125.0f, 10.5f, 185.0f },
                                                          {  85.0f, 10.5f, 235.0f },{ 105.0f, 10.5f, 295.0f },{  15.0f, 10.5f, 285.0f },
														  {  15.0f, 10.5f, 205.0f },{  45.0f, 10.5f, 235.0f },{  65.0f, 10.5f, 235.0f },
														  { 165.0f, 10.5f, 235.0f },{ 125.0f, 10.5f, 235.0f },{ 125.0f, 10.5f, 295.0f },
														  {  15.0f, 10.5f, 365.0f },{  15.0f, 10.5f, 375.0f },{  15.0f, 10.5f, 345.0f },
														  {  15.0f, 10.5f, 335.0f },{ 165.0f, 10.5f, 385.0f },{ 385.0f, 10.5f, 385.0f },
														  { 385.0f, 10.5f, 315.0f },{ 385.0f, 10.5f, 275.0f },{ 345.0f, 10.5f, 185.0f },
														  { 355.0f, 10.5f, 185.0f },{ 375.0f, 10.5f, 185.0f },{ 385.0f, 10.5f, 185.0f },
														  { 315.0f, 10.5f, 185.0f },{ 325.0f, 10.5f, 185.0f },{ 295.0f, 10.5f, 185.0f },
														  { 285.0f, 10.5f, 185.0f },{ 265.0f, 10.5f, 185.0f },{ 255.0f, 10.5f, 185.0f },
														  { 235.0f, 10.5f, 185.0f },{ 225.0f, 10.5f, 185.0f },{ 185.0f, 10.5f, 305.0f },
														  { 275.0f, 10.5f, 275.0f },{ 335.0f, 10.5f, 305.0f },{ 205.0f, 10.5f, 235.0f },
														  { 185.0f, 10.5f, 175.0f },{ 245.0f, 10.5f, 145.0f },{ 295.0f, 10.5f, 165.0f },
														  { 385.0f, 10.5f, 165.0f } };

	keyDetails  level2keyPosition2[kNumLevel2Keys] = { { 105.0f, 10.0f,  165.0f, 1 },{ 55.0f, 10.0f,  255.0f, 1 },{ 365.0f, 10.0f,  185.0f, 1 },
		                                               { 105.0f, 10.0f,  115.0f, 2 },{ 15.0f, 10.0f,  355.0f, 2 },{ 245.0f, 10.0f,  185.0f, 2  },
	                                                   { 165.0f, 10.0f,  215.0f, 3 },{ 275.0f, 10.0f, 325.0f, 3 },{ 305.0f, 10.0f,  185.0f, 3 },
	                                                   {  85.0f, 10.0f,   55.0f, 4 },{ 195.0f, 10.0f,  145.0f, 4 }	};


	keyDetails  level2DoorPosition2[kNumLevel2Doors] = { { 45.0f, 10.0f,  105.0f, 1 },{ 145.0f, 10.0f,  225.0f, 1 },{ 245.0f, 10.0f,  265.0f, 1 },
	                                                     { 145.0f, 10.0f, 155.0f, 2 },{ 175.0f, 10.0f,  355.0f, 2 },{ 305.0f, 10.0f,  265.0f, 2 },
                                                         { 135.0f, 10.0f,  55.0f, 3 },{ 365.0f, 10.0f,  355.0f, 3 },{ 335.0f, 10.0f,  155.0f, 3 },
	                                                     { 55.0f, 10.0f,  225.0f, 4 },{ 365.0f, 10.0f,  265.0f, 4 }
	
	};

	turretDetails level2TurretPosition2[kNumLevel2Turrets] = { {  10.0f, 15.5f,  44.0f,   0.0f }, {  40.0f, 15.5f,  45.0f, 180.0f },   // Laserbolt 1
	                                                           {  10.0f, 15.5f,  84.0f,   0.0f }, {  40.0f, 15.5f,  84.7f, 180.0f },   // Laserbolt 2
		                                                       {  10.0f, 15.5f, 134.0f,   0.0f }, {  40.0f, 15.5f, 134.7f, 180.0f },   // Laserbolt 3
	                                                           {  45.0f, 15.5f, 190.0f,  90.0f }, {  46.0f, 15.5f, 160.0f, 270.0f },   // Lightning 1
														       {  65.0f, 15.5f, 190.0f,  90.0f }, {  66.0f, 15.5f, 160.0f, 270.0f },   // Lightning 2
															   {  80.0f, 15.5f, 214.0f,   0.0f }, { 110.0f, 15.5f, 215.0f, 180.0f },   // Laserbolt 4
	                                                           {  80.0f, 15.5f, 254.0f,   0.0f }, { 110.0f, 15.5f, 255.0f, 180.0f },   // Laserbolt 5
															   {  66.0f, 15.5f, 270.0f, 270.0f }, {  65.0f, 15.5f, 300.0f,  90.0f },   // Laserbolt 6
	
	};


	laserBoltHDetails level2LaserBoltHPosition2[kNumHLaserBolts] = { {  5.0f, 14.0f, 45.0f, 45.0f, 35.0f }, { 5.0f, 14.0f, 85.0f, 45.0f,  40.0f },{ 5.0f, 14.0f, 135.0f,  45.0f, 45.0f },
	                                                                { 75.0f, 14.0f, 215.0f, 115.0f, 50.0f }, { 75.0f, 14.0f, 255.0f, 115.0f, 55.0f } };

	laserBoltVDetails level2LaserBoltVPosition2[kNumVLaserBolts] = { {  65.0f, 14.0f, 265.0f, 305.0f, 60.0f }  };



	for (int i = 0; i < kNumLevel1Doors; i++) level1DoorPosition[i] = level1DoorPosition2[i];
	for (int i = 0; i < kNumLevel1Keys; i++)  level1keyPosition[i]  = level1keyPosition2[i];
	for (int i = 0; i < kNumLevel1Books; i++) level1BookoPosition[i] = level1BookoPosition2[i];

	for (int i = 0; i < kNumLevel2Doors; i++)   level2DoorPosition[i] = level2DoorPosition2[i];
	for (int i = 0; i < kNumLevel2Keys; i++)    level2keyPosition[i] = level2keyPosition2[i];
	for (int i = 0; i < kNumLevel2Books; i++)   level2BookoPosition[i] = level2BookoPosition2[i];
	for (int i = 0; i < kNumLevel2Turrets; i++) level2TurretPosition[i] = level2TurretPosition2[i];
	for (int i = 0; i < kNumHLaserBolts; i++) level2LaserBoltHPosition[i] = level2LaserBoltHPosition2[i];
	for (int i = 0; i < kNumVLaserBolts; i++) level2LaserBoltVPosition[i] = level2LaserBoltVPosition2[i];



	
	wallDetails  level1walls2[kNumLevel1Walls] = { {  85.0f, 5.0f,  15.0f },{ 115.0f, 5.0f,  15.0f },{  85.0f, 5.0f,  25.0f },{  85.0f, 5.0f,  35.0f },
											 {  85.0f, 5.0f,  45.0f },{ 115.0f, 5.0f,  25.0f },{ 115.0f, 5.0f,  35.0f },{ 115.0f, 5.0f,  45.0f },
											 {  15.0f, 5.0f,  55.0f },{  25.0f, 5.0f,  55.0f },{  35.0f, 5.0f,  55.0f },{  45.0f, 5.0f,  55.0f },
											 {  55.0f, 5.0f,  55.0f },{  65.0f, 5.0f,  55.0f },{  85.0f, 5.0f,  55.0f },{ 105.0f, 5.0f,  55.0f },
											 { 115.0f, 5.0f,  55.0f },{ 165.0f, 5.0f,  65.0f },{ 165.0f, 5.0f,  75.0f },{ 165.0f, 5.0f,  85.0f },
											 { 165.0f, 5.0f,  45.0f },{ 165.0f, 5.0f,  55.0f },{ 165.0f, 5.0f,  45.0f },{ 165.0f, 5.0f,  35.0f },
											 { 165.0f, 5.0f,  25.0f },{ 165.0f, 5.0f,  15.0f },{  55.0f, 5.0f,  75.0f },{ 115.0f, 5.0f,  75.0f },
											 {  15.0f, 5.0f,  85.0f },{  25.0f, 5.0f,  85.0f },{  35.0f, 5.0f,  85.0f },{  45.0f, 5.0f,  85.0f },
											 {  55.0f, 5.0f,  85.0f },{ 115.0f, 5.0f,  85.0f },{ 125.0f, 5.0f,  85.0f },{ 135.0f, 5.0f,  85.0f },
											 { 145.0f, 5.0f,  85.0f },{ 155.0f, 5.0f,  85.0f },{  55.0f, 5.0f,  95.0f },{ 115.0f, 5.0f,  95.0f },
											 { 165.0f, 5.0f,  95.0f },{ 165.0f, 5.0f, 105.0f },{  15.0f, 5.0f, 115.0f },{  25.0f, 5.0f, 115.0f },
											 {  35.0f, 5.0f, 115.0f },{  45.0f, 5.0f, 115.0f },{  55.0f, 5.0f, 115.0f },{  75.0f, 5.0f, 115.0f },
											 {  95.0f, 5.0f, 115.0f },{ 115.0f, 5.0f, 115.0f },{ 125.0f, 5.0f, 115.0f },{ 135.0f, 5.0f, 115.0f },
											 { 145.0f, 5.0f, 115.0f },{ 155.0f, 5.0f, 115.0f },{  75.0f, 5.0f, 125.0f },{  95.0f, 5.0f, 125.0f },
											 {  75.0f, 5.0f, 135.0f },{  95.0f, 5.0f, 135.0f },{  75.0f, 5.0f, 145.0f },{  95.0f, 5.0f, 145.0f },
											 {   5.0f, 5.0f,   5.0f },{  15.0f, 5.0f,   5.0f },{  25.0f, 5.0f,   5.0f },{  35.0f, 5.0f,   5.0f },
											 {  45.0f, 5.0f,   5.0f },{  55.0f, 5.0f,   5.0f },{  65.0f, 5.0f,   5.0f },{  75.0f, 5.0f,   5.0f },
											 {  85.0f, 5.0f,   5.0f },{  95.0f, 5.0f,   5.0f },{ 105.0f, 5.0f,   5.0f },{ 115.0f, 5.0f,   5.0f },
											 { 125.0f, 5.0f,   5.0f },{ 135.0f, 5.0f,   5.0f },{ 145.0f, 5.0f,   5.0f },{ 155.0f, 5.0f,   5.0f },
											 {   5.0f, 5.0f,   5.0f },{   5.0f, 5.0f,  15.0f },{   5.0f, 5.0f,  25.0f },{   5.0f, 5.0f,  35.0f },
											 {   5.0f, 5.0f,  45.0f },{   5.0f, 5.0f,  55.0f },{   5.0f, 5.0f,  65.0f },{   5.0f, 5.0f,  75.0f },
											 {   5.0f, 5.0f,  85.0f },{   5.0f, 5.0f,  95.0f },{   5.0f, 5.0f, 105.0f },{   5.0f, 5.0f, 115.0f },
											 {   5.0f, 5.0f, 125.0f },{   5.0f, 5.0f, 135.0f },{   5.0f, 5.0f, 145.0f },{   5.0f, 5.0f, 155.0f },
											 {   5.0f, 5.0f, 155.0f },{  15.0f, 5.0f, 155.0f },{  25.0f, 5.0f, 155.0f },{  35.0f, 5.0f, 155.0f },
											 {  45.0f, 5.0f, 155.0f },{  55.0f, 5.0f, 155.0f },{  65.0f, 5.0f, 155.0f },{  75.0f, 5.0f, 155.0f },
											 {  85.0f, 5.0f, 155.0f },{  95.0f, 5.0f, 155.0f },{ 105.0f, 5.0f, 155.0f },{ 115.0f, 5.0f, 155.0f },
											 { 125.0f, 5.0f, 155.0f },{ 135.0f, 5.0f, 155.0f },{ 145.0f, 5.0f, 155.0f },{ 155.0f, 5.0f, 155.0f },
											 { 165.0f, 5.0f, 155.0f },{ 165.0f, 5.0f, 145.0f },{ 165.0f, 5.0f, 135.0f },{ 165.0f, 5.0f, 125.0f },
											 { 165.0f, 5.0f, 115.0f },{ 165.0f, 5.0f,   5.0f },{  85.0f, 5.0f, 115.0f } };



	wallDetails level2walls2[kNumLevel2Walls] = { {  5.0f,  5.0f,   5.0f },{ 15.0f,  5.0f,   5.0f },{ 25.0f,  5.0f,   5.0f },{ 35.0f,  5.0f,   5.0f },
												  { 45.0f,  5.0f,   5.0f },{ 45.0f,  5.0f,  15.0f },{ 45.0f,  5.0f,  25.0f },{ 45.0f,  5.0f,  35.0f },
												  { 45.0f,  5.0f,  45.0f },{ 45.0f,  5.0f,  55.0f },{ 45.0f,  5.0f,  65.0f },{ 45.0f,  5.0f,  75.0f },
                                                  { 45.0f,  5.0f,  85.0f },{ 45.0f,  5.0f,  95.0f },{ 45.0f,  5.0f, 115.0f },{ 45.0f,  5.0f, 125.0f },
	                                              { 45.0f,  5.0f, 135.0f },{ 45.0f,  5.0f, 145.0f },{ 45.0f,  5.0f, 155.0f },{ 55.0f,  5.0f, 155.0f },
                                                  { 65.0f,  5.0f, 155.0f },{ 75.0f,  5.0f, 155.0f },{ 85.0f,  5.0f, 155.0f },{ 95.0f,  5.0f, 155.0f },
                                                  { 105.0f, 5.0f, 155.0f },{ 115.0f, 5.0f, 155.0f },{ 115.0f, 5.0f, 165.0f },{ 115.0f, 5.0f, 175.0f },
	                                              { 115.0f, 5.0f, 185.0f },{ 115.0f, 5.0f, 195.0f },{ 115.0f, 5.0f, 205.0f },{ 115.0f, 5.0f, 215.0f },
                                                  { 115.0f, 5.0f, 225.0f },{ 115.0f, 5.0f, 235.0f },{ 115.0f, 5.0f, 245.0f },{ 115.0f, 5.0f, 255.0f },
	                                              { 115.0f, 5.0f, 275.0f },{ 115.0f, 5.0f, 285.0f },{ 115.0f, 5.0f, 295.0f },{ 115.0f, 5.0f, 305.0f },
                                                  { 105.0f, 5.0f, 305.0f },{ 95.0f,  5.0f,  305.0f },
 { 85.0f,  5.0f,  305.0f },
 { 75.0f,  5.0f,  305.0f },
 { 65.0f,  5.0f,  305.0f },
 { 55.0f,  5.0f,  305.0f },
 { 45.0f,  5.0f,  305.0f },
 { 35.0f,  5.0f,  305.0f },
 { 25.0f,  5.0f,  305.0f },
 { 15.0f,  5.0f,  305.0f },
 { 5.0f,  5.0f,  305.0f },
 { 5.0f,  5.0f,  295.0f },
 { 5.0f,  5.0f,  285.0f },
 { 5.0f,  5.0f,  275.0f },
 { 5.0f,  5.0f,  265.0f },
 { 5.0f,  5.0f,  255.0f },
 { 5.0f,  5.0f,  245.0f },
 { 5.0f,  5.0f,  235.0f },
 { 5.0f,  5.0f,  225.0f },
 { 5.0f,  5.0f,  215.0f },
 { 5.0f,  5.0f,  205.0f },
 { 5.0f,  5.0f,  195.0f },
 { 5.0f,  5.0f,  185.0f },
 { 5.0f,  5.0f,  175.0f },
 { 5.0f,  5.0f,  165.0f },
 { 5.0f,  5.0f,  155.0f },
 { 5.0f,  5.0f,  145.0f },
 { 5.0f,  5.0f,  135.0f },
 { 5.0f,  5.0f,  125.0f },
 { 5.0f,  5.0f,  115.0f },
 { 5.0f,  5.0f,  105.0f },
 { 5.0f,  5.0f,  95.0f },
 { 5.0f,  5.0f,  85.0f },
 { 5.0f,  5.0f,  75.0f },
 { 5.0f,  5.0f,  65.0f },
 { 5.0f,  5.0f,  55.0f },
 { 5.0f,  5.0f,  45.0f },
 { 5.0f,  5.0f,  35.0f },
 { 5.0f,  5.0f,  25.0f },
 { 5.0f,  5.0f,  15.0f },
 { 15.0f,  5.0f,  195.0f },
 { 25.0f,  5.0f,  195.0f },
 { 35.0f,  5.0f,  195.0f },
 { 45.0f,  5.0f,  195.0f },
 { 55.0f,  5.0f,  195.0f },
 { 65.0f,  5.0f,  195.0f },
 { 75.0f,  5.0f,  195.0f },
 { 75.0f,  5.0f,  205.0f },
 { 75.0f,  5.0f,  215.0f },
 { 75.0f,  5.0f,  225.0f },
 { 75.0f,  5.0f,  235.0f },
 { 75.0f,  5.0f,  245.0f },
 { 75.0f,  5.0f,  255.0f },
 { 75.0f,  5.0f,  265.0f },
 { 65.0f,  5.0f,  265.0f },
 { 55.0f,  5.0f,  265.0f },
 { 45.0f,  5.0f,  265.0f },
 { 35.0f,  5.0f,  265.0f },
 { 35.0f,  5.0f,  255.0f },
 { 35.0f,  5.0f,  245.0f },
 { 35.0f,  5.0f,  235.0f },
 { 35.0f,  5.0f,  225.0f },
 { 45.0f,  5.0f,  225.0f },
 { 65.0f,  5.0f,  225.0f },
 { 115.0f,  5.0f,  145.0f },
 { 115.0f,  5.0f,  135.0f },
 { 115.0f,  5.0f,  125.0f },
 { 115.0f,  5.0f,  115.0f },
 { 115.0f,  5.0f,  105.0f },
 { 115.0f,  5.0f,  95.0f },
 { 115.0f,  5.0f,  85.0f },
 { 115.0f,  5.0f,  75.0f },
 { 125.0f,  5.0f,  75.0f },
 { 135.0f,  5.0f,  75.0f },
 { 135.0f,  5.0f,  65.0f },
 { 135.0f,  5.0f,  45.0f },
 { 135.0f,  5.0f,  35.0f },
 { 125.0f,  5.0f,  35.0f },
 { 115.0f,  5.0f,  35.0f },
 { 105.0f,  5.0f,  35.0f },
 { 95.0f,  5.0f,  35.0f },
 { 85.0f,  5.0f,  35.0f },
 { 75.0f,  5.0f,  35.0f },
 { 75.0f,  5.0f,  45.0f },
 { 75.0f,  5.0f,  55.0f },
 { 75.0f,  5.0f,  65.0f },
 { 75.0f,  5.0f,  75.0f },
 { 85.0f,  5.0f,  75.0f },
 { 95.0f,  5.0f,  75.0f },
 { 105.0f,  5.0f,  75.0f },
 { 55.0f,  5.0f,  5.0f },
 { 65.0f,  5.0f,  5.0f },
 { 75.0f,  5.0f,  5.0f },
 { 85.0f,  5.0f,  5.0f },
 { 95.0f,  5.0f,  5.0f },
 { 105.0f,  5.0f,  5.0f },
 { 115.0f,  5.0f,  5.0f },
 { 125.0f,  5.0f,  5.0f },
 { 135.0f,  5.0f,  5.0f },
 { 145.0f,  5.0f,  5.0f },
 { 155.0f,  5.0f,  5.0f },
 { 165.0f,  5.0f,  5.0f },
 { 175.0f,  5.0f,  5.0f },
 { 175.0f,  5.0f,  15.0f },
 { 175.0f,  5.0f,  25.0f },
 { 175.0f,  5.0f,  35.0f },
 { 175.0f,  5.0f,  45.0f },
 { 125.0f,  5.0f,  155.0f },
 { 135.0f,  5.0f,  155.0f },
 { 155.0f,  5.0f,  155.0f },
 { 165.0f,  5.0f,  155.0f },
 { 175.0f,  5.0f,  155.0f },
 { 175.0f,  5.0f,  145.0f },
 { 175.0f,  5.0f,  135.0f },
 { 175.0f,  5.0f,  125.0f },
 { 175.0f,  5.0f,  115.0f },
 { 175.0f,  5.0f,  105.0f },
 { 175.0f,  5.0f,  95.0f },
 { 175.0f,  5.0f,  85.0f },
 { 175.0f,  5.0f,  75.0f },
 { 175.0f,  5.0f,  65.0f },
 { 175.0f,  5.0f,  55.0f },
 { 175.0f,  5.0f,  165.0f },
 { 175.0f,  5.0f,  175.0f },
 { 175.0f,  5.0f,  185.0f },
 { 175.0f,  5.0f,  195.0f },
 { 175.0f,  5.0f,  205.0f },
 { 175.0f,  5.0f,  215.0f },
 { 175.0f,  5.0f,  225.0f },
 { 165.0f,  5.0f,  225.0f },
 { 155.0f,  5.0f,  225.0f },
 { 135.0f,  5.0f,  225.0f },
 { 125.0f,  5.0f,  225.0f },
 { 115.0f,  5.0f,  265.0f },
 { 175.0f,  5.0f,  235.0f },
 { 175.0f,  5.0f,  245.0f },
 { 175.0f,  5.0f,  255.0f },
 { 175.0f,  5.0f,  265.0f },
 { 175.0f,  5.0f,  275.0f },
 { 175.0f,  5.0f,  285.0f },
 { 175.0f,  5.0f,  295.0f },
 { 175.0f,  5.0f,  305.0f },
 { 175.0f,  5.0f,  315.0f },
 { 175.0f,  5.0f,  325.0f },
 { 175.0f,  5.0f,  335.0f },
 { 175.0f,  5.0f,  345.0f },
 { 175.0f,  5.0f,  395.0f },
 { 175.0f,  5.0f,  385.0f },
 { 175.0f,  5.0f,  375.0f },
 { 175.0f,  5.0f,  365.0f },
 { 185.0f,  5.0f,  395.0f },
 { 195.0f,  5.0f,  395.0f },
 { 205.0f,  5.0f,  395.0f },
 { 215.0f,  5.0f,  395.0f },
 { 225.0f,  5.0f,  395.0f },
 { 235.0f,  5.0f,  395.0f },
 { 245.0f,  5.0f,  395.0f },
 { 255.0f,  5.0f,  395.0f },
 { 265.0f,  5.0f,  395.0f },
 { 275.0f,  5.0f,  395.0f },
 { 285.0f,  5.0f,  395.0f },
 { 295.0f,  5.0f,  395.0f },
 { 305.0f,  5.0f,  395.0f },
 { 315.0f,  5.0f,  395.0f },
 { 325.0f,  5.0f,  395.0f },
 { 335.0f,  5.0f,  395.0f },
 { 185.0f,  5.0f,  315.0f },
 { 195.0f,  5.0f,  315.0f },
 { 205.0f,  5.0f,  315.0f },
 { 215.0f,  5.0f,  315.0f },
 { 225.0f,  5.0f,  315.0f },
 { 235.0f,  5.0f,  315.0f },
 { 245.0f,  5.0f,  315.0f },
 { 255.0f,  5.0f,  315.0f },
 { 265.0f,  5.0f,  315.0f },
 { 275.0f,  5.0f,  315.0f },
 { 285.0f,  5.0f,  315.0f },
 { 295.0f,  5.0f,  315.0f },
 { 305.0f,  5.0f,  315.0f },
 { 315.0f,  5.0f,  315.0f },
 { 325.0f,  5.0f,  315.0f },
 { 335.0f,  5.0f,  315.0f },
 { 345.0f,  5.0f,  315.0f },
 { 355.0f,  5.0f,  315.0f },
 { 345.0f,  5.0f,  395.0f },
 { 355.0f,  5.0f,  395.0f },
 { 365.0f,  5.0f,  395.0f },
 { 365.0f,  5.0f,  385.0f },
 { 365.0f,  5.0f,  375.0f },
 { 365.0f,  5.0f,  365.0f },
 { 365.0f,  5.0f,  345.0f },
 { 365.0f,  5.0f,  335.0f },
 { 365.0f,  5.0f,  325.0f },
 { 365.0f,  5.0f,  315.0f },
 { 375.0f,  5.0f,  395.0f },
 { 385.0f,  5.0f,  395.0f },
 { 395.0f,  5.0f,  395.0f },
 { 395.0f,  5.0f,  385.0f },
 { 395.0f,  5.0f,  375.0f },
 { 395.0f,  5.0f,  365.0f },
 { 395.0f,  5.0f,  355.0f },
 { 395.0f,  5.0f,  345.0f },
 { 395.0f,  5.0f,  335.0f },
 { 395.0f,  5.0f,  325.0f },
 { 395.0f,  5.0f,  315.0f },
 { 395.0f,  5.0f,  305.0f },
 { 395.0f,  5.0f,  295.0f },
 { 395.0f,  5.0f,  285.0f },
 { 395.0f,  5.0f,  275.0f },
 { 5.0f,  5.0f,  315.0f },
 { 5.0f,  5.0f,  325.0f },
 { 5.0f,  5.0f,  335.0f },
 { 5.0f,  5.0f,  345.0f },
 { 5.0f,  5.0f,  355.0f },
 { 5.0f,  5.0f,  365.0f },
 { 5.0f,  5.0f,  375.0f },
 { 5.0f,  5.0f,  385.0f },
 { 5.0f,  5.0f,  395.0f },
 { 15.0f,  5.0f,  395.0f },
 { 25.0f,  5.0f,  395.0f },
 { 35.0f,  5.0f,  395.0f },
 { 45.0f,  5.0f,  395.0f },
 { 55.0f,  5.0f,  395.0f },
 { 65.0f,  5.0f,  395.0f },
 { 75.0f,  5.0f,  395.0f },
 { 85.0f,  5.0f,  395.0f },
 { 95.0f,  5.0f,  395.0f },
 { 105.0f,  5.0f,  395.0f },
 { 115.0f,  5.0f,  395.0f },
 { 125.0f,  5.0f,  395.0f },
 { 135.0f,  5.0f,  395.0f },
 { 145.0f,  5.0f,  395.0f },
 { 155.0f,  5.0f,  395.0f },
 { 165.0f,  5.0f,  395.0f },
 { 395.0f,  5.0f,  265.0f },
 { 385.0f,  5.0f,  265.0f },
 { 375.0f,  5.0f,  265.0f },
 { 355.0f,  5.0f,  265.0f },
 { 345.0f,  5.0f,  265.0f },
 { 335.0f,  5.0f,  265.0f },
 { 335.0f,  5.0f,  255.0f },
 { 395.0f,  5.0f,  255.0f },
 { 325.0f,  5.0f,  265.0f },
 { 315.0f,  5.0f,  265.0f },
 { 295.0f,  5.0f,  265.0f },
 { 285.0f,  5.0f,  265.0f },
 { 275.0f,  5.0f,  265.0f },
 { 265.0f,  5.0f,  265.0f },
 { 255.0f,  5.0f,  265.0f },
 { 235.0f,  5.0f,  265.0f },
 { 225.0f,  5.0f,  265.0f },
 { 215.0f,  5.0f,  265.0f },
 { 275.0f,  5.0f,  255.0f },
 { 215.0f,  5.0f,  255.0f },
 { 215.0f,  5.0f,  235.0f },
 { 215.0f,  5.0f,  245.0f },
 { 215.0f,  5.0f,  225.0f },
 { 215.0f,  5.0f,  215.0f },
 { 215.0f,  5.0f,  205.0f },
 { 215.0f,  5.0f,  195.0f },
 { 215.0f,  5.0f,  185.0f },
 { 215.0f,  5.0f,  175.0f },
 { 225.0f,  5.0f,  175.0f },
 { 235.0f,  5.0f,  175.0f },
 { 245.0f,  5.0f,  175.0f },
 { 255.0f,  5.0f,  175.0f },
 { 265.0f,  5.0f,  175.0f },
 { 275.0f,  5.0f,  175.0f },
 { 275.0f,  5.0f,  185.0f },
 { 275.0f,  5.0f,  195.0f },
 { 275.0f,  5.0f,  205.0f },
 { 275.0f,  5.0f,  215.0f },
 { 275.0f,  5.0f,  225.0f },
 { 275.0f,  5.0f,  235.0f },
 { 275.0f,  5.0f,  245.0f },
 { 285.0f,  5.0f,  175.0f },
 { 295.0f,  5.0f,  175.0f },
 { 305.0f,  5.0f,  175.0f },
 { 315.0f,  5.0f,  175.0f },
 { 325.0f,  5.0f,  175.0f },
 { 335.0f,  5.0f,  175.0f },
 { 335.0f,  5.0f,  185.0f },
 { 335.0f,  5.0f,  195.0f },
 { 335.0f,  5.0f,  205.0f },
 { 335.0f,  5.0f,  215.0f },
 { 335.0f,  5.0f,  225.0f },
 { 335.0f,  5.0f,  235.0f },
 { 335.0f,  5.0f,  245.0f },
 { 345.0f,  5.0f,  175.0f },
 { 355.0f,  5.0f,  175.0f },
 { 365.0f,  5.0f,  175.0f },
 { 375.0f,  5.0f,  175.0f },
 { 385.0f,  5.0f,  175.0f },
 { 395.0f,  5.0f,  175.0f },
 { 395.0f,  5.0f,  185.0f },
 { 395.0f,  5.0f,  195.0f },
 { 395.0f,  5.0f,  205.0f },
 { 395.0f,  5.0f,  215.0f },
 { 395.0f,  5.0f,  225.0f },
 { 395.0f,  5.0f,  235.0f },
 { 395.0f,  5.0f,  245.0f },
 { 185.0f,  5.0f,  135.0f },
 { 195.0f,  5.0f,  135.0f },
 { 205.0f,  5.0f,  135.0f },
 { 215.0f,  5.0f,  135.0f },
 { 225.0f,  5.0f,  135.0f },
 { 235.0f,  5.0f,  135.0f },
 { 245.0f,  5.0f,  135.0f },
 { 255.0f,  5.0f,  135.0f },
 { 265.0f,  5.0f,  135.0f },
 { 275.0f,  5.0f,  135.0f },
 { 285.0f,  5.0f,  135.0f },
 { 295.0f,  5.0f,  135.0f },
 { 305.0f,  5.0f,  135.0f },
 { 315.0f,  5.0f,  135.0f },
 { 325.0f,  5.0f,  135.0f },
 { 335.0f,  5.0f,  135.0f },
 { 345.0f,  5.0f,  135.0f },
 { 355.0f,  5.0f,  135.0f },
 { 365.0f,  5.0f,  135.0f },
 { 385.0f,  5.0f,  135.0f },
 { 395.0f,  5.0f,  135.0f },
{ 395.0f,  5.0f,  125.0f },
 { 395.0f,  5.0f,  115.0f },
 { 395.0f,  5.0f,  105.0f },
 { 395.0f,  5.0f,  95.0f },
 { 395.0f,  5.0f,  85.0f },
 { 395.0f,  5.0f,  75.0f },
 { 395.0f,  5.0f,  65.0f },
 { 395.0f,  5.0f,  55.0f },
 { 395.0f,  5.0f,  45.0f },
 { 395.0f,  5.0f,  35.0f },
 { 395.0f,  5.0f,  25.0f },
 { 395.0f,  5.0f,  15.0f },
 { 395.0f,  5.0f,  5.0f },
 { 385.0f,  5.0f,  5.0f },
 { 375.0f,  5.0f,  5.0f },
 { 365.0f,  5.0f,  5.0f },
 { 355.0f,  5.0f,  5.0f },
 { 345.0f,  5.0f,  5.0f },
 { 335.0f,  5.0f,  5.0f },
 { 325.0f,  5.0f,  5.0f },
 { 315.0f,  5.0f,  5.0f },
 { 305.0f,  5.0f,  5.0f },
 { 295.0f,  5.0f,  5.0f },
 { 285.0f,  5.0f,  5.0f },
 { 275.0f,  5.0f,  5.0f },
 { 265.0f,  5.0f,  5.0f },
 { 255.0f,  5.0f,  5.0f },
 { 245.0f,  5.0f,  5.0f },
 { 235.0f,  5.0f,  5.0f },
 { 225.0f,  5.0f,  5.0f },
 { 215.0f,  5.0f,  5.0f },
 { 205.0f,  5.0f,  5.0f },
 { 195.0f,  5.0f,  5.0f },
 { 185.0f,  5.0f,  5.0f },
 { 395.0f,  5.0f,  165.0f },
 { 395.0f,  5.0f,  155.0f },
 { 395.0f,  5.0f,  145.0f },
 { 335.0f,  5.0f,  165.0f },
 { 335.0f,  5.0f,  145.0f },
 { 195.0f,  5.0f,  115.0f },
 { 195.0f,  5.0f,  125.0f },
 { 185.0f,  5.0f,  115.0f },

 };

	
	enemyWaypoints enemyPositions2[kNumLevel1Zombies] = { {15.0f, 11.5f, 45.0f}, {125.0f, 11.5f, 75.0f}, {15.0f, 11.5f, 145.0f}, {105.0f, 11.5f, 145.0f} };
	for (int i = 0; i < kNumLevel1Zombies; i++)enemyPositions[i] = enemyPositions2[i];

	enemyWaypoints enemyPositionsTwo2[4] = { { 15.0f,15.0f,185.0f },{ 85.0f,15.0f,205.0f },{ 15.0f,15.0f,295.0f },{ 60.0f,15.0f,140.0f } };
	for (int i = 0; i < 4; i++)enemyPositionsTwo[i] = enemyPositionsTwo2[i];

	enemyWaypoints dummyWayPointsCooridnates2[kNumLevel1Zombies * 4] = { {  15.0f, 15.0f,  45.0f},{  75.0f, 15.0f,  45.0f},{  75.0f, 15.0f,  15.0f},{  15.0f, 15.0f,  15.0f},
	                                                                    { 125.0f, 15.0f,  75.0f},{ 155.0f, 15.0f,  75.0f},{ 155.0f, 15.0f,  15.0f},{ 125.0f, 15.0f,  15.0f},
	                                                                    {  15.0f, 15.0f, 145.0f},{  65.0f, 15.0f, 145.0f},{  65.0f, 15.0f, 125.0f},{  15.0f, 15.0f, 125.0f},
	                                                                    { 105.0f, 15.0f, 145.0f},{ 145.0f, 15.0f, 145.0f},{ 145.0f, 15.0f, 125.0f},{ 105.0f, 15.0f, 125.0f}};

	enemyWaypoints dummyWayPointsCoordinatesLvl2[16] = { {15.0f,15.0f,185.0f},{35.0f,15.0f,185.0f},{35.0f,15.0f,165.0f},{15.0f,15.0f,165.0f},
	{85.0f,15.0f,205.0f},{105.0f,15.0f,205.0f},{105.0f,15.0f,165.0f},{85.0f,15.0f,165.0f},
	{15.0f,15.0f,295.0f},{25.0f,15.0f,295.0f},{25.0f,15.0f,205.0f},{15.0f,15.0f,205.0f},
	{60.0f,15.0f,140.0f},{95.0f,15.0f,140.0f},{95.0f,15.0f,90.0f}, {60.0f,15.0f,90.0f} };

	for (int i = 0; i < 16; i++)dummyWayPointsTwoCooridnates[i] = dummyWayPointsCoordinatesLvl2[i];

	for (int i = 0; i < kNumLevel1Zombies *4; i++)dummyWayPointsCooridnates[i] = dummyWayPointsCooridnates2[i];


	bulletDetails  level1BulletDetails[kNumBullets] = { {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f} };

	

	string enemyStartSkins2[kNumLevel1Zombies] = { "zombie1WalkLeft1.png" ,"zombie1WalkLeft1.png" ,"zombie2WalkLeft1.png", "zombie3WalkLeft1.png" };
	for (int i = 0; i < kNumLevel1Zombies; i++)enemyStartSkins[i] = enemyStartSkins2[i];
	for (int i = 0; i < kNumLevel1Walls; i++)
	{
		level1walls[i] = level1walls2[i];
	}
	for (int i = 0; i < kNumLevel2Walls; i++)
	{
		level2walls[i] = level2walls2[i];
	}



	string enemySkinOneLeft2[kNumberOfFrames]{ "zombie1WalkLeft2.png" ,"zombie1WalkLeft3.png" ,"zombie1WalkLeft4.png" ,"zombie1WalkLeft5.png" ,"zombie1WalkLeft6.png" ,
		"zombie1WalkLeft7.png" ,"zombie1WalkLeft8.png","zombie1WalkLeft9.png","zombie1WalkLeft10.png","zombie1WalkLeft11.png","zombie1WalkLeft12.png","zombie1WalkLeft13.png",
		"zombie1WalkLeft14.png","zombie1WalkLeft15.png","zombie1WalkLeft16.png","zombie1WalkLeft17.png","zombie1WalkLeft18.png" };

	string enemySkinOneRight2[kNumberOfFrames]{ "zombie1WalkRight2.png" ,"zombie1WalkRight3.png" ,"zombie1WalkRight4.png" ,"zombie1WalkRight5.png" ,"zombie1WalkRight6.png" ,
		"zombie1WalkRight7.png" ,"zombie1WalkRight8.png","zombie1WalkRight9.png","zombie1WalkRight10.png","zombie1WalkRight11.png","zombie1WalkRight12.png",
		"zombie1WalkRight13.png","zombie1WalkRight14.png","zombie1WalkRight15.png","zombie1WalkRight16.png","zombie1WalkRight17.png","zombie1WalkRight18.png" };

	string enemySkinTwoLeft2[kNumberOfFrames]{ "zombie1WalkLeft2.png" ,"zombie1WalkLeft3.png" ,"zombie1WalkLeft4.png" ,"zombie1WalkLeft5.png" ,"zombie1WalkLeft6.png" ,
		"zombie1WalkLeft7.png" ,"zombie1WalkLeft8.png","zombie1WalkLeft9.png","zombie1WalkLeft10.png","zombie1WalkLeft11.png","zombie1WalkLeft12.png","zombie1WalkLeft13.png",
		"zombie1WalkLeft14.png","zombie1WalkLeft15.png","zombie1WalkLeft16.png","zombie1WalkLeft17.png","zombie1WalkLeft18.png" };

	string enemySkinTwoRight2[kNumberOfFrames]{ "zombie1WalkRight2.png" ,"zombie1WalkRight3.png" ,"zombie1WalkRight4.png" ,"zombie1WalkRight5.png" ,"zombie1WalkRight6.png" ,
		"zombie1WalkRight7.png" ,"zombie1WalkRight8.png","zombie1WalkRight9.png","zombie1WalkRight10.png","zombie1WalkRight11.png","zombie1WalkRight12.png",
		"zombie1WalkRight13.png","zombie1WalkRight14.png","zombie1WalkRight15.png","zombie1WalkRight16.png","zombie1WalkRight17.png","zombie1WalkRight18.png" };

	string enemySkinThreeLeft2[kNumberOfFrames]{ "zombie2WalkLeft2.png" ,"zombie2WalkLeft3.png" ,"zombie2WalkLeft4.png" ,"zombie2WalkLeft5.png" ,"zombie2WalkLeft6.png" ,
		"zombie2WalkLeft7.png" ,"zombie2WalkLeft8.png","zombie2WalkLeft9.png","zombie2WalkLeft10.png","zombie2WalkLeft11.png","zombie2WalkLeft12.png","zombie2WalkLeft13.png",
		"zombie2WalkLeft14.png","zombie2WalkLeft15.png","zombie2WalkLeft16.png","zombie2WalkLeft17.png","zombie2WalkLeft18.png" };

	string enemySkinThreeRight2[kNumberOfFrames]{ "zombie2WalkRight2.png" ,"zombie2WalkRight3.png" ,"zombie2WalkRight4.png" ,"zombie2WalkRight5.png" ,"zombie2WalkRight6.png" ,
		"zombie2WalkRight7.png" ,"zombie2WalkRight8.png","zombie2WalkRight9.png","zombie2WalkRight10.png","zombie2WalkRight11.png","zombie2WalkRight12.png",
		"zombie2WalkRight13.png","zombie2WalkRight14.png","zombie2WalkRight15.png","zombie2WalkRight16.png","zombie2WalkRight17.png","zombie2WalkRight18.png" };

	string enemySkinFourLeft2[kNumberOfFrames]{ "zombie3WalkLeft2.png" ,"zombie3WalkLeft3.png" ,"zombie3WalkLeft4.png" ,"zombie3WalkLeft5.png" ,"zombie3WalkLeft6.png" ,
		"zombie3WalkLeft7.png" ,"zombie3WalkLeft8.png","zombie3WalkLeft9.png","zombie3WalkLeft10.png","zombie3WalkLeft11.png","zombie3WalkLeft12.png","zombie3WalkLeft13.png",
		"zombie3WalkLeft14.png","zombie3WalkLeft15.png","zombie3WalkLeft16.png","zombie3WalkLeft17.png","zombie3WalkLeft18.png" };

	string enemySkinFourRight2[kNumberOfFrames]{ "zombie3WalkRight2.png" ,"zombie3WalkRight3.png" ,"zombie3WalkRight4.png" ,"zombie3WalkRight5.png" ,"zombie3WalkRight6.png" ,
		"zombie3WalkRight7.png" ,"zombie3WalkRight8.png","zombie3WalkRight9.png","zombie3WalkRight10.png","zombie3WalkRight11.png","zombie3WalkRight12.png",
		"zombie3WalkRight13.png","zombie3WalkRight14.png","zombie3WalkRight15.png","zombie3WalkRight16.png","zombie3WalkRight17.png","zombie3WalkRight18.png" };

	for (int i = 0; i < kNumLevel1Zombies; i++)
	{
		for (int j = 0; j < kNumberOfFrames; j++)
		{
			if (i == 0)
			{
				enemySkinsLeft[i][j] = enemySkinOneLeft2[j];
				enemySkinsRight[i][j] = enemySkinOneRight2[j];
			}

			if (i == 1)
			{
				enemySkinsLeft[i][j] = enemySkinTwoLeft2[j];
				enemySkinsRight[i][j] = enemySkinTwoRight2[j];
			}

			if (i == 2)
			{
				enemySkinsLeft[i][j] = enemySkinThreeLeft2[j];
				enemySkinsRight[i][j] = enemySkinThreeRight2[j];
			}

			if (i == 3)
			{
				enemySkinsLeft[i][j] = enemySkinFourLeft2[j];
				enemySkinsRight[i][j] = enemySkinFourRight2[j];
			}
		}
	}
	
}