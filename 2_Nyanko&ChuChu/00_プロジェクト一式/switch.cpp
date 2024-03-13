//===========================================
//
// スイッチのメイン処理[switch.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "switch.h"
#include "model.h"
#include "useful.h"

#include "objectbillboard.h"
#include "texture.h"

// マクロ定義
#define LEVER_SHIFT		(5.0f)		// レバーのずらす幅
#define LEVER_HEIGHT	(18.0f)		// レバーの追加の高さ
#define LEVER_CORRECT	(0.05f)		// レバーの補正係数

//==============================
// コンストラクタ
//==============================
CSwitch::CSwitch() : CObject(CObject::TYPE_NONE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_apModel[nCnt] = nullptr;		// モデルの情報
	}
	m_pGimmickUI = nullptr;				// ギミックUIの情報
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_aUIFalse[nCnt] = false;		// 全部[False]の時にUIを削除する
	}
	m_posCopy = NONE_D3DXVECTOR3;		// 位置のコピー
	m_fRotDest = 0.0f;					// 目的の向き
	m_fPosYDest = 0.0f;					// 目的の位置(Y軸)
	m_bBoot = false;					// 起動状況
}

//==============================
// デストラクタ
//==============================
CSwitch::~CSwitch()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CSwitch::Init(void)
{
	// 全ての値を初期化する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] == nullptr)
		{ // モデルの情報が NULL の場合

			// モデルの生成処理
			m_apModel[nCnt] = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);
		}
	}
	m_pGimmickUI = nullptr;				// ギミックUIの情報
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{
		m_aUIFalse[nCnt] = false;		// 全部[False]の時にUIを削除する
	}
	m_posCopy = NONE_D3DXVECTOR3;		// 位置のコピー
	m_fRotDest = 0.0f;					// 目的の向き
	m_fPosYDest = 0.0f;					// 目的の位置(Y軸)
	m_bBoot = false;					// 起動状況

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CSwitch::Uninit(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルの情報が NULL じゃない場合

			// モデルの終了処理
			m_apModel[nCnt]->Uninit();
			m_apModel[nCnt] = nullptr;
		}
	}

	if (m_pGimmickUI != nullptr)
	{ // ギミックUIが NULL じゃない場合

		// ギミックUIの終了処理
		m_pGimmickUI->Uninit();
		m_pGimmickUI = nullptr;
	}
	
	// 本体の終了処理
	Release();
}

//=====================================
// 破片の更新処理
//=====================================
void CSwitch::Update(void)
{
	// 状態マネージャー
	StateManager();

	if (m_pGimmickUI != nullptr)
	{ // ギミックUIが NULL じゃない場合

		// 更新処理
		m_pGimmickUI->Update();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CSwitch::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルが NULL じゃない場合

			// モデルの描画処理
			m_apModel[nCnt]->Draw();
		}
	}

	if (m_pGimmickUI != nullptr)
	{ // ギミックUIが NULL じゃない場合

		// 描画処理
		m_pGimmickUI->DrawLightOff();
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CSwitch::Draw(const float fAlpha)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_apModel[nCnt] != nullptr)
		{ // モデルが NULL じゃない場合

			// モデルの描画処理
			m_apModel[nCnt]->Draw(fAlpha);
		}
	}

	if (m_pGimmickUI != nullptr)
	{ // ギミックUIが NULL じゃない場合

		// 描画処理
		m_pGimmickUI->DrawLightOff();
	}
}

//=====================================
// 起動状況の入れ替え処理
//=====================================
void CSwitch::ChangeBoot(void)
{
	// 起動状況を入れ替える
	m_bBoot = !m_bBoot;
}

//=====================================
// 情報の設定処理
//=====================================
void CSwitch::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	CXFile::TYPE type;

	// 全ての値を設定する
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// 種類を設定する
		type = (CXFile::TYPE)(CXFile::TYPE_LEVERBODY + nCnt);

		if (m_apModel[nCnt] != nullptr)
		{ // モデルが NULL じゃない場合

			switch (nCnt)
			{
			case TYPE_BASE:

				m_apModel[nCnt]->SetPos(pos);				// 位置

				break;

			case TYPE_LEVER:

				m_apModel[nCnt]->SetPos(D3DXVECTOR3(pos.x + sinf(rot.y) * LEVER_SHIFT, pos.y + LEVER_HEIGHT, pos.z + cosf(rot.y) * LEVER_SHIFT));				// 位置

				break;

			default:

				// 停止
				assert(false);

				break;
			}

			// 情報の設定処理
			m_apModel[nCnt]->SetPosOld(m_apModel[nCnt]->GetPos());			// 前回の位置
			m_apModel[nCnt]->SetRot(rot);				// 向き
			m_apModel[nCnt]->SetScale(NONE_SCALE);		// 拡大率
			m_apModel[nCnt]->SetFileData(type);			// モデル情報
		}
	}
	m_posCopy = pos;						// 位置のコピー
	m_fRotDest = 0.0f;						// 目的の向き
	m_fPosYDest = pos.y + LEVER_HEIGHT;		// 目的の位置(Y軸)
	m_bBoot = false;						// 起動状況
}

