//============================================
//
//	プレイヤーの処理 [player3D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "player3D.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "game.h"
#include "time.h"
#include "debugproc.h"
#include "map2D.h"
#include "bullet3D.h"
#include "LifeGauge.h"
#include "enemy3D.h"
#include "XModel.h"
#include "texture.h"
#include "number.h"
#include "bosslevel.h"
#include "LevelUP.h"
#include "combo.h"
#include "BulletTypeUI.h"
#include "effect.h"
#include "DirectionParticle.h"
#include "Particle.h"
#include "sound.h"
#include "score.h"
#include "objectBillboard.h"

//マクロ定義
#define PLAYER_SPEED (10.0f)		//プレイヤーの速さ
#define PLAYER_FALLMAX (10.0f)		//プレイヤーが落下する最大速度
#define PLAYER_JAMPPOWER (14.0f)	//プレイヤーのジャンプ力
#define PLAYER_STOP (0.5f)			//減衰係数
#define ANIM_SPEED (4)				//アニメーションの速さ
#define PLAYER_LIFE (3)				//プレイヤーのデフォルトのライフ
#define BULLET_LIFE (20)			//プレイヤーが出す弾の寿命
#define SCROLL_LINE (500.0f)		//スクロールをするライン
#define GAME_WIGHT (240.0f)			//画面横の移動制限
#define ULTIMATE_OK (10)			//必殺ゲージのチャージ完了数値
#define ULTIMATE_LINESPEED (20.0f)	//必殺技の発動範囲の速度
#define ULTIMATE_LINEMAX (700.0f)	//必殺技の発動範囲の最大
#define START_BULLET_MAX (5)		//初期の弾の数
#define UP_BULLET_MAX (3)			//レベルアップの時に上がる弾の最大数
#define LEVELUP_POINT_ADDMAX (2)	//レベルアップに必要な経験値の増加量
#define PLAYER_COLLISION (90.0f)	//プレイヤーが当たり判定を行う範囲
#define WIDTH_COLLISION (30.0f)		//プレイヤーの横の当たり判定の大きさ
#define HEIGHT_COLLISION (30.0f)	//プレイヤーの縦の当たり判定の大きさ
#define WAIT_TIME (60)				//プレイヤーの無敵時間の長さ
#define DAMAGE_TIME (5)				//プレイヤーのダメージリアクションの長さ
#define LEVELUP_POINT (2)			//レベルアップに必要な経験値
#define BURST_SHOOT (3)				//バースト弾の連射数
#define BURST_COOLTIME (4)			//バースト弾の連射速度

//静的メンバ変数宣言
LPD3DXMESH CPlayer3D::m_pMesh = NULL;				//メッシュ(頂点情報)へのポインタ
LPD3DXBUFFER CPlayer3D::m_pBuffMat = NULL;			//マテリアルへのポインタ
DWORD CPlayer3D::m_dwNumMat = NULL;					//マテリアルの数
int CPlayer3D::m_nIdxXModel = NULL;					//Xモデルの使用番号
int CPlayer3D::m_nIdxTexture[64] = {};				//Xモデルのテクスチャの使用番号
CGuide *CPlayer3D::m_pGuide = NULL;
CObject2D *CPlayer3D::m_pUIPlayer = NULL;
CObject2D *CPlayer3D::m_pUIPlayerBG = NULL;
CObject2D *CPlayer3D::m_pUIPlayerFG = NULL;
CObject2D *CPlayer3D::m_pUIBullet = NULL;
CObject2D *CPlayer3D::m_pUIBulletBG = NULL;
CObject2D *CPlayer3D::m_pUIBulletFG = NULL;
CObject2D *CPlayer3D::m_pLifeUI = NULL;
CLifeGauge *CPlayer3D::m_pLifeGauge = NULL;
CObject2D *CPlayer3D::m_pLifeFG = NULL;
CObject2D *CPlayer3D::m_pUltimateUI = NULL;
CLifeGauge *CPlayer3D::m_pUltimateGauge = NULL;
CLifeGauge *CPlayer3D::m_pUltimateFG = NULL;
CObject2D *CPlayer3D::m_pBulletUI = NULL;
CLifeGauge *CPlayer3D::m_pBulletGauge = NULL;
CLifeGauge* CPlayer3D::m_pBulletFG = NULL;
CNumber* CPlayer3D::m_pBulletNumber[3] = {};
CLifeGauge *CPlayer3D::m_LevelGauge = NULL;
CLifeGauge *CPlayer3D::m_LevelFG = NULL;
CNumber *CPlayer3D::m_LevelNumber10 = NULL;
CNumber *CPlayer3D::m_LevelNumber1 = NULL;
CObject2D *CPlayer3D::m_pLvPolygon = NULL;
CCombo *CPlayer3D::m_pCombo = NULL;
CBulletTypeUI *CPlayer3D::m_pBulletTypeUI[3] = {};
CBulletTypeUI *CPlayer3D::m_pSelectBulletTypeUI = NULL;
CObject2D *CPlayer3D::m_pWarning = NULL;
CObject2D *CPlayer3D::m_pWarningTex[2] = {};
CObjectBillboard* CPlayer3D::m_NotBullet = NULL;

//====================================================================
//コンストラクタ
//====================================================================
CPlayer3D::CPlayer3D(int nPriority) : CObjectX(nPriority)
{
	m_vtxMin = D3DXVECTOR3(10000.0f, 10000.0f, 10000.0f);
	m_vtxMax = D3DXVECTOR3(-10000.0f, -10000.0f, -10000.0f);
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_stop = PLAYER_STOP;
	m_GuideRot = D3DXVECTOR3(0.0f, 0.0f, 3.14f);
	m_bJump = false;
	m_nLife = PLAYER_LIFE;
	m_Ultimate = 0;
	m_UltimateLine = 0.0f;
	m_UltimatePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bUseUlt = false;
	m_nBullet = START_BULLET_MAX;
	m_nBulletMax = m_nBullet;
	SetWight(WIDTH_COLLISION);
	SetHeight(HEIGHT_COLLISION);
	m_State = STATE_NORMAL;
	m_StateCount = 0;
	m_nLevelUp = LEVELUP_POINT;
	m_nLevelPoint = 0;
	m_nLevel = 1;
	m_bLevelNumber10 = false;
	m_BulletCoolTime = 0;
	m_BulletType = SHOT_NORMAL;
	m_MyBulletType[0] = SHOT_NORMAL;
	m_MyBulletType[1] = SHOT_NORMAL;
	m_MyBulletType[2] = SHOT_NORMAL;
	m_SelectBulletType = -1;
	m_SelectBulletTypeMax = 0;
	m_nBurstCount = BURST_SHOOT;
	m_nBurstCoolTime = 0;
	m_bMachingun = false;
	m_fMachingunJump = 0.0f;
	m_EvolutionCount = 0;
	m_nCombo = 0;
	m_UltimateSpin = 0.0f;
	m_FallMax = PLAYER_FALLMAX;
	m_FallCount = 0;
	m_bFallMax = false;
	m_MaxConboScore = 0;
	m_MaxFallScore = 0;
	m_DepthScore = 0.0f;
	m_bWarning = false;
}

//====================================================================
//デストラクタ
//====================================================================
CPlayer3D::~CPlayer3D()
{

}

