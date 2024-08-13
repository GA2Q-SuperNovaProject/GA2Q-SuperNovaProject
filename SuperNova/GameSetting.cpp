#include "GameSetting.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "SoundManager.h"
#include "EnumDefine.h"
#include "Debug.h"
#include "GameObject.h"
#include "GameManager.h"
#include "Scene.h"

GameSetting::GameSetting()
{

}

GameSetting::~GameSetting()
{

}

void GameSetting::ReadyAllScene()
{
	/// Object 작성 시, Position은 무조건 월드 좌표로 작성할 것
	/// 월드 좌표란, 배경(4800x4800)에 맞게 놓여지는 좌표(예: Player가 배경 중심에 나와야 한다 -> (2400,2400))
	/// *** 카메라 미사용 씬(예: 게임시작 화면) 제외

	ReadySound();

	// MainScene 준비	
	ReadyMainScene();

	// Stage1 준비
	ReadyStage1Scene();
	ReadyStage2Scene();
	ReadyStage3Scene();

	// Planet 준비
	ReadySnakePlanetScene();
	ReadyStoryPlanetScene();

	// Opening 준비
	ReadyOpeningScene();

	// Normal Ending 준비
	ReadyNormalScene();

	// Bad Ending 준비
	ReadyBadScene();

	// True Ending 준비
	ReadyTrueScene();

	// TaewookScene 준비
	//ReadyTaewookScene();
}

void GameSetting::ReadyMainScene()
{
	GameObject* mainBG = ObjectManager::GetInstance().CreateObject(eObjectTag::BACKGROUND, eObjectName::MAIN_BACKGROUND,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));

	GameObject* start = ObjectManager::GetInstance().CreateObject(eObjectTag::MAIN_UI, eObjectName::START_BUTTON,
		Transform(Vec2(960, 450), 0.0f, Vec2(1, 1)));

	GameObject* option = ObjectManager::GetInstance().CreateObject(eObjectTag::MAIN_UI, eObjectName::OPTION_BUTTON,
		Transform(Vec2(960, 677), 0.0f, Vec2(1, 1)));

	GameObject* credit = ObjectManager::GetInstance().CreateObject(eObjectTag::MAIN_UI, eObjectName::CREDIT_BUTTON,
		Transform(Vec2(960, 904), 0.0f, Vec2(1, 1)));

	GameObject* quit = ObjectManager::GetInstance().CreateObject(eObjectTag::MAIN_UI, eObjectName::QUIT_BUTTON,
		Transform(Vec2(157, 957), 0.0f, Vec2(1, 1)));

	GameObject* optionMenu = ObjectManager::GetInstance().CreateObject(eObjectTag::OPTION_UI, eObjectName::OPTION_MENU,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));

	GameObject* optionBarB = ObjectManager::GetInstance().CreateObject(eObjectTag::OPTION_UI, eObjectName::OPTION_BAR,
		Transform(Vec2(1074, 340), 0.0f, Vec2(1, 1)));

	GameObject* optionBarS = ObjectManager::GetInstance().CreateObject(eObjectTag::OPTION_UI, eObjectName::OPTION_BAR,
		Transform(Vec2(1074, 431), 0.0f, Vec2(1, 1)));

	GameObject* optionBoxB = ObjectManager::GetInstance().CreateObject(eObjectTag::OPTION_UI, eObjectName::OPTION_BGMBOX,
		Transform(Vec2(1074, 340), 0.0f, Vec2(1, 1)));

	GameObject* optionBoxS = ObjectManager::GetInstance().CreateObject(eObjectTag::OPTION_UI, eObjectName::OPTION_SOUNDBOX,
		Transform(Vec2(1074, 431), 0.0f, Vec2(1, 1)));

	GameObject* optionQuit = ObjectManager::GetInstance().CreateObject(eObjectTag::OPTION_UI, eObjectName::OPTION_QUIT,
		Transform(Vec2(1258, 237), 0.0f, Vec2(1, 1)));

	Scene* mainScene = SceneManager::GetInstance().CreateScene(eSceneName::MAIN);
	Scene* MainOption = SceneManager::GetInstance().CreateScene(eSceneName::MAIN_OPTION);

	// MAIN SCENE
	SceneManager::GetInstance().PutObjectInScene(mainScene, mainBG);
	SceneManager::GetInstance().PutObjectInScene(mainScene, start);
	SceneManager::GetInstance().PutObjectInScene(mainScene, option);
	SceneManager::GetInstance().PutObjectInScene(mainScene, credit);
	SceneManager::GetInstance().PutObjectInScene(mainScene, quit);

	SceneManager::GetInstance().PutObjectInScene(MainOption, mainBG);
	SceneManager::GetInstance().PutObjectInScene(MainOption, optionMenu);
	SceneManager::GetInstance().PutObjectInScene(MainOption, optionBarB);
	SceneManager::GetInstance().PutObjectInScene(MainOption, optionBarS);
	SceneManager::GetInstance().PutObjectInScene(MainOption, optionBoxB);
	SceneManager::GetInstance().PutObjectInScene(MainOption, optionBoxS);
	SceneManager::GetInstance().PutObjectInScene(MainOption, optionQuit);

	//SetSceneActive를 통해, 해당 씬을 활성화시킴.
	SceneManager::GetInstance().SetSceneActive(mainScene, true);
	SceneManager::GetInstance().SetSceneActive(MainOption, true);

	//SetCurScene을 통해, 현재 씬을 포인터로 넣는다.
	SceneManager::GetInstance().SetCurScene(mainScene);
}

