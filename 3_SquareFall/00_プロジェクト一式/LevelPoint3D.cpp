//============================================
//
//	経験値の処理 [LevelPoint3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "LevelPoint3D.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "texture.h"
#include "Xmodel.h"
#include "particle.h"
#include "player3D.h"
#include "effect.h"

//マクロ定義
#define LEVELPOINT_WIGHT (10.0f)	//横幅
#define LEVELPOINT_HEIGHT (10.0f)	//縦幅
#define LEVELPOINT_SPEED (20.0f)	//経験値のスピード

//静的メンバ変数宣言
int CLevelPoint::m_nIdxXModel = NULL;					//Xモデルの使用番号
int CLevelPoint::m_nIdxTexture[64] = {};				//Xモデルのテクスチャの使用番号

//====================================================================
//コンストラクタ
//====================================================================
CLevelPoint::CLevelPoint(int nPriority) : CObjectX(nPriority)
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	SetWight(LEVELPOINT_WIGHT);
	SetHeight(LEVELPOINT_HEIGHT);
	m_MoveState = MOVE_WAIT;
	m_MoveCount = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CLevelPoint::~CLevelPoint()
{

}

//====================================================================
//生成処理
//====================================================================
CLevelPoint *CLevelPoint::Create()
{
	CLevelPoint *pEnemy = NULL;

	if (pEnemy == NULL)
	{
		//敵の生成
		pEnemy = new CLevelPoint();
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
HRESULT CLevelPoint::Init(void)
{
	SetType(CObject::TYPE_LEVELPOINT3D);

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	m_nIdxXModel = pXModel->Regist("data\\MODEL\\LevelPoint.x");
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	pTexture->XModelRegist(&m_nIdxTexture[0], m_nIdxXModel);

	D3DXVECTOR3 pos = GetPos();

	CObjectX::Init();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CLevelPoint::Uninit(void)
{
	CObjectX::Uninit();
}

//====================================================================
//更新処理
//====================================================================
void CLevelPoint::Update(void)
{
	//位置の取得
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//過去の位置設定
	SetPosOld(GetPos());

	if (m_MoveState == MOVE_PLAYER)
	{
		//プレイヤーの情報を取得する
		CPlayer3D *pPlayer = CGame::GetPlayer3D();
		D3DXVECTOR3 PlayerPos = pPlayer->GetPos();
		PlayerPos.y += pPlayer->GetHeight() * 0.25f;

		//敵がプレイヤーに追尾する
		m_move = PlayerPos - pos;
		D3DXVec3Normalize(&m_move, &m_move);
		m_move *= LEVELPOINT_SPEED;
	}
	else
	{
		m_MoveCount++;
		if (m_MoveCount > 30)
		{
			m_MoveState = MOVE_PLAYER;
		}
	}

	//減衰係数
	m_move = m_move * 0.9f;

	//位置設定
	pos += m_move;

	rot.x += 0.1f;
	rot.z += 0.3f;

	CEffect *pEffect = CEffect::Create();
	pEffect->SetPos(pos);
	pEffect->SetRadius(LEVELPOINT_HEIGHT);
	pEffect->SetLife(20);
	pEffect->SetDel(0.2f);

	//位置の設定
	SetPos(pos);
	SetRot(rot);

	//情報の設定
	CObjectX::Update();
}

//====================================================================
//描画処理
//====================================================================
void CLevelPoint::Draw(void)
{
	CObjectX::Draw();
}