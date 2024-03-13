//===========================================
//
// 歯車のメイン処理[car_gear.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "car_gear.h"
#include "useful.h"
#include "sound.h"
#include "game.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define GEAR_CYCLE_SPEED		(0.1f)		// 回る速度

//==============================
// コンストラクタ
//==============================
CCarGear::CCarGear() : CModel(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	m_bSe = false;		// SE再生状況
}

//==============================
// デストラクタ
//==============================
CCarGear::~CCarGear()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CCarGear::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	m_bSe = false;		// SE再生状況

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CCarGear::Uninit(void)
{
	// 終了処理
	CModel::Uninit();
}

//=====================================
// 破片の更新処理
//=====================================
void CCarGear::Update(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きを加算する
	rot.y += GEAR_CYCLE_SPEED;

	// 向きの正規化
	useful::RotNormalize(&rot.y);

	// 向きを設定する
	SetRot(rot);

	if (m_bSe == false && CGame::GetState() == CGame::STATE_PLAY)
	{
		// ねじ再生
		CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_NEZI);
		m_bSe = true;
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CCarGear::Draw(void)
{
	// 描画処理
	CModel::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CCarGear::SetData(const D3DXVECTOR3& pos)
{
	// 情報の設定処理
	SetPos(pos);								// 位置
	SetPosOld(pos);								// 前回の位置
	SetRot(NONE_D3DXVECTOR3);					// 向き
	SetScale(NONE_SCALE);						// 拡大率
	SetFileData(CXFile::TYPE_TOYCARSCREW);		// モデル情報
}

//=======================================
// 生成処理
//=======================================
CCarGear* CCarGear::Create(const D3DXVECTOR3& pos)
{
	// ローカルオブジェクトを生成
	CCarGear* pCarGear = nullptr;	// インスタンスを生成

	if (pCarGear == nullptr)
	{ // オブジェクトが NULL の場合

		// インスタンスを生成
		pCarGear = new CCarGear;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCarGear != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCarGear->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCarGear->SetData(pos);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 車のギアのポインタを返す
	return pCarGear;
}