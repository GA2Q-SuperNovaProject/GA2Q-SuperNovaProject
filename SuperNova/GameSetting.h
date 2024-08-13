#pragma once
/// <summary>
/// 씬매니저와 오브젝트매니저를 합하여 완성된 게임 씬을 만든다
/// 2023.02.09 [nadong]
/// </summary>
/// 
/// 

class Scene;

class GameSetting
{
public:
	GameSetting();
	~GameSetting();

	static void ReadyAllScene();

private:
	static void ReadySound();
	static void ReadyInGameUI(Scene* exampleScene);
	static void ReadyInGameOption(Scene* exampleScene);

	static void ReadyMainScene();
	static void ReadyOpeningScene();
	static void ReadyStage1Scene();
	static void ReadyStage2Scene();
	static void ReadyStage3Scene();

	static void ReadySnakePlanetScene();	
	static void ReadyStoryPlanetScene();	

	static void ReadyNormalScene();
	static void ReadyBadScene();
	static void ReadyTrueScene();

	/// Debug
	//static void ReadyMouseScene();
	//static void ReadyTaewookScene();
};

