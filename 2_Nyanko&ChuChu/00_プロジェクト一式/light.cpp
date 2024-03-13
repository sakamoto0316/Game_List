//===========================================
//
// ライトのメイン処理[light.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "light.h"

#include "input.h"
#include "debugproc.h"

//-------------------------------------------
// 無名名前空間
//-------------------------------------------
namespace
{
	const float LIGHT_PAWOR = 0.8f;
	const D3DXCOLOR LIGHT_DIFFUSE[NUM_LIGHT] =			// ライトの色
	{
		D3DXCOLOR(LIGHT_PAWOR, LIGHT_PAWOR, LIGHT_PAWOR, 1.0f),
		D3DXCOLOR(LIGHT_PAWOR, LIGHT_PAWOR, LIGHT_PAWOR, 1.0f),
		D3DXCOLOR(LIGHT_PAWOR, LIGHT_PAWOR, LIGHT_PAWOR, 1.0f),
	};
	const D3DXVECTOR3 LIGHT_VECTOR[NUM_LIGHT] =			// ライトの方向
	{
		D3DXVECTOR3(-0.5f, -0.6f, -0.5f),
		D3DXVECTOR3(0.0f, 0.1f, 0.9f),
		D3DXVECTOR3(0.8f, -0.6f, 0.5f),
	};
}

//=========================
// コンストラクタ
//=========================
CLight::CLight()
{
	for (int nCntSet = 0; nCntSet < NUM_LIGHT; nCntSet++)
	{
		// ライトの情報をクリアする
		ZeroMemory(&m_light[nCntSet], sizeof(D3DLIGHT9));
	}
}

//=========================
// デストラクタ
//=========================
CLight::~CLight()
{

}

//=========================
// ライトの初期化処理
//=========================
HRESULT CLight::Init(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	D3DXVECTOR3 vecDir;				// 設定用方向ベクトル

	for (int nCntSet = 0; nCntSet < NUM_LIGHT; nCntSet++)
	{
		// ライトの情報をクリアする
		ZeroMemory(&m_light[nCntSet], sizeof(D3DLIGHT9));

		// ライトの種類を設定
		m_light[nCntSet].Type = D3DLIGHT_DIRECTIONAL;

		// ライトの拡散光を設定
		m_light[nCntSet].Diffuse = LIGHT_DIFFUSE[nCntSet];

		// ライトの方向を設定
		vecDir = LIGHT_VECTOR[nCntSet];

		// ベクトルを正規化する
		D3DXVec3Normalize(&vecDir, &vecDir);

		m_light[nCntSet].Direction = vecDir;

		// ライトを設定する
		pDevice->SetLight(nCntSet, &m_light[nCntSet]);

		// ライトを有効にする
		pDevice->LightEnable(nCntSet, TRUE);
	}

	// 成功を返す
	return S_OK;
}

//=========================
// ライトの終了処理
//=========================
void CLight::Uninit(void)
{

}

//=========================
// ライトの更新処理
//=========================
void CLight::Update(void)
{

}