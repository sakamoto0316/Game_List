//============================================
//
// タイトルロゴ処理[title_logo.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "title_logo.h"
#include "object2D.h"
#include "title.h"
#include "locus2D.h"
#include "texture.h"
#include "useful.h"
#include "sound.h"

#include "title_press.h"

//--------------------------------------------
// マクロ定義
//--------------------------------------------
#define RAT_TEXTURE				"data/TEXTURE/title.3.png"			// タイトルロゴ(ネズミ)のテクスチャ
#define CAT_TEXTURE				"data/TEXTURE/title.1.png"			// タイトルロゴ(ネコ)のテクスチャ
#define AND_TEXTURE				"data/TEXTURE/title.2.png"				// タイトルロゴ(＆)のテクスチャ
#define RAT_POS					(D3DXVECTOR3(-360.0f, 330.0f, 0.0f))	// ネズミの位置
#define CAT_POS					(D3DXVECTOR3(-240.0f, 270.0f, 0.0f))	// ネコの位置
#define AND_POS					(D3DXVECTOR3(530.0f, 300.0f, 0.0f))		// ＆の位置
#define RAT_SIZE				(D3DXVECTOR3(360.0f, 60.0f, 0.0f))		// ネズミのサイズ
#define CAT_SIZE				(D3DXVECTOR3(240.0f, 60.0f, 0.0f))		// ネコのサイズ
#define AND_SIZE				(NONE_D3DXVECTOR3)						// ＆のサイズ
#define ESCAPE_MOVE_SPEED		(60.0f)			// 逃走状態の移動量の速度
#define CAT_APPEAR_RAT_POS		(780.0f)		// ネコが移動しだすネズミの位置
#define RAT_ESCAPE_STOP_POS		(930.0f)		// ネズミの止まる位置
#define CAT_ESCAPE_STOP_POS		(250.0f)		// ネコの止まる位置
#define LOCUS_COUNT				(5)				// 残像の出るカウント数
#define AND_ADD_SIZE			(5.0f)			// アンドのサイズの追加量
#define AND_APPEAR_COUNT		(10)			// アンド出現状態のカウント数
#define AND_DEST_SIZE			(D3DXVECTOR3(AND_ADD_SIZE * AND_APPEAR_COUNT, AND_ADD_SIZE * AND_APPEAR_COUNT, 0.0f))	// アンドの目的のサイズ
#define CAT_FRAMEOUT_RAT_POS	(SCREEN_WIDTH)							// ネコが画面外に移動しだすネズミの位置
#define RAT_FRAMEOUT_STOP_POS	(SCREEN_WIDTH + RAT_SIZE.x)				// ネズミの止まる位置
#define CAT_FRAMEOUT_STOP_POS	(SCREEN_WIDTH + CAT_SIZE.x)				// ネコの止まる位置
#define AND_FRAMEOUT_MOVE		(D3DXVECTOR3(-32.0f, -10.0f, 0.0f))		// 画面外のアンドの移動量
#define SHAKEOFF_MOVE_SPEED		(-60.0f)								// 逃げ切り状態の移動量の速度
#define SHAKEOFF_RAT_POS_Y		(650.0f)								// 逃げ切り状態のネズミの縦の位置
#define SHAKEOFF_RAT_STOP_POS	(SCREEN_WIDTH * 0.5f)					// 逃げ切り状態のネズミの停止する位置
#define HOLEIN_RAT_SIZE_FRAME	(40)									// 穴入り状態のネズミのサイズの縮小フレーム数
#define HOLEIN_RAT_SUB_POS		(2.8f)									// 穴入り状態のネズミの位置の減算量

//============================
// コンストラクタ
//============================
CTitleLogo::CTitleLogo() : CObject(CObject::TYPE_TITLELOGO, PRIORITY_UI)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;	// 移動量
		m_aTitle[nCnt].pLogo = nullptr;			// タイトルのポリゴン
		m_aTitle[nCnt].bDisp = false;			// 表示状況
		m_aTitle[nCnt].bMove = false;			// 移動状況
	}

	m_state = STATE_ESCAPE;		// 状態
	m_nStateCount = 0;			// 状態カウント
	m_bSe = false;				// SE再生状況
}

//============================
// デストラクタ
//============================
CTitleLogo::~CTitleLogo()
{

}

