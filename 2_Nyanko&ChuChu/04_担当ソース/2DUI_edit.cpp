//============================================
//
//	2Dエディット [2DUI_edit.cpp]
//	Author:sakamoto kai
//
//============================================
#include "2DUI_edit.h"
#include "object.h"
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "input.h"
#include "debugproc.h"
#include "Effect.h"
#include "debugproc.h"
#include "texture.h"
#include "useful.h"

//マクロ定義
#define NUM_OBJECT (8)						//マップに出すオブジェクトの種類数
#define START_OK ("STARTSETUI")				//スタートメッセージがあるかどうかの確認
#define END_SET_OK ("ENDSETUI")				//エンドメッセージがあるかどうかの確認
#define UI_SET ("STARTSET")					//ブロックのセットメッセージ
#define DELETE_WIGHT (45.0f)				//削除処理の横の削除範囲
#define DELETE_HEIGHT (45.0f)				//削除処理の縦の削除範囲
#define SIDE_PRESSCOUNT (30)				//横に素早く移動するまでのカウント
#define MOVE_POS (10.0f)					//移動距離

// 静的メンバ変数宣言
C2DUIEdit::UIINFO C2DUIEdit::m_aTextureInfo[UI_LABEL_MAX] =
{
	{ "data\\TEXTURE\\Balloon.png","サンプル00" },
	{ "data\\TEXTURE\\CageMark.png","サンプル01" },
	{ "data\\TEXTURE\\Dstr003.png","サンプル02" },
};
CObject2D *C2DUIEdit::m_pEditUI = NULL;			//ブロックへのポインタ

//====================================================================
//コンストラクタ
//====================================================================
C2DUIEdit::C2DUIEdit()
{
	m_EditPos = NONE_D3DXVECTOR3;
	m_EditRot = NONE_D3DXVECTOR3;
	m_EditSize = D3DXVECTOR3(100.0f,100.0f,0.0f);
	ObjectType = 0;
	m_nSideDistance = 10.0f;
	m_nSideCount = 0;
	m_cTextureName = m_aTextureInfo[ObjectType].pFilename;
}

//====================================================================
//デストラクタ
//====================================================================
C2DUIEdit::~C2DUIEdit()
{

}

//====================================================================
//生成処理
//====================================================================
C2DUIEdit *C2DUIEdit::Create()
{
	C2DUIEdit *pMap = NULL;

	if (pMap == NULL)
	{
		//オブジェクト2Dの生成
		pMap = new C2DUIEdit();
	}

	m_pEditUI = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_EDITUI, CObject::PRIORITY_UI);
	m_pEditUI->SetPos(D3DXVECTOR3(-200.0f, -200.0f, 0.0f));
	m_pEditUI->SetRot(NONE_D3DXVECTOR3);
	m_pEditUI->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_pEditUI->SetAngle();				// 方向
	m_pEditUI->SetLength();				// 長さ

	// テクスチャの読み込み処理
	m_pEditUI->BindTexture(CManager::Get()->GetTexture()->Regist(C2DUIEdit::m_aTextureInfo[0].pFilename));

	return pMap;
}

//====================================================================
//終了処理
//====================================================================
void C2DUIEdit::Uninit(void)
{

}


