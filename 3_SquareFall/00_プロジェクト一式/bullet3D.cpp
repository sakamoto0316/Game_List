//============================================
//
//	弾の処理 [bullet3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "bullet3D.h"
#include "object.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "effect.h"
#include "particle.h"
#include "score.h"
#include "Enemy3D.h"
#include "Break.h"
#include "sound.h"

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
CBullet3D::CBullet3D(BULLET_TYPE Type, int nPriority) : CObjectBillboard(nPriority)
{
	m_Type = Type;
	m_SpreadCount = 0;
	SetWight(BULLET_WIGHT);
	SetHeight(BULLET_HEIGHT);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_stop = BULLET_STOP;
	m_nLife = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CBullet3D::~CBullet3D()
{

}

//====================================================================
//生成処理
//====================================================================
CBullet3D *CBullet3D::Create(BULLET_TYPE Type)
{
	CBullet3D *pBullet = NULL;

	if (pBullet == NULL)
	{
		//オブジェクト3Dの生成
		pBullet = new CBullet3D(Type);
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
HRESULT CBullet3D::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Bullet00.png");

	SetType(CObject::TYPE_BULLET3D);

	CObjectBillboard::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBullet3D::Uninit(void)
{
	CObjectBillboard::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CBullet3D::Update(void)
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
			Hit(pos);
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
void CBullet3D::Draw(void)
{
	CObjectBillboard::Draw();
}

//====================================================================
//弾の当たり判定処理
//====================================================================
bool CBullet3D::CollisionObject(D3DXVECTOR3 pos)
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

			if (type == TYPE_ENEMY3D)
			{//種類が敵の時
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					//敵の終了処理
					pObj->Hit(CollsionPos, 1);

					//弾がぶつかったときの処理
					Hit(pos);

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
						D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
						20,
						50.0f,
						1
					);

					//弾がぶつかったときの処理
					Hit(pos);

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
					CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_BREAK_BLOCK);

					//パーティクルの生成
					CParticle::Create
					(
						pos,
						D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
						20,
						50.0f,
						1
					);

					CBreak *pPiece = CBreak::Create(pObj->GetPos());

					//ブロックの終了処理
					pObj->Uninit();

					//弾がぶつかったときの処理
					Hit(pos);

					return true;
				}
			}
			else if (type == TYPE_BLOCKUI)
			{//種類がブロックの時
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT_PUSH);

					//パーティクルの生成
					CParticle::Create
					(
						pos,
						D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f),
						20,
						50.0f,
						1
					);

					//敵の終了処理
					pObj->Hit(CollsionPos, 1);

					//弾がぶつかったときの処理
					Hit(pos);

					return true;
				}
			}


			pObj = pObjNext;
		}
	}
	return false;
}

//====================================================================
//弾が当たった時の処理
//====================================================================
void CBullet3D::Hit(D3DXVECTOR3 pos)
{
	CBullet3D *pBullet = NULL;

	switch (m_Type)
	{
	case BULLET_NORMAL:
		//パーティクルの生成
		CParticle::Create
		(
			pos,
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			20,
			50.0f,
			1
		);
		break;

	case BULLET_SPREAD_3WAY:

		for (int nCntBullet = 0; nCntBullet < 3; nCntBullet++)
		{
			pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
			pBullet->SetPos(pos);
			D3DXVECTOR3 rot = GetRot();
			pBullet->SetMove(D3DXVECTOR3
			(
				sinf((D3DX_PI *  (-0.25f + 0.25f * nCntBullet)) + rot.z) * 10.0f,
				cosf((D3DX_PI *  (-0.25f + 0.25f * nCntBullet)) + rot.z) * 10.0f,
				0.0f
			));
			pBullet->SetRot(rot);
			pBullet->SetLife(20);
			pBullet->SetVerTex();
		}
		break;

	case BULLET_SPREAD_CONTINUE_3WAY:

		if (m_SpreadCount > 0)
		{
			for (int nCntBullet = 0; nCntBullet < 2; nCntBullet++)
			{
				pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
				pBullet->SetPos(pos);
				D3DXVECTOR3 rot = GetRot();
				pBullet->SetMove(D3DXVECTOR3
				(
					sinf((D3DX_PI *  (-0.75f - 0.5f * nCntBullet)) + rot.z) * 10.0f,
					cosf((D3DX_PI *  (-0.75f - 0.5f * nCntBullet)) + rot.z) * 10.0f,
					0.0f
				));
				pBullet->SetRot(rot);
				pBullet->SetLife(20);
				pBullet->SetVerTex();
			}

			pBullet = CBullet3D::Create(CBullet3D::BULLET_SPREAD_CONTINUE_3WAY);
			pBullet->SetPos(pos);
			D3DXVECTOR3 rot = GetRot();
			pBullet->SetMove(D3DXVECTOR3
			(
				sinf((D3DX_PI * -1.0f) + rot.z) * 10.0f,
				cosf((D3DX_PI * -1.0f) + rot.z) * 10.0f,
				0.0f
			));
			pBullet->SetRot(rot);
			pBullet->SetLife(20);
			pBullet->SetVerTex();
			m_SpreadCount--;
			pBullet->SetSpreadCount(m_SpreadCount);
		}
		else
		{
			for (int nCntBullet = 0; nCntBullet < 3; nCntBullet++)
			{
				pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
				pBullet->SetPos(pos);
				D3DXVECTOR3 rot = GetRot();
				pBullet->SetMove(D3DXVECTOR3
				(
					sinf((D3DX_PI *  (-0.75f - 0.25f * nCntBullet)) + rot.z) * 10.0f,
					cosf((D3DX_PI *  (-0.75f - 0.25f * nCntBullet)) + rot.z) * 10.0f,
					0.0f
				));
				pBullet->SetRot(rot);
				pBullet->SetLife(20);
				pBullet->SetVerTex();
			}
		}

		break;

	case BULLET_SPREAD_CROSS:

			for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
			{
				pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
				pBullet->SetPos(pos);
				D3DXVECTOR3 rot = GetRot();
				pBullet->SetMove(D3DXVECTOR3
				(
					sinf((D3DX_PI *  (-0.75f + 0.5f * nCntBullet)) + rot.z) * 10.0f,
					cosf((D3DX_PI *  (-0.75f + 0.5f * nCntBullet)) + rot.z) * 10.0f,
					0.0f
				));
				pBullet->SetRot(D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI *  (-0.75f + 0.5f * nCntBullet)) + rot.z));
				pBullet->SetLife(20);
				pBullet->SetVerTex();
			}

		break;

	case BULLET_SPREAD_EXCROSS:

		for (int nCntBullet = 0; nCntBullet < 4; nCntBullet++)
		{
			pBullet = CBullet3D::Create(CBullet3D::BULLET_SPREAD_3WAY);
			pBullet->SetPos(pos);
			D3DXVECTOR3 rot = GetRot();
			pBullet->SetMove(D3DXVECTOR3
			(
				sinf((D3DX_PI *  (-0.75f + 0.5f * nCntBullet)) + rot.z) * 10.0f,
				cosf((D3DX_PI *  (-0.75f + 0.5f * nCntBullet)) + rot.z) * 10.0f,
				0.0f
			));
			pBullet->SetRot(D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI *  (-0.75f + 0.5f * nCntBullet)) + rot.z));
			pBullet->SetLife(20);
			pBullet->SetVerTex();
		}
		m_SpreadCount--;
		SetSpreadCount(m_SpreadCount);

		break;
	}

	//自分の終了処理
	Uninit();
}