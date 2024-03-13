//============================================
//
//	エディット [Edit.cpp]
//	Author:sakamoto kai
//
//============================================
#include "Edit.h"
#include "object.h"
#include "EditBlock3D.h"
#include "renderer.h"
#include "break_block3D.h"
#include "manager.h"
#include "game.h"
#include "input.h"
#include "debugproc.h"
#include "Map2D.h"

//マクロ定義
#define SPOWN_MAP (1000)
#define GAME_WIGHT (240.0f)			//画面横の移動制限

//静的メンバ変数宣言
CEdit_Block3D *CEdit::m_pEditBlock = NULL;			//マテリアルへのポインタ

//====================================================================
//コンストラクタ
//====================================================================
CEdit::CEdit()
{
	m_WightNumber = 1;					//横の番号
	m_HeightNumber = 0;					//縦の番号
}

//====================================================================
//デストラクタ
//====================================================================
CEdit::~CEdit()
{

}

//====================================================================
//生成処理
//====================================================================
CEdit *CEdit::Create()
{
	CEdit *pMap = NULL;

	if (pMap == NULL)
	{
		//オブジェクト2Dの生成
		pMap = new CEdit();
	}

	m_pEditBlock = CEdit_Block3D::Create();

	return pMap;
}

//====================================================================
//終了処理
//====================================================================
void CEdit::Uninit(void)
{

}


//====================================================================
//更新処理
//====================================================================
void CEdit::Update(void)
{
	//キーボードの取得
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();

	if (pInputKeyboard->GetTrigger(DIK_W) == true ||
		pInputKeyboard->GetTrigger(DIK_UP) == true)
	{
		m_HeightNumber--;

		if (m_HeightNumber < 0)
		{
			m_HeightNumber = SET_BLOCK_HEIGHT - 1;
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_S) == true ||
		pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{
		m_HeightNumber++;

		if (m_HeightNumber > SET_BLOCK_HEIGHT - 1)
		{
			m_HeightNumber = 0;
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_A) == true ||
		pInputKeyboard->GetTrigger(DIK_LEFT) == true)
	{
		m_WightNumber--;

		if (m_WightNumber < 1)
		{
			m_WightNumber = SET_BLOCK_WIGHT;
		}
	}
	if (pInputKeyboard->GetTrigger(DIK_D) == true ||
		pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
	{
		m_WightNumber++;

		if (m_WightNumber > SET_BLOCK_WIGHT)
		{
			m_WightNumber = 1;
		}
	}

	m_pEditBlock->SetHNumber(m_HeightNumber);
	m_pEditBlock->SetWNumber(m_WightNumber);

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{
		if (CBreak_Block3D::GetCheckUse(0, m_WightNumber, m_HeightNumber) == false)
		{
			CBreak_Block3D *pBBlock = CBreak_Block3D::Create();
			pBBlock->SetPos(D3DXVECTOR3(-400.0f + 40.0f * m_WightNumber, 400.0f - 40.0f * m_HeightNumber, 0.0f));
			pBBlock->SetCNumber(0);
			pBBlock->SetWNumber(m_WightNumber);
			pBBlock->SetHNumber(m_HeightNumber);
			pBBlock->SetUse(0, m_WightNumber, m_HeightNumber, true);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_BACKSPACE) == true)
	{
		if (CBreak_Block3D::GetCheckUse(0, m_WightNumber, m_HeightNumber) == true)
		{
			CBreak_Block3D::UseBreak(0, m_WightNumber, m_HeightNumber);
		}
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{
		SaveData();
	}
}

//====================================================================
//保存処理
//====================================================================
void CEdit::SaveData(void)
{
	FILE *pFile; //ファイルポインタを宣言

	//ファイルを開く
	pFile = fopen(DATA_NAME, "w");

	if (pFile != NULL)
	{//ファイルが開けた場合

	 //ステージをセーブする開始の合図
		fprintf(pFile, "%s\n\n", "STARTSETSTAGE");

		for (int nCntPriority = 0; nCntPriority < PRIORITY_MAX; nCntPriority++)
		{
			//オブジェクトを取得
			CObject *pObj = CObject::GetTop(nCntPriority);

			while (pObj != NULL)
			{
				CObject *pObjNext = pObj->GetNext();

				CObject::TYPE type = pObj->GetType();				//種類を取得

				if (type == CObject::TYPE_BREAKBLOCK3D)
				{//種類がブロックの時
					CBreak_Block3D *m_pBBlock = (CBreak_Block3D*)pObj;

					if (m_pBBlock->GetUse() == true)
					{
						fprintf(pFile, "%s\n", "STARTSETBLOCK");

						//ステージをセーブした終了の合図
						fprintf(pFile, "%d\n", m_pBBlock->GetCNumber());
						fprintf(pFile, "%d\n", m_pBBlock->GetWNumber());
						fprintf(pFile, "%d\n", m_pBBlock->GetHNumber());

						fprintf(pFile, "%s\n\n", "ENDSETBLOCK");
					}
				}

				pObj = pObjNext;
			}
		}

		//ステージをセーブした終了の合図
		fprintf(pFile, "%s", "ENDSETSTAGE");

		fclose(pFile);
	}
	else
	{//ファイルが開けなかった場合
		printf("***ファイルを開けませんでした***\n");
	}
}