//============================================
//
//	敵の処理 [Enemy3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "Enemy3D.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "bullet3D.h"
#include "time.h"
#include "effect.h"
#include "debugproc.h"
#include "texture.h"
#include "Xmodel.h"
#include "player3D.h"
#include "particle.h"
#include "score.h"
#include "LifeGaugeBillboard.h"
#include "break_block3D.h"
#include "LevelPoint3D.h"
#include "EnemyBullet3D.h"
#include "sound.h"

//マクロ定義
#define ENEMY_WIGHT (40.0f)		//横幅
#define ENEMY_HEIGHT (40.0f)	//縦幅
#define ENEMY_SPEED (20.0f)		//敵のスピード
#define ENEMY_SCORE (200)		//敵がしんだときの加算スコア
#define ENEMYNORMAL_LIFE (3)	//通常敵の体力
#define ENEMYWALL_LIFE (2)		//壁敵の体力
#define ENEMYGROUND_LIFE (5)	//地上敵の体力
#define WAIT_TIME (2)			//プレイヤーの無敵時間の長さ
#define DAMAGE_TIME (3)			//プレイヤーのダメージリアクションの長さ
#define BULLET_TIME (60)		//弾を撃つまでのカウント
#define JUMP_TIME	(300)		//ジャンプまでのカウント

//静的メンバ変数宣言
int CEnemy3D::m_nIdxXModel[ENEMY_MAX] = {};			//Xモデルの使用番号
int CEnemy3D::m_nIdxTexture[ENEMY_MAX][64] = {};	//Xモデルのテクスチャの使用番号

//====================================================================
//コンストラクタ
//====================================================================
CEnemy3D::CEnemy3D(ENEMY_TYPE Type, int nPriority) : CObjectX(nPriority)
{
	m_pLifeGauge = NULL;
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Type = Type;
	pEnemy = NULL;
	m_BulletCount = 0;
	m_JumpCount = 0;
	m_bJump = false;
	m_bDeath = false;
	m_bDeathCountFlog = false;
	m_nDeathStopCount = 2;

	switch (m_Type)
	{
	case ENEMY_NORMAL:
		SetWight(ENEMY_WIGHT);
		SetHeight(ENEMY_HEIGHT);
		m_nLife = ENEMYNORMAL_LIFE;
		break;
	case ENEMY_WALLD:
		SetWight(ENEMY_WIGHT);
		SetHeight(ENEMY_HEIGHT);
		m_nLife = ENEMYWALL_LIFE;
		break;
	case ENEMY_WALLU:
		SetWight(0.0f);
		SetHeight(0.0f);
		m_nLife = 0;
		break;
	case ENEMY_GROUND:
		SetWight(ENEMY_WIGHT);
		SetHeight(ENEMY_HEIGHT);
		m_nLife = ENEMYGROUND_LIFE;
		break;
	}

	switch (m_Type)
	{
	case ENEMY_NORMAL:
		break;
	case ENEMY_WALLD:
		break;
	case ENEMY_WALLU:
		break;
	case ENEMY_GROUND:
		break;
	}
}

//====================================================================
//デストラクタ
//====================================================================
CEnemy3D::~CEnemy3D()
{

}