void GameSetting::ReadyOpeningScene()
{
	Scene* opening = SceneManager::GetInstance().CreateScene(eSceneName::OPENING);

	GameObject* opening1 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING1,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* opening2 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING2,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* opening3 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING3,
		Transform(Vec2(512, 332), 0.0f, Vec2(1, 1)));
	GameObject* opening4 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING4,
		Transform(Vec2(1260, 582), 0.0f, Vec2(1, 1)));
	GameObject* opening5 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING5,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));

	GameObject* opening_line1 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING_LINE1,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* opening_line2 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING_LINE2,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* opening_line3 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING_LINE3,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* opening_line4 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING_LINE4,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* opening_line5 = ObjectManager::GetInstance().CreateObject(eObjectTag::OPENING, eObjectName::OPENING_LINE5,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));

	SceneManager::GetInstance().PutObjectInScene(opening, opening1);
	SceneManager::GetInstance().PutObjectInScene(opening, opening2);
	SceneManager::GetInstance().PutObjectInScene(opening, opening3);
	SceneManager::GetInstance().PutObjectInScene(opening, opening4);
	SceneManager::GetInstance().PutObjectInScene(opening, opening5);
	SceneManager::GetInstance().PutObjectInScene(opening, opening_line1);
	SceneManager::GetInstance().PutObjectInScene(opening, opening_line2);
	SceneManager::GetInstance().PutObjectInScene(opening, opening_line3);
	SceneManager::GetInstance().PutObjectInScene(opening, opening_line4);
	SceneManager::GetInstance().PutObjectInScene(opening, opening_line5);

	SceneManager::GetInstance().SetSceneActive(opening, true);

}

