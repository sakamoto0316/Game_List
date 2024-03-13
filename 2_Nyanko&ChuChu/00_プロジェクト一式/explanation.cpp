//===========================================
//
// 説明のメイン処理[explanation.cpp]
// Author 坂本翔唯
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "explanation.h"
#include "answer.h"
#include "object2D.h"
#include "manager.h"
#include "texture.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SET_SIDE		(100.0f)										//画面外に置いておくテクスチャの初期横位置
#define CAT_SIDE		(280.0f)										//画面外に置いておくテクスチャの初期横位置
#define CAT_SIDE2		(300.0f)										//画面外に置いておくテクスチャの初期横位置
#define RAT_SIDE0		(120.0f)										//画面外に置いておくテクスチャの初期横位置
#define RAT_SIDE		(350.0f)										//画面外に置いておくテクスチャの初期横位置
#define RAT_SIDE2		(145.0f)										//画面外に置いておくテクスチャの初期横位置
#define CAT_KING_POS	(D3DXVECTOR3(-SET_SIDE,330.0f,0.0f))			//ネコ代表の位置
#define CAT_KING_SIZE	(D3DXVECTOR3(200.0f,400.0f,0.0f))				//ネコ代表のサイズ
#define CAT_BG_POS		(D3DXVECTOR3(-SET_SIDE + CAT_SIDE,170.0f,0.0f)) //猫背景の位置
#define CAT_BG_POS2		(D3DXVECTOR3(-SET_SIDE + CAT_SIDE2,170.0f,0.0f)) //猫背景の位置
#define CAT_BG_SIZE		(D3DXVECTOR3(80.0f,80.0f,0.0f))					//猫背景のサイズ
#define CAT_BG_SIZE2	(D3DXVECTOR3(50.0f,50.0f,0.0f))					//猫背景のサイズ
#define CAT_TEXT_POS	(D3DXVECTOR3(-SET_SIDE,200.0f,0.0f))			//猫テキストの位置
#define CAT_TEXT_SIZE	(D3DXVECTOR3(400.0f,200.0f,0.0f))				//猫テキストのサイズ
																		
#define RAT_KING_POS	(D3DXVECTOR3(1280.0f + SET_SIDE,520,0.0f))		//ネズミ代表の位置
#define RAT_KING_SIZE	(D3DXVECTOR3(125.0f,200.0f,0.0f))				//ネズミ代表のサイズ
#define RAT_BG_POS0		(D3DXVECTOR3(1280.0f + SET_SIDE - RAT_SIDE,50.0f,0.0f))	//ネズミ背景の位置
#define RAT_BG_POS		(D3DXVECTOR3(1280.0f + SET_SIDE - RAT_SIDE,550.0f,0.0f))	//ネズミ背景の位置
#define RAT_BG_POS2		(D3DXVECTOR3(1280.0f + SET_SIDE - RAT_SIDE2,680.0f,0.0f))	//ネズミ背景の位置
#define RAT_BG_SIZE0	(D3DXVECTOR3(120.0f,50.0f,0.0f))					//ネズミ背景のサイズ
#define RAT_BG_SIZE		(D3DXVECTOR3(50.0f,60.0f,0.0f))					//ネズミ背景のサイズ
#define RAT_BG_SIZE2	(D3DXVECTOR3(160.0f,50.0f,0.0f))					//ネズミ背景のサイズ
#define RAT_TEXT_POS	(D3DXVECTOR3(1280.0f + SET_SIDE,500.0f,0.0f))	//ネズミテキストの位置
#define RAT_TEXT_SIZE	(D3DXVECTOR3(400.0f,200.0f,0.0f))				//ネズミテキストのサイズ

#define IMAGE_POS	(D3DXVECTOR3(640.0f,360.0f,0.0f))					//画像の位置
#define IMAGE_SIZE	(D3DXVECTOR3(590.0f,310.0f,0.0f))					//画像のサイズ
#define START_POS	(D3DXVECTOR3(1080.0f,620.0f,0.0f))					//画像の位置
#define START_SIZE	(D3DXVECTOR3(150.0f,50.0f,0.0f))					//画像のサイズ

