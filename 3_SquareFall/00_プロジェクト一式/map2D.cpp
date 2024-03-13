//============================================
//
//	マップの自動生成処理 [map2D.cpp]
//	Author:sakamoto kai
//
//============================================
#include "map2D.h"
#include "object.h"
#include "renderer.h"
#include "break_block3D.h"
#include "manager.h"
#include "game.h"
#include "player3D.h"
#include "input.h"
#include "debugproc.h"
#include "Enemy3D.h"
#include "camera.h"
#include "DirectionParticle.h"
#include "ForeGround2D.h"
#include "effect.h"
#include "bosslevel.h"
#include "Sideblock3D.h"

//マクロ定義
#define SPOWN_MAP (1000)
#define GAME_WIGHT (240.0f)			//画面横の移動制限
#define MAP_EBENT (15000.0f)		//イベントマップの発生間隔
#define START_OK ("STARTSETSTAGE")	//スタートメッセージがあるかどうかの確認
#define END_SET_OK ("ENDSETSTAGE")	//エンドメッセージがあるかどうかの確認

//静的メンバ変数宣言

//====================================================================
//コンストラクタ
//====================================================================
CMap2D::CMap2D()
{
	m_MapLevel = 1;
	m_BreakPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_BreakEnd = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_DepthOld = 0.0f;
	m_Depth = 0.0f;
	m_bCreate = false;
	m_bSpownMove = false;
	m_fCreatePoint = 0.0f;
	CreateEnemy = 2;
	CreateEnemyCount = 0;
	CreateNumber = 0;
	m_pNormalBlock = NULL;
	m_pBreakBlock3D = NULL;
	m_pEnemy = NULL;
	m_pItem = NULL;
	m_DepthOld = 100.0f;
	m_Depth = 0.0f;
	m_TestCount = 0;
	m_EventEnemy = 0;
	m_EventStartLine = 0.0f;
	m_EventEndBreakPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_EndDirectionTime = 0;
	m_bEndDirection = false;
	m_fCirclePos = 0.0f;
	m_bColorCircle = false;
	m_BreakSelect = 451;
	m_EnemySelect = 0;
	m_EnemySelect2 = 0;
	m_nCntCreateEventMap = 0;
	m_nCreateEventMap = 0;
}

//====================================================================
//デストラクタ
//====================================================================
CMap2D::~CMap2D()
{

}

//====================================================================
//生成処理
//====================================================================
CMap2D *CMap2D::Create()
{
	CMap2D *pMap = NULL;

	if (pMap == NULL)
	{
		//オブジェクト2Dの生成
		pMap = new CMap2D();
	}

	return pMap;
}

//====================================================================
//終了処理
//====================================================================
void CMap2D::Uninit(void)
{

}

//====================================================================
//更新処理
//====================================================================
void CMap2D::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();
	CDebugProc *pD = CManager::GetInstance()->GetDebugProc();

	CPlayer3D *pPlayer = CGame::GetPlayer3D();

	if (CGame::GetTutorial() == true &&
		m_bCreate == false)
	{
		LoadBlock("data\\TXT\\Stage00", D3DXVECTOR3(-400.0f, -1000.0f, 0.0f));
		CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
		pEnemy->SetPos(D3DXVECTOR3(0.0f, -1450.0f, 0.0f));
		m_bCreate = true;
	}
	else if(CGame::GetTutorial() == false)
	{
		//マップの自動生成処理
		if (m_bCreate == false)
		{
			if (
				((int)m_DepthOld % SPOWN_MAP) < ((int)m_Depth % SPOWN_MAP) &&
				pPlayer->GetMove().y < 0.0f
				)
			{//マップを生成し、生成フラグをtrueにする
				int nRand = rand() % 100;
				if (pPlayer->GetPos().y < m_MapLevel * -MAP_EBENT && nRand <= 50)
				{
					CreateEventMap();
				}
				else
				{
					CreateMap();
					BreakBlck();
					BreakBlck();

					m_bCreate = true;
					m_fCreatePoint = m_Depth;
				}
			}
		}
		else
		{
			if (
				(m_fCreatePoint - 800.0f) > m_Depth &&
				pPlayer->GetMove().y < 0.0f &&
				CGame::GetEvent() == false
				)
			{//生成から一定の距離を落下したとき生成フラグをfalseにする
				m_bCreate = false;
				CreateEnemyCount = 0;
			}
		}
	}

	if (
		((int)m_DepthOld % SPOWN_MAP) < ((int)m_Depth % SPOWN_MAP) &&
		pPlayer->GetMove().y < 0.0f
		)
	{
		CreateSideMap();
	}

	if (CGame::GetEvent() == true && m_bEndDirection == false)
	{
		if (CGame::GetEventStart() == true)
		{
			EventUpdate();
		}
		else
		{
			if (pPlayer->GetPos().y < m_EventStartLine)
			{
 				EventStart();
				m_EventEndBreakPos = D3DXVECTOR3(20.0f, m_EventStartLine - 680.0f, 0.0f);
			}
		}
	}

	if (m_bEndDirection == true)
	{
		EndDirection();
	}

	if (m_bColorCircle == true)
	{
		ColorCircle(m_DirectionPos);
	}
}