//====================================================================
//生成処理
//====================================================================
CEnemy3D *CEnemy3D::Create(ENEMY_TYPE Type)
{
	CEnemy3D *pEnemy = NULL;

	if (pEnemy == NULL)
	{
		//敵の生成
		pEnemy = new CEnemy3D(Type);
	}

	//オブジェクトの初期化処理
	if (FAILED(pEnemy->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pEnemy;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CEnemy3D::Init(void)
{
	SetType(CObject::TYPE_ENEMY3D);

	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	switch (m_Type)
	{
	case ENEMY_NORMAL:
		//Xファイルの割り当て
		m_nIdxXModel[ENEMY_NORMAL] = pXModel->Regist("data\\MODEL\\Enemy00.x");
		pTexture->XModelRegist(&m_nIdxTexture[ENEMY_NORMAL][0], m_nIdxXModel[ENEMY_NORMAL]);
		break;
	case ENEMY_WALLD:
		//Xファイルの割り当て
		m_nIdxXModel[ENEMY_WALLD] = pXModel->Regist("data\\MODEL\\EnemyWallD.x");
		pTexture->XModelRegist(&m_nIdxTexture[ENEMY_WALLD][0], m_nIdxXModel[ENEMY_WALLD]);
		pEnemy = Create(ENEMY_WALLU);
		break;
	case ENEMY_WALLU:
		//Xファイルの割り当て
		m_nIdxXModel[ENEMY_WALLU] = pXModel->Regist("data\\MODEL\\EnemyWallU.x");
		pTexture->XModelRegist(&m_nIdxTexture[ENEMY_WALLU][0], m_nIdxXModel[ENEMY_WALLU]);
		break;
	case ENEMY_GROUND:
		//Xファイルの割り当て
		m_nIdxXModel[ENEMY_GROUND] = pXModel->Regist("data\\MODEL\\EnemyGround.x");
		pTexture->XModelRegist(&m_nIdxTexture[ENEMY_GROUND][0], m_nIdxXModel[ENEMY_GROUND]);
		break;
	}

	if (m_Type != ENEMY_WALLU)
	{
		D3DXVECTOR3 pos = GetPos();

		//ライフゲージの生成と設定
		m_pLifeGauge = CLifeGaugeBillboard::Create();
		m_pLifeGauge->SetPos(D3DXVECTOR3(pos.x - ENEMY_WIGHT, pos.y - 20.0f, pos.z));
		m_pLifeGauge->SetGaugeMax(m_nLife);
		m_pLifeGauge->SetGauge(m_nLife);
	}

	CObjectX::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CEnemy3D::Uninit(void)
{
	if (m_Type != ENEMY_WALLU)
	{
		if (m_pLifeGauge != NULL)
		{
			m_pLifeGauge->SetDeathFlag(true);
		}

		CObjectX::Uninit();
	}
}
//====================================================================
//NULLにする処理
//====================================================================
void CEnemy3D::SetNULL(void)
{
	m_pLifeGauge = NULL;

	if (pEnemy != NULL)
	{
		pEnemy->SetEnemyType(ENEMY_NORMAL);
		pEnemy->Uninit();
		pEnemy = NULL;
	}
}

//====================================================================
//更新処理
//====================================================================
void CEnemy3D::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPos();

	//過去の位置設定
	SetPosOld(GetPos());

	//敵の状態管理
	StateManager();

	switch (m_Type)
	{
	case ENEMY_NORMAL:

		//敵の動き
		pos = MoveNormal(pos);

		//ライフゲージの位置更新
		m_pLifeGauge->SetPos(D3DXVECTOR3(pos.x - ENEMY_WIGHT, pos.y - 20.0f, pos.z));

		break;

	case ENEMY_WALLD:

		//敵の動き
		pos = MoveWallD(pos);

		//ライフゲージの位置更新
		m_pLifeGauge->SetPos(D3DXVECTOR3(pos.x - ENEMY_WIGHT, pos.y - 20.0f, pos.z));

		break;

	case ENEMY_WALLU:

		//敵の動き
		MoveWallU(pos);

		break;

	case ENEMY_GROUND:

		//敵の動き
		pos = MoveGround(pos);

		//ライフゲージの位置更新
		m_pLifeGauge->SetPos(D3DXVECTOR3(pos.x - ENEMY_WIGHT, pos.y - 20.0f, pos.z));

		break;
	}
	//位置の設定
	SetPos(pos);

	//情報の設定
	CObjectX::Update();

	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	if (pPlayer->GetPos().y + 400.0f < pos.y &&
		CGame::GetEventStart() == false)
	{
		Uninit();
		return;
	}

	if (m_bDeathCountFlog == true)
	{
		if (m_nDeathStopCount > 0)
		{
			m_nDeathStopCount--;
		}
		else
		{
			Death(pos, 200.0f, 6);
		}
	}
}

//====================================================================
//通常敵の更新処理
//====================================================================
D3DXVECTOR3 CEnemy3D::MoveNormal(D3DXVECTOR3 pos)
{
	//プレイヤーの位置を取得する
	CPlayer3D *pPlayer = CGame::GetPlayer3D();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	PlayerPos.y += pPlayer->GetHeight() * 0.25f;

	//敵がプレイヤーに追尾する
	m_move = PlayerPos - pos;
	D3DXVec3Normalize(&m_move, &m_move);
	m_move *= ENEMY_SPEED;

	//減衰係数
	m_move = m_move * 0.1f;

	//X軸の位置設定
	pos.x += m_move.x;
	//X軸のブロックとの当たり判定
	CollisionBlock(&pos, true);

	//Y軸の位置設定
	pos.y += m_move.y;
	//Y軸のブロックとの当たり判定
	CollisionBlock(&pos, false);

	return pos;
}

//====================================================================
//壁に張り付く敵の更新処理
//====================================================================
D3DXVECTOR3 CEnemy3D::MoveWallD(D3DXVECTOR3 pos)
{
	if (pos.x >= 0.0f)
	{//右にいる時

		//向きの設定
		SetRot(D3DXVECTOR3(0.0f, 0.0f, 1.57f));

		//重力
		pos.x += 10.0f;

		//床の判定
		if (pos.x > 400.0f)
		{
			pos.x = 400.0f;
		}
	}
	else
	{//左にいる時
		SetRot(D3DXVECTOR3(0.0f, 0.0f, -1.57f));

		//重力
		pos.x -= 10.0f;

		//床の判定
		if (pos.x < -360.0f)
		{
			pos.x = -360.0f;
		}
	}

	////X軸の位置設定
	pos.x += m_move.x;
	//X軸のブロックとの当たり判定
	CollisionBlock(&pos, true);

	//Y軸の位置設定
	pos.y += m_move.y;
	//Y軸のブロックとの当たり判定
	CollisionBlock(&pos, false);

	//頭パーツの位置設定
	pEnemy->SetPos(D3DXVECTOR3(
		pos.x + cosf(GetRot().z + 0.75f) * 25.0f,
		pos.y + sinf(GetRot().z + 0.75f) * 25.0f,
		pos.z
	));

	return pos;
}

//====================================================================
//壁に張り付く敵の更新処理
//====================================================================
void CEnemy3D::MoveWallU(D3DXVECTOR3 pos)
{
	//プレイヤーの位置を取得する
	CPlayer3D *pPlayer = CGame::GetPlayer3D();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	PlayerPos.y += pPlayer->GetHeight() * 0.25f;

	if (sqrtf((pos.x - PlayerPos.x) * (pos.x - PlayerPos.x)
		+ (pos.y - PlayerPos.y) * (pos.y - PlayerPos.y)) <= 600.0f)
	{//円の判定が当たった

		//プレイヤーの方をむ向く
		float fAngle = atan2f(pos.x - PlayerPos.x, PlayerPos.y - pos.y);
		SetRot(D3DXVECTOR3(0.0f, 0.0f, fAngle));

		if (m_BulletCount < BULLET_TIME)
		{
			m_BulletCount++;
		}
		else
		{
			m_BulletCount = 0;

			CEenmyBullet3D *pBullet = CEenmyBullet3D::Create();
			pBullet->SetPos(pos);
			pBullet->SetLife(60);
			pBullet->SetMove(D3DXVECTOR3
			(
				sinf(-fAngle) * 7.5f,
				cosf(fAngle) * 7.5f,
				0.0f
			));
		}
	}
}

//====================================================================
//地上敵の更新処理
//====================================================================
D3DXVECTOR3 CEnemy3D::MoveGround(D3DXVECTOR3 pos)
{
	//プレイヤーの位置を取得する
	CPlayer3D *pPlayer = CGame::GetPlayer3D();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
	PlayerPos.y += pPlayer->GetHeight() * 0.25f;

	//重力
	m_move.y -= 0.98f;

	if (m_JumpCount > JUMP_TIME)
	{
		if (PlayerPos.x >= pos.x)
		{
			m_move.x = 10.0f;
			m_move.y = 20.0f;
		}
		else
		{
			m_move.x = -10.0f;
			m_move.y = 20.0f;
		}
		m_JumpCount = 0;
	}
	else
	{
		m_JumpCount++;
	}

	if (PlayerPos.x >= pos.x)
	{
		SetRot(D3DXVECTOR3(0.0f, 3.14f, 0.0f));
	}
	else
	{
		SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	}

	//減衰係数
	m_move.x = m_move.x * 0.98f;

	//X軸の位置設定
	pos.x += m_move.x;
	//X軸のブロックとの当たり判定
	CollisionBlock(&pos, true);

	//Y軸の位置設定
	pos.y += m_move.y;
	//Y軸のブロックとの当たり判定
	if (CollisionBlock(&pos, false) == true)
	{
		m_move.x = 0.0f;
	}

	return pos;
}

//====================================================================
//描画処理
//====================================================================
void CEnemy3D::Draw(void)
{
	CObjectX::Draw();
}

//====================================================================
//状態管理
//====================================================================
void CEnemy3D::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;

	case STATE_DAMAGE:
		if (m_StateCount <= 0)
		{
			SetMatColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_State = STATE_WAIT;
			m_StateCount = WAIT_TIME;
		}
		break;

	case STATE_WAIT:
		if (m_StateCount <= 0)
		{
			SetDefColor();
			m_State = STATE_NORMAL;
		}
		break;
	}

	if (m_StateCount > 0)
	{
		m_StateCount--;
	}
}

//====================================================================
//ヒット処理
//====================================================================
void CEnemy3D::Hit(D3DXVECTOR3 pos, int Damage)
{
	if (m_nLife > 0)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENEMY_DAMAGE);
		m_nLife -= Damage;
		if (m_nLife < 0)
		{
			m_nLife = 0;
		}
		m_pLifeGauge->SetGauge(m_nLife);
	}
	SetMatColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_State = STATE_DAMAGE;
	m_StateCount = DAMAGE_TIME;

	if (m_nLife <= 0 && m_bDeath == false && m_Type != ENEMY_WALLU)
	{
		Death(pos, 200.0f, 6);
	}
}