#define CAT_KING_STOP	(150.0f)										// ネコ代表の停止位置
#define CAT_BG_STOP		(630.0f + CAT_SIDE)								// 猫背景の停止位置
#define CAT_BG_STOP2	(630.0f + CAT_SIDE2)							// 猫背景の停止位置
#define CAT_TEXT_STOP	(630.0f)										// 猫テキストの停止位置
#define RAT_KING_STOP	(1280.0f - 150.0f)								// ネズミ代表の停止位置
#define RAT_BG_STOP0	(1280.0f - RAT_SIDE0)							// ネズミ背景の停止位置
#define RAT_BG_STOP		(1280.0f - 630.0f - RAT_SIDE)					// ネズミ背景の停止位置
#define RAT_BG_STOP2	(1280.0f - 630.0f - RAT_SIDE2)					// ネズミ背景の停止位置
#define RAT_TEXT_STOP	(1280.0f - 630.0f)								// ネズミテキストの停止位置
#define SIDE_MOVESPEED	(5.0f)											// 横移動の速度
#define A_PLUS_KING		(0.013f)										// 代表のα値の加算
#define A_PLUS_TEXT		(0.015f)										// テキストのα値の加算
//-------------------------------------------
// 静的メンバ変数宣言
//-------------------------------------------

//==============================
// コンストラクタ
//==============================
CExplanation::CExplanation() : CObject(CObject::TYPE_2DUI, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_pBG = NULL;
	m_pCatKing = NULL;
	m_pCatBG = NULL;
	m_pCatText = NULL;
	m_pRatKing = NULL;
	m_pRatBG = NULL;
	m_pRatText = NULL;
	m_ColorKing = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_ColorText = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		m_apImage[nCnt] = NULL;
	}
	m_fStartAlpha = D3DX_PI;
}

//==============================
// デストラクタ
//==============================
CExplanation::~CExplanation()
{

}

//==============================
// 破片の初期化処理
//==============================
HRESULT CExplanation::Init(void)
{
	// 全ての値を初期化する

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CExplanation::Uninit(void)
{
	if (m_pBG != NULL)
	{
		m_pBG->Uninit();
		m_pBG = NULL;
	}
	if (m_pCatKing != NULL)
	{
		m_pCatKing->Uninit();
		m_pCatKing = NULL;
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Uninit();
		m_pCatBG = NULL;
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Uninit();
		m_pCatText = NULL;
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Uninit();
		m_pRatKing = NULL;
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Uninit();
		m_pRatBG = NULL;
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Uninit();
		m_pRatText = NULL;
	}
	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Uninit();
			m_apImage[nCnt] = NULL;
		}
	}

	Release();
}

