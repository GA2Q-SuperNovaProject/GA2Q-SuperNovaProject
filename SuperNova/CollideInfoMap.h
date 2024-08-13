#pragma once
#include <utility>
#include <map>

//Map은 ImageIndex - FLOATPAIR가 될 예정 [TW]
typedef std::pair<float, float> FLOATPAIR;

class CollideInfoMap
{
public:
	static CollideInfoMap& GetInstance()
	{
		static CollideInfoMap inst;
		return inst;
	}
	
	//(WIDTH / HEIGHT 순서!) 이 쌍을 Width와 Height을 기록하는 Map에 넣는다.
	void AddWidthHeightToMap(int imageIndex, float width, float height);

	//이미지 인덱스를 받아 Width를 반환받는다.
	float GetWidthByImageIndex(int imageIndex);

	//이미지 인덱스를 받아 Height을 반환받는다.
	float GetHeightByImageIndex(int imageIndex);

	//이미지 인덱스대로 값 임의 할당. (너비) <GetWidth 발동되기 전에 NO!>
	void SetWidthByImageIndex(int imageIndex, float widthValue);

	//이미지 인덱스대로 값 임의 할당. (높이) <GetWidth 발동되기 전에 NO!>
	void SetHeightByImageIndex(int imageIndex, float heightValue);

	//GIF, (WIDTH / HEIGHT 순서!) 이 쌍을 Width와 Height을 기록하는 GIF의 Map에 넣는다.
	void AddWidthHeightToGIFMap(int imageIndex, float width, float height);

	//GIF 인덱스대로 값 임의 할당. (너비) <GetWidth 발동되기 전에 NO!>
	void SetWidthByGIFIndex(int imageIndex, float widthValue);

	//GIF 인덱스대로 값 임의 할당. (높이) <GetWidth 발동되기 전에 NO!>
	void SetHeightByGIFIndex(int imageIndex, float heightValue);

	//GIF, 이미지 인덱스를 받아 Width를 반환받는다.
	float GetWidthByGIFIndex(int imageIndex);

	//GIF, 이미지 인덱스를 받아 Height을 반환받는다.
	float GetHeightByGIFIndex(int imageIndex);
private:
	std::map<int, FLOATPAIR> m_InfoMap;
	std::map<int, FLOATPAIR> m_GIFMap;
};

///[TW] 현재 GameObject가 만들어질 때 Width와 Height을 받을 수 없으므로, 
///별도로 std::map을 통해 오브젝트의 형식 정리. 
/// DRSprite 내부의 Width/Height에 접근하던가..
/// 아니면 LoadSpriteFromSheet할 때 ColliderMap에 접근하게 하여 요소를 더하게 하던가..
/// 으악.. 하지만, 쉽게 해결될 수 있는 문제이다. 별도로 이에 접근할 수 있는 클래스로... 
/// 
/// 다만, 런타임 중 Instantiate 상황을 위해 명시적으로 
/// Width/Height을 설정할 수도 있게 할 예정.
/// 싱글턴 남용이라 좀 그렇지만, 당장으로서는 어쩔 수 없다.