//====================================================================
//生成処理
//====================================================================
CPlayer3D *CPlayer3D::Create()
{
	CPlayer3D *pPlayer = NULL;

	if (pPlayer == NULL)
	{
		//プレイヤーの生成
		pPlayer = new CPlayer3D();
	}

	//Xファイルの割り当て
	CXModel *pXModel = CManager::GetInstance()->GetXModel();
	m_nIdxXModel = pXModel->Regist("data\\MODEL\\Player01.x");
	CTexture *pTexture = CManager::GetInstance()->GetTexture();
	pTexture->XModelRegist(&m_nIdxTexture[0], m_nIdxXModel);

	//pXModel->GetXModelInfo(&m_pBuffMat, &m_dwNumMat, &m_pMesh, m_nIdxXModel);
	//pPlayer->BindFile(m_pMesh, m_pBuffMat, m_dwNumMat);

	//オブジェクトの初期化処理
	if (FAILED(pPlayer->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pPlayer;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CPlayer3D::Init(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	SetType(CObject::TYPE_PLAYER3D);

	CObjectX::Init();

	//SizeVtx();

	if (CScene::GetMode() == CScene::MODE_GAME)
	{
		//プレイヤーの情報UIを生成
		UICreate();
	}

	return S_OK;
}

//====================================================================
//プレイヤーの情報UIを生成
//====================================================================
void CPlayer3D::UICreate(void)
{
#if NUM_PLAYER == 0

	//ライフゲージの生成と設定
	m_pLifeUI = CObject2D::Create();
	m_pLifeUI->SetPos(D3DXVECTOR3(200.0f, 25.0f, 0.0f));
	m_pLifeUI->SetWight(150.0f);
	m_pLifeUI->SetHeight(37.5f);
	m_pLifeUI->SetTexture("data\\TEXTURE\\LIFE_UI.png");

	m_pLifeGauge = CLifeGauge::Create(false, false);
	m_pLifeGauge->SetPos(D3DXVECTOR3(70.0f, 50.0f, 0.0f));
	m_pLifeGauge->SetWight(225.0f);
	m_pLifeGauge->SetHeight(37.5f);
	m_pLifeGauge->SetGaugeMax(m_nLife);
	m_pLifeGauge->SetGauge(m_nLife);
	m_pLifeGauge->SetTilt(0.0f);

	m_pLifeFG = CObject2D::Create();
	m_pLifeFG->SetPos(D3DXVECTOR3(185.0f, 68.75f, 0.0f));
	m_pLifeFG->SetWight(225.0f);
	m_pLifeFG->SetHeight(37.5f);
	m_pLifeFG->SetColor(D3DXCOLOR(0.2f, 0.2f, 0.2f, 1.0f));
	m_pLifeFG->SetTexture("data\\TEXTURE\\GaugeFrame.png");
	
	//必殺ゲージの生成と設定
	m_pUltimateUI = CObject2D::Create();
	m_pUltimateUI->SetPos(D3DXVECTOR3(450.0f, 135.0f, 0.0f));
	m_pUltimateUI->SetWight(120.0f);
	m_pUltimateUI->SetHeight(60.0f);
	m_pUltimateUI->SetTexture("data\\TEXTURE\\ULT_UI.png");
	m_pUltimateUI->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

	m_pUltimateGauge = CLifeGauge::Create(false, false);
	m_pUltimateGauge->SetPos(D3DXVECTOR3(35.0f, 87.5f, 0.0f));
	m_pUltimateGauge->SetWight(345.0f);
	m_pUltimateGauge->SetHeight(30.0f);
	m_pUltimateGauge->SetTilt(7.5f);
	m_pUltimateGauge->SetGaugeMax(ULTIMATE_OK);
	m_pUltimateGauge->SetGauge(m_Ultimate);

	m_pUltimateFG = CLifeGauge::Create(false, false);
	m_pUltimateFG->SetPos(D3DXVECTOR3(35.0f, 87.5f, 0.0f));
	m_pUltimateFG->SetWight(345.0f);
	m_pUltimateFG->SetHeight(30.0f);
	m_pUltimateFG->SetTilt(7.5f);
	m_pUltimateFG->SetGaugeMax(ULTIMATE_OK);
	m_pUltimateFG->SetGauge(ULTIMATE_OK);
	m_pUltimateFG->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));

	//バレットゲージの生成と設定
	m_pBulletUI = CObject2D::Create();
	m_pBulletUI->SetPos(D3DXVECTOR3(180.0f, 140.0f, 0.0f));
	m_pBulletUI->SetWight(90.0f);
	m_pBulletUI->SetHeight(30.0f);
	m_pBulletUI->SetTexture("data\\TEXTURE\\BULLET_UI.png");

	m_pBulletGauge = CLifeGauge::Create(false, false);
	m_pBulletGauge->SetPos(D3DXVECTOR3(110.0f, 152.5f, 0.0f));
	m_pBulletGauge->SetWight(150.0f);
	m_pBulletGauge->SetHeight(30.0f);
	m_pBulletGauge->SetTilt(0.0f);
	m_pBulletGauge->SetGaugeMax(m_nBulletMax);
	m_pBulletGauge->SetGauge(m_nBullet);

	m_pBulletFG = CLifeGauge::Create(false, false);
	m_pBulletFG->SetPos(D3DXVECTOR3(110.0f, 152.5f, 0.0f));
	m_pBulletFG->SetWight(150.0f);
	m_pBulletFG->SetHeight(30.0f);
	m_pBulletFG->SetTilt(0.0f);
	m_pBulletFG->SetGaugeMax(m_nBulletMax);
	m_pBulletFG->SetGauge(m_nBullet);
	m_pBulletFG->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_pBulletNumber[nCnt] = CNumber::Create();
		m_pBulletNumber[nCnt]->SetPos(D3DXVECTOR3(270.0f + nCnt * 15.0f, 167.5f, 0.0f));
		m_pBulletNumber[nCnt]->SetWight(20.0f);
		m_pBulletNumber[nCnt]->SetHeight(20.0f);
	}

	m_pBulletNumber[0]->SetNumber(m_nBullet % 1000 / 100);
	m_pBulletNumber[1]->SetNumber(m_nBullet % 100 / 10);
	m_pBulletNumber[2]->SetNumber(m_nBullet % 10 / 1);

	//レベルゲージの生成と設定
	m_LevelGauge = CLifeGauge::Create(true, false);
	m_LevelGauge->SetPos(D3DXVECTOR3(1210.0f, 650.0f, 0.0f));
	m_LevelGauge->SetGaugeMax(m_nLevelUp);
	m_LevelGauge->SetGauge(m_nLevelPoint);
	m_LevelGauge->SetWight(50.0f);
	m_LevelGauge->SetHeight(630.0f);

	m_LevelFG = CLifeGauge::Create(true, false);
	m_LevelFG->SetPos(D3DXVECTOR3(1210.0f, 650.0f, 0.0f));
	m_LevelFG->SetGaugeMax(m_nLevelUp);
	m_LevelFG->SetGauge(m_nLevelUp);
	m_LevelFG->SetWight(50.0f);
	m_LevelFG->SetHeight(630.0f);
	m_LevelFG->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f));

	//レベルUIの生成と設定
	m_LevelNumber1 = CNumber::Create();
	m_LevelNumber1->SetNumber(m_nLevel);
	m_LevelNumber1->SetPos(D3DXVECTOR3(1245.0f, 670.0f, 0.0f));
	m_LevelNumber1->SetWight(30.0f);
	m_LevelNumber1->SetHeight(30.0f);

	m_pLvPolygon = CObject2D::Create();
	m_pLvPolygon->SetPos(D3DXVECTOR3(1225.0f, 670.0f, 0.0f));
	m_pLvPolygon->SetWight(30.0f);
	m_pLvPolygon->SetHeight(30.0f);
	m_pLvPolygon->SetTexture("data\\TEXTURE\\LvPolygon.png");

	//コンボ表記
	m_pCombo = CCombo::Create();

	m_pSelectBulletTypeUI = CBulletTypeUI::Create();
	m_pSelectBulletTypeUI->SetWight(120.0f);
	m_pSelectBulletTypeUI->SetHeight(120.0f);
	m_pSelectBulletTypeUI->SetPos(D3DXVECTOR3(75.0f, 650.0f, 0.0f));
	m_pSelectBulletTypeUI->SetColor(D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f));
	if (CManager::GetInstance()->GetSetTutorialPad() == false)
	{
		m_pSelectBulletTypeUI->SetIdx(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\BulletSelect.png"));
	}
	else
	{
		m_pSelectBulletTypeUI->SetIdx(CManager::GetInstance()->GetTexture()->Regist("data\\TEXTURE\\BulletSelectPad.png"));
	}

	SetBulletTypeUI("data\\TEXTURE\\Bullet_Normal.png", SHOT_NORMAL);

	//プレイヤーUIの生成と設定
	m_pUIPlayerBG = CObject2D::Create();
	m_pUIPlayerBG->SetPos(D3DXVECTOR3(50.0f, 45.0f, 0.0f));
	m_pUIPlayerBG->SetWight(90.0f);
	m_pUIPlayerBG->SetHeight(90.0f);
	m_pUIPlayerBG->SetTexture("data\\TEXTURE\\Polygon8.png");

	m_pUIPlayer = CObject2D::Create();
	m_pUIPlayer->SetPos(D3DXVECTOR3(50.0f, 45.0f, 0.0f));
	m_pUIPlayer->SetWight(75.0f);
	m_pUIPlayer->SetHeight(75.0f);
	m_pUIPlayer->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pUIPlayer->SetTexture("data\\TEXTURE\\Polygon8.png");

	m_pUIPlayerFG = CObject2D::Create();
	m_pUIPlayerFG->SetPos(D3DXVECTOR3(50.0f, 45.0f, 0.0f));
	m_pUIPlayerFG->SetWight(75.0f);
	m_pUIPlayerFG->SetHeight(75.0f);
	m_pUIPlayerFG->SetTexture("data\\TEXTURE\\PlayerLife3.png");

	//バレットUIの生成と設定
	m_pUIBulletBG = CObject2D::Create();
	m_pUIBulletBG->SetPos(D3DXVECTOR3(77.0f, 150.0f, 0.0f));
	m_pUIBulletBG->SetWight(68.0f);
	m_pUIBulletBG->SetHeight(68.0f);

	m_pUIBullet = CObject2D::Create();
	m_pUIBullet->SetPos(D3DXVECTOR3(77.0f, 150.0f, 0.0f));
	m_pUIBullet->SetWight(60.0f);
	m_pUIBullet->SetHeight(60.0f);
	m_pUIBullet->SetTexture("data\\TEXTURE\\BulletIcon.png");

	m_pUIBulletFG = CObject2D::Create();
	m_pUIBulletFG->SetPos(D3DXVECTOR3(77.0f, 150.0f, 0.0f));
	m_pUIBulletFG->SetWight(60.0f);
	m_pUIBulletFG->SetHeight(60.0f);
	m_pUIBulletFG->SetTexture("data\\TEXTURE\\PlayerLife3.png");
	m_pUIBulletFG->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.2f));

	m_NotBullet = CObjectBillboard::Create();
	m_NotBullet->SetPos(D3DXVECTOR3(GetPos().x + 50.0f, GetPos().y + 50.0f, GetPos().z));
	m_NotBullet->SetWight(40.0f);
	m_NotBullet->SetHeight(40.0f);
	m_NotBullet->SetTexture("data\\TEXTURE\\NotBullet00.png");
	m_NotBullet->SetDisp(false);


