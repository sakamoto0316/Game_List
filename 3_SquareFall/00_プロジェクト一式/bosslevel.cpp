//============================================
//
//	ボスの処理 [bosslevel.cpp]
//	Author:sakamoto kai
//
//============================================
#include "bosslevel.h"
#include "object.h"
#include "manager.h"
#include "game.h"
#include "renderer.h"
#include "model.h"
#include "motion.h"
#include "input.h"
#include "player3D.h"
#include "effect.h"
#include <stdio.h>

//====================================================================
//コンストラクタ
//====================================================================
CBossLevel::CBossLevel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_eatpos = D3DXVECTOR3(-500.0f, 2000.0f, 0.0f);
	m_EatFallSpeed = 2.0f;
}

//====================================================================
//デストラクタ
//====================================================================
CBossLevel::~CBossLevel()
{

}

//====================================================================
//生成処理
//====================================================================
CBossLevel *CBossLevel::Create()
{
	CBossLevel *pBoss = NULL;

	if (pBoss == NULL)
	{
		//プレイヤーの生成
		pBoss = new CBossLevel();
	}

	//オブジェクトの初期化処理
	if (FAILED(pBoss->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pBoss;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CBossLevel::Init(void)
{
	//位置の設定
	m_pos = D3DXVECTOR3(0.0f, 0.0f, -50.0f);

	//向きの設定
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 3.14f);

	//モデルの生成
	LoadLevelData("data\\TXT\\motion_BOSS_DOWN.txt");

	//モーションの生成
	if (m_pMotion == NULL)
	{
		//モーションの生成
		m_pMotion = new CMotion;
	}
	//初期化処理
	m_pMotion->SetModel(&m_apModel[0], m_nNumModel);
	m_pMotion->LoadData("data\\TXT\\motion_BOSS_DOWN.txt");

	SetType(CObject::TYPE_BOSSLEVEL);

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CBossLevel::Uninit(void)
{
	SetDeathFlag(true);
}

//====================================================================
//終了処理
//====================================================================
void CBossLevel::SetNULL(void)
{
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_apModel[nCntModel]->Uninit();
		delete m_apModel[nCntModel];
		m_apModel[nCntModel] = NULL;
	}

	//モーションの終了処理
	if (m_pMotion != NULL)
	{
		//モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}
}

//====================================================================
//更新処理
//====================================================================
void CBossLevel::Update(void)
{
	//プレイヤーの位置を取得する
	CPlayer3D *pPlayer = CGame::GetPlayer3D();
	D3DXVECTOR3 PlayerPos = pPlayer->GetPos();

	if (CGame::GetTutorial() == false &&
		CGame::GetEventStart() == false)
	{
		//死亡するラインの処理
		if (m_eatpos.y > PlayerPos.y + 800.0f)
		{
			m_eatpos.y = PlayerPos.y + 800.0f;
		}

		m_eatpos.y -= m_EatFallSpeed;

		m_pos.y = m_eatpos.y + 150.0f;
	}

	CollisionObject();

	//for (int nCnt = 0; nCnt < 20; nCnt++)
	//{
	//	CEffect *pEffect = CEffect::Create();
	//	pEffect->SetPos(D3DXVECTOR3(m_eatpos.x + (50.0f * nCnt), m_eatpos.y, m_eatpos.z));
	//	pEffect->SetRadius(20.0f);
	//	pEffect->SetLife(10);
	//	pEffect->SetColor(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	//}
	MotionTest();
}

//====================================================================
//更新処理
//====================================================================
void CBossLevel::MotionTest(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

#ifdef _DEBUG

	//モーションのセット
	if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{
		m_pMotion->Set(0);
	}
	if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{
		m_pMotion->Set(1);
	}
	if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		m_pMotion->Set(2);
	}
	if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		m_pMotion->Set(3);
	}
#endif

	//モーションの更新
	m_pMotion->Update();
}

//====================================================================
//描画処理
//====================================================================
void CBossLevel::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

									//ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//モデルの描画(全パーツ)
	for (int nCntModel = 0; nCntModel < m_nNumModel; nCntModel++)
	{
		m_apModel[nCntModel]->Draw();
	}
}