//============================
// 初期化処理
//============================
HRESULT CTitleLogo::Init(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo == nullptr)
		{ // タイトルが NULL の場合

			// タイトルのロゴを生成する
			m_aTitle[nCnt].pLogo = CObject2D::Create(CObject2D::TYPE_NONE, CObject::TYPE_NONE, CObject::PRIORITY_UI);
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}

		// 全ての値を初期化する
		m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// 移動量
		m_aTitle[nCnt].bDisp = false;				// 表示状況
		m_aTitle[nCnt].bMove = false;				// 移動状況
	}

	m_state = STATE_ESCAPE;		// 状態
	m_nStateCount = 0;			// 状態カウント
	m_bSe = false;				// SE再生状況

	// 成功を返す
	return S_OK;
}

//============================
// 終了処理
//============================
void CTitleLogo::Uninit(void)
{
	// 全ての値をクリアする
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // タイトルのポリゴンが NULL じゃない場合

			// 終了処理
			m_aTitle[nCnt].pLogo->Uninit();
			m_aTitle[nCnt].pLogo = nullptr;
		}
	}

	// 本体の終了処理
	Release();
}

//============================
// 更新処理
//============================
void CTitleLogo::Update(void)
{
	switch (CTitle::GetState())
	{
	case CTitle::STATE_TITLE_APPEAR:	// 出現状態

		switch (m_state)
		{
		case STATE_ESCAPE:

			// 逃走状態の処理
			EscapeProcess();

			break;

		case STATE_AND:

			// ＆出現状態の処理
			AndProcess();

			break;

		default:

			// 停止
			assert(false);

			break;
		}

		break;

	case CTitle::STATE_WAIT:			// 待機状態

		break;

	case CTitle::STATE_TRANS:			// 遷移状態

		switch (m_state)
		{
		case STATE_WAIT:

			// 画面外状態にする
			m_state = STATE_FRAMEOUT;

			// アンドの移動量を設定する
			m_aTitle[TYPE_AND].move = AND_FRAMEOUT_MOVE;

			break;

		case CTitleLogo::STATE_FRAMEOUT:

			// 画面外状態の処理
			FrameOutProcess();

			break;

		case CTitleLogo::STATE_SHAKEOFF:

			// 逃げ切り状態の処理
			ShakeOffProcess();

			break;

		case CTitleLogo::STATE_HOLEIN:

			// 穴入り状態の処理
			HoleInProcess();

			if (m_bSe == false)
			{ // SE鳴らしてなかったら

				// ホールイン再生
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLEHOLE);
				m_bSe = true;
			}

			break;

		case STATE_STOP:

			// 停止しているので特に処理は無し

			break;

		default:

			// 停止
			assert(false);

			break;
		}

		break;

	case CTitle::STATE_HOLEIN:			// 穴の中に入る状態

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// 方向と長さを設定する
		m_aTitle[nCnt].pLogo->SetAngle();
		m_aTitle[nCnt].pLogo->SetLength();

		// 頂点座標の設定処理
		m_aTitle[nCnt].pLogo->SetVertexRot();
	}
}

//============================
// 描画処理
//============================
void CTitleLogo::Draw(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr &&
			m_aTitle[nCnt].bDisp == true)
		{ // タイトルが NULL じゃない場合

			// 描画処理
			m_aTitle[nCnt].pLogo->Draw();
		}
	}
}

//============================
// 情報の設定処理
//============================
void CTitleLogo::SetData(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_aTitle[nCnt].pLogo != nullptr)
		{ // タイトルが NULL じゃない場合

			// 情報を設定する
			switch (nCnt)
			{
			case TYPE_RAT:		// ネズミ

				m_aTitle[nCnt].pLogo->SetPos(RAT_POS);		// 位置
				m_aTitle[nCnt].pLogo->SetPosOld(RAT_POS);	// 前回の位置
				m_aTitle[nCnt].pLogo->SetSize(RAT_SIZE);	// サイズ

				// テクスチャの設定処理
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(RAT_TEXTURE));

				// 情報を設定する
				m_aTitle[nCnt].move.x = ESCAPE_MOVE_SPEED;	// 移動量
				m_aTitle[nCnt].bDisp = true;				// 表示状況
				m_aTitle[nCnt].bMove = true;				// 移動状況

				break;

			case TYPE_AND:		// アンド

				m_aTitle[nCnt].pLogo->SetPos(AND_POS);		// 位置
				m_aTitle[nCnt].pLogo->SetPosOld(AND_POS);	// 前回の位置
				m_aTitle[nCnt].pLogo->SetSize(AND_SIZE);	// サイズ

				// テクスチャの設定処理
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(AND_TEXTURE));

				// 情報を設定する
				m_aTitle[nCnt].move = NONE_D3DXVECTOR3;		// 移動量
				m_aTitle[nCnt].bDisp = false;				// 表示状況
				m_aTitle[nCnt].bMove = false;				// 移動状況

				break;

			case TYPE_CAT:		// ネコ

				m_aTitle[nCnt].pLogo->SetPos(CAT_POS);		// 位置
				m_aTitle[nCnt].pLogo->SetPosOld(CAT_POS);	// 前回の位置
				m_aTitle[nCnt].pLogo->SetSize(CAT_SIZE);	// サイズ

				// テクスチャの設定処理
				m_aTitle[nCnt].pLogo->BindTexture(CManager::Get()->GetTexture()->Regist(CAT_TEXTURE));

				// 情報を設定する
				m_aTitle[nCnt].move.x = ESCAPE_MOVE_SPEED;	// 移動量
				m_aTitle[nCnt].bDisp = true;				// 表示状況
				m_aTitle[nCnt].bMove = false;				// 移動状況

				break;
			}

			m_aTitle[nCnt].pLogo->SetRot(NONE_D3DXVECTOR3);	// 向き
			m_aTitle[nCnt].pLogo->SetAngle();				// 方向
			m_aTitle[nCnt].pLogo->SetLength();				// 長さ

			// 頂点座標の設定処理
			m_aTitle[nCnt].pLogo->SetVertexRot();
		}
		else
		{ // 上記以外

			// 停止
			assert(false);
		}
	}

	m_state = STATE_ESCAPE;		// 状態
	m_nStateCount = 0;			// 状態カウント
}