#endif // !NUM == 0
}

//====================================================================
//終了処理
//====================================================================
void CPlayer3D::Uninit(void)
{
	CObjectX::Uninit();

	SetDeathFlag(true);

	if (m_pCombo != NULL)
	{
		m_pCombo->Uninit();
		m_pCombo = NULL;
	}

	if (m_pUltimateGauge != NULL)
	{
		m_pUltimateGauge->Uninit();
		m_pUltimateGauge->SetDeathFlag(true);
		m_pUltimateGauge = NULL;
	}

	if (m_pLifeGauge != NULL)
	{
		m_pLifeGauge->Uninit();
		m_pLifeGauge->SetDeathFlag(true);
		m_pLifeGauge = NULL;
	}

	if (m_pBulletGauge != NULL)
	{
		m_pBulletGauge->Uninit();
		m_pBulletGauge->SetDeathFlag(true);
		m_pBulletGauge = NULL;
	}

	if (m_LevelGauge != NULL)
	{
		m_LevelGauge->Uninit();
		m_LevelGauge->SetDeathFlag(true);
		m_LevelGauge = NULL;
	}

	if (m_LevelNumber1 != NULL)
	{
		m_LevelNumber1->Uninit();
		m_LevelNumber1->SetDeathFlag(true);
		m_LevelNumber1 = NULL;
	}

	if (m_pSelectBulletTypeUI != NULL)
	{
		m_pSelectBulletTypeUI->Uninit();
		m_pSelectBulletTypeUI->SetDeathFlag(true);
		m_pSelectBulletTypeUI = NULL;
	}

	for (int nCntBulletTypeUI = 0; nCntBulletTypeUI < 3; nCntBulletTypeUI++)
	{
		if (m_pBulletTypeUI[nCntBulletTypeUI] != NULL)
		{
			m_pBulletTypeUI[nCntBulletTypeUI]->Uninit();
			m_pBulletTypeUI[nCntBulletTypeUI]->SetDeathFlag(true);
		}
	}

	if (m_LevelNumber10 != NULL)
	{
		m_LevelNumber10->Uninit();
		m_LevelNumber10->SetDeathFlag(true);
	}

	if (m_pWarning != NULL)
	{
		m_pWarning->Uninit();
		m_pWarning->SetDeathFlag(true);
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pWarningTex[nCnt] != NULL)
		{
			m_pWarningTex[nCnt]->Uninit();
			m_pWarningTex[nCnt]->SetDeathFlag(true);
		}
	}
}

//====================================================================
//終了処理
//====================================================================
void CPlayer3D::SetNULL(void)
{
	for (int nCntBulletTypeUI = 0; nCntBulletTypeUI < 3; nCntBulletTypeUI++)
	{
		if (m_pBulletTypeUI[nCntBulletTypeUI] != NULL)
		{
			m_pBulletTypeUI[nCntBulletTypeUI] = NULL;
		}
	}

	if (m_LevelNumber10 != NULL)
	{
		m_LevelNumber10 = NULL;
	}

	if (m_pWarning != NULL)
	{
		m_pWarning = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pWarningTex[nCnt] != NULL)
		{
			m_pWarningTex[nCnt] = NULL;
		}
	}
}
//====================================================================
//更新処理
//====================================================================
void CPlayer3D::Update(void)
{
	switch (CScene::GetMode())
	{
	case CScene::MODE_TITLE:
		TitleUpdate();
		break;

	case CScene::MODE_GAME:
		GameUpdate();
		break;

	default:
		break;
	}
}

//====================================================================
//更新処理(タイトル画面)
//====================================================================
void CPlayer3D::TitleUpdate(void)
{
	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//過去の位置を記録する
	m_posOld = pos;

	StateManager();

	//重力
	m_move.y -= 0.98f;
	if (m_move.y < -m_FallMax)
	{
		m_move.y = -m_FallMax;
	}

	//落下速度が一定以上になった場合ジャンプを不能にする
	if (m_move.y < -5.0f)
	{
		m_bJump = true;
	}

	//弾発射処理
	Shoot(pos, rot);

	//移動処理
	Move();

	PlayPad();

	//減衰係数
	m_move.x = m_move.x * m_stop;
	if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
	{
		m_move.x = 0.0f;
	}

	//X軸の位置更新
	pos.x += m_move.x;
	//X軸のブロックとの当たり判定
	CollisionBlock(&pos, true);
	CollisionUI(&pos, true);

	//Y軸の位置更新
	pos.y += m_move.y;
	//Y軸のブロックとの当たり判定
	CollisionBlock(&pos, false);
	CollisionUI(&pos, false);

	//画面外判定
	if (pos.x > 400.0f)
	{
		pos.x = 400.0f;
	}
	if (pos.x < -360.0f)
	{
		pos.x = -360.0f;
	}

	SetPos(pos);

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤーのX:[%f]\n", pos.x);
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤーのY:[%f]\n", pos.y);

	//頂点情報の更新
	CObjectX::Update();
}

//====================================================================
//タイトル画面のプレイヤーはパッドで操作しているかどうか
//====================================================================
void CPlayer3D::PlayPad(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_LEFT) == true ||
		pInputKeyboard->GetPress(DIK_D) == true ||
		pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{
		CManager::GetInstance()->SetSetTutorialPad(false);
	}
	if (pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == true ||
		pInputJoypad->Get_Stick_Left(0).x > 0.1f || 
		pInputJoypad->Get_Stick_Left(0).x < -0.1f)
	{
		CManager::GetInstance()->SetSetTutorialPad(true);
	}
}

