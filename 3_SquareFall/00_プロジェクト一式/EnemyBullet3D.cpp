//============================================
//
//	敵の弾の処理 [EnemyBullet3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "EnemyBullet3D.h"
#include "object.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "effect.h"
#include "particle.h"
#include "score.h"
#include "Enemy3D.h"
#include "Game.h"

//マクロ定義
#define BULLET_WIGHT (10.0f)		//横幅
#define BULLET_HEIGHT (10.0f)		//縦幅
#define BULLET_SPEED (10.0f)		//プレイヤーの速さ
#define BULLET_STOP (0.5f)			//減衰係数
#define EFFECT_SIZE (35.0f)			//エフェクトの大きさ
#define EFFECT_LIFE (50)			//エフェクトの寿命

//====================================================================
//コンストラクタ
//====================================================================
CEenmyBullet3D::CEenmyBullet3D(int nPriority) : CObjectBillboard(nPriority)
{
	SetWight(BULLET_WIGHT);
	SetHeight(BULLET_HEIGHT);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_stop = BULLET_STOP;
	m_nLife = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CEenmyBullet3D::~CEenmyBullet3D()
{

}

//====================================================================
//生成処理
//====================================================================
CEenmyBullet3D *CEenmyBullet3D::Create()
{
	CEenmyBullet3D *pBullet = NULL;

	if (pBullet == NULL)
	{
		//オブジェクト3Dの生成
		pBullet = new CEenmyBullet3D();
	}

	//オブジェクトの初期化処理
	if (FAILED(pBullet->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pBullet;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CEenmyBullet3D::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Bullet00.png");

	SetType(CObject::TYPE_ENEMYBULLET3D);

	CObjectBillboard::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CEenmyBullet3D::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CEenmyBullet3D::Update(void)
{
	bool bHit = false;

	D3DXVECTOR3 pos = GetPos();

	//位置更新
	pos += m_move;

	//敵との当たり判定処理
	bHit = CollisionObject(pos);

	if (bHit == false)
	{
		//弾の寿命
		if (m_nLife <= 0)
		{
			//パーティクルの生成
			CParticle::Create
			(
				pos,
				D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f),
				20,
				50.0f,
				1
			);

			Uninit();
			return;
		}
		else
		{
			CEffect *pEffect = NULL;

			//エフェクトの生成
			pEffect = CEffect::Create();

			pEffect->SetPos(pos);
			pEffect->SetRadius(EFFECT_SIZE);
			pEffect->SetLife(EFFECT_LIFE);
			pEffect->SetColor(D3DXCOLOR(0.5f, 0.0f, 0.5f, 1.0f));

			m_nLife--;
		}

		SetPos(pos);

		//頂点情報の更新
		CObjectBillboard::Update();
	}
}

//====================================================================
//描画処理
//====================================================================
void CEenmyBullet3D::Draw(void)
{
	CObjectBillboard::Draw();
}

//====================================================================
//弾の当たり判定処理
//====================================================================
bool CEenmyBullet3D::CollisionObject(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();
			CObject::TYPE type = pObj->GetType();				//種類を取得
			D3DXVECTOR3 CollsionPos = pObj->GetPos();			//位置を取得
			float CollsionWight = pObj->GetWight() * 0.5f;		//幅を取得
			float CollsionHeight = pObj->GetHeight() * 0.5f;	//高さを取得
			float fmyWight = GetWight() * 0.5f;					//中心からの幅
			float fmyHeight = GetHeight() * 0.5f;				//中心からの高さ

			if (type == TYPE_PLAYER3D)
			{//種類が敵の時
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					//敵の終了処理
					pObj->HitDamage(1);

					//自分の終了処理
					Uninit();

					return true;
				}
			}
			else if (type == TYPE_NORMALBLOCK)
			{//種類がブロックの時
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					//パーティクルの生成
					CParticle::Create
					(
						pos,
						D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f),
						20,
						50.0f,
						1
					);

					//自分の終了処理
					Uninit();

					return true;
				}
			}
			else if (type == TYPE_BREAKBLOCK3D)
			{//種類がブロックの時
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					//パーティクルの生成
					CParticle::Create
					(
						pos,
						D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f),
						20,
						50.0f,
						1
					);

					//ブロックの終了処理
					pObj->Uninit();

					//スコアの加算
					CGame::GetScore()->AddScore(30);

					//自分の終了処理
					Uninit();

					return true;
				}
			}
			pObj = pObjNext;
		}
	}
	return false;
}