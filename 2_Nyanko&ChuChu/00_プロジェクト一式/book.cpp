//===========================================
//
// 本の処理[book.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "book.h"
#include "useful.h"
#include "collision.h"
#include "sound.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SHIFT_HEIGHT			(27.5f)			// ずらす高さ
#define COLLAPSE_RANGE			(80.0f)			// ヒット判定の範囲
#define COLLAPSE_MOVE			(4.0f)			// 倒れ状態の移動量
#define COLLAPSE_GRAVITY		(8)				// 倒れ状態の重力
#define COLLAPSE_MIN_GRAVITY	(3)				// 倒れ状態の重力の最低値
#define COLLAPSE_ROT_CORRECT	(0.05f)			// 倒れ状態の向きの補正値
#define NEXT_MOVE_POS_Y			(20.0f)			// 次のオブジェクトが動き出す座標(Y軸)
#define DEATH_POS_Y				(0.0f)			// 見えなくなる座標(Y軸)
#define NONE_ACTIONID			(-1)			// アクションIDの初期値

//==============================
// コンストラクタ
//==============================
CBook::CBook() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		m_aBook[nCnt].pBook = nullptr;			// 本の情報
		m_aBook[nCnt].move = NONE_D3DXVECTOR3;	// 移動量
		m_aBook[nCnt].fGravity = 0.0f;			// 重力
		m_aBook[nCnt].bDisp = true;				// 描画状況
		m_aBook[nCnt].bMove = false;			// 移動状況
		m_aBook[nCnt].bSe = false;				// SE再生状況
	}
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
	m_nActionID = NONE_ACTIONID;	// アクションID
	m_fGravity = 0.0f;				// 重力
	m_bDisp = true;					// 描画状況
	m_bMove = false;				// 移動状況
	m_bSe = false;					// SE再生状況
	SetCatUse(true);				// ネコの使用条件
	SetRatUse(true);				// ネズミの使用条件
}

//==============================
// デストラクタ
//==============================
CBook::~CBook()
{

}

//==============================
// 本の初期化処理
//==============================
HRESULT CBook::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_aBook[nCnt].pBook == nullptr)
		{ // 本の情報が NULL の場合

			// 本を生成する
			m_aBook[nCnt].pBook = CModel::Create(TYPE_NONE, PRIORITY_BLOCK);
		}
		m_aBook[nCnt].move = NONE_D3DXVECTOR3;		// 移動量
		m_aBook[nCnt].fGravity = 0.0f;				// 重力
		m_aBook[nCnt].bDisp = true;					// 描画状況
		m_aBook[nCnt].bMove = false;			// 移動状況
		m_aBook[nCnt].bSe = false;				// SE再生状況
	}

	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
	m_nActionID = NONE_ACTIONID;	// アクションID
	m_fGravity = 0.0f;				// 重力
	m_bDisp = true;					// 描画状況
	m_bMove = false;				// 移動状況
	m_bSe = false;					// SE再生状況

	// 値を返す
	return S_OK;
}

//========================================
// 本の終了処理
//========================================
void CBook::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_aBook[nCnt].pBook != nullptr)
		{ // 本の情報が NULL じゃない場合

			// 本の終了処理
			m_aBook[nCnt].pBook->Uninit();
			m_aBook[nCnt].pBook = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 本の更新処理
//=====================================
void CBook::Update(void)
{
	// 前回の位置を設定する
	SetPosOld(GetPos());

	// 状態マネージャー
	StateManager();

	if (KillZ() == true)
	{ // 全てが一定の高さまで落ちた場合

		// 終了処理
		Uninit();

		// この先の処理を行わない
		return;
	}
}

//=====================================
// 本の描画処理
//=====================================
void CBook::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_aBook[nCnt].pBook != nullptr &&
			m_aBook[nCnt].bDisp == true)
		{ // 本の情報が NULL じゃない場合

			// 本の描画処理
			m_aBook[nCnt].pBook->Draw();
		}
	}

	if (m_bDisp == true)
	{ // 描画状況が true の場合

		// 描画処理
		CObstacle::Draw();
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CBook::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos,rot, type);

	// 向きの変数を宣言する
	float fRot;

	for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
	{
		if (m_aBook[nCnt].pBook != nullptr)
		{ // 本の情報が NULL じゃない場合

			// 向きをランダムで算出
			fRot = (rand() % 81 - 40) * 0.01f;

			// 本(赤)の向きにプラスする
			fRot +=GetRot().y;

			// 情報を設定する
			m_aBook[nCnt].pBook->SetPos(D3DXVECTOR3(pos.x, pos.y + ((nCnt + 1) * SHIFT_HEIGHT), pos.z));
			m_aBook[nCnt].pBook->SetPosOld(m_aBook[nCnt].pBook->GetPos());
			m_aBook[nCnt].pBook->SetRot(D3DXVECTOR3(0.0f, fRot, 0.0f));
			m_aBook[nCnt].pBook->SetScale(NONE_SCALE);
			m_aBook[nCnt].pBook->SetFileData((CXFile::TYPE)(CXFile::TYPE_BOOKBLUE + nCnt));
		}
	}
	m_move = NONE_D3DXVECTOR3;		// 移動量
	m_state = STATE_STOP;			// 状態
	m_fGravity = 0.0f;				// 重力
	m_nActionID = NONE_ACTIONID;	// アクションID
	m_bDisp = true;					// 描画状況
}