//====================================================================
//更新処理(ゲーム画面)
//====================================================================
void CPlayer3D::GameUpdate(void)
{
	//マップ情報の取得
	CMap2D* pMap = CGame::GetMap2D();
	D3DXVECTOR3 pEatPos = CGame::GetBossLevel()->GetEatPos();

	D3DXVECTOR3 pos = GetPos();
	D3DXVECTOR3 rot = GetRot();

	//過去の位置を記録する
	m_posOld = pos;

	StateManager();

	//重力
	m_move.y -= 0.98f;
	if (m_move.y < -m_FallMax)
	{
		m_move.y = -m_FallMax;
		m_bFallMax = true;
		m_FallCount++;
	}
	else
	{
		m_bFallMax = false;
		m_FallCount = 0;
	}

	if (m_bFallMax == true &&
		m_FallCount % 2 == 0 &&
		m_FallCount > 30)
	{
		m_MaxFallScore++;
		CParticle::Create
		(
			D3DXVECTOR3(pos.x, pos.y, pos.z),
			D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f),
			300,
			10.0f,
			3
		);
	}

	//落下速度が一定以上になった場合ジャンプを不能にする
	if (m_move.y < -5.0f)
	{
		m_bJump = true;
	}

	//弾発射処理
	Shoot(pos, rot);

	//移動処理
	Move();

	//ライフ点滅処理
	if (m_nLife <= 2 && m_State == STATE_NORMAL)
	{
		LifeBlinking();
	}

	//減衰係数
	m_move.x = m_move.x * m_stop;
	if (m_move.x <= 0.0001f && m_move.x >= -0.0001f)
	{
		m_move.x = 0.0f;
	}

	//X軸の位置更新
	pos.x += m_move.x;
	//X軸のブロックとの当たり判定
	CollisionBlock(&pos, true);

	//Y軸の位置更新
	pos.y += m_move.y;
	//Y軸のブロックとの当たり判定
	CollisionBlock(&pos, false);

	SetWarning(pos);

	//画面外判定
	if (pos.x > 400.0f)
	{
		pos.x = 400.0f;
	}
	if (pos.x < -360.0f)
	{
		pos.x = -360.0f;
	}

	//上から迫ってくるラインの当たり判定
	if (pos.y > pEatPos.y)
	{
		HitDamage(3);
	}

	//オブジェクトとの当たり判定(矩形の範囲)
	CollisionObjectSquareSpace();

	//敵との当たり判定(矩形の４面)
	CollisionObjectSquareLine(pos);

	//敵との当たり判定
	if (m_State == STATE_NORMAL)
	{
		CollisionEnemyCircle(D3DXVECTOR3(pos.x, pos.y + HEIGHT_COLLISION * 0.5f, pos.z), 15.0f);
	}

	//経験値との当たり判定
	CollisionPointCircle(D3DXVECTOR3(pos.x, pos.y + HEIGHT_COLLISION * 0.5f, pos.z), 10.0f);

	//必殺技発動処理
	if (m_Ultimate >= ULTIMATE_OK)
	{
		UltOKParticleCount++;
		if (UltOKParticleCount % 2 == 0)
		{
			//パーティクルの生成
			CDirectionParticle::Create
			(
				pos,
				D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f),
				50.0f,
				20,
				30,
				1
			);
		}

		UltimateTrigger(pos);
	}

	//必殺技処理
	if (m_bUseUlt == true)
	{
		Ultimate(m_UltimatePos);
	}

	//バースト弾処理
	if (m_MyBulletType[m_SelectBulletType] == SHOT_BURST)
	{
		BurstShoot(pos);
	}

	//マシンガン処理
	if (m_MyBulletType[m_SelectBulletType] == SHOT_MACHINEGUN)
	{
		Machinegun(pos);
	}

	//コンボの更新処理
	m_pCombo->SetPos(pos);
	m_pCombo->SetCombo(m_nCombo);
	if (m_MaxConboScore < m_nCombo)
	{
		m_MaxConboScore = m_nCombo;
	}
	m_pCombo->Update();

	//深さ設定
	pMap->SetDepth(pos.y);

	//選択している銃のUI位置更新
	m_pSelectBulletTypeUI->SetPos(D3DXVECTOR3(75.0f, 650.0f - (m_SelectBulletType * 125.0f), 0.0f));

	//キーボードの取得
	CInputKeyboard* pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad* pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (pInputKeyboard->GetTrigger(DIK_W) == true ||
		pInputKeyboard->GetTrigger(DIK_UP) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::BUTTON_R, 0))
	{
		if (m_SelectBulletTypeMax != 1)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT_PUSH);
		}

		m_SelectBulletType++;

		if (m_SelectBulletType >= m_SelectBulletTypeMax)
		{
			m_SelectBulletType = 0;
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true ||
		pInputKeyboard->GetTrigger(DIK_DOWN) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::BUTTON_L, 0))
	{
		if (m_SelectBulletTypeMax != 1)
		{
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_SELECT_PUSH);
		}

		m_SelectBulletType--;

		if (m_SelectBulletType < 0)
		{
			m_SelectBulletType = m_SelectBulletTypeMax - 1;
		}
	}

#if _DEBUG
	if (pInputKeyboard->GetTrigger(DIK_Z) == true)
	{
		CGame::GetScore()->AddScore(300000);
		HitDamage(3);
	}
	if (pInputKeyboard->GetTrigger(DIK_F3) == true)
	{
		LevelUp();
	}
	if (pInputKeyboard->GetTrigger(DIK_F4) == true)
	{
		CEnemy3D* pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_GROUND);
		pEnemy->SetPos(D3DXVECTOR3(pos.x, pos.y + 100.0f, pos.z));
	}

	if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{
		switch (m_BulletType)
		{
		case SHOT_NORMAL:
			m_BulletType = SHOT_3WAY;
			break;
		case SHOT_3WAY:
			m_BulletType = SHOT_TRIPLE_3WAY;
			break;
		case SHOT_TRIPLE_3WAY:
			m_BulletType = SHOT_8WAY;
			break;
		case SHOT_8WAY:
			m_BulletType = SHOT_BURST;
			break;
		case SHOT_BURST:
			m_BulletType = SHOT_LESER;
			break;
		case SHOT_LESER:
			m_BulletType = SHOT_MACHINEGUN;
			break;
		case SHOT_MACHINEGUN:
			m_BulletType = SHOT_EXPLOSION;
			break;
		case SHOT_EXPLOSION:
			m_BulletType = SHOT_SPREAD_EXPLOSION;
			break;
		case SHOT_SPREAD_EXPLOSION:
			m_BulletType = SHOT_CONTINUE_EXPLOSION;
			break;
		case SHOT_CONTINUE_EXPLOSION:
			m_BulletType = SHOT_NORMAL;
			break;
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		switch (m_BulletType)
		{
		case SHOT_NORMAL:
			m_BulletType = SHOT_CONTINUE_EXPLOSION;
			break;
		case SHOT_3WAY:
			m_BulletType = SHOT_NORMAL;
			break;
		case SHOT_TRIPLE_3WAY:
			m_BulletType = SHOT_3WAY;
			break;
		case SHOT_8WAY:
			m_BulletType = SHOT_TRIPLE_3WAY;
			break;
		case SHOT_BURST:
			m_BulletType = SHOT_8WAY;
			break;
		case SHOT_LESER:
			m_BulletType = SHOT_BURST;
			break;
		case SHOT_MACHINEGUN:
			m_BulletType = SHOT_LESER;
			break;
		case SHOT_EXPLOSION:
			m_BulletType = SHOT_MACHINEGUN;
			break;
		case SHOT_SPREAD_EXPLOSION:
			m_BulletType = SHOT_EXPLOSION;
			break;
		case SHOT_CONTINUE_EXPLOSION:
			m_BulletType = SHOT_SPREAD_EXPLOSION;
			break;
		}
	}

	//デバッグ表示
	CManager::GetInstance()->GetDebugProc()->Print("プレイヤーの体力:[%d]\n", m_nLife);
	CManager::GetInstance()->GetDebugProc()->Print("最高コンボ数:[%d]\n", m_MaxConboScore);
	CManager::GetInstance()->GetDebugProc()->Print("\n\n\nボスとの距離:[%f]\n", CGame::GetBossLevel()->GetEatPos().y - pos.y);

	switch (m_BulletType)
	{
	case SHOT_NORMAL:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (ノーマル) \n");
		break;
	case SHOT_3WAY:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (３WAY) \n");
		break;
	case SHOT_TRIPLE_3WAY:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (トリプル３WAY) \n");
		break;
	case SHOT_8WAY:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (８WAY) \n");
		break;
	case SHOT_BURST:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (バースト) \n");
		break;
	case SHOT_LESER:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (レーザー) \n");
		break;
	case SHOT_MACHINEGUN:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (マシンガン) \n");
		break;
	case SHOT_EXPLOSION:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (爆裂弾) \n");
		break;
	case SHOT_SPREAD_EXPLOSION:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (爆裂拡散弾) \n");
		break;
	case SHOT_CONTINUE_EXPLOSION:
		CManager::GetInstance()->GetDebugProc()->Print("銃の種類切り替え:[ ← : → ] (爆裂連弾) \n");
		break;
	}
#endif

	SetPos(pos);

	//頂点情報の更新
	CObjectX::Update();

	//残り弾数の表示更新
	if (m_pBulletNumber[0] != NULL)
	{
		m_pBulletNumber[0]->SetNumber(m_nBullet % 1000 / 100);
	}

	if (m_pBulletNumber[1] != NULL)
	{
		m_pBulletNumber[1]->SetNumber(m_nBullet % 100 / 10);
	}

	if (m_pBulletNumber[2] != NULL)
	{
		m_pBulletNumber[2]->SetNumber(m_nBullet % 10 / 1);
	}

	//弾切れUIの表示更新
	if (m_NotBullet != NULL)
	{
		m_NotBullet->SetPos(D3DXVECTOR3(GetPos().x + 25.0f, GetPos().y + 25.0f, GetPos().z));

		if (m_nBullet > 0)
		{
			m_NotBullet->SetDisp(false);
		}
		else
		{
			m_NotBullet->SetDisp(true);
		}
	}

	if (m_nLife == 0)
	{
		CGame::SetGameEnd(120);
		SetAppear(false);
	}
}