//====================================================================
//死亡時処理
//====================================================================
void CEnemy3D::Death(D3DXVECTOR3 pos,float nRadius,int BreakCount)
{
	if (m_bDeathCountFlog == true && m_nDeathStopCount <= 0)
	{
		//プレイヤーの取得
		CPlayer3D *pPlayer = CGame::GetPlayer3D();

		//コンボ加算処理
		pPlayer->AddCombo();

		//必殺ゲージ加算処理
		if (pPlayer->GetUseUlt() == false)
		{
			pPlayer->AddUlt();
		}

		//コンボ数による経験値生成数設定
		int nCnmbo = pPlayer->GetCombo();
		nCnmbo = (nCnmbo / 5) + 1;

		//踏んだ時用
		m_nLife = 0;

		//パーティクルの生成
		CParticle::Create
		(
			pos,
			D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
			10,
			50.0f,
			2
		);
		//スコアの加算
		CGame::GetScore()->AddScore(ENEMY_SCORE);

		//円の当たり判定
		CollisionObjectCircle(pos, nRadius, BreakCount);

		//移動量の設定
		D3DXVECTOR3 Move;

		//自分の円周上のランダムな位置に経験値を飛ばす
		for (int nCnt = 0; nCnt < nCnmbo; nCnt++)
		{
			Move.x = sinf((float)(rand() % 731 - (731 - 1) / 2) / 100.0f + D3DX_PI * -0.5f);
			Move.y = cosf((float)(rand() % 731 - (731 - 1) / 2) / 100.0f + D3DX_PI * -0.5f);
			Move.z = 0.0f;

			D3DXVec3Normalize(&Move, &Move);
			Move *= 15.0f;

			CLevelPoint *pLevelPoint = CLevelPoint::Create();
			pLevelPoint->SetPos(pos);
			pLevelPoint->SetMove(Move);
		}

		//階層構造の頭部分を消す
		if (pEnemy != NULL)
		{
			pEnemy->Uninit();
		}

		m_bDeath = true;
		Uninit();
	}
	else if(m_bDeathCountFlog == false)
	{
		if (CGame::GetEventStart() == true)
		{//イベントのモンスターハウス内の場合
			CGame::GetMap2D()->DeleteEventEnemy();
		}

		if (CGame::GetMap2D()->GetEventEnemy() == 0)
		{
			CGame::GetMap2D()->SetDirectionPos(pos);
		}

		m_bDeathCountFlog = true;
		SetMatColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

//====================================================================
//ブロックとの当たり判定処理
//====================================================================
bool CEnemy3D::CollisionBlock(D3DXVECTOR3 *pos, bool bX)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();
			D3DXVECTOR3 ObjPos = pObj->GetPos();

			if (sqrtf((pos->x - ObjPos.x) * (pos->x - ObjPos.x)
				+ (pos->y - ObjPos.y) * (pos->y - ObjPos.y)) <= 100.0f)
			{//円の判定が当たった

				CObject::TYPE type = pObj->GetType();			//種類を取得

				if (type == TYPE_BREAKBLOCK3D)
				{//種類がブロックの時
					if (pObj->Collision(pos, GetPosOld(), &m_move, ENEMY_HEIGHT * 0.5f, ENEMY_WIGHT * 0.5f, bX) == true)
					{
						return true;
					}
				}
			}
			pObj = pObjNext;
		}
	}
	return false;
}

