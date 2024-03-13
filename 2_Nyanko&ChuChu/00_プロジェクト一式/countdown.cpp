//=======================================
//
// カウントダウンのメイン処理[countdown.cpp]
// Author 小原立暉
//
//=======================================
#include "manager.h"
#include "countdown.h"
#include "renderer.h"
#include "texture.h"
#include "sound.h"
#include "useful.h"

#include "game.h"

//=======================================
// マクロ定義
//=======================================
#define COUNTDOWN_INIT_ROT	(D3DXVECTOR3(0.0f, 0.0f, -0.5f))		// カウントダウンの初期の向き
#define COUNTDOWN_TIME		(5)										// カウントダウンの時間
#define COUNTDOWN_TEXTURE	"data\\TEXTURE\\Number.png"				// カウントダウンのテクスチャ

//=========================
// コンストラクタ
//=========================
CCountdown::CCountdown() : CNumber(CObject::TYPE_COUNTDOWN, CObject::PRIORITY_UI)
{
	// 全ての値をクリアする
	m_sizeDest = NONE_D3DXVECTOR3;		// 目的のサイズ
	m_sizeInit = NONE_D3DXVECTOR3;		// 初期サイズ
	m_nFrame = 0;						// 経過フレーム数
	m_nSecond = 0;						// 秒数
	m_nProgressCount = 0;				// 経過させるカウント
	m_bEnd = false;						// 終了状況
}

//=========================
// デストラクタ
//=========================
CCountdown::~CCountdown()
{

}

//=========================
// 初期化処理
//=========================
HRESULT CCountdown::Init(void)
{
	if (FAILED(CNumber::Init()))
	{ // 初期化に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_sizeDest = NONE_D3DXVECTOR3;		// 目的のサイズ
	m_sizeInit = NONE_D3DXVECTOR3;		// 初期サイズ
	m_nFrame = 0;						// 経過フレーム数
	m_nSecond = 0;						// 秒数
	m_nProgressCount = 0;				// 経過させるカウント
	m_bEnd = false;						// 終了状況

	// 成功を返す
	return S_OK;
}

//=========================
// 終了処理
//=========================
void CCountdown::Uninit(void)
{
	// 終了
	CNumber::Uninit();
}

//=========================
// 更新処理
//=========================
void CCountdown::Update(void)
{
	if (CGame::GetState() != CGame::STATE_CAT_WIN)
	{// 猫が勝っている状態じゃない時

		// 計算処理
		Calculate();

		if (m_nSecond <= 0)
		{ // 時間が0を超えた場合

			// 時間を補正する
			m_nSecond = 0;

			// プレイ状態にする
			CGame::SetState(CGame::STATE_PLAY);

			// 終了処理
			Uninit();

			// この先の処理を行わない
			return;
		}

		// 回転処理
		Cycle();

		// 拡大処理
		Scaling();

		// 頂点座標の設定処理
		SetVertexRot();

		// テクスチャの設定処理(アニメーションバージョン)
		SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_nSecond);
	}
}

//=========================
// 描画処理
//=========================
void CCountdown::Draw(void)
{
	// 描画処理
	CNumber::Draw();
}

//=========================
// 情報の設定処理
//=========================
void CCountdown::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nCount, bool bEnd)
{
	// 数字の設定処理
	SetPos(pos);				// 位置
	SetPosOld(pos);				// 前回の位置
	SetRot(COUNTDOWN_INIT_ROT);	// 向き
	SetSize(size * 0.6f);		// サイズ
	SetLength();				// 長さ
	SetAngle();					// 方向
	SetNumber(COUNTDOWN_TIME);	// 数字
	SetType(TYPE_DECIMAL);		// 種類

	// 全ての値を初期化する
	m_sizeDest = size;			// 目的のサイズ
	m_sizeInit = size * 0.6f;	// 初期サイズ
	m_nFrame = 0;				// 経過フレーム数
	m_nSecond = COUNTDOWN_TIME;	// 秒数
	m_nProgressCount = nCount;	// 経過させるカウント
	m_bEnd = bEnd;				// 終了状況

	if (m_nProgressCount < 0)
	{ // 経過させるカウントが0未満の場合

		// 最低数を入力する
		m_nProgressCount = 1;
	}

	// 頂点座標の設定処理
	SetVertexRot();

	// テクスチャの設定処理(アニメーションバージョン)
	SetVtxTextureAnim(NUMBER_TEXTURE_PATTERN, m_nSecond);

	// テクスチャの割り当て処理
	BindTexture(CManager::Get()->GetTexture()->Regist(COUNTDOWN_TEXTURE));
}

//=========================
// 生成処理
//=========================
CCountdown* CCountdown::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nCount, bool bEnd)
{
	// ローカルオブジェクトを生成
	CCountdown* pCountdown = nullptr;	// プレイヤーのインスタンスを生成

	if (pCountdown == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pCountdown = new CCountdown;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pCountdown != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pCountdown->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pCountdown->SetData(pos, size, nCount, bEnd);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// カウントダウンのポインタを返す
	return pCountdown;
}

//=========================
// 計算処理
//=========================
void CCountdown::Calculate(void)
{
	// 時間の経過を加算する
	m_nFrame++;

	if ((m_nFrame % m_nProgressCount) == 0)
	{ // 1秒経ったら

		// 1秒減らす
		m_nSecond--;

		// 向きを設定する
		SetRot(COUNTDOWN_INIT_ROT);

		// サイズを設定する
		SetSize(m_sizeInit);

		// 数字の設定処理
		SetNumber(m_nSecond);

		if (m_bEnd == true)
		{ // 終了の場合

			// 終了のカウントダウンを鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_COUNT_END);
		}
		else
		{ // 上記以外

			// 始まりのカウントダウンを鳴らす
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_COUNT_START);
		}
	}
}

//=========================
// 回転処理
//=========================
void CCountdown::Cycle(void)
{
	// 向きを取得する
	D3DXVECTOR3 rot = GetRot();

	// 向きの補正処理
	useful::RotCorrect(0.0f, &rot.z, 0.1f);

	// 向きを適用する
	SetRot(rot);
}

//=========================
// 拡大処理
//=========================
void CCountdown::Scaling(void)
{
	// サイズを取得する
	D3DXVECTOR3 size = GetSize();

	// サイズの補正処理
	useful::Correct(m_sizeDest.x, &size.x, 0.2f);
	useful::Correct(m_sizeDest.y, &size.y, 0.2f);
	useful::Correct(m_sizeDest.z, &size.z, 0.2f);

	// サイズの設定処理
	SetSize(size);

	// 方向の設定処理
	SetAngle();

	// 長さの設定処理
	SetLength();
}