void GameSetting::ReadyStage1Scene()
{
	GameObject* background = ObjectManager::GetInstance().CreateObject(eObjectTag::BACKGROUND, eObjectName::STAGE1_BACKGROUND,
		Transform(Vec2(2400, 3600), 0.0f, Vec2(1, 1)));

	GameObject* player = ObjectManager::GetInstance().CreateObject(eObjectTag::PLAYER, eObjectName::PLAYER,
		Transform(Vec2(995, 6793), 0.0f, Vec2(0.25, 0.25)));
	player->PutCollider(eColType::BOX, IMAGE_PLAYER); //콜라이더 넣은 거임
	player->SetColState(true);
	player->PutBody(3); //플레이어에 물리력이 작용될 수 있게.
	player->SetPhysicsState(true);

	// Star Piece_1
	GameObject* star1 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(1864, 6291), 0.0f, Vec2(1, 1)));
	star1->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star1->SetColState(true);

	GameObject* star2 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(343, 4033), 0.0f, Vec2(1, 1)));
	star2->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star2->SetColState(true);

	GameObject* star3 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(4307, 2680), 0.0f, Vec2(1, 1)));
	star3->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star3->SetColState(true);

	GameObject* star4 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(4405, 951), 0.0f, Vec2(1, 1)));
	star4->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star4->SetColState(true);

	GameObject* star5 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(3766, 147), 0.0f, Vec2(1, 1)));
	star5->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star5->SetColState(true);

	GameObject* star6 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(493, 851), 0.0f, Vec2(1, 1)));
	star6->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star6->SetColState(true);

	// Star Piece_2
	GameObject* star7 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(197, 6002), 0.0f, Vec2(1, 1)));
	star7->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star7->SetColState(true);

	GameObject* star8 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(4481, 7031), 0.0f, Vec2(1, 1)));
	star8->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star8->SetColState(true);

	GameObject* star9 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(2952, 4059), 0.0f, Vec2(1, 1)));
	star9->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star9->SetColState(true);

	GameObject* star10 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(737, 3518), 0.0f, Vec2(1, 1)));
	star10->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star10->SetColState(true);

	GameObject* star11 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(1402, 1747), 0.0f, Vec2(1, 1)));
	star11->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star11->SetColState(true);

	// Star Piece_3
	GameObject* star12 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(2829, 6002), 0.0f, Vec2(1, 1)));
	star12->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star12->SetColState(true);

	GameObject* star13 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(4595, 6407), 0.0f, Vec2(1, 1)));
	star13->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star13->SetColState(true);

	GameObject* star14 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(2017, 3814), 0.0f, Vec2(1, 1)));
	star14->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star14->SetColState(true);

	GameObject* star15 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(2638, 2301), 0.0f, Vec2(1, 1)));
	star15->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star15->SetColState(true);

	//ITEM
	GameObject* potion1 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(664, 5779), 0.0f, Vec2(1, 1)));
	potion1->PutCollider(eColType::BOX, IMAGE_POTION);
	potion1->SetColState(true);

	GameObject* potion2 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(2399, 5003), 0.0f, Vec2(1, 1)));
	potion2->PutCollider(eColType::BOX, IMAGE_POTION);
	potion2->SetColState(true);

	GameObject* potion3 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(3814, 1369), 0.0f, Vec2(1, 1)));
	potion3->PutCollider(eColType::BOX, IMAGE_POTION);
	potion3->SetColState(true);

	GameObject* potion4 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(158, 370), 0.0f, Vec2(1, 1)));
	potion4->PutCollider(eColType::BOX, IMAGE_POTION);
	potion4->SetColState(true);

	// BlackHole
	GameObject* blackHole1 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(3904, 6457), 0.0f, Vec2(1, 1)));
	blackHole1->PutCollider(eColType::BOX, IMAGE_BLACKHOLE);
	blackHole1->SetColState(true);
	blackHole1->PutBody(1000);

	GameObject* blackHole2 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(1314, 4804), 0.0f, Vec2(1, 1))); // scale
	blackHole2->PutCollider(eColType::BOX, IMAGE_BLACKHOLE);
	blackHole2->SetColState(true);
	blackHole2->PutBody(1000);

	GameObject* blackHole3 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(272, 2630), 0.0f, Vec2(1, 1))); // scale
	blackHole3->PutCollider(eColType::BOX, IMAGE_BLACKHOLE);
	blackHole3->SetColState(true);
	blackHole3->PutBody(1000);

	GameObject* blackHole4 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(3419, 2251), 0.0f, Vec2(1, 1)));
	blackHole4->PutCollider(eColType::CIRCLE, IMAGE_BLACKHOLE);
	blackHole4->SetColState(true);
	blackHole4->PutBody(1000);

	// Portal
	GameObject* portal = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::PORTAL,
		Transform(Vec2(3079, 423), 0.0f, Vec2(1, 1)));
	portal->PutCollider(eColType::BOX, IMAGE_PORTAL);
	portal->SetColState(true);

	// Planet
	GameObject* icePlanet = ObjectManager::GetInstance().CreateObject(eObjectTag::PLANET, eObjectName::ICE_PLANET,
		Transform(Vec2(3945, 3911), 0.0f, Vec2(1, 1)));
	icePlanet->PutCollider(eColType::CIRCLE, IMAGE_ICE_PLANET);
	icePlanet->SetColState(true);
	icePlanet->PutBody(500);

	GameObject* snakePlanet = ObjectManager::GetInstance().CreateObject(eObjectTag::PLANET, eObjectName::SNAKE_PLANET,
		Transform(Vec2(2086, 901), 0.0f, Vec2(1, 1)));
	snakePlanet->PutCollider(eColType::CIRCLE, IMAGE_SNAKE_PLANET);
	snakePlanet->SetColState(true);
	snakePlanet->PutBody(500);

	Scene* stage1 = SceneManager::GetInstance().CreateScene(eSceneName::STAGE1);

	//PutObjectInScene을 통해, 오브젝트들을 해당 씬 안에 넣음.
	SceneManager::GetInstance().PutObjectInScene(stage1, background);

	SceneManager::GetInstance().PutObjectInScene(stage1, star1);
	SceneManager::GetInstance().PutObjectInScene(stage1, star2);
	SceneManager::GetInstance().PutObjectInScene(stage1, star3);
	SceneManager::GetInstance().PutObjectInScene(stage1, star4);
	SceneManager::GetInstance().PutObjectInScene(stage1, star5);
	SceneManager::GetInstance().PutObjectInScene(stage1, star6);
	SceneManager::GetInstance().PutObjectInScene(stage1, star7);
	SceneManager::GetInstance().PutObjectInScene(stage1, star8);
	SceneManager::GetInstance().PutObjectInScene(stage1, star9);
	SceneManager::GetInstance().PutObjectInScene(stage1, star10);
	SceneManager::GetInstance().PutObjectInScene(stage1, star11);
	SceneManager::GetInstance().PutObjectInScene(stage1, star12);
	SceneManager::GetInstance().PutObjectInScene(stage1, star13);
	SceneManager::GetInstance().PutObjectInScene(stage1, star14);
	SceneManager::GetInstance().PutObjectInScene(stage1, star15);

	SceneManager::GetInstance().PutObjectInScene(stage1, potion1);
	SceneManager::GetInstance().PutObjectInScene(stage1, potion2);
	SceneManager::GetInstance().PutObjectInScene(stage1, potion3);
	SceneManager::GetInstance().PutObjectInScene(stage1, potion4);

	SceneManager::GetInstance().PutObjectInScene(stage1, blackHole1);
	SceneManager::GetInstance().PutObjectInScene(stage1, blackHole2);
	SceneManager::GetInstance().PutObjectInScene(stage1, blackHole3);
	SceneManager::GetInstance().PutObjectInScene(stage1, blackHole4);

	SceneManager::GetInstance().PutObjectInScene(stage1, portal);

	SceneManager::GetInstance().PutObjectInScene(stage1, icePlanet);
	SceneManager::GetInstance().PutObjectInScene(stage1, snakePlanet);

	SceneManager::GetInstance().PutObjectInScene(stage1, player);

	ReadyInGameUI(stage1);

	// InGameOption 준비
	ReadyInGameOption(stage1);

	SceneManager::GetInstance().SetSceneActive(stage1, true);
}