//============================
//生成処理
//============================
CTitleLogo* CTitleLogo::Create(void)
{
	// タイトルロゴのポインタを生成
	CTitleLogo* pTitle = nullptr;

	if (pTitle == nullptr)
	{ // オブジェクトが NULL の場合

		// オブジェクトを生成
		pTitle = new CTitleLogo;
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pTitle != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pTitle->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pTitle->SetData();
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// タイトルロゴのポインタを返す
	return pTitle;
}

//============================
// 逃走状態の処理
//============================
void CTitleLogo::EscapeProcess(void)
{
	// 移動処理
	Move(TYPE::TYPE_RAT);		// ネズミ
	Move(TYPE::TYPE_CAT);		// ネコ

	// ネズミの位置の設定処理
	EscapeRatPosSet();

	// ネコの位置の設定処理
	EscapeCatPosSet();

	if (m_nStateCount % LOCUS_COUNT == 0)
	{ // 一定時間ごとに

		// 残像の発生処理
		Locus(TYPE_RAT);
		Locus(TYPE_CAT);
	}

	// 残像の発生カウントを加算する
	m_nStateCount++;
}

//============================
// ＆出現状態の処理
//============================
void CTitleLogo::AndProcess(void)
{
	// 状態カウントを加算する
	m_nStateCount++;

	// サイズを取得する
	D3DXVECTOR3 rot = m_aTitle[TYPE_AND].pLogo->GetRot();
	D3DXVECTOR3 size = m_aTitle[TYPE_AND].pLogo->GetSize();

	// サイズを加算する
	size.x = AND_ADD_SIZE * m_nStateCount;
	size.y = AND_ADD_SIZE * m_nStateCount;

	// 向きを減算する
	rot.z -= (D3DX_PI * 2) / AND_APPEAR_COUNT;

	// 向きの正規化
	useful::RotNormalize(&rot.z);

	if (size.x >= AND_DEST_SIZE.x ||
		size.y >= AND_DEST_SIZE.y)
	{ // サイズが一定以上になった場合

		// サイズを補正する
		size = AND_DEST_SIZE;

		// 向きをまっすぐに補正する
		rot.z = 0.0f;

		// 待機状態にする
		m_state = STATE_WAIT;

		// タイトルを待機状態にする
		CTitle::SetState(CTitle::STATE_WAIT);

		// 移動状況を true にする(いつ次に動くタイミングに入るか分からないため対策しておく)
		m_aTitle[TYPE_RAT].bMove = true;
		m_aTitle[TYPE_CAT].bMove = true;

		// タイトルのプレスを生成
		CTitlePress::Create();
	}

	// 向きとサイズを適用する
	m_aTitle[TYPE_AND].pLogo->SetRot(rot);
	m_aTitle[TYPE_AND].pLogo->SetSize(size);
}

//============================
// 画面外状態の処理
//============================
void CTitleLogo::FrameOutProcess(void)
{
	// 移動状況を true にする
	m_aTitle[TYPE_RAT].bMove = true;
	m_aTitle[TYPE_CAT].bMove = true;

	// 移動処理
	Move(TYPE::TYPE_RAT);		// ネズミ
	Move(TYPE::TYPE_CAT);		// ネコ

	// 画面外状態のネズミの位置関係処理
	FrameOutRatPosSet();

	// 画面外状態のネコの位置関係処理
	FrameOutCatPosSet();

	// 画面外状態のアンドの処理
	FrameOutAnd();

	if (m_nStateCount % LOCUS_COUNT == 0)
	{ // 一定時間ごとに

		// 残像の発生処理
		Locus(TYPE_RAT);
		Locus(TYPE_CAT);
	}

	// 残像の発生カウントを加算する
	m_nStateCount++;
}

//============================
// 逃げ切り状態の処理
//============================
void CTitleLogo::ShakeOffProcess(void)
{
	// 移動状況を true にする
	m_aTitle[TYPE_RAT].bMove = true;

	// 移動処理
	Move(TYPE::TYPE_RAT);		// ネズミ

	// 逃げ切り状態のネズミの位置関係処理
	ShakeOffRatPosSet();

	if (m_nStateCount % LOCUS_COUNT == 0)
	{ // 一定時間ごとに

		// 残像の発生処理
		Locus(TYPE_RAT);
	}

	m_bSe = false;		// SE再生しない

	// 残像の発生カウントを加算する
	m_nStateCount++;
}

//============================
// 穴入り状態の処理
//============================
void CTitleLogo::HoleInProcess(void)
{
	// ネズミの情報を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();		// 位置
	D3DXVECTOR3 size = m_aTitle[TYPE_RAT].pLogo->GetSize();		// サイズ

	// サイズを減算する
	size.x -= RAT_SIZE.x / HOLEIN_RAT_SIZE_FRAME;
	size.y -= RAT_SIZE.y / HOLEIN_RAT_SIZE_FRAME;

	// 上に移動させる(穴の中に入っていく感じを演出)
	pos.y -= HOLEIN_RAT_SUB_POS;

	if (size.x <= 0.0f ||
		size.y <= 0.0f)
	{ // サイズが0.0f以下になった場合

		// サイズを補正する
		size = NONE_D3DXVECTOR3;

		// ネズミを描画しないようにする
		m_aTitle[TYPE_RAT].bDisp = false;

		// 停止状態にする
		m_state = STATE_STOP;

		// タイトルを穴の中に入った状態にする
		CTitle::SetState(CTitle::STATE_HOLEIN);

		m_bSe = false;		// SE再生しない
	}

	// ネズミの情報を適用する
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);		// 位置
	m_aTitle[TYPE_RAT].pLogo->SetSize(size);	// サイズ
}

