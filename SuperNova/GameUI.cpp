#include "GameUI.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "MouseInputManager.h"
#include "RenderSystem.h"
#include "Debug.h"
#include "Player.h"
#include "SceneManager.h"
#include "GameManager.h"
#include "EnumDefine.h"
#include "SoundManager.h"
#include "Scene.h"

bool GameUI::IsGameOptionOn = false;

GameUI::GameUI(eObjectTag tag, eObjectName name, Transform transform)
	: GameObject(tag, name, transform),
	m_beginPos(transform.GetPosition()),
	m_isClick(false),
	m_DragOn(false),
	m_OptionClick(false)
{
	Sortation();
}

GameUI::~GameUI()
{

}

void GameUI::Start()
{
	playerObject = static_cast<Player*>(belongScene->FindObjectInScene(eObjectName::PLAYER));
	//optionObject = static_cast<OptionUI*>(belongScene->FindObjectInScene(eObjectName::OPTION_UI));
}

void GameUI::Update()
{
	/// <summary>
	/// 모든 클릭 이벤트
	/// </summary>
	ClickEvent();

	/// <summary>
	/// 드래그앤 드랍
	/// </summary>
	if (m_DragOn == true && InputManager::GetInstance().IsKeyPress(VK_LMB))
	{
		m_mousePos = MouseInputManager::GetInstance().GetPos();
	}

	/// <summary>
	/// 부스터 개수
	/// </summary>
	BoostCheck();

}

void GameUI::Render()
{
	if (m_name == eObjectName::OPTION_MENU || m_name == eObjectName::OPTION_BAR
		|| m_name == eObjectName::OPTION_SOUNDBOX || m_name == eObjectName::OPTION_BGMBOX
		|| m_name == eObjectName::OPTION_QUIT || m_name == eObjectName::OPTION_GOMAIN || m_name == eObjectName::OPTION_RETRY)
	{
		if (IsGameOptionOn == true)
		{
			RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
		}
	}
	else
	{
		RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_pTransform->GetPosition().x, m_pTransform->GetPosition().y, this->GetPTransform());
	}


	if (m_DragOn == true && InputManager::GetInstance().IsKeyPress(VK_LMB))
	{
		RenderSystem::GetInstance().DrawSprite(m_imageIndex, m_mousePos.x, m_mousePos.y, this->GetPTransform());
	}
	else if (m_DragOn == false)
	{
		if (!IsGameOptionOn)
		{
			m_pTransform->m_Position = m_beginPos;
		}
	}

	//RenderSystem::GetInstance().Fadein();
	CheckHpCount();
	DrawStarPieceCount();

	if (m_ShowNoteMain == true)
	{
		ShowNoteMain();
	}
}

bool GameUI::GetStartPiece(eObjectName star)
{
	if (star == eObjectName::STAR_PIECE1)
	{
		return m_Star1;
	}

	if (star == eObjectName::STAR_PIECE2)
	{
		return m_Star2;
	}

	if (star == eObjectName::STAR_PIECE3)
	{
		return m_Star3;
	}

	return false;
}