void GameSetting::ReadyStage2Scene()
{
	GameObject* background = ObjectManager::GetInstance().CreateObject(eObjectTag::BACKGROUND, eObjectName::STAGE2_BACKGROUND,
		Transform(Vec2(2400, 3600), 0.0f, Vec2(1, 1)));

	GameObject* player = ObjectManager::GetInstance().CreateObject(eObjectTag::PLAYER, eObjectName::PLAYER,
		Transform(Vec2(959, 6781), 0.0f, Vec2(0.25, 0.25))); // Vec2(500, 1025)
	player->PutCollider(eColType::BOX, IMAGE_PLAYER); //콜라이더 넣은 거임
	player->SetColState(true);

	//starpiece1 = 4
	GameObject* star1 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(321, 5892), 0.0f, Vec2(1, 1)));
	star1->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star1->SetColState(true);

	GameObject* star2 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(2264, 5241), 0.0f, Vec2(1, 1)));
	star2->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star2->SetColState(true);

	GameObject* star3 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(3149, 6694), 0.0f, Vec2(1, 1)));
	star3->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star3->SetColState(true);

	GameObject* star4 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE1,
		Transform(Vec2(4576, 221), 0.0f, Vec2(1, 1)));
	star4->PutCollider(eColType::BOX, IMAGE_STAR_PIECE1);
	star4->SetColState(true);


	//starpiece2 = 4
	GameObject* star5 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(1600, 6372), 0.0f, Vec2(1, 1)));
	star5->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star5->SetColState(true);

	GameObject* star6 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(2180, 3239), 0.0f, Vec2(1, 1)));
	star6->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star6->SetColState(true);

	GameObject* star7 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(563, 688), 0.0f, Vec2(1, 1)));
	star7->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star7->SetColState(true);

	GameObject* star8 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE2,
		Transform(Vec2(4258, 1305), 0.0f, Vec2(1, 1)));
	star8->PutCollider(eColType::BOX, IMAGE_STAR_PIECE2);
	star8->SetColState(true);
	
	//starpiece3 = 3
	GameObject* star9 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(3814, 5138), 0.0f, Vec2(1, 1)));
	star9->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star9->SetColState(true);

	GameObject* star10 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(1747, 4036), 0.0f, Vec2(1, 1)));
	star10->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star10->SetColState(true);

	GameObject* star11 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(2633, 1107), 0.0f, Vec2(1, 1)));
	star11->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star11->SetColState(true);

	GameObject* star12 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::STAR_PIECE3,
		Transform(Vec2(1402, 1869), 0.0f, Vec2(1, 1)));
	star12->PutCollider(eColType::BOX, IMAGE_STAR_PIECE3);
	star12->SetColState(true);

	//potion
	GameObject* potion1 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(3945, 7110), 0.0f, Vec2(1, 1)));
	potion1->PutCollider(eColType::BOX, IMAGE_POTION);
	potion1->SetColState(true);

	GameObject* potion2 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(181, 3099), 0.0f, Vec2(1, 1)));
	potion2->PutCollider(eColType::BOX, IMAGE_POTION);
	potion2->SetColState(true);

	GameObject* potion3 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(4651, 2362), 0.0f, Vec2(1, 1)));
	potion3->PutCollider(eColType::BOX, IMAGE_POTION);
	potion3->SetColState(true);

	GameObject* potion4 = ObjectManager::GetInstance().CreateObject(eObjectTag::ITEM, eObjectName::POTION,
		Transform(Vec2(410, 1540), 0.0f, Vec2(1, 1)));
	potion4->PutCollider(eColType::BOX, IMAGE_POTION);
	potion4->SetColState(true);

	//BlackHole
	GameObject* blackHole1 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(2263, 6922), 0.0f, Vec2(1, 1)));
	blackHole1->PutCollider(eColType::BOX, IMAGE_BLACKHOLE);
	blackHole1->SetColState(true);
	blackHole1->PutBody(1000);

	GameObject* blackHole2 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(4799, 6010), 0.0f, Vec2(1, 1))); // scale
	blackHole2->PutCollider(eColType::BOX, IMAGE_BLACKHOLE);
	blackHole2->SetColState(true);
	blackHole2->PutBody(1000);

	GameObject* blackHole3 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(2916, 4717), 0.0f, Vec2(1, 1))); // scale
	blackHole3->PutCollider(eColType::BOX, IMAGE_BLACKHOLE);
	blackHole3->SetColState(true);
	blackHole3->PutBody(1000);

	GameObject* blackHole4 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(4332, 2945), 0.0f, Vec2(1, 1)));
	blackHole4->PutCollider(eColType::CIRCLE, IMAGE_BLACKHOLE);
	blackHole4->SetColState(true);
	blackHole4->PutBody(1000);

	GameObject* blackHole5 = ObjectManager::GetInstance().CreateObject(eObjectTag::OBSTACLE, eObjectName::BLACKHOLE,
		Transform(Vec2(1649, 2311), 0.0f, Vec2(1, 1)));
	blackHole5->PutCollider(eColType::CIRCLE, IMAGE_BLACKHOLE);
	blackHole5->SetColState(true);
	blackHole5->PutBody(1000);

	// Portal
	GameObject* portal1 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::PORTAL,
		Transform(Vec2(370, 5090), 0.0f, Vec2(1, 1)));
	portal1->PutCollider(eColType::BOX, IMAGE_PORTAL);
	portal1->SetColState(true);

	GameObject* portal2 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::PORTAL,
		Transform(Vec2(2507, 255), 0.0f, Vec2(1, 1)));
	portal2->PutCollider(eColType::BOX, IMAGE_PORTAL_SEA);
	portal2->SetColState(true);

	//Planet
	GameObject* lavaPlanet = ObjectManager::GetInstance().CreateObject(eObjectTag::PLANET, eObjectName::LAVA_PLANET,
		Transform(Vec2(3395, 1767), 0.0f, Vec2(1, 1)));
	lavaPlanet->PutCollider(eColType::CIRCLE, IMAGE_LAVA_PLANET);
	lavaPlanet->SetColState(true);
	lavaPlanet->PutBody(500);

	GameObject* storyPlanet = ObjectManager::GetInstance().CreateObject(eObjectTag::PLANET, eObjectName::STORY_PLANET,
		Transform(Vec2(959, 4133), 0.0f, Vec2(1, 1)));
	storyPlanet->PutCollider(eColType::CIRCLE, IMAGE_STORY_PLANET);
	storyPlanet->SetColState(true);
	storyPlanet->PutBody(500);

	Scene* stage2 = SceneManager::GetInstance().CreateScene(eSceneName::STAGE2);

	SceneManager::GetInstance().PutObjectInScene(stage2, background);

	SceneManager::GetInstance().PutObjectInScene(stage2, star1);
	SceneManager::GetInstance().PutObjectInScene(stage2, star2);
	SceneManager::GetInstance().PutObjectInScene(stage2, star3);
	SceneManager::GetInstance().PutObjectInScene(stage2, star4);
	SceneManager::GetInstance().PutObjectInScene(stage2, star5);
	SceneManager::GetInstance().PutObjectInScene(stage2, star6);
	SceneManager::GetInstance().PutObjectInScene(stage2, star7);
	SceneManager::GetInstance().PutObjectInScene(stage2, star8);
	SceneManager::GetInstance().PutObjectInScene(stage2, star9);
	SceneManager::GetInstance().PutObjectInScene(stage2, star10);
	SceneManager::GetInstance().PutObjectInScene(stage2, star11);
	SceneManager::GetInstance().PutObjectInScene(stage2, star12);


	SceneManager::GetInstance().PutObjectInScene(stage2, potion1);
	SceneManager::GetInstance().PutObjectInScene(stage2, potion2);
	SceneManager::GetInstance().PutObjectInScene(stage2, potion3);
	SceneManager::GetInstance().PutObjectInScene(stage2, potion4);

	SceneManager::GetInstance().PutObjectInScene(stage2, blackHole1);
	SceneManager::GetInstance().PutObjectInScene(stage2, blackHole2);
	SceneManager::GetInstance().PutObjectInScene(stage2, blackHole3);
	SceneManager::GetInstance().PutObjectInScene(stage2, blackHole4);

	SceneManager::GetInstance().PutObjectInScene(stage2, portal1);
	SceneManager::GetInstance().PutObjectInScene(stage2, portal2);

	SceneManager::GetInstance().PutObjectInScene(stage2, lavaPlanet);
	SceneManager::GetInstance().PutObjectInScene(stage2, storyPlanet);

	SceneManager::GetInstance().PutObjectInScene(stage2, player);

	ReadyInGameUI(stage2);
	ReadyInGameOption(stage2);

	SceneManager::GetInstance().SetSceneActive(stage2, true);
}

