//===========================================
//
// 爆弾のメイン処理[dynamite.cpp]
// Author 堀川萩大
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "dynamite.h"
#include "obstacle.h"
#include "useful.h"
#include "Effect.h"
#include "collision.h"
#include "object3Dfan.h"
#include "texture.h"
#include "sound.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define SCALE_SPEED	(D3DXVECTOR3(0.1f,0.1f,0.1f))	// サイズの変更速度
#define COLOR_SPEED	(D3DXCOLOR(0.0f,0.1f,0.1f,0.0f))	// サイズの変更速度
#define EXPLOSION_COUNT		(300)		// 爆発までのカウント
#define DELEAT_COUNT		(10)		// 爆発の判定時間
#define EXPLOSION_RADIUS	(1000.0f)	// 爆発の範囲
#define EXPLOSION_TIME		(300)		// 爆発までのカウント
#define START_RADIUS		(15.0f)		// 初期の爆風円の範囲
#define MAX_BURNWIND		(4)
#define BRUN_TEXTURE  "data\\TEXTURE\\Rupture.tga"				// 何でもない画面のテクスチャ

//==============================
// コンストラクタ
//==============================
CDynamite::CDynamite() : CObstacle(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// 全ての値をクリアする
	m_state =STATE_NONE;							// 状態
	m_nExplosion = 0;								// 爆発タイミング
	m_pFan = nullptr;
	m_SizeChangeSpeed = SCALE_SPEED;
	m_ColChangeSpeed = COLOR_SPEED;
	m_WindSize = D3DXVECTOR3(100.0f, 100.0f, 0.0f);;
	m_pExWind[0] = nullptr;
	m_pExWind[1] = nullptr;
	m_pExWind[2] = nullptr;
	m_pExWind[3] = nullptr;
	// 使用条件
	SetCatUse(true);
}

//==============================
// デストラクタ
//==============================
CDynamite::~CDynamite()
{

}

