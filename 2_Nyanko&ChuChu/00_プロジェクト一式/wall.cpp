//=======================================
//
//壁関係メイン処理
//Author:澗口将太郎
//
//=======================================
#include "wall.h"
#include "manager.h"
#include "texture.h"

//=======================================
// マクロ定義
//=======================================
#define MAP_INDOOR0_WALL_TEXTURE		"data\\TEXTURE\\wall001.png"		// 屋内床テクスチャ
//=======================================
CWall::CWall() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

CWall::CWall(PRIORITY priority) : CObject3D(CObject::TYPE_MAP, priority)
{

}

CWall::~CWall()
{

}

HRESULT CWall::Init(void)
{
	CObject3D::Init();

	CObject3D::BindTexture(CManager::Get()->GetTexture()->Regist(MAP_INDOOR0_WALL_TEXTURE));
	CObject3D::SetPos(m_pos);
	CObject3D::SetRot(m_rot);
	CObject3D::SetSize(D3DXVECTOR3(m_size));

	return S_OK;
}
void CWall::Uninit(void)
{
	CObject3D::Uninit();
}
void CWall::Update(void)
{
	CObject3D::Update();
}
void CWall::Draw(void)
{
	CObject3D::Draw();
}
CWall* CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CObject::PRIORITY pritype)
{
	CWall *pWall;

	pWall = new CWall(pritype);

	pWall->SetType(TYPE_MAP);

	pWall->m_pos = pos;
	pWall->m_rot = rot;
	pWall->m_size = size;

	pWall->Init();

	return pWall;
}