//============================
// 移動処理
//============================
void CTitleLogo::Move(const TYPE type)
{
	if (m_aTitle[type].bMove == true)
	{ // 移動状況が true の場合

		// 位置を取得する
		D3DXVECTOR3 pos = m_aTitle[type].pLogo->GetPos();

		// 位置を加算する
		pos.x += m_aTitle[type].move.x;

		// 位置を適用する
		m_aTitle[type].pLogo->SetPos(pos);
	}
}

//============================
// 残像発生処理
//============================
void CTitleLogo::Locus(const TYPE type)
{
	if (m_aTitle[type].bMove == true)
	{ // 移動状況が true の場合

		// 残像の生成処理
		CLocus2D::Create
		(
			m_aTitle[type].pLogo->GetPos(),		// 位置
			NONE_D3DXVECTOR3,					// 向き
			m_aTitle[type].pLogo->GetSize(),	// サイズ
			0.2f,								// 透明度
			40,									// 寿命
			m_aTitle[type].pLogo->GetTexIdx()	// テクスチャのインデックス
		);
	}
}

//============================
// 逃走状態のネズミの位置関係処理
//============================
void CTitleLogo::EscapeRatPosSet(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x >= CAT_APPEAR_RAT_POS)
	{ // ネズミの位置が一定位置を超えた場合

		// 移動状況を true にする
		m_aTitle[TYPE_CAT].bMove = true;
	}

	if (pos.x >= RAT_ESCAPE_STOP_POS)
	{ // ネズミの位置が一定の位置に達した場合

		// ネズミの位置を補正する
		pos.x = RAT_ESCAPE_STOP_POS;

		// 移動状況を false にする
		m_aTitle[TYPE_RAT].bMove = false;
	}

	// 位置を適用する
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// 逃走状態のネコの位置関係処理
//============================
void CTitleLogo::EscapeCatPosSet(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_CAT].pLogo->GetPos();

	if (pos.x >= CAT_ESCAPE_STOP_POS)
	{ // ネコの位置が一定の位置に達した場合

		// ネコの位置を補正する
		pos.x = CAT_ESCAPE_STOP_POS;

		// 移動状況を false にする
		m_aTitle[TYPE_CAT].bMove = false;

		// アンドの表示状況を true にする
		m_aTitle[TYPE_AND].bDisp = true;

		// 待機状態にする
		m_state = STATE_AND;

		// 状態カウントを初期化する
		m_nStateCount = 0;
	}

	// 位置を適用する
	m_aTitle[TYPE_CAT].pLogo->SetPos(pos);
}