//====================================================================
//更新処理
//====================================================================
void C2DUIEdit::Update(void)
{
	CObject2D *pEditUI = NULL;

	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::Get()->GetInputKeyboard();

	//エディットの位置を動かす----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_W) == true)
	{
		m_EditPos.y -= MOVE_POS;
	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true)
	{
		m_EditPos.y += MOVE_POS;
	}

	if (pInputKeyboard->GetTrigger(DIK_A) == true)
	{
		m_EditPos.x -= MOVE_POS;
	}
	if (pInputKeyboard->GetTrigger(DIK_D) == true)
	{
		m_EditPos.x += MOVE_POS;
	}

	//長押し移動----------------------------------------------------------------------
	if (pInputKeyboard->GetPress(DIK_W) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.y -= MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.y += MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x -= MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}
	else if (pInputKeyboard->GetPress(DIK_D) == true)
	{
		if (m_nSideCount > SIDE_PRESSCOUNT && m_nSideCount % 2 == 0)
		{
			m_EditPos.x += MOVE_POS * 2.0f;
		}
		m_nSideCount++;
	}

	if (pInputKeyboard->GetPress(DIK_A) == false &&
		pInputKeyboard->GetPress(DIK_D) == false &&
		pInputKeyboard->GetPress(DIK_W) == false &&
		pInputKeyboard->GetPress(DIK_S) == false)
	{
		m_nSideCount = 0;
	}

	//オブジェクト切り替え----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{
		ObjectType++;

		if (ObjectType >= UI_LABEL_MAX)
		{
			ObjectType = 0;
		}

		m_cTextureName = m_aTextureInfo[ObjectType].pFilename;

		// テクスチャの読み込み処理
		m_pEditUI->BindTexture(CManager::Get()->GetTexture()->Regist(m_cTextureName));
	}

	//向きと位置の切り替え----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_9) == true)
	{
		m_EditRot.y += 1.57f;

		if (m_EditRot.y >= 6.0f)
		{
			m_EditRot.y = 0;
		}
	}

	//とげの移動範囲調整----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_3) == true)
	{
		m_nSideDistance -= 5.0f;
	}
	if (pInputKeyboard->GetTrigger(DIK_4) == true)
	{
		m_nSideDistance += 5.0f;
	}

	//とげの移動範囲調整----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_5) == true)
	{
		m_EditSize.x -= m_nSideDistance;
	}
	if (pInputKeyboard->GetTrigger(DIK_6) == true)
	{
		m_EditSize.x += m_nSideDistance;
	}
	if (pInputKeyboard->GetTrigger(DIK_7) == true)
	{
		m_EditSize.y -= m_nSideDistance;
	}
	if (pInputKeyboard->GetTrigger(DIK_8) == true)
	{
		m_EditSize.y += m_nSideDistance;
	}

	//位置更新----------------------------------------------------------
	m_pEditUI->SetPos(m_EditPos);
	m_pEditUI->SetRot(m_EditRot);
	m_pEditUI->SetSize(m_EditSize);
	m_pEditUI->SetAngle();				// 方向
	m_pEditUI->SetLength();				// 長さ

	//オブジェクト設置----------------------------------------------------------
	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		pEditUI = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_2DUI, CObject::PRIORITY_UI);
		pEditUI->SetPos(m_EditPos);
		pEditUI->SetRot(m_EditRot);
		pEditUI->SetSize(m_EditSize);
		pEditUI->SetAngle();				// 方向
		pEditUI->SetLength();				// 長さ
		pEditUI->BindTexture(CManager::Get()->GetTexture()->Regist(m_cTextureName));
	}

	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		DeleteObject(m_EditPos);
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveData();
	}

	DebugObject();
}

//====================================================================
//削除処理
//====================================================================
void C2DUIEdit::DeleteObject(D3DXVECTOR3 pos)
{
	for (int nCntPriority = 0; nCntPriority < CObject::PRIORITY_MAX; nCntPriority++)
	{
		//オブジェクトを取得
		CObject *pObj = CObject::GetTop((CObject::PRIORITY)nCntPriority);

		while (pObj != NULL)
		{
			CObject *pObjNext = pObj->GetNext();

			CObject::TYPE type = pObj->GetType();				//種類を取得

			if (type == CObject::TYPE_2DUI)
			{//種類がブロックの時
				CObject2D *pUI = (CObject2D*)pObj;

				if (useful::RectangleCollisionXY(pos, pUI->GetPos(), D3DXVECTOR3(DELETE_WIGHT, DELETE_HEIGHT, 0.0f), pUI->GetSize(), D3DXVECTOR3(-DELETE_WIGHT, -DELETE_HEIGHT, 0.0f), pUI->GetSize() * -1.0f) == true)
				{
					pUI->Uninit();
				}
			}

			pObj = pObjNext;
		}
	}
}

