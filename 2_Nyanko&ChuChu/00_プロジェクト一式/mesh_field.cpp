//======================================================================================================================
//
//	メッシュフィールド処理 [mesh_field.cpp]
//	Author：小原立暉
//
//======================================================================================================================
//**********************************************************************************************************************
//	インクルードファイル
//**********************************************************************************************************************
#include "mesh_field.h"

//================================
// コンストラクタ
//================================
CMeshField::CMeshField() : CMesh(CObject::TYPE_MESH, CObject::PRIORITY_BG)
{
	
}

//================================
// デストラクタ
//================================
CMeshField::~CMeshField()
{

}

//================================
// 初期化処理
//================================
HRESULT CMeshField::Init(void)
{
	if (FAILED(CMesh::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//================================
// 終了処理
//================================
void CMeshField::Uninit(void)
{
	// 終了処理
	CMesh::Uninit();
}

//================================
// 更新処理
//================================
void CMeshField::Update(void)
{

}

//================================
// 描画処理
//================================
void CMeshField::Draw(void)
{
	// 描画処理
	CMesh::Draw();
}