//============================================
//
//	ゲージの処理 [Gauge.cpp]
//	Author:sakamoto kai
//
//============================================
#include "Gauge.h"
#include "renderer.h"
#include "manager.h"
#include "texture.h"
#include "number.h"

//====================================================================
//コンストラクタ
//====================================================================
CGauge::CGauge(int nPriority) :CObject(nPriority)
{
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_bVertical = false;
	m_bNumberUI = false;
	m_bNumber10UI = false;

	m_Tilt = 0.0f;
	m_Height = 0.0f;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_pNumberMax10 = NULL;
	m_pNumberMax1 = NULL;
	m_pNumber10 = NULL;
	m_pNumber1 = NULL;
}

//====================================================================
//デストラクタ
//====================================================================
CGauge::~CGauge()
{

}

//====================================================================
//生成処理
//====================================================================
CGauge *CGauge::Create(void)
{
	CGauge *pObject2D = NULL;

	if (pObject2D == NULL)
	{
		//オブジェクト2Dの生成
		pObject2D = new CGauge();
	}

	//オブジェクトの初期化処理
	if (FAILED(pObject2D->Init()))
	{//初期化処理が失敗した場合
		return NULL;
	}

	return pObject2D;
}

//====================================================================
//初期化処理
//====================================================================
HRESULT CGauge::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();;
	m_nIdxTexture = pTexture->Regist("data\\TEXTURE\\Test.jpg");

	if (m_bNumberUI == true)
	{
		//ライフゲージの生成と設定
		m_pNumberMax1 = CNumber::Create();
		m_pNumberMax1->SetNumber(m_GaugeMax);
		m_pNumberMax1->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.4f), m_pos.y + (m_Height * 0.5f), m_pos.z));
		m_pNumberMax1->SetWight(30.0f);
		m_pNumberMax1->SetHeight(30.0f);

		m_pNumber1 = CNumber::Create();
		m_pNumber1->SetNumber(m_Gauge);
		m_pNumber1->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.6f), m_pos.y + (m_Height * 0.5f), m_pos.z));
		m_pNumber1->SetWight(30.0f);
		m_pNumber1->SetHeight(30.0f);
	}

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{
		return E_FAIL;
	}

	//ゲージの割合を出す
	float fRatio = 0.0f;

	if (m_Gauge != 0)
	{
		fRatio = ((float)m_Gauge / (float)m_GaugeMax);
	}

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_bVertical == true)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - (m_Height * fRatio), m_pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Wight, m_pos.y - (m_Height * fRatio), m_pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Wight, m_pos.y, m_pos.z);
	}
	else
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_Wight * fRatio), m_pos.y, m_pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_Tilt, m_pos.y + m_Height, m_pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Tilt + (m_Wight * fRatio), m_pos.y + m_Height, m_pos.z);
	}

	//rhwの設定
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();

	return S_OK;
}

//====================================================================
//終了処理
//====================================================================
void CGauge::Uninit(void)
{
	if (m_pNumberMax10 != NULL)
	{
		m_pNumberMax10->Uninit();
		m_pNumberMax10->SetDeathFlag(true);
	}
	if (m_pNumberMax1 != NULL)
	{
		m_pNumberMax1->Uninit();
		m_pNumberMax1->SetDeathFlag(true);
	}
	if (m_pNumber10 != NULL)
	{
		m_pNumber10->Uninit();
		m_pNumber10->SetDeathFlag(true);
	}
	if (m_pNumber1 != NULL)
	{
		m_pNumber1->Uninit();
		m_pNumber1->SetDeathFlag(true);
	}

	SetDeathFlag(true);
}