void GameSetting::ReadyStage3Scene()
{
	GameObject* background = ObjectManager::GetInstance().CreateObject(eObjectTag::BACKGROUND, eObjectName::STAGE3_BACKGROUND,
		Transform(Vec2(5000, 750), 0.0f, Vec2(1, 1)));

	GameObject* player = ObjectManager::GetInstance().CreateObject(eObjectTag::PLAYER, eObjectName::PLAYER,
		Transform(Vec2(4500, 700), 0.0f, Vec2(0.25, 0.25))); // Vec2(500, 1025)
	player->PutCollider(eColType::BOX, IMAGE_PLAYER); //콜라이더 넣은 거임
	player->SetColState(true);

	// 석상
	GameObject* statue1 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::BEAR_STATUE,
		Transform(Vec2(3178, 795), 0.0f, Vec2(0.4, 0.4)));
	statue1->PutCollider(eColType::BOX, IMAGE_BEAR_STATUE);
	statue1->SetColState(true);

	GameObject* statue2 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::BIRD_STATUE,
		Transform(Vec2(4650, 502), 0.0f, Vec2(0.4, 0.4)));
	statue2->PutCollider(eColType::BOX, IMAGE_BIRD_STATUE);
	statue2->SetColState(true);

	GameObject* statue3 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::DEAR_STATUE,
		Transform(Vec2(5947, 800), 0.0f, Vec2(0.4, 0.4)));
	statue3->PutCollider(eColType::BOX, IMAGE_DEAR_STATUE);
	statue3->SetColState(true);

	GameObject* statue4 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::WHALE_STATUE,
		Transform(Vec2(7437, 700), 0.0f, Vec2(0.4, 0.4)));
	statue4->PutCollider(eColType::BOX, IMAGE_WHALE_STATUE);
	statue4->SetColState(true);

	GameObject* statue5 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::GRANDPA_STATUE,
		Transform(Vec2(8980, 834), 0.0f, Vec2(0.4, 0.4)));
	statue5->PutCollider(eColType::BOX, IMAGE_GRANDPA_STATUE);
	statue5->SetColState(true);

	GameObject* under1 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::UNDER_STATUE,
		Transform(Vec2(3178, 795), 0.0f, Vec2(0.4, 0.4)));

	GameObject* under2 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::UNDER_STATUE,
		Transform(Vec2(4650, 502), 0.0f, Vec2(0.4, 0.4)));

	GameObject* under3 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::UNDER_STATUE,
		Transform(Vec2(5947, 800), 0.0f, Vec2(0.4, 0.4)));

	GameObject* under4 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::UNDER_STATUE,
		Transform(Vec2(7437, 700), 0.0f, Vec2(0.4, 0.4)));

	GameObject* under5 = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::UNDER_STATUE,
		Transform(Vec2(8980, 834), 0.0f, Vec2(0.4, 0.4)));


	Scene* stage3 = SceneManager::GetInstance().CreateScene(eSceneName::STAGE3);

	SceneManager::GetInstance().PutObjectInScene(stage3, background);
	SceneManager::GetInstance().PutObjectInScene(stage3, under1);
	SceneManager::GetInstance().PutObjectInScene(stage3, under2);
	SceneManager::GetInstance().PutObjectInScene(stage3, under3);
	SceneManager::GetInstance().PutObjectInScene(stage3, under4);
	SceneManager::GetInstance().PutObjectInScene(stage3, under5);
	SceneManager::GetInstance().PutObjectInScene(stage3, statue1);
	SceneManager::GetInstance().PutObjectInScene(stage3, statue2);
	SceneManager::GetInstance().PutObjectInScene(stage3, statue3);
	SceneManager::GetInstance().PutObjectInScene(stage3, statue4);
	SceneManager::GetInstance().PutObjectInScene(stage3, statue5);
	SceneManager::GetInstance().PutObjectInScene(stage3, player);

	ReadyInGameUI(stage3);

	SceneManager::GetInstance().SetSceneActive(stage3, true);
}