//=====================================
// 破片の更新処理
//=====================================
void CExplanation::Update(void)
{
	m_ColorKing.a += A_PLUS_KING;

	if (m_ColorKing.a > 1.0f)
	{
		m_ColorKing.a = 1.0f;
		m_ColorText.a += A_PLUS_TEXT;
	}
	if (m_ColorText.a > 1.0f)
	{
		m_ColorText.a = 1.0f;
	}

	if (m_pCatKing != NULL)
	{
		m_pCatKing->Update();

		D3DXVECTOR3 pos = m_pCatKing->GetPos();

		pos.x += SIDE_MOVESPEED;

		if (pos.x > CAT_KING_STOP)
		{
			pos.x = CAT_KING_STOP;
		}

		m_pCatKing->SetVtxColor(m_ColorKing);
		m_pCatKing->SetPos(pos);
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Update();

		D3DXVECTOR3 pos = m_pCatBG->GetPos();
		pos.x += SIDE_MOVESPEED;

		if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ACTION)
		{
			if (pos.x > CAT_BG_STOP)
			{
				pos.x = CAT_BG_STOP;
			}
		}
		else if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ITEM_MULTI)
		{
			if (pos.x > CAT_BG_STOP2)
			{
				pos.x = CAT_BG_STOP2;
			}
		}

		m_pCatBG->SetVtxColor(m_ColorText);
		m_pCatBG->SetPos(pos);
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Update();

		D3DXVECTOR3 pos = m_pCatText->GetPos();
		pos.x += SIDE_MOVESPEED;

		if (pos.x > CAT_TEXT_STOP)
		{
			pos.x = CAT_TEXT_STOP;
		}

		m_pCatText->SetVtxColor(m_ColorText);
		m_pCatText->SetPos(pos);
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Update();

		D3DXVECTOR3 pos = m_pRatKing->GetPos();
		pos.x -= SIDE_MOVESPEED;

		if (pos.x < RAT_KING_STOP)
		{
			pos.x = RAT_KING_STOP;
		}

		m_pRatKing->SetVtxColor(m_ColorKing);
		m_pRatKing->SetPos(pos);
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Update();

		D3DXVECTOR3 pos = m_pRatBG->GetPos();
		pos.x -= SIDE_MOVESPEED;

		if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_MOVE)
		{
			if (pos.x < RAT_BG_STOP0)
			{
				pos.x = RAT_BG_STOP0;
			}
		}
		if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ACTION)
		{
			if (pos.x < RAT_BG_STOP)
			{
				pos.x = RAT_BG_STOP;
			}
		}
		else if (CTutorial::GetTutorial() == CTutorial::TUTORIAL::TUTORIAL_ITEM_MULTI)
		{
			if (pos.x < RAT_BG_STOP2)
			{
				pos.x = RAT_BG_STOP2;
			}
		}

		m_pRatBG->SetVtxColor(m_ColorText);
		m_pRatBG->SetPos(pos);
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Update();

		D3DXVECTOR3 pos = m_pRatText->GetPos();
		pos.x -= SIDE_MOVESPEED;

		if (pos.x < RAT_TEXT_STOP)
		{
			pos.x = RAT_TEXT_STOP;
		}

		m_pRatText->SetVtxColor(m_ColorText);
		m_pRatText->SetPos(pos);
	}

	if (m_apImage[2] != NULL)
	{
		if (sinf(m_fStartAlpha) >= 0.5f)
		{
			m_fStartAlpha += 0.03f;
		}
		else
		{
			m_fStartAlpha += 0.2f;
		}
		m_apImage[2]->SetVtxColor(D3DXCOLOR(1.0f, 1.01f, 1.0f, sinf(m_fStartAlpha)));
	}

	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Update();
		}
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CExplanation::Draw(void)
{
	if (m_pBG != NULL)
	{
		m_pBG->Draw();
	}
	if (m_pCatKing != NULL)
	{
		m_pCatKing->Draw();
	}
	if (m_pCatText != NULL)
	{
		m_pCatText->Draw();
	}
	if (m_pRatKing != NULL)
	{
		m_pRatKing->Draw();
	}
	if (m_pRatText != NULL)
	{
		m_pRatText->Draw();
	}
	if (m_pCatBG != NULL)
	{
		m_pCatBG->Draw();
	}
	if (m_pRatBG != NULL)
	{
		m_pRatBG->Draw();
	}
	for (int nCnt = 0; nCnt < IMAGE_MAX; nCnt++)
	{
		if (m_apImage[nCnt] != NULL)
		{
			m_apImage[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CExplanation::SetData(CTutorial::TUTORIAL Tutorial)
{
	//Tutorial = CTutorial::TUTORIAL_ITEM_MULTI;

	if (m_pBG == NULL)
	{
		m_pBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
		m_pBG->SetPos(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// 位置
		m_pBG->SetPosOld(D3DXVECTOR3(640.0f, 360.0f, 0.0f));// 前回の位置
		m_pBG->SetRot(NONE_D3DXVECTOR3);					// 向き
		m_pBG->SetSize(D3DXVECTOR3(640.0f, 360.0f, 0.0f));	// サイズ
		m_pBG->SetLength();									// 長さ
		m_pBG->SetAngle();									// 方向
		m_pBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.8f));	// 色

		// 頂点座標の設定処理
		m_pBG->SetVertex();
	}

	if(Tutorial == CTutorial::TUTORIAL_GIMMICK)
	{
		if (m_apImage[0] == NULL)
		{
			m_apImage[0] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[0]->SetPos(IMAGE_POS);			// 位置
			m_apImage[0]->SetPosOld(IMAGE_POS);			// 前回の位置
			m_apImage[0]->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_apImage[0]->SetSize(IMAGE_SIZE);			// サイズ
			m_apImage[0]->SetLength();					// 長さ
			m_apImage[0]->SetAngle();					// 方向

			// 頂点座標の設定処理
			m_apImage[0]->SetVertex();
		}
	}
	else if (Tutorial == CTutorial::TUTORIAL_LETS_GO)
	{
		if (m_apImage[0] == NULL)
		{
			m_apImage[0] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[0]->SetPos(IMAGE_POS);			// 位置
			m_apImage[0]->SetPosOld(IMAGE_POS);			// 前回の位置
			m_apImage[0]->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_apImage[0]->SetSize(IMAGE_SIZE);			// サイズ
			m_apImage[0]->SetLength();					// 長さ
			m_apImage[0]->SetAngle();					// 方向

														// 頂点座標の設定処理
			m_apImage[0]->SetVertex();
		}

		if (m_apImage[1] == NULL)
		{
			m_apImage[1] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[1]->SetPos(START_POS);			// 位置
			m_apImage[1]->SetPosOld(START_POS);			// 前回の位置
			m_apImage[1]->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_apImage[1]->SetSize(START_SIZE);			// サイズ
			m_apImage[1]->SetLength();					// 長さ
			m_apImage[1]->SetAngle();					// 方向

			// 頂点座標の設定処理
			m_apImage[1]->SetVertex();
		}
		if (m_apImage[2] == NULL)
		{			  
			m_apImage[2] = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_apImage[2]->SetPos(START_POS);			// 位置
			m_apImage[2]->SetPosOld(START_POS);			// 前回の位置
			m_apImage[2]->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_apImage[2]->SetSize(START_SIZE);			// サイズ
			m_apImage[2]->SetLength();					// 長さ
			m_apImage[2]->SetAngle();					// 方向
					  
			// 頂点座標の設定処理
			m_apImage[2]->SetVertex();
		}
	}
	else
	{
		if (m_pCatKing == NULL && Tutorial != CTutorial::TUTORIAL_RAT_RESCUE)
		{
			m_pCatKing = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatKing->SetPos(CAT_KING_POS);			// 位置
			m_pCatKing->SetPosOld(CAT_KING_POS);		// 前回の位置
			m_pCatKing->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_pCatKing->SetSize(CAT_KING_SIZE);			// サイズ
			m_pCatKing->SetLength();					// 長さ
			m_pCatKing->SetAngle();						// 方向
			m_pCatKing->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色
			m_pCatKing->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_icon_Obanyan.png"));		// テクスチャの割り当て処理

			// 頂点座標の設定処理
			m_pCatKing->SetVertex();

		}
		if (m_pCatBG == NULL && Tutorial == CTutorial::TUTORIAL_ACTION)
		{
			m_pCatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatBG->SetPos(CAT_BG_POS);				// 位置
			m_pCatBG->SetPosOld(CAT_BG_POS);			// 前回の位置
			m_pCatBG->SetRot(NONE_D3DXVECTOR3);			// 向き
			m_pCatBG->SetSize(CAT_BG_SIZE);				// サイズ
			m_pCatBG->SetLength();						// 長さ
			m_pCatBG->SetAngle();						// 方向
			m_pCatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色

			// 頂点座標の設定処理
			m_pCatBG->SetVertex();
		}
		else if (m_pCatBG == NULL && Tutorial == CTutorial::TUTORIAL_ITEM_MULTI)
		{
			m_pCatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatBG->SetPos(CAT_BG_POS2);				// 位置
			m_pCatBG->SetPosOld(CAT_BG_POS2);			// 前回の位置
			m_pCatBG->SetRot(NONE_D3DXVECTOR3);			// 向き
			m_pCatBG->SetSize(CAT_BG_SIZE2);				// サイズ
			m_pCatBG->SetLength();						// 長さ
			m_pCatBG->SetAngle();						// 方向
			m_pCatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色

																		// 頂点座標の設定処理
			m_pCatBG->SetVertex();
		}

		if (m_pCatText == NULL && Tutorial != CTutorial::TUTORIAL_RAT_RESCUE)
		{
			m_pCatText = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pCatText->SetPos(CAT_TEXT_POS);			// 位置
			m_pCatText->SetPosOld(CAT_TEXT_POS);		// 前回の位置
			m_pCatText->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_pCatText->SetSize(CAT_TEXT_SIZE);			// サイズ
			m_pCatText->SetLength();					// 長さ
			m_pCatText->SetAngle();						// 方向
			m_pCatText->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色

			// 頂点座標の設定処理
			m_pCatText->SetVertex();
		}
		if (m_pRatKing == NULL && Tutorial != CTutorial::TUTORIAL_TABLESWING && Tutorial != CTutorial::TUTORIAL_CAT_KILL)
		{
			m_pRatKing = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatKing->SetPos(RAT_KING_POS);			// 位置
			m_pRatKing->SetPosOld(RAT_KING_POS);		// 前回の位置
			m_pRatKing->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_pRatKing->SetSize(RAT_KING_SIZE);			// サイズ
			m_pRatKing->SetLength();					// 長さ
			m_pRatKing->SetAngle();						// 方向
			m_pRatKing->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色
			m_pRatKing->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_icon_ChuChuGG.png"));		// テクスチャの割り当て処理

			// 頂点座標の設定処理
			m_pRatKing->SetVertex();
		}

		if (m_pRatBG == NULL && Tutorial == CTutorial::TUTORIAL_MOVE)
		{
			m_pRatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatBG->SetPos(RAT_BG_POS0);				// 位置
			m_pRatBG->SetPosOld(RAT_BG_POS0);			// 前回の位置
			m_pRatBG->SetRot(NONE_D3DXVECTOR3);			// 向き
			m_pRatBG->SetSize(RAT_BG_SIZE0);				// サイズ
			m_pRatBG->SetLength();						// 長さ
			m_pRatBG->SetAngle();						// 方向
			m_pRatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色

																		// 頂点座標の設定処理
			m_pRatBG->SetVertex();
		}
		else if (m_pRatBG == NULL && Tutorial == CTutorial::TUTORIAL_ACTION)
		{
			m_pRatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatBG->SetPos(RAT_BG_POS);				// 位置
			m_pRatBG->SetPosOld(RAT_BG_POS);			// 前回の位置
			m_pRatBG->SetRot(NONE_D3DXVECTOR3);			// 向き
			m_pRatBG->SetSize(RAT_BG_SIZE);				// サイズ
			m_pRatBG->SetLength();						// 長さ
			m_pRatBG->SetAngle();						// 方向
			m_pRatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色

			// 頂点座標の設定処理
			m_pRatBG->SetVertex();
		}
		else if (m_pRatBG == NULL && Tutorial == CTutorial::TUTORIAL_ITEM_MULTI)
		{
			m_pRatBG = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatBG->SetPos(RAT_BG_POS2);				// 位置
			m_pRatBG->SetPosOld(RAT_BG_POS2);			// 前回の位置
			m_pRatBG->SetRot(NONE_D3DXVECTOR3);			// 向き
			m_pRatBG->SetSize(RAT_BG_SIZE2);				// サイズ
			m_pRatBG->SetLength();						// 長さ
			m_pRatBG->SetAngle();						// 方向
			m_pRatBG->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色

																		// 頂点座標の設定処理
			m_pRatBG->SetVertex();
		}
		if (m_pRatText == NULL && Tutorial != CTutorial::TUTORIAL_TABLESWING && Tutorial != CTutorial::TUTORIAL_CAT_KILL)
		{
			m_pRatText = CObject2D::Create(CObject2D::TYPE::TYPE_NONE, CObject::TYPE::TYPE_NONE, CObject::PRIORITY_UI);
			m_pRatText->SetPos(RAT_TEXT_POS);			// 位置
			m_pRatText->SetPosOld(RAT_TEXT_POS);		// 前回の位置
			m_pRatText->SetRot(NONE_D3DXVECTOR3);		// 向き
			m_pRatText->SetSize(RAT_TEXT_SIZE);			// サイズ
			m_pRatText->SetLength();					// 長さ
			m_pRatText->SetAngle();						// 方向
			m_pRatText->SetVtxColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));	// 色

			// 頂点座標の設定処理
			m_pRatText->SetVertex();
		}
	}

	switch (Tutorial)
	{
	case CTutorial::TUTORIAL_MOVE:
		if (m_pRatBG != NULL)
		{
			m_pRatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_ok.png"));		// テクスチャの割り当て処理
		}
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat00.png"));		// テクスチャの割り当て処理
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat00.png"));		// テクスチャの割り当て処理
		}

		break;

	case CTutorial::TUTORIAL_ATTACK_JAMP:
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat01.png"));		// テクスチャの割り当て処理
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat01.png"));		// テクスチャの割り当て処理
		}
		break;

	case CTutorial::TUTORIAL_TABLESWING:
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat05.png"));		// テクスチャの割り当て処理
		}
		break;

	case CTutorial::TUTORIAL_CAT_KILL:
		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat02.png"));		// テクスチャの割り当て処理
		}
		break;

	case CTutorial::TUTORIAL_RAT_RESCUE:
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat02.png"));		// テクスチャの割り当て処理
		}
		break;

	case CTutorial::TUTORIAL_ACTION:
		if (m_pCatBG != NULL)
		{
			m_pCatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_Himo.png"));		// テクスチャの割り当て処理
		}
		if (m_pRatBG != NULL)
		{
			m_pRatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_pin.png"));		// テクスチャの割り当て処理
		}

		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat03.png"));		// テクスチャの割り当て処理
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat03.png"));		// テクスチャの割り当て処理
		}
		break;

	case CTutorial::TUTORIAL_ITEM_MULTI:
		if (m_pCatBG != NULL)
		{
			m_pCatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_mousetrap.png"));		// テクスチャの割り当て処理
		}
		if (m_pRatBG != NULL)
		{
			m_pRatBG->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_action_leash.png"));		// テクスチャの割り当て処理
		}

		if (m_pCatText != NULL)
		{
			m_pCatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textcat04.png"));		// テクスチャの割り当て処理
		}
		if (m_pRatText != NULL)
		{
			m_pRatText->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_textrat04.png"));		// テクスチャの割り当て処理
		}
		break;

	case CTutorial::TUTORIAL_GIMMICK:
		if (m_apImage[0] != NULL)
		{
			m_apImage[0]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_explanation00.png"));		// テクスチャの割り当て処理
		}
		break;

	case CTutorial::TUTORIAL_LETS_GO:
		if (m_apImage[0] != NULL)
		{
			m_apImage[0]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_explanation01.png"));		// テクスチャの割り当て処理
		}
		if (m_apImage[1] != NULL)
		{
			m_apImage[1]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_start00.png"));		// テクスチャの割り当て処理
		}
		if (m_apImage[2] != NULL)
		{
			m_apImage[2]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\TUTORIAL\\tutorial_start01.png"));		// テクスチャの割り当て処理
		}
		break;

	default:

		break;
	}
}

//=======================================
// 生成処理
//=======================================
CExplanation* CExplanation::Create(CTutorial::TUTORIAL Tutorial)
{
	// ローカルオブジェクトを生成
	CExplanation* pSample = nullptr;	// 返事入力のリアクションのインスタンスを生成

	if (pSample == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pSample = new CExplanation;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pSample != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 初期化処理
		if (FAILED(pSample->Init()))
		{ // 初期化に失敗した場合

		  // 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pSample->SetData(Tutorial);
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 返事入力のリアクションのポインタを返す
	return pSample;
}