//=====================================
// 状態マネージャー
//=====================================
void CBook::StateManager(void)
{
	// 位置と向きを取得する
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();
	D3DXVECTOR3 objpos = NONE_D3DXVECTOR3;
	D3DXVECTOR3 objrot = NONE_D3DXVECTOR3;

	switch (m_state)
	{
	case CBook::STATE_STOP:			// 停止状態

		// 特になし

		break;

	case CBook::STATE_COLLAPSE:		// 倒れ状態

		if (m_bMove == true)
		{ // 移動状況が true の場合

			if(m_bSe == false)
			{ // SE再生してないとき

				// 歩くSE再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_BOOLDOWN);
				m_bSe = true;		//SE再生した状態にする
			}

			// 向きの補正処理
			useful::RotCorrect(D3DX_PI, &rot.z, COLLAPSE_ROT_CORRECT);

			// 重力処理
			useful::Gravity(&m_move.y, &pos.y, m_fGravity);

			// 移動量を加算する
			pos += m_move;
		}

		for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
		{
			if (m_aBook[nCnt].bMove == true)
			{ // 移動状況が true の場合

				if (m_aBook[nCnt].bSe == false)
				{ // SE再生してないとき

					// 歩くSE再生
					CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_BOOLDOWN);
					m_aBook[nCnt].bSe = true;		//SE再生した状態にする
				}

				// 位置と向きを取得する
				objpos = m_aBook[nCnt].pBook->GetPos();
				objrot = m_aBook[nCnt].pBook->GetRot();

				// 向きの補正処理
				useful::RotCorrect(D3DX_PI, &objrot.z, COLLAPSE_ROT_CORRECT);

				// 重力処理
				useful::Gravity(&m_aBook[nCnt].move.y, &objpos.y, m_aBook[nCnt].fGravity);

				// 移動量を加算する
				objpos += m_aBook[nCnt].move;

				// 位置と向きを設定する
				m_aBook[nCnt].pBook->SetPos(objpos);
				m_aBook[nCnt].pBook->SetRot(objrot);
			}
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 位置と向きを適用する
	SetPos(pos);
	SetRot(rot);
}

//=====================================
// Z軸による消去処理
//=====================================
bool CBook::KillZ(void)
{
	// 高さ状況
	bool bHeight = true;

	if (GetPos().y <= DEATH_POS_Y)
	{ // 位置が一定の位置以下になった場合

		// 描画状況を false にする
		m_bDisp = false;
	}
	else
	{ // 上記以外

		// 高さ状況を false にする
		bHeight = false;
	}

	if (m_aBook[2].pBook->GetPos().y <= m_aBook[1].pBook->GetPos().y - NEXT_MOVE_POS_Y)
	{ // 本が一定の位置まで落ちた場合

		// 移動状況を true にする
		m_aBook[1].bMove = true;
	}

	if (m_aBook[1].pBook->GetPos().y <= m_aBook[0].pBook->GetPos().y - NEXT_MOVE_POS_Y)
	{ // 本が一定の位置まで落ちた場合

		// 移動状況を true にする
		m_aBook[0].bMove = true;
	}

	if (m_aBook[0].pBook->GetPos().y <= GetPos().y - NEXT_MOVE_POS_Y)
	{ // 本が一定の位置まで落ちた場合

		// 移動状況を true にする
		m_bMove = true;
	}

	// 高さ状況を返す
	return bHeight;
}

//=====================================
// 当たり判定処理
//=====================================
bool CBook::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 move = pPlayer->GetMove();
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	D3DXVECTOR3 objMax = D3DXVECTOR3(GetFileData().vtxMax.x, GetFileData().vtxMax.y + (GetFileData().collsize.y * MAX_BOOK), GetFileData().vtxMax.z);
	collision::SCollision coll = { false,false,false,false,false,false };

	if (m_state == STATE_STOP)
	{ // 停止状態の場合

		// 六面体の当たり判定
		coll = collision::HexahedronClush
		(
			&pos,					// 位置
			GetPos(),				// 本の位置
			pPlayer->GetPosOld(),	// 前回の位置
			GetPosOld(),			// 本の前回の位置
			vtxMin,					// 最小値
			GetFileData().vtxMin,	// 本の最小値
			vtxMax,					// 最大値
			objMax					// 本の最小値
		);

		// 位置を適用する
		pPlayer->SetPos(pos);

		if (coll.bTop == true)
		{ // 上に乗った場合

			// 移動量を初期化する
			move.y = 0.0f;

			// 移動量を適用する
			pPlayer->SetMove(move);

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CBook::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 最大値と最小値を設定する
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);
	CModel* pBook = nullptr;

	if (pPlayer->GetPlayerIdx() != m_nActionID)
	{ // 発動した本人じゃなかった場合

		for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
		{
			// 本の情報を設定する
			pBook = m_aBook[nCnt].pBook;

			if (m_state == STATE_COLLAPSE &&
				useful::RectangleCollisionXY(pPlayer->GetPos(), pBook->GetPos(), vtxMax, pBook->GetFileData().vtxMax, vtxMin, pBook->GetFileData().vtxMin) == true &&
				useful::RectangleCollisionXZ(pPlayer->GetPos(), pBook->GetPos(), vtxMax, pBook->GetFileData().vtxMax, vtxMin, pBook->GetFileData().vtxMin) == true &&
				useful::RectangleCollisionYZ(pPlayer->GetPos(), pBook->GetPos(), vtxMax, pBook->GetFileData().vtxMax, vtxMin, pBook->GetFileData().vtxMin) == true)
			{ // 倒れ状態で本に当たった場合

				// true を返す
				return true;
			}
		}

		if (m_state == STATE_COLLAPSE &&
			useful::RectangleCollisionXY(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(pPlayer->GetPos(), GetPos(), vtxMax, GetFileData().vtxMax, vtxMin, GetFileData().vtxMin) == true)
		{ // 倒れ状態で本に当たった場合

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CBook::HitCircle(CPlayer* pPlayer, const float Radius)
{
	if (GetAction() == false &&
		useful::CircleCollisionXZ(pPlayer->GetPos(), GetPos(), Radius, GetFileData().fRadius) == true)
	{ // 停止状態かつ、円の範囲内の場合

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// 起動時の処理
//=====================================
void CBook::Action(CPlayer* pPlayer)
{
	if (m_state == STATE_STOP)
	{ // 停止状態の場合

		// 向きを取得する
		D3DXVECTOR3 rot = GetRot();

		// 倒れ状態にする
		m_state = STATE_COLLAPSE;

		// 移動量を設定する
		m_move.x = sinf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;
		m_move.z = cosf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;

		// 重力を設定する
		m_fGravity = (float)((rand() % COLLAPSE_GRAVITY + COLLAPSE_MIN_GRAVITY) * 0.01f);

		for (int nCnt = 0; nCnt < MAX_BOOK; nCnt++)
		{
			// 移動量を設定する
			m_aBook[nCnt].move.x = sinf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;
			m_aBook[nCnt].move.z = cosf(rot.y + (D3DX_PI * -0.5f)) * COLLAPSE_MOVE;

			// 重力を設定する
			m_aBook[nCnt].fGravity = (float)((rand() % COLLAPSE_GRAVITY + COLLAPSE_MIN_GRAVITY) * 0.01f);

			m_aBook[nCnt].pBook->SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_BOOKBLUE + nCnt));
		}
		SetFileData((CXFile::TYPE)(CXFile::TYPE_RED_BOOKRED));

		// 移動状況を true にする(動き始める)
		m_aBook[2].bMove = true;

		// アクション状況を true にする
		SetAction(true);

		// プレイヤーIdxを代入する
		m_nActionID = pPlayer->GetPlayerIdx();
	}
}