void GameSetting::ReadySnakePlanetScene()
{
	GameObject* background = ObjectManager::GetInstance().CreateObject(eObjectTag::BACKGROUND, eObjectName::SNAKE_BACKGROUND,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));

	GameObject* planet = ObjectManager::GetInstance().CreateObject(eObjectTag::PLANET, eObjectName::SNAKE_PLANET,
		Transform(Vec2(960, 1080), 0.0f, Vec2(1, 1)));

	//GameObject* portal = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::PORTAL,
	//	Transform(Vec2(960, 780), 0.0f, Vec2(1, 1)));
	//portal->PutCollider(eColType::BOX, IMAGE_PORTAL);
	//portal->SetColState(true);

	GameObject* player = ObjectManager::GetInstance().CreateObject(eObjectTag::PLAYER, eObjectName::PLAYER,
		Transform(Vec2(960, 540), 0.0f, Vec2(0.25, 0.25))); // Vec2(500, 1025)
	player->PutCollider(eColType::BOX, IMAGE_PLAYER); //콜라이더 넣은 거임
	player->SetColState(true);

	Scene* snakePlanet = SceneManager::GetInstance().CreateScene(eSceneName::SNAKE_PLANET);

	SceneManager::GetInstance().PutObjectInScene(snakePlanet, background);
	SceneManager::GetInstance().PutObjectInScene(snakePlanet, planet);
	//SceneManager::GetInstance().PutObjectInScene(snakePlanet, portal);
	SceneManager::GetInstance().PutObjectInScene(snakePlanet, player);

	SceneManager::GetInstance().SetSceneActive(snakePlanet, true);
}

void GameSetting::ReadyStoryPlanetScene()
{
	GameObject* background = ObjectManager::GetInstance().CreateObject(eObjectTag::BACKGROUND, eObjectName::STORY_BACKGROUND,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));

	GameObject* planet = ObjectManager::GetInstance().CreateObject(eObjectTag::PLANET, eObjectName::STORY_PLANET,
		Transform(Vec2(960, 1080), 0.0f, Vec2(1, 1)));

	GameObject* portal = ObjectManager::GetInstance().CreateObject(eObjectTag::EVENTOBJECT, eObjectName::PORTAL,
		Transform(Vec2(960, 880), 0.0f, Vec2(1, 1)));
	portal->PutCollider(eColType::BOX, IMAGE_PORTAL);
	portal->SetColState(true);

	GameObject* player = ObjectManager::GetInstance().CreateObject(eObjectTag::PLAYER, eObjectName::PLAYER,
		Transform(Vec2(960, 540), 0.0f, Vec2(0.25, 0.25))); // Vec2(500, 1025)
	player->PutCollider(eColType::BOX, IMAGE_PLAYER); //콜라이더 넣은 거임
	player->SetColState(true);

	Scene* storyPlanet = SceneManager::GetInstance().CreateScene(eSceneName::STORY_PLANET);

	SceneManager::GetInstance().PutObjectInScene(storyPlanet, background);
	SceneManager::GetInstance().PutObjectInScene(storyPlanet, planet);
	SceneManager::GetInstance().PutObjectInScene(storyPlanet, portal);
	SceneManager::GetInstance().PutObjectInScene(storyPlanet, player);

	SceneManager::GetInstance().SetSceneActive(storyPlanet, true);
}

