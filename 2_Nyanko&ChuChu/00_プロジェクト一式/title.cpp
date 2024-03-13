//============================================
//
// タイトル画面のメイン処理[title.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "input.h"
#include "renderer.h"
#include "object.h"
#include "title.h"
#include "fade.h"
#include "Objectmesh.h"
#include "sound.h"

#include "2DUI_edit.h"
#include "skybox.h"
#include "title_logo.h"
#include "title_wall.h"
#include "title_floor.h"
#include "title_back.h"

// マクロ定義
#define ENTRY_TRANS_TIMER		(180)										// ランキング画面に遷移するカウント数
#define WALL_POS				(D3DXVECTOR3(0.0f, 300.0f, 600.0f))			// 壁の位置
#define WALL_ROT				(D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f))	// 壁の向き
#define WALL_SIZE				(D3DXVECTOR3(800.0f, 0.0f, 600.0f))			// 壁のサイズ

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
CTitle::STATE CTitle::m_state = STATE_TITLE_APPEAR;			// 状態

//=========================================
// コンストラクタ
//=========================================
CTitle::CTitle() : CScene(TYPE_SCENE, PRIORITY_BG)
{
	// 全ての値をクリアする
	m_pUIEdit = NULL;
	m_state = STATE_TITLE_APPEAR;			// 状態
	m_nTransCount = 0;						// 遷移カウント
	m_bEdit = false;
}

//=========================================
// デストラクタ
//=========================================
CTitle::~CTitle()
{

}

//=========================================
//初期化処理
//=========================================
HRESULT CTitle::Init(void)
{
	//　シーンの初期化
	CScene::Init();

	// タイトルロゴの生成処理
	CTitleLogo::Create();

	// タイトルの壁の生成処理
	CTitleWall::Create();

	// タイトルの床の生成処理
	CTitleFloor::Create();

	// タイトルの背景の生成処理
	CTitleBack::Create();

	//UIエディターの生成
	m_pUIEdit = C2DUIEdit::Create();
	m_pUIEdit->LoadData(LOADUI_NAME,NONE_D3DXVECTOR3);

	// 全ての値を初期化する
	m_state = STATE_TITLE_APPEAR;	// 状態
	m_nTransCount = 0;				// 遷移カウント

	// 成功を返す
	return S_OK;
}

//=============================================
//終了処理
//=============================================
void CTitle::Uninit(void)
{
	// 終了処理
	CScene::Uninit();

	if (m_pUIEdit != NULL)
	{
		//エディットモードの終了処理
		m_pUIEdit->Uninit();

		delete m_pUIEdit;
		m_pUIEdit = NULL;
	}

	// 再生中のサウンドを停止
	CManager::Get()->GetSound()->Stop();
}

//======================================
//更新処理
//======================================
void CTitle::Update(void)
{
	//エディットモードのオンオフ
	if (m_bEdit)
	{
		//エディットモードの更新処理
		m_pUIEdit->Update();
	}
	else
	{
		switch (m_state)
		{
		case CTitle::STATE_TITLE_APPEAR:


			break;

		case CTitle::STATE_WAIT:

			if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_RETURN) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_START, 0) == true ||
				CManager::Get()->GetInputGamePad()->GetTrigger(CInputGamePad::JOYKEY_A, 0) == true)
			{ // ENTERキーを押した場合

				// タイトルのスタート音を鳴らす
				CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_TITLE_START);

				// 遷移状態に設定する
				m_state = STATE_TRANS;

				// この先の処理を行わない
				return;
			}

			break;

		case CTitle::STATE_TRANS:

			// 遷移カウントを加算する
			m_nTransCount++;

			break;

		case STATE_HOLEIN:

			// 遷移カウントを加算する
			m_nTransCount++;

			if (m_nTransCount % ENTRY_TRANS_TIMER == 0)
			{ // 遷移カウントが一定時間

				// エントリーに遷移する
				CManager::Get()->GetFade()->SetFade(CScene::MODE_ENTRY);
			}

			break;

		default:

			// 停止
			assert(false);

			break;
		}
	}

#ifdef _DEBUG

	if (CManager::Get()->GetInputKeyboard()->GetTrigger(DIK_F2) == true)
	{
		m_bEdit = m_bEdit ? false : true;
	}

#endif // _DEBUG

	// レンダラーの更新
	CManager::Get()->GetRenderer()->Update();
}

//======================================
//描画処理
//======================================
void CTitle::Draw(void)
{

}

//======================================
// 状態の設定処理
//======================================
void CTitle::SetState(const STATE state)
{
	// 状態を設定する
	m_state = state;
}

//======================================
// 状態の取得処理
//======================================
CTitle::STATE CTitle::GetState(void)
{
	// 状態を返す
	return m_state;
}