//====================================================================
//描画処理
//====================================================================
void CPlayer3D::Draw(void)
{
	CObjectX::Draw();
}

//====================================================================
//大きさ指定処理
//====================================================================
void CPlayer3D::SizeVtx(void)
{
	int nNumVtx;		//頂点数
	DWORD dwSizeFVF;	//頂点フォーマットのサイズ
	BYTE *pVtxBuff;		//頂点バッファへのポインタ

	//頂点数を所得
	nNumVtx = m_pMesh->GetNumVertices();

	//頂点フォーマットのサイズを所得
	dwSizeFVF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;	//頂点座標の代入

		if (m_vtxMin.x > vtx.x)
		{
			m_vtxMin.x = vtx.x;
		}
		if (m_vtxMin.y > vtx.y)
		{
			m_vtxMin.y = vtx.y;
		}
		if (m_vtxMin.z > vtx.z)
		{
			m_vtxMin.z = vtx.z;
		}

		if (m_vtxMax.x < vtx.x)
		{
			m_vtxMax.x = vtx.x;
		}
		if (m_vtxMax.y < vtx.y)
		{
			m_vtxMax.y = vtx.y;
		}
		if (m_vtxMax.z < vtx.z)
		{
			m_vtxMax.z = vtx.z;
		}

		pVtxBuff += dwSizeFVF;	//頂点フォーマットのサイズ分ポインタを進める
	}

	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();
}

//====================================================================
//状態管理
//====================================================================
void CPlayer3D::StateManager(void)
{
	switch (m_State)
	{
	case STATE_NORMAL:
		break;

	case STATE_DAMAGE:
		if (m_StateCount <= 0)
		{
			SetMatColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
			m_State = STATE_WAIT;
			m_StateCount = WAIT_TIME;
			m_pLifeGauge->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pUIPlayerBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
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
//移動処理
//====================================================================
void CPlayer3D::Move(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (
		(pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A, 0) == true) &&
		m_bJump == false
		)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_JUMP);
		m_move.y += PLAYER_JAMPPOWER;
		m_bJump = true;
	}
	if (pInputKeyboard->GetPress(DIK_A) == true ||
		pInputKeyboard->GetPress(DIK_LEFT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == true)
	{
		m_move.x -= PLAYER_SPEED;
	}
	if (pInputKeyboard->GetPress(DIK_D) == true ||
		pInputKeyboard->GetPress(DIK_RIGHT) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == true)
	{
		m_move.x += PLAYER_SPEED;
	}

	if (pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_LEFT) == false &&
		pInputJoypad->GetPress(CInputJoypad::BUTTON_LEFT, 0) == false &&
		pInputKeyboard->GetPress(DIK_D) == false &&
		pInputKeyboard->GetPress(DIK_RIGHT) == false &&
		pInputJoypad->GetPress(CInputJoypad::BUTTON_RIGHT, 0) == false)
	{
		m_move.x += pInputJoypad->Get_Stick_Left(0).x * PLAYER_SPEED;
	}
}

//====================================================================
//ライフ点滅処理
//====================================================================
void CPlayer3D::LifeBlinking(void)
{
	m_LifeRedCount++;

	if (m_LifeNormalCount > 0)
	{
		m_LifeNormalCount--;
		if (m_LifeNormalCount == 0)
		{
			m_pLifeGauge->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_pUIPlayerBG->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	if (m_nLife == 2)
	{
		if (m_LifeRedCount % 60 == 0)
		{
			m_pLifeGauge->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_pUIPlayerBG->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_LifeNormalCount = 5;
		}
	}
	else if (m_nLife == 1)
	{
		if (m_LifeRedCount % 30 == 0)
		{
			m_pLifeGauge->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_pUIPlayerBG->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			m_LifeNormalCount = 10;
		}
	}
	else
	{
		m_pLifeGauge->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_pUIPlayerBG->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	}
}

//====================================================================
//必殺技処理
//====================================================================
void CPlayer3D::UltimateTrigger(D3DXVECTOR3 pos)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();

	if (pInputKeyboard->GetTrigger(DIK_X) == true ||
		pInputJoypad->GetTrigger(CInputJoypad::BUTTON_X, 0) == true)
	{
		CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ULT);
		m_Ultimate = 0;
		m_pUltimateGauge->SetGauge(m_Ultimate);
		m_pUltimateGauge->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		m_pUltimateUI->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		m_UltimateLine = 0.0f;
		m_UltimatePos = pos;
		m_bUseUlt = true;
		m_UltimateSpin = 0.0f;
	}
}

//====================================================================
//必殺技処理
//====================================================================
void CPlayer3D::Ultimate(D3DXVECTOR3 pos)
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

			if (type == TYPE_ENEMY3D || type == TYPE_BREAKBLOCK3D)
			{//種類が敵の時
				if (CollisionCircleOut(pos, CollsionPos, m_UltimateLine, m_UltimateLine - ULTIMATE_LINESPEED) == true)
				{//円の判定が当たった

					//敵の終了処理
					pObj->Hit(CollsionPos, 10);
				}
			}
			pObj = pObjNext;
		}
	}

	m_UltimateLine += ULTIMATE_LINESPEED;
	m_UltimateSpin += 0.125f;

	CEffect *pEffect = NULL;

	for (int nCnt = 0; nCnt < 8; nCnt++)
	{
		//デバッグ用エフェクトの生成
		pEffect = CEffect::Create();
		pEffect->SetPos(D3DXVECTOR3(
			pos.x + sinf(D3DX_PI * 0.25f * nCnt + m_UltimateSpin) * m_UltimateLine,
			pos.y + cosf(D3DX_PI * 0.25f * nCnt + m_UltimateSpin) * m_UltimateLine,
			pos.z
		));
		pEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		pEffect->SetRadius(100.0f);
		pEffect->SetLife(200);

		//デバッグ用エフェクトの生成
		pEffect = CEffect::Create();
		pEffect->SetPos(D3DXVECTOR3(
			pos.x + sinf(D3DX_PI * 0.25f * nCnt - m_UltimateSpin * 0.5f) * m_UltimateLine,
			pos.y + cosf(D3DX_PI * 0.25f * nCnt - m_UltimateSpin * 0.5f) * m_UltimateLine,
			pos.z
		));
		pEffect->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		pEffect->SetRadius(100.0f);
		pEffect->SetLife(200);
	}

	if (m_UltimateLine > ULTIMATE_LINEMAX)
	{
		m_bUseUlt = false;
	}
}