//====================================================================
//オブジェクトの当たり判定処理(円)
//====================================================================
void CEnemy3D::CollisionObjectCircle(D3DXVECTOR3 pos, float nRadiusOut, int BreakCount)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();
			CObject::TYPE type = pObj->GetType();				//種類を取得
			if (type == TYPE_BREAKBLOCK3D)
			{//種類が敵の時
				CBreak_Block3D *pBreakBlock = (CBreak_Block3D*)pObj;

				D3DXVECTOR3 CollisionPos = pBreakBlock->GetPos();			//位置を取得

				if (sqrtf((pos.x - CollisionPos.x) * (pos.x - CollisionPos.x)
					+ (pos.y - CollisionPos.y) * (pos.y - CollisionPos.y)) <= nRadiusOut)
				{//円の判定が当たった
					if (sqrtf((pos.x - CollisionPos.x) * (pos.x - CollisionPos.x)
						+ (pos.y - CollisionPos.y) * (pos.y - CollisionPos.y)) <= nRadiusOut * 0.5f)
					{//円の判定が当たった
						pBreakBlock->BreakCountSet((int)(BreakCount * 0.5f));
					}
					else
					{
						pBreakBlock->BreakCountSet(BreakCount);
					}
				}
			}
			else if (type == TYPE_ENEMY3D
				&& pObj != this
				&& pObj->GetLife() > 0)
			{//種類が敵の時
				D3DXVECTOR3 CollisionPos = pObj->GetPos();			//位置を取得

				if (sqrtf((pos.x - CollisionPos.x) * (pos.x - CollisionPos.x)
					+ (pos.y - CollisionPos.y) * (pos.y - CollisionPos.y)) <= nRadiusOut)
				{//円の判定が当たった
					pObj->Hit(CollisionPos, 2);
				}
			}
			pObj = pObjNext;
		}
	}
}