//====================================================================
//弾の当たり判定処理
//====================================================================
bool CBossLevel::CollisionObject(void)
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

			if (type == TYPE_ENEMY3D ||
				type == TYPE_BREAKBLOCK3D)
			{//種類が敵の時
				if (m_eatpos.y < CollsionPos.y)
				{
					//敵の終了処理
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
//描画処理
//====================================================================
void CBossLevel::LoadLevelData(const char *pFilename)
{
	FILE *pFile; //ファイルポインタを宣言

				 //ファイルを開く
	pFile = fopen(pFilename, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		int ModelParent = 0;
		D3DXVECTOR3 ModelPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		D3DXVECTOR3 ModelRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		char ModelName[128] = {};
		int nCntModel = 0;
		int nCntParts = 0;
		int nCntMotion = 0;
		int nCntKeySet = 0;
		int nCntKey = 0;

		char aString[128] = {};				//ゴミ箱
		char aMessage[128] = {};			//スタートとエンドのメッセージ
		char aBool[128] = {};				//bool変換用メッセージ

											// 読み込み開始-----------------------------------------------------
		while (1)
		{//「SCRIPT」を探す
			fscanf(pFile, "%s", &aMessage[0]);
			if (strcmp(&aMessage[0], "SCRIPT") == 0)
			{
				// モデル数読み込み-----------------------------------------------------
				while (1)
				{//「NUM_MODEL」を探す
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "NUM_MODEL") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%d", &m_nNumModel);		//モデル数の設定
						break;
					}
				}

				//モデルファイルの読み込み
				while (1)
				{//「MODEL_FILENAME」を探す
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "MODEL_FILENAME") == 0)
					{
						fscanf(pFile, "%s", &aString[0]);
						fscanf(pFile, "%s", &ModelName[0]);		//読み込むモデルのパスを取得

						m_apModel[nCntModel] = CModel::Create(&ModelName[0]);
						nCntModel++;
					}
					if (nCntModel >= m_nNumModel)
					{
						nCntModel = 0;
						break;
					}
				}

				// キャラクター情報読み込み-----------------------------------------------------
				while (1)
				{//「PARTSSET」を探す
					fscanf(pFile, "%s", &aMessage[0]);
					if (strcmp(&aMessage[0], "PARTSSET") == 0)
					{
						while (1)
						{//各種変数を探す
							fscanf(pFile, "%s", &aMessage[0]);
							if (strcmp(&aMessage[0], "INDEX") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &nCntModel);	//インデックスを設定
							}
							if (strcmp(&aMessage[0], "PARENT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%d", &ModelParent);	//親モデルのインデックスを設定

								if (ModelParent == -1)
								{
									m_apModel[nCntModel]->SetParent(NULL);
								}
								else
								{
									m_apModel[nCntModel]->SetParent(m_apModel[ModelParent]);
								}
							}
							if (strcmp(&aMessage[0], "POS") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelPos.x);				//位置(オフセット)の初期設定
								fscanf(pFile, "%f", &ModelPos.y);				//位置(オフセット)の初期設定
								fscanf(pFile, "%f", &ModelPos.z);				//位置(オフセット)の初期設定

								m_apModel[nCntModel]->SetPos(ModelPos);
								m_apModel[nCntModel]->SetStartPos(ModelPos);
							}
							if (strcmp(&aMessage[0], "ROT") == 0)
							{
								fscanf(pFile, "%s", &aString[0]);
								fscanf(pFile, "%f", &ModelRot.x);				////向きの初期設定
								fscanf(pFile, "%f", &ModelRot.y);				////向きの初期設定
								fscanf(pFile, "%f", &ModelRot.z);				////向きの初期設定

								m_apModel[nCntModel]->SetRot(ModelRot);
								m_apModel[nCntModel]->SetStartRot(ModelRot);
							}
							if (strcmp(&aMessage[0], "END_PARTSSET") == 0)
							{
								break;
							}
						}
						nCntModel++;
						if (nCntModel >= m_nNumModel)
						{
							break;
						}
					}
				}
			}
			if (strcmp(&aMessage[0], "END_SCRIPT") == 0)
			{
				break;
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}