//====================================================================
//弾発射処理
//====================================================================
void CPlayer3D::Shoot(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	CSound *pSound = CManager::GetInstance()->GetSound();
	CBullet3D *pBullet = NULL;


	if (m_BulletCoolTime <= 0)
	{
		if ((pInputKeyboard->GetTrigger(DIK_SPACE) == true ||
			pInputJoypad->GetTrigger(CInputJoypad::BUTTON_A, 0) == true) &&
			m_bJump == true)
		{
			if (m_nBullet > 0)
			{
				switch (m_MyBulletType[m_SelectBulletType])
				{
				case SHOT_NORMAL:
					//弾の弾数を減らす
					m_nBullet--;

					if (CScene::GetMode() == CScene::MODE_GAME)
					{
						m_pBulletGauge->SetGauge(m_nBullet);
					}

					pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
					pBullet->SetPos(pos);
					pBullet->SetMove(D3DXVECTOR3
					(
						sinf((D3DX_PI * 1.0f) + rot.z) * 5.0f,
						cosf((D3DX_PI * 1.0f) + rot.z) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
						0.0f
					));
					pBullet->SetLife(BULLET_LIFE);
					pBullet->SetVerTex();

					if (m_move.y <= 5.0f)
					{
						m_move.y = 5.0f;
					}

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 3;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;

				case SHOT_3WAY:
					//弾の弾数を減らす
					m_nBullet -= 3;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);

					for (int nCntBullet = 0; nCntBullet < 3; nCntBullet++)
					{
						pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
						pBullet->SetPos(pos);
						pBullet->SetMove(D3DXVECTOR3
						(
							sinf((D3DX_PI * 1.0f) - 0.5f + (0.5f * nCntBullet)) * 10.0f,
							cosf((D3DX_PI * 1.0f) - 0.5f + (0.5f * nCntBullet)) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
							0.0f
						));
						pBullet->SetLife(BULLET_LIFE);
						pBullet->SetVerTex();
					}

					if (m_move.y <= 5.0f)
					{
						m_move.y = 8.0f;
					}

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 5;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;

				case SHOT_TRIPLE_3WAY:
					//弾の弾数を減らす
					m_nBullet -= 9;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);

					for (int nCntBullet = 0; nCntBullet < 3; nCntBullet++)
					{
						pBullet = CBullet3D::Create(CBullet3D::BULLET_SPREAD_3WAY);
						pBullet->SetPos(pos);
						pBullet->SetMove(D3DXVECTOR3
						(
							sinf((D3DX_PI * 1.0f) - 0.5f + (0.5f * nCntBullet)) * 10.0f,
							cosf((D3DX_PI * 1.0f) - 0.5f + (0.5f * nCntBullet)) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
							0.0f
						));
						pBullet->SetRot(D3DXVECTOR3(0.0f, 0.0f, (D3DX_PI * 1.0f) - 0.5f + (0.5f * nCntBullet)));
						pBullet->SetLife(BULLET_LIFE);
						pBullet->SetVerTex();
					}

					if (m_move.y <= 5.0f)
					{
						m_move.y = 12.0f;
					}

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 10;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;

				case SHOT_8WAY:
					//弾の弾数を減らす
					m_nBullet -= 8;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);

					for (int nCntBullet = 0; nCntBullet < 8; nCntBullet++)
					{
						pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
						pBullet->SetPos(pos);
						pBullet->SetMove(D3DXVECTOR3
						(
							sinf((D3DX_PI * (0.25f * nCntBullet))) * 10.0f,
							cosf((D3DX_PI * (0.25f * nCntBullet))) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
							0.0f
						));
						pBullet->SetLife(BULLET_LIFE);
						pBullet->SetVerTex();
					}

					m_move.x = 0.0f;
					m_move.y = 0.0f;

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 10;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;

				case SHOT_BURST:
					//弾の弾数を減らす
					m_nBullet -= 3;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);
					m_nBurstCount = 0;

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 20;
					break;

				case SHOT_LESER:
					//弾の弾数を減らす
					m_nBullet -= 10;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);

					for (int nCntBullet = 0; nCntBullet < 20; nCntBullet++)
					{
						pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
						pBullet->SetPos(D3DXVECTOR3(pos.x, pos.y - (15.0f * nCntBullet), pos.z));
						pBullet->SetLife(1);
						pBullet->SetVerTex();
					}

					if (m_move.y <= 5.0f)
					{
						m_move.y = 10.0f;
					}

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 35;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;

				case SHOT_EXPLOSION:
					//弾の弾数を減らす
					m_nBullet -= 5;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);

					pBullet = CBullet3D::Create(CBullet3D::BULLET_SPREAD_CROSS);
					pBullet->SetPos(pos);
					pBullet->SetMove(D3DXVECTOR3
					(
						sinf((D3DX_PI * 1.0f) + rot.z) * 5.0f,
						cosf((D3DX_PI * 1.0f) + rot.z) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
						0.0f
					));
					pBullet->SetLife(BULLET_LIFE);
					pBullet->SetVerTex();

					if (m_move.y <= 5.0f)
					{
						m_move.y = 7.0f;
					}

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 10;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;

				case SHOT_SPREAD_EXPLOSION:
					//弾の弾数を減らす
					m_nBullet -= 15;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);

					pBullet = CBullet3D::Create(CBullet3D::BULLET_SPREAD_EXCROSS);
					pBullet->SetPos(pos);
					pBullet->SetMove(D3DXVECTOR3
					(
						sinf((D3DX_PI * 1.0f) + rot.z) * 5.0f,
						cosf((D3DX_PI * 1.0f) + rot.z) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
						0.0f
					));
					pBullet->SetLife(BULLET_LIFE);
					pBullet->SetVerTex();
					pBullet->SetSpreadCount(1);

					if (m_move.y <= 5.0f)
					{
						m_move.y = 10.0f;
					}

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 10;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;

				case SHOT_CONTINUE_EXPLOSION:
					//弾の弾数を減らす
					m_nBullet -= 10;
					if (m_nBullet < 0)
					{
						m_nBullet = 0;
					}
					m_pBulletGauge->SetGauge(m_nBullet);

					pBullet = CBullet3D::Create(CBullet3D::BULLET_SPREAD_CONTINUE_3WAY);
					pBullet->SetPos(pos);
					pBullet->SetMove(D3DXVECTOR3
					(
						sinf((D3DX_PI * 1.0f) + rot.z) * 5.0f,
						cosf((D3DX_PI * 1.0f) + rot.z) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
						0.0f
					));
					pBullet->SetLife(BULLET_LIFE);
					pBullet->SetVerTex();
					pBullet->SetSpreadCount(3);

					if (m_move.y <= 5.0f)
					{
						m_move.y = 12.0f;
					}

					//次の弾までのクールタイムを設定する
					m_BulletCoolTime = 25;

					////SE(ショット音)を鳴らす
					//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
					break;
				}

				pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
			}
			else
			{
				if (m_move.y <= 5.0f)
				{
					CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NOBULLET);

					m_move.y = 0.0f;

					CEffect *pEffect = CEffect::Create();
					pEffect->SetPos(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z));
					pEffect->SetMove(D3DXVECTOR3(7.0f, m_move.y - 4.0f, 0.0f));
					pEffect->SetRadius(10.0f);
					pEffect->SetDel(0.1f);
					pEffect->SetLife(6);

					pEffect = CEffect::Create();
					pEffect->SetPos(D3DXVECTOR3(pos.x, pos.y - 15.0f, pos.z));
					pEffect->SetMove(D3DXVECTOR3(-7.0f, m_move.y - 4.0f, 0.0f));
					pEffect->SetRadius(10.0f);
					pEffect->SetDel(0.1f);
					pEffect->SetLife(6);

					m_BulletCoolTime = 15;
				}
			}
		}
	}
	else
	{
		m_BulletCoolTime--;
	}
}

//====================================================================
//バースト弾発射処理
//====================================================================
void CPlayer3D::BurstShoot(D3DXVECTOR3 pos)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	//CSound *pSound = CManager::GetInstance()->GetSound();
	CBullet3D *pBullet = NULL;

	//バースト弾の設定
	if (m_nBurstCoolTime >= BURST_COOLTIME
		&& m_nBurstCount < BURST_SHOOT)
	{
		pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
		pBullet->SetPos(pos);
		pBullet->SetMove(D3DXVECTOR3
		(
			sinf(D3DX_PI * 1.0f) * 15.0f,
			cosf(D3DX_PI * 1.0f) * 15.0f,
			0.0f
		));
		pBullet->SetLife(BULLET_LIFE);
		pBullet->SetVerTex();

		if (m_move.y <= 5.0f)
		{
			m_move.y = 10.0f;
		}

		//ジャンプをした状態にする
		m_bJump = true;

		//次の弾までのクールタイムを設定する
		m_nBurstCount++;
		m_nBurstCoolTime = 0;

		////SE(ショット音)を鳴らす
		//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
	}
	else
	{
		m_nBurstCoolTime++;
	}
}

//====================================================================
//マシンガン発射処理
//====================================================================
void CPlayer3D::Machinegun(D3DXVECTOR3 pos)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CInputJoypad *pInputJoypad = CManager::GetInstance()->GetInputJoyPad();
	CBullet3D *pBullet = NULL;

	if ((pInputKeyboard->GetPress(DIK_SPACE) == true ||
		pInputJoypad->GetPress(CInputJoypad::BUTTON_A, 0) == true) && m_nBullet > 0)
	{
		//弾の弾数を減らす
		m_nBullet--;
		m_pBulletGauge->SetGauge(m_nBullet);

		pBullet = CBullet3D::Create(CBullet3D::BULLET_NORMAL);
		pBullet->SetPos(pos);
		pBullet->SetMove(D3DXVECTOR3
		(
			sinf(D3DX_PI * 1.0f) * 5.0f,
			cosf(D3DX_PI * 1.0f) * 10.0f + 10.0f * (m_move.y / PLAYER_FALLMAX),
			0.0f
		));
		pBullet->SetLife(BULLET_LIFE);
		pBullet->SetVerTex();

		m_fMachingunJump += 0.5f;

		if (m_move.y <= 5.0f)
		{
			m_move.y = m_fMachingunJump;
		}

		////SE(ショット音)を鳴らす
		//pSound->PlaySoundA(CSound::SOUND_LABEL_SE_ATTACK_NORMAL);
	}
	else
	{
		m_fMachingunJump = 0.0f;
	}
}