void GameSetting::ReadyNormalScene()
{
	Scene* normal = SceneManager::GetInstance().CreateScene(eSceneName::NORMAL_ENDING);

	GameObject* normal1 = ObjectManager::GetInstance().CreateObject(eObjectTag::NORMAL_ENDING, eObjectName::NORMAL1,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));

	GameObject* normal_line1 = ObjectManager::GetInstance().CreateObject(eObjectTag::NORMAL_ENDING, eObjectName::NORMAL_LINE1,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));

	SceneManager::GetInstance().PutObjectInScene(normal, normal1);
	SceneManager::GetInstance().PutObjectInScene(normal, normal_line1);


	SceneManager::GetInstance().SetSceneActive(normal, true);
}

void GameSetting::ReadyBadScene()
{
	Scene* bad = SceneManager::GetInstance().CreateScene(eSceneName::BAD_ENDING);

	GameObject* bad1 = ObjectManager::GetInstance().CreateObject(eObjectTag::BAD_ENDING, eObjectName::BAD1,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* bad2 = ObjectManager::GetInstance().CreateObject(eObjectTag::BAD_ENDING, eObjectName::BAD2,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));

	GameObject* bad_line1 = ObjectManager::GetInstance().CreateObject(eObjectTag::BAD_ENDING, eObjectName::BAD_LINE1,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));

	GameObject* gameover = ObjectManager::GetInstance().CreateObject(eObjectTag::BAD_ENDING, eObjectName::GAMEOVER,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));
	GameObject* gameover_main = ObjectManager::GetInstance().CreateObject(eObjectTag::BAD_ENDING, eObjectName::GAMEOVER_MAIN,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));
	GameObject* gameover_retry = ObjectManager::GetInstance().CreateObject(eObjectTag::BAD_ENDING, eObjectName::GAMEOVER_RETRY,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));


	SceneManager::GetInstance().PutObjectInScene(bad, bad1);
	SceneManager::GetInstance().PutObjectInScene(bad, bad2);
	SceneManager::GetInstance().PutObjectInScene(bad, bad_line1);
	SceneManager::GetInstance().PutObjectInScene(bad, gameover);
	SceneManager::GetInstance().PutObjectInScene(bad, gameover_main);
	SceneManager::GetInstance().PutObjectInScene(bad, gameover_retry);


	SceneManager::GetInstance().SetSceneActive(bad, true);
}

void GameSetting::ReadyTrueScene()
{
	Scene* trueEnding = SceneManager::GetInstance().CreateScene(eSceneName::TRUE_ENDING);

	GameObject* true1 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE1,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true2 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE2,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true3 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE3,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true4 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE4,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true5 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE5,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true6 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE6,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true7 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE7,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true8_1 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE8_1,
		Transform(Vec2(512, 332), 0.0f, Vec2(1, 1)));
	GameObject* true8_2 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE8_2,
		Transform(Vec2(1260, 582), 0.0f, Vec2(1, 1)));
	GameObject* true9 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE9,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true10 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE10,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true11 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE11,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true12 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE12,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));
	GameObject* true13 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE13,
		Transform(Vec2(960, 460), 0.0f, Vec2(1, 1)));

	GameObject* true_line1 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE1,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line2 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE2,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line3 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE3,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line4 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE4,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line5 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE5,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line6 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE6,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line7 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE7,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line8 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE8,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line9 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE9,
		Transform(Vec2(960, 970), 0.0f, Vec2(1, 1)));
	GameObject* true_line10 = ObjectManager::GetInstance().CreateObject(eObjectTag::TRUE_ENDING, eObjectName::TRUE_LINE10,
		Transform(Vec2(930, 111), 0.0f, Vec2(1, 1)));



	SceneManager::GetInstance().PutObjectInScene(trueEnding, true1);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true2);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true3);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true4);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true5);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true6);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true7);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true8_1);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true8_2);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true9);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true10);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true11);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true12);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true13);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line1);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line2);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line3);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line4);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line5);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line6);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line7);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line8);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line9);
	SceneManager::GetInstance().PutObjectInScene(trueEnding, true_line10);


	SceneManager::GetInstance().SetSceneActive(trueEnding, true);
}