//====================================================================
//マップの生成
//====================================================================
void CMap2D::CreateMap(void)
{
	SetBlock();
}

//====================================================================
//左右のマップ生成
//====================================================================
void CMap2D::CreateSideMap(void)
{
	CSide_Block3D *pSideBlock = CSide_Block3D::Create();
	pSideBlock->SetPos(D3DXVECTOR3(620.0f, ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 2000.0f, 0.0f));

	pSideBlock = CSide_Block3D::Create();
	pSideBlock->SetPos(D3DXVECTOR3(-580.0f, ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 2000.0f, 0.0f));
}

//====================================================================
//イベントとマップの生成
//====================================================================
void CMap2D::CreateEventMap(void)
{
	m_nCntCreateEventMap++;
	if (m_nCntCreateEventMap == 1)
	{
		LoadBlock("data\\TXT\\Stage01", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
		m_nCreateEventMap = 1;
	}
	else if (m_nCntCreateEventMap == 2)
	{
		LoadBlock("data\\TXT\\Stage02", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
		m_nCreateEventMap = 2;
	}
	else if (m_nCntCreateEventMap == 3)
	{
		LoadBlock("data\\TXT\\Stage03", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
		m_nCreateEventMap = 3;
	}
	else if (m_nCntCreateEventMap == 4)
	{
		LoadBlock("data\\TXT\\Stage04", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
		m_nCreateEventMap = 4;
	}
	else
	{
		int nRandMap = rand() % 4;
		switch (nRandMap)
		{
		case 0:
			LoadBlock("data\\TXT\\Stage01", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
			break;
		case 1:
			LoadBlock("data\\TXT\\Stage02", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
			break;
		case 2:
			LoadBlock("data\\TXT\\Stage03", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
			break;
		case 3:
			LoadBlock("data\\TXT\\Stage04", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
			break;
		default:
			LoadBlock("data\\TXT\\Stage01", D3DXVECTOR3(-400.0f, -2000.0f, 0.0f));
			break;
		}
		m_nCreateEventMap = nRandMap + 1;
	}

	m_EventEnemy = 0;
	m_EventStartLine = ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 2200.0f;
	CGame::SetEventStart(false);

	CGame::SetEvent(true);
	m_bCreate = true;
}

//====================================================================
//イベントとマップの生成
//====================================================================
void CMap2D::EventStart(void)
{
	//敵の破棄
	CObject::ReleaseEnemy();

	CEnemy3D *pEnemy = NULL;

	switch (m_nCreateEventMap)
	{
	case 1:
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
			pEnemy->SetPos(D3DXVECTOR3(-300.0f + (nCnt * 300.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 750.0f, 0.0f));
			m_EventEnemy++;
		}
		break;

	case 2:
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_GROUND);
			pEnemy->SetPos(D3DXVECTOR3(-160.0f + (nCnt * 360.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 650.0f, 0.0f));
			m_EventEnemy++;
		}

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
			pEnemy->SetPos(D3DXVECTOR3(-200.0f + (nCnt * 200.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 850.0f, 0.0f));
			m_EventEnemy++;
		}
		break;

	case 3:
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_WALLD);
			pEnemy->SetPos(D3DXVECTOR3(-40.0f + (nCnt * 80.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 760.0f, 0.0f));
			m_EventEnemy++;
		}

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
			pEnemy->SetPos(D3DXVECTOR3(-160.0f + (nCnt * 280.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 680.0f, 0.0f));
			m_EventEnemy++;
		}

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
			pEnemy->SetPos(D3DXVECTOR3(-0.0f, ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 450.0f, 0.0f));
			m_EventEnemy++;
		}
		break;

	case 4:
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_GROUND);
			pEnemy->SetPos(D3DXVECTOR3(-240.0f + (nCnt * 520.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 760.0f, 0.0f));
			m_EventEnemy++;
		}

		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
			pEnemy->SetPos(D3DXVECTOR3(-160.0f + (nCnt * 360.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 600.0f, 0.0f));
			m_EventEnemy++;
		}

		for (int nCnt = 0; nCnt < 1; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
			pEnemy->SetPos(D3DXVECTOR3(-0.0f, ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 800.0f, 0.0f));
			m_EventEnemy++;
		}

		break;

	default:
		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			CEnemy3D *pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
			pEnemy->SetPos(D3DXVECTOR3(-300.0f + (nCnt * 300.0f), ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 750.0f, 0.0f));
			m_EventEnemy++;
		}
		break;
	}

	CManager::GetInstance()->GetCamera()->SetCameraPosY(((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 700.0f);
	CGame::SetEventStart(true);
}

//====================================================================
//イベント中の更新
//====================================================================
void CMap2D::EventUpdate(void)
{
	if (m_EventEnemy <= 0)
	{//モンスターハウス内の敵が全て死亡したとき
		m_EndDirectionTime = 60;
		CFG *pFG = CFG::Create(60, 1);
		m_bEndDirection = true;
		CManager::GetInstance()->SetStop(true);
	}
}

//====================================================================
//イベント終了時の演出
//====================================================================
void CMap2D::EndDirection(void)
{
	if (m_EndDirectionTime <= 0)
	{
		CGame::SetEventStart(false);
		CGame::SetEvent(false);
		CManager::GetInstance()->SetStop(false);
		m_bEndDirection = false;
		m_fCirclePos = 0.0f;
		m_bColorCircle = true;
		m_MapLevel++;
		SetLevelUP();

		CollisionSquare(m_EventEndBreakPos);
	}
	else
	{
		m_EndDirectionTime--;

		if (m_EndDirectionTime % 5 == 0)
		{
			//パーティクルの生成
			CDirectionParticle::Create
			(
				m_DirectionPos,
				D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f),
				250.0f,
				20,
				50.0f,
				1
			);
		}
	}
}

//====================================================================
//色変更処理用の円判定を広げる処理
//====================================================================
void CMap2D::ColorCircle(D3DXVECTOR3 pos)
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

			if (type == CObject::TYPE_BREAKBLOCK3D)
			{//種類が敵の時
				if (CollisionCircleOut(pos, CollsionPos, m_fCirclePos, m_fCirclePos - 15.0f) == true)
				{//円の判定が当たった

					CBreak_Block3D *pBlock = (CBreak_Block3D*)pObj;

					pBlock->ChangeColor(m_MapLevel);
				}
			}
			else if (type == CObject::TYPE_SIDEBLOCK3D)
			{//種類が敵の時
				if (CollisionCircleOut(pos, CollsionPos, m_fCirclePos, m_fCirclePos - 15.0f) == true)
				{//円の判定が当たった

					CSide_Block3D *pBlock = (CSide_Block3D*)pObj;

					pBlock->ChangeColor(m_MapLevel);
				}
			}
			pObj = pObjNext;
		}
	}

	m_fCirclePos += 15.0f;

	CEffect *pEffect = NULL;

	for (int nCnt = 0; nCnt < 32; nCnt++)
	{
		//デバッグ用エフェクトの生成
		pEffect = CEffect::Create();
		pEffect->SetPos(D3DXVECTOR3(
			pos.x + sinf(D3DX_PI * 0.0625f * nCnt) * m_fCirclePos,
			pos.y + cosf(D3DX_PI * 0.0625f * nCnt) * m_fCirclePos,
			pos.z
		));
		pEffect->SetColor(D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f));
		pEffect->SetRadius(40.0f);
		pEffect->SetDel(0.5f);
		pEffect->SetLife(100);
	}

	if (m_fCirclePos > 2000.0f)
	{
		m_bColorCircle = false;
	}
}

