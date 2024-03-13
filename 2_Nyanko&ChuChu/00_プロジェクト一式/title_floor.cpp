//=======================================
//
// タイトルの床のメイン処理[title_floor.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "title_floor.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define FLOOR_TEXTURE	"data\\TEXTURE\\ground001.jpg"			// 屋内床テクスチャ
#define FLOOR_SIZE		(D3DXVECTOR3(1000.0f, 0.0f, 1000.0f))	// 床のサイズ

//=========================
// コンストラクタ
//=========================
CTitleFloor::CTitleFloor() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// デストラクタ
//=========================
CTitleFloor::~CTitleFloor()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CTitleFloor::Init(void)
{
	if (FAILED(CObject3D::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CTitleFloor::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//=========================
// 更新処理
//=========================
void CTitleFloor::Update(void)
{
	
}

//=========================
// 描画処理
//=========================
void CTitleFloor::Draw(void)
{
	// 描画処理
	CObject3D::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CTitleFloor::SetData(void)
{
	// 情報の設定処理
	SetPos(NONE_D3DXVECTOR3);		// 位置
	SetPosOld(NONE_D3DXVECTOR3);	// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetSize(FLOOR_SIZE);			// サイズ設定

	// 頂点情報の初期化
	SetVertex();

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(FLOOR_TEXTURE));
}

//=========================
// 生成処理
//=========================
CTitleFloor* CTitleFloor::Create(void)
{
	// ローカルオブジェクトを生成
	CTitleFloor* pFloor = nullptr;	// プレイヤーのインスタンスを生成

	if (pFloor == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pFloor = new CTitleFloor;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pFloor != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pFloor->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pFloor->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 床のポインタを返す
	return pFloor;
}