//==============================
// 爆弾の初期化処理
//==============================
HRESULT CDynamite::Init(void)
{
	if (FAILED(CObstacle::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}

	// 全ての値をクリアする
	m_state = STATE_NONE;							// 状態
	m_nExplosion = 0;								// 爆発タイミング
	m_pFan = nullptr;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_WindSize = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fRadius = START_RADIUS;
	m_pExWind[0] = nullptr;
	m_pExWind[1] = nullptr;
	m_pExWind[2] = nullptr;
	m_pExWind[3] = nullptr;


	// 値を返す
	return S_OK;
}

//========================================
// 爆弾の終了処理
//========================================
void CDynamite::Uninit(void)
{
	if (m_pFan != nullptr)
	{
		m_pFan->Uninit();
		m_pFan = nullptr;
	}

	for (int nCnt = 0; nCnt < MAX_BURNWIND; nCnt++)
	{
		if (m_pExWind[nCnt] != nullptr)
		{
			m_pExWind[nCnt]->Uninit();
			m_pExWind[nCnt] = nullptr;
		}
	}

	// 終了処理
	CObstacle::Uninit();
}

//=====================================
// 爆弾の更新処理
//=====================================
void CDynamite::Update(void)
{
	if (m_nExplosion > EXPLOSION_COUNT - EXPLOSION_TIME && m_state != STATE_EXPLOSION)
	{ // 残り2秒になった場合
		if (m_pFan == nullptr)
		{// 爆風円の生成
			m_pFan = CExplosionFan::Create(GetPos(), m_col);
		}
		if (m_state == STATE_NONE)
		{
			m_state = STATE_MINI;
		}

		// モデルサイズ変更処理
		ChageScale();
	}

	if (m_state == STATE_EXPLOSION)
	{// 爆発後

		// 爆発の判定時間を加算する
		m_nDelTyming++;

		m_WindSize += D3DXVECTOR3(EXPLOSION_RADIUS / DELEAT_COUNT, EXPLOSION_RADIUS / DELEAT_COUNT, 0.0f);

		for (int nCnt = 0; nCnt < MAX_BURNWIND; nCnt++)
		{
			if (m_pExWind[nCnt] != nullptr)
			{
				m_pExWind[nCnt]->SetSize(m_WindSize);
				m_pExWind[nCnt]->Update();
			}
		}
		
		if (m_nDelTyming > DELEAT_COUNT)
		{ // 一定カウントになった場合

			// 爆弾の削除
			Uninit();
		}
	}

	// 爆発処理
	Explosion();
}

//=====================================
// 爆弾の描画処理
//=====================================
void CDynamite::Draw(void)
{
	if (m_state != STATE_EXPLOSION)
	{// 爆発のタイミングで描画を消す

		// 描画処理
		CObstacle::Draw();

	}

	// 爆風用の3Dポリゴンの描画
	for (int nCnt = 0; nCnt < MAX_BURNWIND; nCnt++)
	{
		if (m_pExWind[nCnt] != nullptr)
		{
			m_pExWind[nCnt]->DrawLightOff();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CDynamite::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	CObstacle::SetData(pos, rot, type);
}

//=====================================
// 当たり判定処理
//=====================================
bool CDynamite::Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	// 位置と最小値と最大値を設定する
	D3DXVECTOR3 pos = pPlayer->GetPos();
	D3DXVECTOR3 vtxMax = collSize;
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);

	// 六面体の当たり判定
	if (collision::HexahedronCollision
	(
		&pos,					// プレイヤーの位置
		GetPos(),				// 位置
		pPlayer->GetPosOld(),	// プレイヤーの前回の位置
		GetPosOld(),			// 前回の位置
		vtxMin,					// プレイヤーの最小値
		GetFileData().vtxMin,	// 最小値
		vtxMax,					// プレイヤーの最大値
		GetFileData().vtxMax	// 最大値
	) == true)
	{ // 当たった場合

		// 位置を適用する
		pPlayer->SetPos(pos);

		// true を返す
		return true;
	}

	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CDynamite::Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize)
{
	if (m_state == STATE_EXPLOSION)
	{ // 爆発状態の場合

		if (useful::CylinderInner(pPlayer->GetPos(), GetPos(), collSize.x + EXPLOSION_RADIUS))
		{ // 円の中に入った場合

			// true を返す
			return true;
		}
	}

	// false を返す
	return false;
}

//=====================================
// モデルサイズ変更処理
//=====================================
void CDynamite::ChageScale(void)
{
	// 拡大サイズを取得
	D3DXVECTOR3 scale = CObstacle::GetScale();

	switch (m_state)
	{
	case CDynamite::STATE_NONE:	// 通常状態
		break;
	
	case CDynamite::STATE_MINI:	// 縮小状態

		scale += m_SizeChangeSpeed;

		if (m_pFan != nullptr)
		{
			// 赤色に変えていく
			m_col -= m_ColChangeSpeed;

			m_fRadius += (EXPLOSION_RADIUS - START_RADIUS) / EXPLOSION_TIME;
			m_pFan->SetColor(m_col);
			m_pFan->SetRadius(m_fRadius);
		}

		if (scale.x > 2.5f)
		{
			m_state = STATE_BIG;
			m_SizeChangeSpeed += D3DXVECTOR3(0.01f,0.01f,0.01f);
			m_ColChangeSpeed += COLOR_SPEED / 0.1f;
		}

		break;

	case CDynamite::STATE_BIG:	// 拡大状態

		scale -= m_SizeChangeSpeed;

		if (m_pFan != nullptr)
		{
			// 白色に変えていく
			m_col += m_ColChangeSpeed;

			m_fRadius += (EXPLOSION_RADIUS - START_RADIUS) / EXPLOSION_TIME;
			m_pFan->SetColor(m_col);
			m_pFan->SetRadius(m_fRadius);
		}


		if (scale.x <= 1.0f)
		{
			m_state = STATE_MINI;
			m_SizeChangeSpeed += D3DXVECTOR3(0.01f, 0.01f, 0.01f);
			m_ColChangeSpeed += COLOR_SPEED / 0.1f;


		}
		break;
	case CDynamite::STATE_EXPLOSION:	// 爆発状態

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 拡大サイズを設定
	SetScale(scale);
}

//=====================================
// 爆発処理
//=====================================
void CDynamite::Explosion(void)
{
	// 爆発までのカウントを加算する
	m_nExplosion++;

	if (m_nExplosion >= EXPLOSION_COUNT)
	{// 爆発の時が来た時

		if (m_state != STATE_EXPLOSION)
		{ // 爆発状態以外の場合
			if (m_pFan != nullptr)
			{
				m_pFan->Uninit();
				m_pFan = nullptr;
			}
			//爆発状態にする
			m_state = STATE_EXPLOSION;

			// ダイナマイトの爆発音を鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_DYNAMITE);

			//	爆風用の3Dポリゴンの生成
			for (int nCnt = 0; nCnt < MAX_BURNWIND; nCnt++)
			{
				if (m_pExWind[nCnt] == nullptr)
				{
					m_pExWind[nCnt] = CObject3D::Create(CObject::TYPE_NONE, CObject::PRIORITY_SHADOW);
					m_pExWind[nCnt]->SetPos(GetPos() + D3DXVECTOR3(0.0f, 280.0f, 0.0f));
					m_pExWind[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist(BRUN_TEXTURE));
					m_pExWind[nCnt]->SetVtxColor(D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
				}
			}
			m_pExWind[0]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.0f, 0.0f));
			m_pExWind[1]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 1.0f, 0.0f));
			m_pExWind[2]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * -0.5f, 0.0f));
			m_pExWind[3]->SetRot(D3DXVECTOR3(0.0f, D3DX_PI * 0.5f, 0.0f));

		}
	}
}