void GameUI::Sortation()
{
	switch (m_name)
	{
		case eObjectName::HEALTH_POINT1:
			m_imageIndex = IMAGE_HEALTH_POINT;
			break;

		case eObjectName::HEALTH_POINT2:
			m_imageIndex = IMAGE_HEALTH_POINT;
			break;

		case eObjectName::HEALTH_POINT3:
			m_imageIndex = IMAGE_HEALTH_POINT;
			break;

		case eObjectName::OPTION_ICON:
			m_imageIndex = IMAGE_OPTION_BUTTON;
			break;

		case eObjectName::NOTE_BUTTON:
			m_imageIndex = IMAGE_NOTE_BUTTON;
			break;

		case eObjectName::STAR_PIECE1:
			m_imageIndex = IMAGE_STAR_PIECE1;
			break;

		case eObjectName::STAR_PIECE2:
			m_imageIndex = IMAGE_STAR_PIECE2;
			break;

		case eObjectName::STAR_PIECE3:
			m_imageIndex = IMAGE_STAR_PIECE3;
			break;

		case eObjectName::BOOSTER_GAGE:
			m_imageIndex = IMAGE_BOOSTER_GAGE3;
			break;

		case eObjectName::BOOSTER_ARROW:
			m_imageIndex = IMAGE_BOOSTER_ARROW;
			break;

			// In-Game Option
		case eObjectName::OPTION_MENU:
			m_imageIndex = IMAGE_OPTION_MENU;
			break;

		case eObjectName::OPTION_BAR:
			m_imageIndex = IMAGE_OPTION_BAR;
			break;

		case eObjectName::OPTION_SOUNDBOX:
			m_imageIndex = IMAGE_OPTION_BOX;
			break;

		case eObjectName::OPTION_BGMBOX:
			m_imageIndex = IMAGE_OPTION_BOX;
			break;

		case eObjectName::OPTION_QUIT:
			m_imageIndex = IMAGE_OPTION_QUIT;
			break;

		case eObjectName::OPTION_GOMAIN:
			m_imageIndex = IMAGE_OPTION_GO_MAIN;
			break;

		case eObjectName::OPTION_RETRY:
			m_imageIndex = IMAGE_OPTION_RETRY;
			break;

			//노트 메인
		case eObjectName::NOTE_MAIN:
			m_imageIndex = IMAGE_NOTE_MAIN;
			break;
	}
}

void GameUI::ClickEvent()
{
	if (MouseInputManager::GetInstance().IsOnBoard(m_pTransform->m_Position, m_imageIndex))
	{
		if (m_isClick == false && InputManager::GetInstance().IsKeyDown(VK_LMB))
		{
			m_isClick = true;

			switch (m_imageIndex)
			{
				case IMAGE_NOTE_BUTTON:
					if (m_ShowNoteMain == true)
					{
						m_ShowNoteMain = false;
					}
					else
					{
						m_ShowNoteMain = true;
					}
					break;

				case IMAGE_STAR_PIECE1:
					m_DragOn = true;
					m_Star1 = true;
					break;

				case IMAGE_STAR_PIECE2:
					m_DragOn = true;
					m_Star2 = true;
					break;

				case IMAGE_STAR_PIECE3:
					m_DragOn = true;
					m_Star3 = true;
					break;

				case IMAGE_OPTION_BUTTON:
					IsGameOptionOn = true;
					break;

				case IMAGE_OPTION_BOX:
					IsGameOptionOn = true;
					break;

				case IMAGE_OPTION_QUIT:
					IsGameOptionOn = false;
					break;

				case IMAGE_OPTION_GO_MAIN:
					SceneManager::GetInstance().ChangeScene(eSceneName::MAIN);
					IsGameOptionOn = false;
					break;

				case IMAGE_OPTION_RETRY:
					IsGameOptionOn = false;
					break;
			}
		}
	}
	if (InputManager::GetInstance().IsKeyUp(VK_LMB))
	{
		m_isClick = false;
		m_DragOn = false;

		m_Star1 = false;
		m_Star2 = false;
		m_Star3 = false;
	}

	if (InputManager::GetInstance().IsKeyDown(VK_LMB))
	{
		if (!(MouseInputManager::GetInstance().IsOnBoardRect(MouseInputManager::GetInstance().GetPos(), optionRect)))
		{
			//IsGameOptionOn = false;

		}
	}

	if (MouseInputManager::GetInstance().IsOnBoard(m_pTransform->m_Position, m_imageIndex))
	{

		if (m_isClick == false && InputManager::GetInstance().IsKeyDown(VK_LMB)
			|| InputManager::GetInstance().IsKeyPress(VK_LMB))
		{
			m_isClick = true;

			switch (m_name)
			{
				case eObjectName::OPTION_SOUNDBOX:
					m_pTransform->m_Position.x = MouseInputManager::GetInstance().GetPos().x;

					if (m_pTransform->m_Position.x <= 901)
					{
						m_pTransform->m_Position.x = 901;
					}

					if (m_pTransform->m_Position.x >= 1247)
					{
						m_pTransform->m_Position.x = 1247;
					}
					VolumeEvent();
					break;

				case eObjectName::OPTION_BGMBOX:
					m_pTransform->m_Position.x = MouseInputManager::GetInstance().GetPos().x;

					if (m_pTransform->m_Position.x <= 901)
					{
						m_pTransform->m_Position.x = 901;
					}

					if (m_pTransform->m_Position.x >= 1247)
					{
						m_pTransform->m_Position.x = 1247;
					}
					VolumeEvent();
					break;
			};
		}
	}
}

