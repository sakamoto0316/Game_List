//===========================================
//
// ひもの処理[Himo.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Himo.h"
#include "useful.h"
#include "objectX.h"
#include "tarai.h"
#include "input.h"
#include "sound.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define TARAI_FALL_AREA_X	(3001)		// たらいの落下範囲(X)
#define TARAI_FALL_AREA_Z	(2001)		// たらいの落下範囲(Z)
#define TARAI_COUNT			(40)		// 1度の起動でたらいが落ちる数

//==============================
// コンストラクタ
//==============================
CHimo::CHimo() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for(int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		m_apTarai[nCnt] = NULL;
	}
	m_nTaraiCount = 0;
	m_fDownPosY = 0.0f;
	m_fUpPosY = 0.0f;
	m_bFall = false;
	SetCatUse(true);
}

//==============================
// デストラクタ
//==============================
CHimo::~CHimo()
{

}

//==============================
// ひもの初期化処理
//==============================
HRESULT CHimo::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 値を返す
	return S_OK;
}

//========================================
// ひもの終了処理
//========================================
void CHimo::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != nullptr)
		{ // タライが NULL じゃない場合

			// タライの終了処理
			m_apTarai[nCnt]->Uninit();
			m_apTarai[nCnt] = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// ひもの更新処理
//=====================================
void CHimo::Update(void)
{
	// タライの存在確認処理
	TaraiCheck();

	{ // 紐の移動処理

		// 位置を取得する
		D3DXVECTOR3 pos = GetPos();

		if (GetAction() == true)
		{ // アクション状況が true の場合
			
			if (pos.y > m_fDownPosY)
			{ // 規定の位置まで下がっていない場合

				// 位置を下げる
				pos.y -= 2.0f;
			}

			// タライの生成処理
			SetTarai();
		}
		else
		{ // 上記以外

			if (pos.y < m_fUpPosY)
			{ // 規定の位置まで上がっていない場合

				// 位置を上げる
				pos.y += 2.0f;
			}

			// 落下状況を false にする
			m_bFall = false;
		}

		// 位置の設定処理
		SetPos(pos);
	}

	// タライのカウント判断処理
	CountJudge();

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{ // タライが NULL じゃない場合

			// タライの更新処理
			m_apTarai[nCnt]->Update();
		}
	}
}

//=====================================
// ひもの描画処理
//=====================================
void CHimo::Draw(void)
{
	// 描画処理
	CObstacle::Draw(1.0f);

	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] != NULL)
		{
			m_apTarai[nCnt]->Draw();
		}
	}
}

//=====================================
// たらいの存在確認処理
//=====================================
void CHimo::TaraiCheck(void)
{
	for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
	{
		if (m_apTarai[nCnt] == nullptr)
		{ // タライが NULL じゃない場合

			// 落下状況を false にする
			m_bFall = false;

			// この先の処理を行わない
			return;
		}
	}

	// 落下状況を true にする
	m_bFall = true;
}

//=====================================
// たらいの生成処理
//=====================================
void CHimo::SetTarai(void)
{
	// ランダムの範囲を宣言
	int nRandX;
	int nRandY;

	if (m_bFall == false)
	{ // 落下状況が false の場合

		for (int nCnt = 0; nCnt < MAX_TARAI; nCnt++)
		{
			if (m_apTarai[nCnt] == NULL)
			{ // タライが NULL の場合

				// 座標をランダムで算出
				nRandX = rand() % TARAI_FALL_AREA_X;
				nRandY = rand() % TARAI_FALL_AREA_Z;

				// タライを生成
				m_apTarai[nCnt] = CTarai::Create(D3DXVECTOR3((float)nRandX - ((float)TARAI_FALL_AREA_X * 0.5f), 1000.0f, (float)nRandY - ((float)TARAI_FALL_AREA_Z * 0.5f)), this);
				m_apTarai[nCnt]->SetIndex(nCnt);

				// タライの落ちたカウント数を加算する
				m_nTaraiCount++;

				// for文を抜け出す
				break;
			}
		}
	}
}

//=====================================
// タライのカウント判断処理
//=====================================
void CHimo::CountJudge(void)
{
	if (m_nTaraiCount >= TARAI_COUNT)
	{ // カウントが一定以上の場合

		// タライカウントを0にする
		m_nTaraiCount = 0;

		// アクション状況を false にする
		SetAction(false);
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CHimo::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 上がる位置・下がる位置を設定する
	m_fDownPosY = pos.y - 50.0f;
	m_fUpPosY = pos.y;
}

//=====================================
// 紐を引っ張られた時の処理
//=====================================
void CHimo::Action(void)
{
	// アクション状況を true にする
	SetAction(true);

	// ひものSE鳴らす
	CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_HIMO);
}

//=====================================
// ヒット処理
//=====================================
bool CHimo::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	for (int nCntTarai = 0; nCntTarai < MAX_TARAI; nCntTarai++)
	{
		if (m_apTarai[nCntTarai] != nullptr)
		{ // タライが NULL じゃない場合

			if (pPlayer->GetPos().y + collSize.y <= m_apTarai[nCntTarai]->GetPosOld().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				pPlayer->GetPos().y + collSize.y >= m_apTarai[nCntTarai]->GetPos().y + m_apTarai[nCntTarai]->GetFileData().vtxMin.y &&
				useful::CylinderInner(pPlayer->GetPos(), m_apTarai[nCntTarai]->GetPos(), m_apTarai[nCntTarai]->GetFileData().fRadius + collSize.x) == true)
			{ // タライが頭上に落ちてきた場合

				// タライが頭に落ちる音を鳴らす
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TUB);

				// true を返す
				return true;
			}
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CHimo::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // 円の範囲内の場合

		// trueを返す
		return true;
	}

	// false を返す
	return false;
}