//============================
// 画面外状態のネズミの位置関係処理
//============================
void CTitleLogo::FrameOutRatPosSet(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x >= CAT_FRAMEOUT_RAT_POS)
	{ // ネズミの位置が一定位置を超えた場合

		// 移動状況を true にする
		m_aTitle[TYPE_CAT].bMove = true;
	}

	if (pos.x >= RAT_FRAMEOUT_STOP_POS)
	{ // ネズミの位置が一定の位置に達した場合

		// ネズミの位置を補正する
		pos.x = RAT_FRAMEOUT_STOP_POS;

		// 移動状況を false にする
		m_aTitle[TYPE_RAT].bMove = false;
	}

	// 位置を適用する
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// 画面外状態のネコの位置関係処理
//============================
void CTitleLogo::FrameOutCatPosSet(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_CAT].pLogo->GetPos();

	if (pos.x >= CAT_FRAMEOUT_STOP_POS)
	{ // ネコの位置が一定の位置に達した場合

		// ネコの位置を補正する
		pos.x = CAT_FRAMEOUT_STOP_POS;

		// 移動状況を false にする
		m_aTitle[TYPE_CAT].bMove = false;

		// ネコを表示させなくする
		m_aTitle[TYPE_CAT].bDisp = false;

		// 状態カウントを初期化する
		m_nStateCount = 0;

		// 逃げ切り状態にする
		m_state = STATE_SHAKEOFF;

		// 画面外時のネズミの設定処理
		FrameOutSetRat();
	}
	else
	{
		if (m_bSe == false)
		{ // SE鳴らしてなかったら

			// ホールイン再生
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLEBLOW);
			m_bSe = true;
		}
	}

	// 位置を適用する
	m_aTitle[TYPE_CAT].pLogo->SetPos(pos);
}

//============================
// 画面外時のネズミの設定処理
//============================
void CTitleLogo::FrameOutSetRat(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	// ネズミの移動量を設定する
	m_aTitle[TYPE_RAT].move.x = SHAKEOFF_MOVE_SPEED;

	// 位置を設定する
	pos.y = SHAKEOFF_RAT_POS_Y;

	// 位置を適用する
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}

//============================
// 画面外状態のアンドの処理
//============================
void CTitleLogo::FrameOutAnd(void)
{
	// 位置とサイズを取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_AND].pLogo->GetPos();
	D3DXVECTOR3 rot = m_aTitle[TYPE_AND].pLogo->GetRot();

	// 位置を加算する
	pos += m_aTitle[TYPE_AND].move;

	// 重力をかける
	m_aTitle[TYPE_AND].move.y += 0.3f;

	// 向きを減算する
	rot.z += 0.02f;

	// 向きの正規化
	useful::RotNormalize(&rot.z);

	if (m_state == STATE_SHAKEOFF)
	{ // サイズが一定以上になった場合

		// 向きをまっすぐに補正する
		rot.z = 0.0f;

		// アンドの描画をしないようにする
		m_aTitle[TYPE_AND].bDisp = false;

		//m_bSe = false;
	}

	// 位置とサイズを適用する
	m_aTitle[TYPE_AND].pLogo->SetPos(pos);
	m_aTitle[TYPE_AND].pLogo->SetRot(rot);
}

//============================
// 逃げ切り状態のネズミの位置関係処理
//============================
void CTitleLogo::ShakeOffRatPosSet(void)
{
	// 位置を取得する
	D3DXVECTOR3 pos = m_aTitle[TYPE_RAT].pLogo->GetPos();

	if (pos.x <= SHAKEOFF_RAT_STOP_POS)
	{ // ネズミの位置が一定の位置に達した場合

		// ネズミの位置を補正する
		pos.x = SHAKEOFF_RAT_STOP_POS;

		// 移動状況を false にする
		m_aTitle[TYPE_RAT].bMove = false;

		// 穴入り状態にする
		m_state = STATE_HOLEIN;
	}

	// 位置を適用する
	m_aTitle[TYPE_RAT].pLogo->SetPos(pos);
}