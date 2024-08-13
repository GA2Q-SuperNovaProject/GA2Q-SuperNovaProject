#pragma once
/// <summary>
/// ���Ŵ����� ������Ʈ�Ŵ����� ���Ͽ� �ϼ��� ���� ���� �����
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