//====================================================================
//マップを全て埋めて生成
//====================================================================
void CMap2D::SetBlock(void)
{
	CreateNumber++;
	if (CreateNumber >= 100)
	{
		CreateNumber = 0;
	}

	for (int nCntObjHeight = 0; nCntObjHeight < SET_BLOCK_HEIGHT; nCntObjHeight++)
	{
		for (int nCntObjWight = 0 + 1; nCntObjWight < SET_BLOCK_WIGHT + 1; nCntObjWight++)
		{
			m_pBreakBlock3D = CBreak_Block3D::Create();
			m_pBreakBlock3D->SetPos(D3DXVECTOR3(-400.0f + 40.0f * nCntObjWight, ((float)((int)m_Depth / SPOWN_MAP) * 1000.0f) - 2000.0f - 40.0f * nCntObjHeight, 0.0f));
			m_pBreakBlock3D->SetCNumber(CreateNumber);
			m_pBreakBlock3D->SetWNumber(nCntObjWight);
			m_pBreakBlock3D->SetHNumber(nCntObjHeight);
			m_pBreakBlock3D->SetUse(CreateNumber, nCntObjWight, nCntObjHeight, true);
		}
	}
}

//====================================================================
//マップを全て埋めて生成
//====================================================================
void CMap2D::LoadBlock(char *Name, D3DXVECTOR3 pos)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(Name, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		CreateNumber++;

		char aString[128] = {};			//ゴミ箱
		char aStartMessage[32] = {};	//スタートメッセージ
		char aSetMessage[32] = {};		//セットメッセージ
		char aEndMessage[32] = {};		//終了メッセージ
		char aType[32] = {};			//終了メッセージ

		fscanf(pFile, "%s", &aStartMessage[0]);
		if (strcmp(&aStartMessage[0], START_OK) == 0)
		{
			while (1)
			{
				fscanf(pFile, "%s", &aSetMessage[0]);
				if (strcmp(&aSetMessage[0], END_SET_OK) == 0)
				{
					break;
				}
				else if (strcmp(&aSetMessage[0], "STARTSETBLOCK") == 0)
				{
					fscanf(pFile, "%d", &m_CreateNumber);
					fscanf(pFile, "%d", &m_WightNumber);
					fscanf(pFile, "%d", &m_HeightNumber);
					fscanf(pFile, "%s", &aSetMessage[0]);

					CBreak_Block3D::TrueUse(CreateNumber, m_WightNumber, m_HeightNumber);
				}
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
	CBreak_Block3D::CreateMapBlocks(CreateNumber , pos);
}

//====================================================================
//マップを全て埋めて生成
//====================================================================
void CMap2D::CleanBlockUse(void)
{
	m_pBreakBlock3D->CleanBlockUse();
}

//====================================================================
//レベルアップによる難易度変更
//====================================================================
void CMap2D::SetLevelUP(void)
{
	//ブロックの破壊範囲を選択する
	m_BreakSelect = 451 - m_MapLevel * 75;
	if (m_BreakSelect <= 101)
	{
		m_BreakSelect = 101;
	}

	//出現する敵の種類を選択する
	m_EnemySelect = m_MapLevel * 7;
	m_EnemySelect2 = m_MapLevel * 12;
	if (m_EnemySelect >= 50)
	{
		m_EnemySelect = 40;
	}
	if (m_EnemySelect2 >= 80)
	{
		m_EnemySelect2 = 80;
	}

	//一回の生成に出現出来る敵の最大数を設定する
	CreateEnemy = m_MapLevel * 2;

	//プレイヤーの落下の最高速度を設定する
	CGame::GetPlayer3D()->SetFallMax(10.0f + m_MapLevel * 1.0f);

	//ボスの進行速度を設定する
	CGame::GetBossLevel()->SetEatSpeed(2.0f + m_MapLevel * 1.0f);
}

//====================================================================
//マップの形を自動生成する処理(ブロックの破壊と敵の出現)
//====================================================================
void CMap2D::BreakBlck(void)
{
	//ブロック破壊の開始位置を1000.0f区切りの指定の位置に設定する
	m_BreakPos = D3DXVECTOR3(m_BreakEnd.x, ((int)m_Depth / SPOWN_MAP) * 1000.0f - 2000.0f, 0.0f);

	//ブロック破壊の終了位置を設定する
	float fBreakEnd = m_BreakPos.y - 1000.0f;

	while (1)
	{
		//乱数処理
		bool bMovePoint = false;

		//破壊地点の移動選択用ランダム関数
		int MoveRoot = rand() % 8;

		//敵の出現確率用ランダム関数
		int m_EnemySpown = rand() % 101;

		//マップのブロック破壊範囲を出すランダム関数
		float fRandWight = (float)(rand() % m_BreakSelect);
		float fRandHeight = (float)(rand() % m_BreakSelect);

		//破壊地点移動処理
		switch (MoveRoot)
		{
		case 0:
		case 1:
		case 2:
			if (m_BreakPos.x >= 400.0f)
			{//エリアの範囲外に出たら処理せずもう一度ランダム関数を回す
				continue;
			}
			else
			{//右に破壊位置を移動する
				m_BreakPos.x += fRandWight * 0.5f;
				bMovePoint = true;
				m_bSpownMove = false;
				break;
			}
		case 3:
		case 4:
		case 5:
			if (m_BreakPos.x <= -400.0f)
			{//エリアの範囲外に出たら処理せずもう一度ランダム関数を回す
				continue;
			}
			else
			{//左に破壊位置を移動する
				m_BreakPos.x -= fRandWight * 0.5f;
				bMovePoint = true;
				m_bSpownMove = false;
				break;
			}
			break;
		case 6:
			if (m_BreakPos.x >= 400.0f)
			{//エリアの範囲外に出たら処理せずもう一度ランダム関数を回す
				continue;
			}
			else
			{//右下に破壊位置を移動する
				m_BreakPos.x += fRandWight * 0.5f;
				m_BreakPos.y -= fRandHeight * 0.5f;
				bMovePoint = true;
				m_bSpownMove = false;
				break;
			}
		case 7:
			if (m_BreakPos.x <= -400.0f)
			{//エリアの範囲外に出たら処理せずもう一度ランダム関数を回す
				continue;
			}
			else
			{//左下に破壊位置を移動する
				m_BreakPos.x -= fRandWight * 0.5f;
				m_BreakPos.y -= fRandHeight * 0.5f;
				bMovePoint = true;
				m_bSpownMove = false;
				break;
			}
		}

		if (bMovePoint == true)
		{
			//破壊処理
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
					float fmyWight = fRandWight * 0.5f;					//中心からの幅
					float fmyHeight = fRandHeight * 0.5f;				//中心からの高さ

					if (type == CObject::TYPE_NORMALBLOCK || type == CObject::TYPE_BREAKBLOCK3D)
					{//種類がブロックの時
						if (m_BreakPos.x + fmyWight > CollsionPos.x - CollsionWight &&
							m_BreakPos.x - fmyWight < CollsionPos.x + CollsionWight &&
							m_BreakPos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
							m_BreakPos.y - fmyHeight < CollsionPos.y + CollsionHeight)
						{
							pObj->Uninit();
							m_pBreakBlock3D = NULL;

							if (m_EnemySpown < 5 && CreateEnemyCount < CreateEnemy && fRandWight > 40.0f && fRandHeight > 40.0f)
							{//敵が5%の確率で出現 && 敵の出現数が上限に達していないとき && 破壊範囲が敵より大きいとき
								if (m_bSpownMove == false)
								{
									//出現させる敵の種類選択
									int nRandEenemy = rand() % 101;

									if (nRandEenemy < m_EnemySelect)
									{
										m_pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_WALLD);
									}
									else if (nRandEenemy < m_EnemySelect2)
									{
										m_pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_GROUND);
									}
									else
									{
										m_pEnemy = CEnemy3D::Create(CEnemy3D::ENEMY_NORMAL);
									}
									CreateEnemyCount++;
									m_bSpownMove = true;
								}
								m_pEnemy->SetPos(m_BreakPos);
							}
						}
					}

					pObj = pObjNext;
				}
			}

			bMovePoint = false;

			if (m_BreakPos.y < fBreakEnd)
			{
				break;
			}
		}
	}

	m_BreakEnd = m_BreakPos;
}

//====================================================================
//円の当たり判定(外周のみ)
//====================================================================
bool CMap2D::CollisionCircleOut(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn)
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
//矩形の範囲内の当たり判定
//====================================================================
void CMap2D::CollisionSquare(D3DXVECTOR3 pos)
{
	//破壊処理
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
			float fmyWight = 300.0f;							//中心からの幅
			float fmyHeight = 80.0f;							//中心からの高さ

			if (type == CObject::TYPE_BREAKBLOCK3D)
			{//種類がブロックの時
				if (pos.x + fmyWight > CollsionPos.x - CollsionWight &&
					pos.x - fmyWight < CollsionPos.x + CollsionWight &&
					pos.y + fmyHeight > CollsionPos.y - CollsionHeight &&
					pos.y - fmyHeight < CollsionPos.y + CollsionHeight)
				{
					CBreak_Block3D *pBlock = (CBreak_Block3D*)pObj;

					pBlock->BreakCountSet(10);
				}
			}

			pObj = pObjNext;
		}
	}
}