//=======================================
// 生成処理
//=======================================
CSwitch* CSwitch::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot)
{
	// ローカルオブジェクトを生成
	CSwitch* pSwitch = nullptr;

	if (pSwitch == nullptr)
	{ // オブジェクトが NULL の場合

		// スイッチを生成
		pSwitch = new CSwitch;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pSwitch != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pSwitch->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSwitch->SetData(pos, rot);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// スイッチのポインタを返す
	return pSwitch;
}

//=======================================
// 状態マネージャー
//=======================================
void CSwitch::StateManager(void)
{
	// 位置と向きを取得する
	D3DXVECTOR3 pos = m_apModel[TYPE::TYPE_LEVER]->GetPos();
	D3DXVECTOR3 rot = m_apModel[TYPE::TYPE_LEVER]->GetRot();

	if (m_bBoot == true)
	{ // 起動状況が true の場合

		// 目的の向きを設定する
		m_fRotDest = D3DX_PI * -0.5f;

		// 目的の位置を設定する
		m_fPosYDest = m_posCopy.y - LEVER_HEIGHT;
	}
	else
	{ // 上記以外

		// 目的の向きを設定する
		m_fRotDest = 0.0f;

		// 目的の位置を設定する
		m_fPosYDest = m_posCopy.y + LEVER_HEIGHT;
	}

	// 向きの補正処理
	useful::RotCorrect(m_fRotDest, &rot.x, LEVER_CORRECT);

	// 位置の補正処理
	useful::Correct(m_fPosYDest, &pos.y, LEVER_CORRECT);

	// 向きの正規化
	useful::RotNormalize(&rot.x);

	// 位置と向きを適用する
	m_apModel[TYPE_LEVER]->SetPos(pos);
	m_apModel[TYPE_LEVER]->SetRot(rot);
}

//=======================================
// ギミックUIの設定処理
//=======================================
void CSwitch::SetGimmickUI(bool Set, int Player_Idx)
{
	if (Set == true)
	{//UI表示の範囲内にいる場合

		if (m_pGimmickUI == nullptr)
		{ // ギミックUIが NULL じゃない場合

			//自分のUI表示状態をONにする
			m_aUIFalse[Player_Idx] = true;

			//UIの表示
			m_pGimmickUI = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
			m_pGimmickUI->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\UI_GimmickOn.png"));
			m_pGimmickUI->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

			// 情報の設定処理
			m_pGimmickUI->SetPos(D3DXVECTOR3(				// 位置
				m_apModel[TYPE_BASE]->GetPos().x,
				m_apModel[TYPE_BASE]->GetPos().y + 60.0f,
				m_apModel[TYPE_BASE]->GetPos().z));
			m_pGimmickUI->SetPosOld(D3DXVECTOR3(			// 前回の位置
				m_apModel[TYPE_BASE]->GetPos().x,
				m_apModel[TYPE_BASE]->GetPos().y + 60.0f,
				m_apModel[TYPE_BASE]->GetPos().z));

			// 頂点座標の設定処理
			m_pGimmickUI->SetVertex();
		}
	}
	else
	{//UI表示の範囲内にいない場合

		//自分のUI表示状態をOFFにする
		m_aUIFalse[Player_Idx] = false;
	}

	//全てのプレイヤーの表示状態がOFFのとき削除する
	if (m_aUIFalse[0] == false &&
		m_aUIFalse[1] == false &&
		m_aUIFalse[2] == false &&
		m_aUIFalse[3] == false)
	{
		if (m_pGimmickUI != NULL)
		{ // ギミックUIが NULL の場合

			// ギミックUIの終了処理
			m_pGimmickUI->Uninit();
			m_pGimmickUI = NULL;
		}
	}
}

//=======================================
// モデルの取得処理
//=======================================
CModel* CSwitch::GetModel(const TYPE type)
{
	// モデルの情報を返す
	return m_apModel[type];
}

//=======================================
// 起動状況の設定処理
//=======================================
void CSwitch::SetBoot(const bool bBoot)
{
	// 起動状況を設定する
	m_bBoot = bBoot;
}

//=======================================
// 起動状況の取得処理
//=======================================
bool CSwitch::GetBoot(void) const
{
	// 起動状況を返す
	return m_bBoot;
}