//======================================================爆風円のクラス========================================================================

//==============================
// コンストラクタ
//==============================
CExplosionFan::CExplosionFan() : CObject3DFan(CObject::TYPE_PLAYER, CObject::PRIORITY_PLAYER)
{

}

//==============================
// デストラクタ
//==============================
CExplosionFan::~CExplosionFan()
{

}

//==============================
// 爆風の円の初期化処理
//==============================
HRESULT CExplosionFan::Init(void)
{
	if (FAILED(CObject3DFan::Init()))
	{ // 初期化処理に失敗した場合

	  // 失敗を返す
		return E_FAIL;
	}
							// 値を返す
	return S_OK;
}

//========================================
// 爆風の円の終了処理
//========================================
void CExplosionFan::Uninit(void)
{
	// 終了処理
	CObject3DFan::Uninit();
}

//=====================================
// 爆風の円の更新処理
//=====================================
void CExplosionFan::Update(void)
{
	// 頂点座標の設定処理
	SetVertex();

	// 頂点カラーの設定処理
	SetVtxColor(GetColor());		

}

//=====================================
// 爆風の円の描画処理
//=====================================
void CExplosionFan::Draw(void)
{
	// 描画処理
	CObject3DFan::Draw();
}

//=====================================
// 情報の設定処理
//=====================================
void CExplosionFan::SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// 設定処理に便利なマクロ定義
	//NONE_D3DXVECTOR3					// 向きを傾けない時とかに使用する
	//NONE_SCALE						// 拡大率を変更しないときとかに使う
	// 情報の設定処理

	//==========================================================================
	// 3Dポリゴン
	//==========================================================================
	SetPos(pos);					// 位置
	SetPosOld(GetPos());			// 前回の位置
	SetRot(NONE_D3DXVECTOR3);		// 向き
	SetSize(NONE_SCALE);			// サイズ
	SetNumAngle(120);				// 角度の総数
	SetRadius(START_RADIUS);		// 半径
	SetColor(col);					// 色
}

//=======================================
// 生成処理
//=======================================
CExplosionFan* CExplosionFan::Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	// ローカルオブジェクトを生成
	CExplosionFan* pExplosionFan = nullptr;	// サンプルのインスタンスを生成

	if (pExplosionFan == nullptr)
	{ // オブジェクトが NULL の場合

	  // インスタンスを生成
		pExplosionFan = new CExplosionFan;
	}
	else
	{ // オブジェクトが NULL じゃない場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pExplosionFan != nullptr)
	{ // オブジェクトが NULL じゃない場合

	  // 情報の設定処理
		pExplosionFan->SetData(pos, col);

		// 初期化処理
		if (FAILED(pExplosionFan->Init()))
		{ // 初期化に失敗した場合

		  // 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}
	}
	else
	{ // オブジェクトが NULL の場合

	  // 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// サンプルのポインタを返す
	return pExplosionFan;
}