//====================================================================
//ダメージヒット処理
//====================================================================
void CPlayer3D::SetWarning(D3DXVECTOR3 pos)
{
	if (CGame::GetBossLevel()->GetEatPos().y - pos.y < 300.0f)
	{
		if (m_bWarning == false)
		{
			m_bWarning = true;
			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_WARNING);

			if (m_pWarning == NULL)
			{
				m_pWarning = CObject2D::Create();
				m_pWarning->SetPos(D3DXVECTOR3(640.0f, 100.0f, 0.0f));
				m_pWarning->SetWight(250.0f);
				m_pWarning->SetHeight(250.0f);
				m_pWarning->SetTexture("data\\TEXTURE\\Warning.png");
			}

			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				if (m_pWarningTex[nCnt] == NULL)
				{
					m_pWarningTex[nCnt] = CObject2D::Create();
					m_pWarningTex[nCnt]->SetPos(D3DXVECTOR3(440.0f + nCnt * 400.0f, 100.0f, 0.0f));
					m_pWarningTex[nCnt]->SetWight(100.0f);
					m_pWarningTex[nCnt]->SetHeight(20.0f);
					m_pWarningTex[nCnt]->SetTexture("data\\TEXTURE\\WarningTex.png");
				}
			}
		}
	}
	else
	{
		if (m_bWarning == true)
		{
			m_bWarning = false;

			if (m_pWarning != NULL)
			{
				m_pWarning->Uninit();
				m_pWarning->SetDeathFlag(true);
				m_pWarning = NULL;
			}

			for (int nCnt = 0; nCnt < 2; nCnt++)
			{
				if (m_pWarningTex[nCnt] != NULL)
				{
					m_pWarningTex[nCnt]->Uninit();
					m_pWarningTex[nCnt]->SetDeathFlag(true);
					m_pWarningTex[nCnt] = NULL;
				}
			}
		}
	}
}

//====================================================================
//ダメージヒット処理
//====================================================================
void CPlayer3D::HitDamage(int Damage)
{
	if (m_State == STATE_NORMAL)
	{
		if (m_nLife > 0)
		{
			CXModel *pXModel = CManager::GetInstance()->GetXModel();

			CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_PLAYER_DAMAGE);
			m_nLife -= Damage;
			if (m_nLife < 0)
			{
				m_nLife = 0;
			}

			switch (m_nLife)
			{
			case 2:
				m_pUIPlayerFG->SetTexture("data\\TEXTURE\\PlayerLife2.png");
				m_nIdxXModel = pXModel->Regist("data\\MODEL\\Player02.x");
				break;
			case 1:
				m_pUIPlayerFG->SetTexture("data\\TEXTURE\\PlayerLife1.png");
				m_nIdxXModel = pXModel->Regist("data\\MODEL\\Player03.x");
				break;
			case 0:
				m_pUIPlayerFG->SetTexture("data\\TEXTURE\\PlayerLife0.png");
				break;
			}
		}
		m_pLifeGauge->SetGauge(m_nLife);
		m_pLifeGauge->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_pUIPlayerBG->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		SetMatColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		m_State = STATE_DAMAGE;
		m_StateCount = DAMAGE_TIME;
	}
}

//====================================================================
//レベルアップ処理
//====================================================================
void CPlayer3D::LevelUp(void)
{
	m_nBulletMax += UP_BULLET_MAX;
	m_pBulletGauge->SetGaugeMax(m_nBulletMax);
	m_nLevelPoint = 0;
	m_nLevel++;
	if (m_bLevelNumber10 == false && m_nLevel >= 10)
	{
		SetLevelNumber10();
		m_bLevelNumber10 = true;
	}

	if (m_bLevelNumber10 == true)
	{
		m_LevelNumber1->SetPos(D3DXVECTOR3(1220.0f, 670.0f, 0.0f));
		m_LevelNumber1->SetNumber(m_nLevel / 10);
		m_LevelNumber10->SetPos(D3DXVECTOR3(1240.0f, 670.0f, 0.0f));
		m_LevelNumber10->SetNumber(m_nLevel % 10);

		m_pLvPolygon->SetPos(D3DXVECTOR3(1202.0f, 670.0f, 0.0f));
	}
	else
	{
		m_LevelNumber1->SetNumber(m_nLevel);
	}

	if (m_nLevel == 3 || m_nLevel == 6)
	{
		Evolution();
	}
}

//====================================================================
//進化の処理
//====================================================================
void CPlayer3D::Evolution(void)
{
	CManager::GetInstance()->SetLevelUP(CLevelUP::Create(m_EvolutionCount, m_BulletType));

	m_EvolutionCount++;

	CObject::SetLevelStop(true);
}

//====================================================================
//進化時の銃切り替え処理
//====================================================================
void CPlayer3D::SetBullet(SHOT_TYPE type)
{
	m_BulletType = type;
}

//====================================================================
//必殺ゲージ加算処理
//====================================================================
void CPlayer3D::AddUlt(void)
{
	m_Ultimate++;
	if (m_Ultimate >= ULTIMATE_OK)
	{
		m_Ultimate = ULTIMATE_OK;
		m_pUltimateGauge->SetColor(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));
		m_pUltimateUI->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
	m_pUltimateGauge->SetGauge(m_Ultimate);
}

//====================================================================
//レベルアップ処理
//====================================================================
void CPlayer3D::SetLevelNumber10(void)
{
	//レベルUIの生成と設定
	m_LevelNumber10 = CNumber::Create();
	m_LevelNumber10->SetNumber(m_nLevel);
	m_LevelNumber10->SetWight(30.0f);
	m_LevelNumber10->SetHeight(30.0f);
}

//====================================================================
//ブロックとの当たり判定処理
//====================================================================
bool CPlayer3D::CollisionBlock(D3DXVECTOR3 *pos, bool bX)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//種類を取得

			if (type == TYPE_BREAKBLOCK3D)
			{//種類がブロックの時
				if (pObj->Collision(pos, m_posOld, &m_move, HEIGHT_COLLISION * 0.5f, WIDTH_COLLISION * 0.5f, bX) == true)
				{
					//弾の弾数を元に戻す
					ResetBullet();

					//コンボ数を０にする
					m_nCombo = 0;

					m_move.y = 0.0f;

					if (m_bJump == true)
					{
						LandingEffect(*pos);
					}

					m_bJump = false;

					return true;
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}

//====================================================================
//ブロックの上に着地した時のエフェクト
//====================================================================
void CPlayer3D::LandingEffect(D3DXVECTOR3 pos)
{
	CEffect *pEffect;
	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//デバッグ用エフェクトの生成
		pEffect = CEffect::Create();
		pEffect->SetPos(D3DXVECTOR3(
			pos.x + 5.0f + nCnt * 7.5f,
			pos.y - 20.0f,
			pos.z
		));
		pEffect->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		pEffect->SetRadius(30.0f + nCnt * 10.0f);
		pEffect->SetLife(20);
	}

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		//デバッグ用エフェクトの生成
		pEffect = CEffect::Create();
		pEffect->SetPos(D3DXVECTOR3(
			pos.x - 5.0f - nCnt * 7.5f,
			pos.y - 20.0f,
			pos.z
		));
		pEffect->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));
		pEffect->SetRadius(30.0f + nCnt * 10.0f);
		pEffect->SetLife(20);
	}
}

//====================================================================
//ブロックとの当たり判定処理
//====================================================================
bool CPlayer3D::CollisionUI(D3DXVECTOR3 *pos, bool bX)
{
	for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop(nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();			//種類を取得

			if (type == TYPE_BLOCKUI)
			{//種類がブロックの時
				if (pObj->Collision(pos, m_posOld, &m_move, HEIGHT_COLLISION * 0.5f, WIDTH_COLLISION * 0.5f, bX) == true)
				{
					//弾の弾数を元に戻す
					ResetBullet();

					//コンボ数を０にする
					m_nCombo = 0;

					m_move.y = 0.0f;
					m_bJump = false;
					return true;
				}
			}

			pObj = pObjNext;
		}
	}

	return false;
}

