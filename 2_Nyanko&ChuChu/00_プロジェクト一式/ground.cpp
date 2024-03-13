//=======================================
//
//地面関係メイン処理
//Author:澗口将太郎
//
//=======================================
#include "ground.h"
#include "manager.h"
#include "texture.h"
//=======================================
// マクロ定義
//=======================================
#define MAP_INDOOR_TEXTURE		"data\\TEXTURE\\ground001.jpg"		// 屋内床テクスチャ
//=======================================
CGround::CGround() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}
CGround::~CGround()
{

}

HRESULT CGround::Init(void)
{
	CObject3D::Init();

	CObject3D::BindTexture(CManager::Get()->GetTexture()->Regist(MAP_INDOOR_TEXTURE));
	CObject3D::SetSize(MAP_SIZE);

	return S_OK;
}
void CGround::Uninit(void)
{
	CObject3D::Uninit();
}
void CGround::Update(void)
{


	CObject3D::Update();
}
void CGround::Draw(void)
{
	CObject3D::Draw();
}
CGround* CGround::Create(void)
{
	CGround *pGround;

	pGround = new CGround;

	pGround->SetType(TYPE_MAP);

	pGround->Init();

	return pGround;
}