void GameUI::BoostCheck()
{
	if (m_name == eObjectName::BOOSTER_GAGE)
	{
		if (playerObject->m_boostCount == 3)
		{
			m_imageIndex = IMAGE_BOOSTER_GAGE3;
		}
		if (playerObject->m_boostCount == 2)
		{
			m_imageIndex = IMAGE_BOOSTER_GAGE2;
		}
		if (playerObject->m_boostCount == 1)
		{
			m_imageIndex = IMAGE_BOOSTER_GAGE1;
		}
		if (playerObject->m_boostCount == 0)
		{
			m_imageIndex = IMAGE_BOOSTER_GAGE0;
		}
	}
}


void GameUI::VolumeEvent()
{
	float volume = (1247 - m_pTransform->m_Position.x) / 346;

	SoundManager::SetSoundVolume(SOUND_STAGE1, volume);
}

void GameUI::CheckHpCount()
{
	switch (playerObject->m_hpCount)
	{
		case 3:
			RenderSystem::GetInstance().DrawSprite(IMAGE_HEALTH_POINT, 75, 61);
			RenderSystem::GetInstance().DrawSprite(IMAGE_HEALTH_POINT, 152, 61);
			RenderSystem::GetInstance().DrawSprite(IMAGE_HEALTH_POINT, 232, 61);
			break;

		case 2:
			RenderSystem::GetInstance().DrawSprite(IMAGE_HEALTH_POINT, 75, 61);
			RenderSystem::GetInstance().DrawSprite(IMAGE_HEALTH_POINT, 152, 61);
			break;

		case 1:
			RenderSystem::GetInstance().DrawSprite(IMAGE_HEALTH_POINT, 75, 61);
			break;

	}
}

//별 개수가 몇개 있는지 그려주는 텍스트
void GameUI::DrawStarPieceCount()
{
	std::wstring wstr1 = L"X ";
	int tmpX1 = playerObject->m_StarPiece1count1;
	wstr1 += std::to_wstring(tmpX1);
	RenderSystem::GetInstance().InfoText(Vec2(1170, 920), wstr1);// star1 text

	std::wstring wstr2 = L"X ";
	int tmpX2 = playerObject->m_StarPiece1count2;
	wstr2 += std::to_wstring(tmpX2);
	RenderSystem::GetInstance().InfoText(Vec2(1350, 920), wstr2);// star1 text

	std::wstring wstr3 = L"X ";
	int tmpX3 = playerObject->m_StarPiece1count3;
	wstr3 += std::to_wstring(tmpX3);
	RenderSystem::GetInstance().InfoText(Vec2(1530, 920), wstr3);// star1 text
}


void GameUI::ShowNoteMain()
{
	RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE_MAIN, 960, 540);
	RenderSystem::GetInstance().DrawSprite(IMAGE_MISSION_UI, 700, 370);



	RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE2, 700, 700);	// 좌측하단
	if (playerObject->m_NotePage >= 1)
	{
		RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE2_WRITE, 700, 700);	// 좌측하단
	}

	RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE1, 1250, 370);	// 우측상단
	if (playerObject->m_NotePage >= 2)
	{
		RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE1_WRITE, 1250, 370);	// 우측상단
	}

	RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE5, 1230, 730);	// 우측하단
	if (playerObject->m_NotePage >= 3)
	{
		RenderSystem::GetInstance().DrawSprite(IMAGE_NOTE5_WRITE, 1230, 730);	// 우측하단
	}


}