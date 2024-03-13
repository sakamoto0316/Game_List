//=======================================
//
// タイトルの背景のメイン処理[title_back.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "title_back.h"
#include "renderer.h"
#include "texture.h"
#include "useful.h"

//=======================================
// マクロ定義
//=======================================
#define BACK_POS		(D3DXVECTOR3(0.0f, 300.0f, 600.0f))		// 背景の位置
#define BACK_SIZE		(D3DXVECTOR3(1000.0f, 1000.0f, 0.0f))	// 背景のサイズ
#define BACK_TEXTURE	"data\\TEXTURE\\wall001.png"			// 屋内床テクスチャ

//=========================
// コンストラクタ
//=========================
CTitleBack::CTitleBack() : CObject3D(CObject::TYPE_MAP, CObject::PRIORITY_BG)
{

}

//=========================
// デストラクタ
//=========================
CTitleBack::~CTitleBack()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CTitleBack::Init(void)
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
void CTitleBack::Uninit(void)
{
	// 終了
	CObject3D::Uninit();
}

//=========================
// 更新処理
//=========================
void CTitleBack::Update(void)
{
	
}

//=========================
// 描画処理
//=========================
void CTitleBack::Draw(void)
{
	// 描画処理
	CObject3D::DrawLightOff();
}

//=========================
// 情報の設定処理
//=========================
void CTitleBack::SetData(void)
{
	// 情報の設定処理
	SetPos(BACK_POS);			// 位置
	SetPosOld(BACK_POS);		// 前回の位置
	SetRot(NONE_D3DXVECTOR3);	// 向き
	SetSize(BACK_SIZE);			// サイズ設定

	// 頂点情報の初期化
	SetVertex();

	// テクスチャの読み込み処理
	BindTexture(CManager::Get()->GetTexture()->Regist(BACK_TEXTURE));
}

//=========================
// 生成処理
//=========================
CTitleBack* CTitleBack::Create(void)
{
	// ローカルオブジェクトを生成
	CTitleBack* pBack = nullptr;	// プレイヤーのインスタンスを生成

	if (pBack == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pBack = new CTitleBack;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pBack != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pBack->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pBack->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 背景のポインタを返す
	return pBack;
}