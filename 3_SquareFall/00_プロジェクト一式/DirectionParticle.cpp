//============================================
//
//	パーティクル処理 [DirectionParticle.cpp]
//	Author:sakamoto kai
//
//============================================
#include "DirectionParticle.h"
#include "effect.h"

//マクロ定義
#define STANDERD_SPEED1 (1.0f)	//パーティクルの基準のスピード
#define RAND_PAI1 (731)			//角度のランダム
#define PUT_PARTICLE1 (1)		//１フレームに出すパーティクルの数

//====================================================================
//コンストラクタ
//====================================================================
CDirectionParticle::CDirectionParticle()
{
	m_Rand = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nLife = 0;
	m_nSize = 0.0f;
	m_nType = 0;
}

//====================================================================
//コンストラクタ
//====================================================================
CDirectionParticle::CDirectionParticle(D3DXVECTOR3 pos, D3DXCOLOR col, float Radius, int nLife, float nSize, int nType)
{
	m_pos = pos;
	m_col = col;
	m_nLife = nLife;
	m_nSize = nSize;
	m_nType = nType;
	m_nRadius = Radius;
}

//====================================================================
//デストラクタ
//====================================================================
CDirectionParticle::~CDirectionParticle()
{

}

//====================================================================
//生成処理
//====================================================================
CDirectionParticle *CDirectionParticle::Create(D3DXVECTOR3 pos, D3DXCOLOR col, float Radius, int nLife, float nSize, int nType)
{
	CDirectionParticle *pParticle = NULL;

	if (pParticle == NULL)
	{
		//オブジェクト2Dの生成
		pParticle = new CDirectionParticle(pos, col, Radius, nLife, nSize, nType);
	}

	//オブジェクトの初期化処理
	if (FAILED(pParticle->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pParticle;
}

//====================================================================
//初期化
//====================================================================
HRESULT CDirectionParticle::Init(void)
{
	CEffect *pEffect = NULL;
	SetType(CObject::TYPE_PARTICLE);

	if (m_nType == 1)
	{
		for (int nCntAppear = 0; nCntAppear < PUT_PARTICLE1; nCntAppear++)
		{
			D3DXVECTOR3 StartPos = m_pos;

			//移動量の設定
			m_Rand.x = sinf((float)(rand() % RAND_PAI1 - (RAND_PAI1 - 1) / 2) / 100.0f + D3DX_PI * -0.5f);
			m_Rand.y = cosf((float)(rand() % RAND_PAI1 - (RAND_PAI1 - 1) / 2) / 100.0f + D3DX_PI * -0.5f);
			m_Rand.z = 0.0f;

			D3DXVec3Normalize(&m_Rand, &m_Rand);
			m_Rand *= m_nRadius;

			//移動量の設定
			m_move = m_Rand * -0.05f;

			//位置の設定
			StartPos += m_Rand;

			//エフェクトの生成
			pEffect = CEffect::Create();

			pEffect->SetPos(StartPos);
			pEffect->SetDel(2.0f);
			pEffect->SetMove(m_move);
			pEffect->SetColor(m_col);
			pEffect->SetRadius(m_nSize);
			pEffect->SetLife(m_nLife);
		}
	}

	Uninit();

	return S_OK;
}

//====================================================================
//パーティクルの終了処理
//====================================================================
void CDirectionParticle::Uninit(void)
{
	SetDeathFlag(true);
}

//====================================================================
//パーティクルの更新処理
//====================================================================
void CDirectionParticle::Update(void)
{

}

//====================================================================
//パーティクルの描画処理
//====================================================================
void CDirectionParticle::Draw(void)
{

}