//====================================================================
//オブジェクトの当たり判定処理(矩形範囲)
//====================================================================
bool CPlayer3D::CollisionObjectSquareSpace(void)
{
	//for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
	//{
	//	for (int nCntObj = 0; nCntObj < MAX_OBJECT; nCntObj++)
	//	{
	//		CObject *pObj;

	//		//オブジェクトを取得
	//		pObj = Getobject(nCntPriority, nCntObj);

	//		if (pObj != NULL)
	//		{
	//			CObject::TYPE type = pObj->GetType();				//種類を取得
	//			D3DXVECTOR3 CollsionPos = pObj->GetPos();			//位置を取得
	//			float CollsionWight = pObj->GetWight() * 0.5f;		//幅を取得
	//			float CollsionHeight = pObj->GetHeight() * 0.5f;	//高さを取得
	//			float fmyWight = m_Wight * 0.5f;					//中心からの幅
	//			float fmyHeight = m_Height * 0.5f;					//中心からの高さ

	//			if (type == TYPE_ITEM)
	//			{//種類がアイテムの時

	//				CItem *m_pItem = (CItem*)pObj;

	//				if (m_pos.x + fmyWight > CollsionPos.x - CollsionWight &&
	//					m_pos.x - fmyWight < CollsionPos.x + CollsionWight &&
	//					m_pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
	//					m_pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
	//				{
	//					CExplosion *pExplosion = NULL;

	//					//爆発の生成
	//					pExplosion = CExplosion::Create();
	//					pExplosion->SetPos(CollsionPos);

	//					switch (m_pItem->GetItem())
	//					{
	//					case CItem::ITEM_LIFE:

	//						//爆発の色を設定する
	//						pExplosion->SetColor(D3DXCOLOR(1.0f, 0.5f, 0.5f, 1.0f));

	//						//スコアの加算
	//						CScore::AddScore(3000);

	//						break;
	//					case CItem::ITEM_RAIN:

	//						//爆発の色を設定する
	//						pExplosion->SetColor(D3DXCOLOR(0.5f, 0.5f, 1.0f, 1.0f));

	//						//スコアの加算
	//						CScore::AddScore(700);

	//						break;
	//					case CItem::ITEM_TIME:

	//						//爆発の色を設定する
	//						pExplosion->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));

	//						//スコアの加算
	//						CTime::AddTime(30);

	//						break;
	//					}

	//					//敵の終了処理
	//					pObj->Uninit();

	//					return true;
	//				}
	//			}
	//		}
	//	}
	//}
	return false;
}

//====================================================================
//オブジェクトの当たり判定処理(矩形4面分け)
//====================================================================
bool CPlayer3D::CollisionObjectSquareLine(D3DXVECTOR3 pos)
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
			D3DXVECTOR3 CollsionPosOld = pObj->GetPosOld();		//位置を取得
			float CollsionWight = pObj->GetWight();				//幅を取得
			float CollsionHeight = pObj->GetHeight() * 0.5f;	//高さを取得
			float fmyWight = GetWight() * 0.5f;					//中心からの幅
			float fmyHeight = GetHeight() * 0.5f;					//中心からの高さ

			if (type == TYPE_ENEMY3D)
			{//種類が敵の時

				CEnemy3D *m_pEnemy = (CEnemy3D*)pObj;

				if (
					(pos.y < CollsionPos.y + CollsionHeight &&
						m_posOld.y >= CollsionPos.y + CollsionHeight ||
						pos.y < CollsionPosOld.y + CollsionHeight &&
						m_posOld.y >= CollsionPosOld.y + CollsionHeight ||
						CollsionPos.y + CollsionHeight > pos.y &&
						CollsionPosOld.y + CollsionHeight <= pos.y) &&
					pos.x + fmyWight > CollsionPos.x - CollsionWight&&
					pos.x - fmyWight < CollsionPos.x + CollsionWight
					)
				{
					//弾の弾数を元に戻す
					ResetBullet();

					CManager::GetInstance()->GetSound()->PlaySoundA(CSound::SOUND_LABEL_SE_ENEMY_DAMAGE);

					//敵の終了処理
					m_pEnemy->Death(CollsionPos, 200, 6);

					m_move.y = +10.0f;

					//ジャンプをした状態にする
					m_bJump = true;

					return true;
				}
			}

			pObj = pObjNext;
		}
	}
	return false;
}

//====================================================================
//敵の当たり判定処理(円)
//====================================================================
bool CPlayer3D::CollisionEnemyCircle(D3DXVECTOR3 pos, float nRadiusOut)
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

			if (type == TYPE_ENEMY3D)
			{//種類が敵の時
				if (sqrtf((pos.x - CollsionPos.x) * (pos.x - CollsionPos.x)
					+ (pos.y - CollsionPos.y) * (pos.y - CollsionPos.y)) <= nRadiusOut)
				{//円の判定が当たった

					//ダメージヒット処理
					HitDamage(1);

					return true;
				}
			}
			pObj = pObjNext;
		}
	}
	return false;
}

//====================================================================
//経験値の当たり判定処理(円)
//====================================================================
bool CPlayer3D::CollisionPointCircle(D3DXVECTOR3 pos, float nRadiusOut)
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

			if (type == TYPE_LEVELPOINT3D)
			{//種類が敵の時
				if (sqrtf((pos.x - CollsionPos.x) * (pos.x - CollsionPos.x)
					+ (pos.y - CollsionPos.y) * (pos.y - CollsionPos.y)) <= nRadiusOut)
				{//円の判定が当たった

				 //経験値ゲージを上げる
					m_nLevelPoint++;

					if (m_nLevelPoint >= m_nLevelUp)
					{//レベルが上がった時

						//レベルアップまでに必要な経験値を増やす
						m_nLevelUp += LEVELUP_POINT_ADDMAX;

						//レベルゲージの最大数の設定
						m_LevelGauge->SetGaugeMax(m_nLevelUp);
						
						//レベルアップ処理
						LevelUp();

					}

					m_LevelGauge->SetGauge(m_nLevelPoint);

					//経験値用アイテムを消す
					pObj->Uninit();
					return true;
				}
			}
			pObj = pObjNext;
		}
	}
	return false;
}

//====================================================================
//円の当たり判定
//====================================================================
bool CPlayer3D::CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut)
{
	bool nHit = false;

	if (sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.y - pos2.y) * (pos1.y - pos2.y)) <= nRadiusOut)
	{//円の判定が当たった
		nHit = true;
	}

	return nHit;
}

//====================================================================
//円の当たり判定(外周のみ)
//====================================================================
bool CPlayer3D::CollisionCircleOut(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn)
{
	bool nHit = false;

	if ((sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
		+ (pos1.y - pos2.y) * (pos1.y - pos2.y)) <= nRadiusOut) &&
		(sqrtf((pos1.x - pos2.x) * (pos1.x - pos2.x)
			+ (pos1.y - pos2.y) * (pos1.y - pos2.y)) > nRadiusIn))
	{//円の判定が当たった
		nHit = true;
	}

	return nHit;
}

//====================================================================
//消費した弾を元に戻す処理
//====================================================================
void CPlayer3D::ResetBullet(void)
{
	//弾の弾数を元に戻す
	if (m_nBullet != m_nBulletMax)
	{
		m_nBullet = m_nBulletMax;
		if (CScene::GetMode() == CScene::MODE_GAME)
		{
			m_pBulletGauge->SetGauge(m_nBullet);
		}
	}
}

//====================================================================
//消費した弾を元に戻す処理
//====================================================================
void CPlayer3D::SetBulletTypeUI(const char *Texture, SHOT_TYPE Type)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;

	for (int nCntBulletTypeUI = 0; nCntBulletTypeUI < 3; nCntBulletTypeUI++)
	{
		if (m_pBulletTypeUI[nCntBulletTypeUI] == NULL)
		{
			m_pBulletTypeUI[nCntBulletTypeUI] = CBulletTypeUI::Create();
			m_pBulletTypeUI[nCntBulletTypeUI]->SetPos(D3DXVECTOR3(60.0f, 650.0f - (nCntBulletTypeUI * 125.0f), 0.0f));
			m_pBulletTypeUI[nCntBulletTypeUI]->SetIdx(pTexture->Regist(Texture));
			m_MyBulletType[nCntBulletTypeUI] = Type;
			m_SelectBulletType++;
			m_SelectBulletTypeMax++;
			break;
		}
	}
}