void GameSetting::ReadyInGameUI(Scene* exampleScene)
{
	Scene* PresentScene = exampleScene;

	GameObject* starpiece1 = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::STAR_PIECE1,
		Transform(Vec2(1120, 970), 0.0f, Vec2(1, 1)));

	GameObject* starpiece2 = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::STAR_PIECE2,
		Transform(Vec2(1300, 970), 0.0f, Vec2(1, 1)));

	GameObject* starpiece3 = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::STAR_PIECE3,
		Transform(Vec2(1480, 970), 0.0f, Vec2(1, 1)));

	GameObject* notemain = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::NOTE_MAIN,
		Transform(Vec2(2400, 2400), 0.0f, Vec2(1, 1)));

	GameObject* notebutton = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::NOTE_BUTTON,
		Transform(Vec2(1748, 938), 0.0f, Vec2(1, 1)));

	GameObject* boostergage = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::BOOSTER_GAGE,
		Transform(Vec2(319, 945), 0.0f, Vec2(1, 1)));

	GameObject* boosterarrow = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::BOOSTER_ARROW,
		Transform(Vec2(105, 946), 0.0f, Vec2(1, 1)));

	//GameObject* heart1 = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::HEALTH_POINT1,
	//	Transform(Vec2(72, 61), 0.0f, Vec2(1, 1)));

	//GameObject* heart2 = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::HEALTH_POINT2,
	//	Transform(Vec2(152, 61), 0.0f, Vec2(1, 1)));

	//GameObject* heart3 = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::HEALTH_POINT3,
	//	Transform(Vec2(232, 61), 0.0f, Vec2(1, 1)));

	GameObject* optionbtn = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_ICON,
		Transform(Vec2(1858, 61), 0.0f, Vec2(1, 1)));

	SceneManager::GetInstance().PutObjectInScene(PresentScene, starpiece1);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, starpiece2);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, starpiece3);

	SceneManager::GetInstance().PutObjectInScene(PresentScene, boostergage);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, boosterarrow);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, notebutton);

	//SceneManager::GetInstance().PutObjectInScene(PresentScene, heart1);
	//SceneManager::GetInstance().PutObjectInScene(PresentScene, heart2);
	//SceneManager::GetInstance().PutObjectInScene(PresentScene, heart3);

	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionbtn);
}

void GameSetting::ReadyInGameOption(Scene* exampleScene)
{
	Scene* PresentScene = exampleScene;

	GameObject* optionMenu = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_MENU,
		Transform(Vec2(960, 540), 0.0f, Vec2(1, 1)));

	GameObject* optionBarB = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_BAR,
		Transform(Vec2(1074, 340), 0.0f, Vec2(1, 1)));

	GameObject* optionBarS = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_BAR,
		Transform(Vec2(1074, 431), 0.0f, Vec2(1, 1)));

	GameObject* optionBoxB = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_BGMBOX,
		Transform(Vec2(1074, 340), 0.0f, Vec2(1, 1)));

	GameObject* optionBoxS = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_SOUNDBOX,
		Transform(Vec2(1074, 431), 0.0f, Vec2(1, 1)));

	GameObject* optionQuit = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_QUIT,
		Transform(Vec2(1258, 237), 0.0f, Vec2(1, 1)));

	GameObject* optionGoMain = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_GOMAIN,
		Transform(Vec2(840, 800), 0.0f, Vec2(1, 1)));

	GameObject* optionRetry = ObjectManager::GetInstance().CreateObject(eObjectTag::INGAME_UI, eObjectName::OPTION_RETRY,
		Transform(Vec2(1080, 800), 0.0f, Vec2(1, 1)));

	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionMenu);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionBarB);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionBarS);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionBoxB);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionBoxS);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionQuit);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionGoMain);
	SceneManager::GetInstance().PutObjectInScene(PresentScene, optionRetry);
}

void GameSetting::ReadySound()
{
	SoundManager::Initialize();

	/// BackGround
	SoundManager::CreateSound("Resource\\Sound\\BackGround\\Intro.wav", SOUND_INTRO, true);

	SoundManager::CreateSound("Resource\\Sound\\BackGround\\Space_01.wav", SOUND_STAGE1, true);
	SoundManager::CreateSound("Resource\\Sound\\BackGround\\Space_03.wav", SOUND_STAGE2, true);
	SoundManager::CreateSound("Resource\\Sound\\BackGround\\Sea.wav", SOUND_STAGE3, true);

	SoundManager::CreateSound("Resource\\Sound\\BackGround\\SnakePlanet.wav", SOUND_SNAKE_PLANET, true);
	SoundManager::CreateSound("Resource\\Sound\\BackGround\\StoryPlanet.wav", SOUND_STORY_PLANET, true);

	SoundManager::CreateSound("Resource\\Sound\\BackGround\\TrueEnding.wav", SOUND_TRUE_ENDING, true);
	SoundManager::CreateSound("Resource\\Sound\\BackGround\\TrueEnding.wav", SOUND_NORMAL_ENDING, true);
	SoundManager::CreateSound("Resource\\Sound\\BackGround\\BadEnding.wav", SOUND_BAD_ENDING, true);

	/// Effect
	SoundManager::CreateSound("Resource\\Sound\\Effect\\ShootingStarTail_Attack.wav", SOUND_SHOOTING_STAR_TAIL_CRASH, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\ShootingStar_Attack.wav", SOUND_SHOOTING_STAR_CRASH, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\BlackHole.wav", SOUND_BLACKHOLE, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\Booster.wav", SOUND_BOOSTER, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\Get_Item.wav", SOUND_GET_ITEM, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\Portal_To_Sea.wav", SOUND_PORTAL_TO_SEA, true);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\Pull_Planet.wav", SOUND_PULL_PLANET, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\Push_Planet.wav", SOUND_PUSH_PLANET, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\Satellite_Warning.wav", SOUND_SATELLITE_WARGING, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\Satellite_Boom.wav", SOUND_SATELLITE_BOOM, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\StarPiece_1.wav", SOUND_STAR_PIECE_1, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\StarPiece_2.wav", SOUND_STAR_PIECE_2, false);
	SoundManager::CreateSound("Resource\\Sound\\Effect\\StarPiece_3.wav", SOUND_STAR_PIECE_3, false);
}

