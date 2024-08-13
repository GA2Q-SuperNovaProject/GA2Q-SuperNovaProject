#pragma once
#include <utility>
#include <map>

//Map�� ImageIndex - FLOATPAIR�� �� ���� [TW]
typedef std::pair<float, float> FLOATPAIR;

class CollideInfoMap
{
public:
	static CollideInfoMap& GetInstance()
	{
		static CollideInfoMap inst;
		return inst;
	}
	
	//(WIDTH / HEIGHT ����!) �� ���� Width�� Height�� ����ϴ� Map�� �ִ´�.
	void AddWidthHeightToMap(int imageIndex, float width, float height);

	//�̹��� �ε����� �޾� Width�� ��ȯ�޴´�.
	float GetWidthByImageIndex(int imageIndex);

	//�̹��� �ε����� �޾� Height�� ��ȯ�޴´�.
	float GetHeightByImageIndex(int imageIndex);

	//�̹��� �ε������ �� ���� �Ҵ�. (�ʺ�) <GetWidth �ߵ��Ǳ� ���� NO!>
	void SetWidthByImageIndex(int imageIndex, float widthValue);

	//�̹��� �ε������ �� ���� �Ҵ�. (����) <GetWidth �ߵ��Ǳ� ���� NO!>
	void SetHeightByImageIndex(int imageIndex, float heightValue);

	//GIF, (WIDTH / HEIGHT ����!) �� ���� Width�� Height�� ����ϴ� GIF�� Map�� �ִ´�.
	void AddWidthHeightToGIFMap(int imageIndex, float width, float height);

	//GIF �ε������ �� ���� �Ҵ�. (�ʺ�) <GetWidth �ߵ��Ǳ� ���� NO!>
	void SetWidthByGIFIndex(int imageIndex, float widthValue);

	//GIF �ε������ �� ���� �Ҵ�. (����) <GetWidth �ߵ��Ǳ� ���� NO!>
	void SetHeightByGIFIndex(int imageIndex, float heightValue);

	//GIF, �̹��� �ε����� �޾� Width�� ��ȯ�޴´�.
	float GetWidthByGIFIndex(int imageIndex);

	//GIF, �̹��� �ε����� �޾� Height�� ��ȯ�޴´�.
	float GetHeightByGIFIndex(int imageIndex);
private:
	std::map<int, FLOATPAIR> m_InfoMap;
	std::map<int, FLOATPAIR> m_GIFMap;
};

///[TW] ���� GameObject�� ������� �� Width�� Height�� ���� �� �����Ƿ�, 
///������ std::map�� ���� ������Ʈ�� ���� ����. 
/// DRSprite ������ Width/Height�� �����ϴ���..
/// �ƴϸ� LoadSpriteFromSheet�� �� ColliderMap�� �����ϰ� �Ͽ� ��Ҹ� ���ϰ� �ϴ���..
/// ����.. ������, ���� �ذ�� �� �ִ� �����̴�. ������ �̿� ������ �� �ִ� Ŭ������... 
/// 
/// �ٸ�, ��Ÿ�� �� Instantiate ��Ȳ�� ���� ��������� 
/// Width/Height�� ������ ���� �ְ� �� ����.
/// �̱��� �����̶� �� �׷�����, �������μ��� ��¿ �� ����.