//====================================================================
//終了処理
//====================================================================
void CGauge::SetNULL(void)
{
	if (m_pNumberMax10 != NULL)
	{
		m_pNumberMax10 = NULL;
	}
	if (m_pNumberMax1 != NULL)
	{
		m_pNumberMax1 = NULL;
	}
	if (m_pNumber10 != NULL)
	{
		m_pNumber10 = NULL;
	}
	if (m_pNumber1 != NULL)
	{
		m_pNumber1 = NULL;
	}

	//頂点バッファの破棄
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

//====================================================================
//更新処理
//====================================================================
void CGauge::Update(void)
{
	if (m_bNumberUI == true)
	{
		if (m_bNumber10UI == true)
		{
			m_pNumberMax1->SetNumber(m_GaugeMax / 10);
			m_pNumberMax1->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.2f), m_pos.y + (m_Height * 0.5f), m_pos.z));

			m_pNumberMax10->SetNumber(m_GaugeMax);
			m_pNumberMax10->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.3f), m_pos.y + (m_Height * 0.5f), m_pos.z));

			m_pNumber1->SetNumber(m_Gauge / 10);
			m_pNumber1->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.6f), m_pos.y + (m_Height * 0.5f), m_pos.z));

			m_pNumber10->SetNumber(m_Gauge);
			m_pNumber10->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.7f), m_pos.y + (m_Height * 0.5f), m_pos.z));
		}
		else if (m_GaugeMax >= 10)
		{
			SetNumber10();
			SetNumberMax10();
			m_bNumber10UI = true;
		}
		else
		{
			//ライフゲージの設定
			m_pNumberMax1->SetNumber(m_GaugeMax);
			m_pNumberMax1->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.3f), m_pos.y + (m_Height * 0.5f), m_pos.z));

			m_pNumber1->SetNumber(m_Gauge);
			m_pNumber1->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.7f), m_pos.y + (m_Height * 0.5f), m_pos.z));
		}
	}

	SetVerTex(m_bVertical);
}

//====================================================================
//描画処理
//====================================================================
void CGauge::Draw(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	////テクスチャの設定
	//pDevice->SetTexture(0, m_pTexture);

	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	assert(GetIdx() != -1);		//テクスチャの番号を入れ忘れた場合エラーを吐く

								//テクスチャの設定
	pDevice->SetTexture(0, pTexture->GetAddress(GetIdx()));

	//ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
		0,						//描画の開始位置
		2);						//プリミティブ(ポリゴン)数
}

//====================================================================
//テクスチャの割り当て
//====================================================================
void CGauge::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

//====================================================================
//頂点座標の設定
//====================================================================
void CGauge::SetVerTex(bool Vertical)
{
	//ゲージの割合を出す
	float fRatio = 0.0f;

	if (m_Gauge != 0)
	{
		fRatio = ((float)m_Gauge / (float)m_GaugeMax);
	}

	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (Vertical == true)
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - (m_Height * fRatio), m_pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_Wight, m_pos.y - (m_Height * fRatio), m_pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Wight, m_pos.y, m_pos.z);
	}
	else
	{
		//頂点座標の設定 
		pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + (m_Wight * fRatio), m_pos.y, m_pos.z);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_Tilt, m_pos.y + m_Height, m_pos.z);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_Tilt + (m_Wight * fRatio), m_pos.y + m_Height, m_pos.z);
	}

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//====================================================================
//テクスチャ座標の設定
//====================================================================
void CGauge::SetAnim(D3DXVECTOR2 Tex)
{
	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(Tex.x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, Tex.y);
	pVtx[3].tex = D3DXVECTOR2(Tex.x, Tex.y);

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//====================================================================
//頂点カラーの設定
//====================================================================
void CGauge::SetColor(D3DXCOLOR col)
{
	VERTEX_2D*pVtx;	//頂点ポインタを所得

	//頂点バッファをロックし、両店情報へのポインタを所得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//頂点カラーの設定
	pVtx[0].col =
		pVtx[1].col =
		pVtx[2].col =
		pVtx[3].col = col;

	//頂点バッファをアンロックする
	m_pVtxBuff->Unlock();
}

//====================================================================
//数字の最大数の10の位の生成
//====================================================================
void CGauge::SetNumberMax10(void)
{
	//ライフゲージの生成と設定
	m_pNumberMax10 = CNumber::Create();
	m_pNumberMax10->SetNumber(m_GaugeMax % 10);
	m_pNumberMax10->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.3f), m_pos.y + (m_Height * 0.5f), m_pos.z));
	m_pNumberMax10->SetWight(30.0f);
	m_pNumberMax10->SetHeight(30.0f);
}

//====================================================================
//数字の10の位の生成
//====================================================================
void CGauge::SetNumber10(void)
{
	//ライフゲージの生成と設定
	m_pNumber10 = CNumber::Create();
	m_pNumber10->SetNumber(m_Gauge % 10);
	m_pNumber10->SetPos(D3DXVECTOR3(m_pos.x + (m_Wight * 0.7f), m_pos.y + (m_Height * 0.5f), m_pos.z));
	m_pNumber10->SetWight(30.0f);
	m_pNumber10->SetHeight(30.0f);
}