//====================================================================
//デバッグ表示
//====================================================================
void C2DUIEdit::DebugObject(void)
{
	CManager::Get()->GetDebugProc()->Print("\n%s\n", "ーーーーーエディットモードーーーーー");

	CManager::Get()->GetDebugProc()->Print("\n%s\n", "操作説明ーー");
	//操作説明
	CManager::Get()->GetDebugProc()->Print("%s\n", "移動：[W],[A],[S],[D]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "サイズ変更値の下降上昇：[３：４]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "UIの横サイズの下降上昇：[５：６]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "UIの縦サイズの下降上昇：[７：８]");
	CManager::Get()->GetDebugProc()->Print("%s\n", "オブジェクト回転：[９]");

	CManager::Get()->GetDebugProc()->Print("\n%s\n", "ーーエディット情報ーー");

	//オブジェクト
	CManager::Get()->GetDebugProc()->Print("テクスチャ：[%s]\n", m_aTextureInfo[ObjectType].pCommentname);

	//位置・向き・大きさ
	CManager::Get()->GetDebugProc()->Print("位置：[%f:%f]\n", m_EditPos.x, m_EditPos.y);
	CManager::Get()->GetDebugProc()->Print("サイズ変更値：[%f]\n", m_nSideDistance);
	CManager::Get()->GetDebugProc()->Print("サイズ：[%f:%f]\n", m_EditSize.x, m_EditSize.y);
	CManager::Get()->GetDebugProc()->Print("向き：[%f]\n", m_EditRot.y);

	//とげの移動範囲

	CManager::Get()->GetDebugProc()->Print("\n%s\n", "ーーーーーエディットモードーーーーー");
}

//====================================================================
//保存処理
//====================================================================
void C2DUIEdit::SaveData(void)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(LOADUI_NAME, "w");

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //ステージをセーブする開始の合図
		fprintf(pFile, "%s\n\n", START_OK);

		for (int nCntPriority = 0; nCntPriority < CObject::PRIORITY_MAX; nCntPriority++)
		{
			//オブジェクトを取得
			CObject *pObj = CObject::GetTop((CObject::PRIORITY)nCntPriority);

			while (pObj != NULL)
			{
				CObject *pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();				//種類を取得

				if (type == CObject::TYPE_2DUI)
				{//種類がブロックの時
					CObject2D *pUI = (CObject2D*)pObj;

					fprintf(pFile, "%s\n", UI_SET);

					//位置の取得
					fprintf(pFile, "%f ", pUI->GetPos().x);
					fprintf(pFile, "%f ", pUI->GetPos().y);
					fprintf(pFile, "%f\n", pUI->GetPos().z);

					//向きの取得
					fprintf(pFile, "%f ", pUI->GetRot().x);
					fprintf(pFile, "%f ", pUI->GetRot().y);
					fprintf(pFile, "%f\n", pUI->GetRot().z);

					//大きさの取得
					fprintf(pFile, "%f ", pUI->GetSize().x);
					fprintf(pFile, "%f ", pUI->GetSize().y);
					fprintf(pFile, "%f\n", pUI->GetSize().z);

					fprintf(pFile, "%s\n", pUI->GetTexName());

					fprintf(pFile, "%s\n\n", "ENDSET");
				}

				pObj = pObjNext;
			}
		}

		//ステージをセーブした終了の合図
		fprintf(pFile, "%s", END_SET_OK);

		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}

//====================================================================
//マップを全て埋めて生成
//====================================================================
void C2DUIEdit::LoadData(char *Name, D3DXVECTOR3 pos)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(Name, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合
		D3DXVECTOR3 SetPos = NONE_D3DXVECTOR3;
		D3DXVECTOR3 SetRot = NONE_D3DXVECTOR3;
		D3DXVECTOR3 SetSize = NONE_D3DXVECTOR3;
		char TexName[256] = {};
		char aStartMessage[32] = {};	//スタートメッセージ
		char aSetMessage[32] = {};		//セットメッセージ

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
				else if (strcmp(&aSetMessage[0], UI_SET) == 0)
				{
					fscanf(pFile, "%f", &SetPos.x);
					fscanf(pFile, "%f", &SetPos.y);
					fscanf(pFile, "%f", &SetPos.z);
					fscanf(pFile, "%f", &SetRot.x);
					fscanf(pFile, "%f", &SetRot.y);
					fscanf(pFile, "%f", &SetRot.z);
					fscanf(pFile, "%f", &SetSize.x);
					fscanf(pFile, "%f", &SetSize.y);
					fscanf(pFile, "%f", &SetSize.z);
					fscanf(pFile, "%s", &TexName[0]);
					fscanf(pFile, "%s", &aSetMessage[0]);

					CObject2D *pUI = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_2DUI, CObject::PRIORITY_UI);
					pUI->SetPos(pos + SetPos);
					pUI->SetRot(SetRot);
					pUI->SetSize(SetSize);
					pUI->SetAngle();				// 方向
					pUI->SetLength();				// 長さ
					pUI->BindTexture(CManager::Get()->GetTexture()->Regist(TexName));
				}
			}
		}
		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}