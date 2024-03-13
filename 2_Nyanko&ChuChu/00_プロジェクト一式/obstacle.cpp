//===========================================
//
// 障害物のメイン処理[obstacle.cpp]
// Author 小原立暉
//
//===========================================
//*******************************************
// インクルードファイル
//*******************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "obstacle.h"
#include "obstacle_manager.h"
#include "useful.h"
#include "objectbillboard.h"
#include "texture.h"

#include "honey.h"
#include "slime.h"
#include "hairball.h"
#include "petbottle.h"
#include "toycar.h"
#include "roomba.h"
#include "Himo.h"
#include "speaker.h"
#include "mousetrap.h"
#include "leash.h"
#include "Pin.h"
#include "electricfan.h"
#include "cup.h"
#include "garbagecan.h"
#include "tv.h"
#include "dynamite.h"
#include "book.h"
#include "curtain.h"
#include "ratmecha.h"
#include "game.h"
#include "tutorial.h"

//==============================
// コンストラクタ
//==============================
CObstacle::CObstacle() : CModel(CObject::TYPE_OBSTACLE, CObject::PRIORITY_BLOCK)
{
	// コンストラクタの箱
	Box();
}

//==============================
// オーバーロードコンストラクタ
//==============================
CObstacle::CObstacle(CObject::TYPE type, PRIORITY priority) : CModel(type, priority)
{
	// コンストラクタの箱
	Box();
}

//==============================
// デストラクタ
//==============================
CObstacle::~CObstacle()
{

}

//==============================
// コンストラクタの箱
//==============================
void CObstacle::Box(void)
{
	// 全ての値をクリアする
	m_type = TYPE_HONEY;	// 種類
	m_pPrev = nullptr;		// 前のへのポインタ
	m_pNext = nullptr;		// 次のへのポインタ
	m_pGimmickUI = NULL;
	m_pMultiGimmickUI[0] = NULL;
	m_pMultiGimmickUI[1] = NULL;
	for (int nCnt = 0; nCnt < 4; nCnt++)
	{
		m_pGimmickUIFalse[nCnt] = false;
	}
	m_bCatUse = false;
	m_bRatUse = false;
	m_bAction = false;
	m_fAlpha = 1.0f;
	m_bCatDisp = false;
	m_bRatDisp = false;

	if (CObstacleManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// マネージャーへの登録処理
		CObstacleManager::Get()->Regist(this);
	}
}

//============================
// 前のポインタの設定処理
//============================
void CObstacle::SetPrev(CObstacle* pPrev)
{
	// 前のポインタを設定する
	m_pPrev = pPrev;
}

//============================
// 後のポインタの設定処理
//============================
void CObstacle::SetNext(CObstacle* pNext)
{
	// 次のポインタを設定する
	m_pNext = pNext;
}

//============================
// 前のポインタの設定処理
//============================
CObstacle* CObstacle::GetPrev(void) const
{
	// 前のポインタを返す
	return m_pPrev;
}

//============================
// 次のポインタの設定処理
//============================
CObstacle* CObstacle::GetNext(void) const
{
	// 次のポインタを返す
	return m_pNext;
}

//==============================
// 破片の初期化処理
//==============================
HRESULT CObstacle::Init(void)
{
	if (FAILED(CModel::Init()))
	{ // 初期化処理に失敗した場合

		// 失敗を返す
		return E_FAIL;
	}

	// 全ての値を初期化する
	m_type = TYPE_HONEY;	// 種類

	// 値を返す
	return S_OK;
}

//========================================
// 破片の終了処理
//========================================
void CObstacle::Uninit(void)
{
	// 終了処理
	CModel::Uninit();

	if (CObstacleManager::Get() != nullptr)
	{ // マネージャーが存在していた場合

		// リスト構造の引き抜き処理
		CObstacleManager::Get()->Pull(this);
	}

	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->Uninit();
		m_pGimmickUI = NULL;
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Uninit();
			m_pMultiGimmickUI[nCnt] = NULL;
		}
	}

	// リスト構造関係のポインタを NULL にする
	m_pPrev = nullptr;
	m_pNext = nullptr;
}

//=====================================
// 破片の更新処理
//=====================================
void CObstacle::Update(void)
{
	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->Update();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Update();
		}
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CObstacle::Draw(void)
{
	// 描画処理
	CModel::Draw();

	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->DrawLightOff();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Draw();
		}
	}
}

//=====================================
// 破片の描画処理
//=====================================
void CObstacle::Draw(const float fAlpha)
{
	for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
	{// どのプレイヤーのカメラ番号か回して確かめる
		if (CManager::Get()->GetMode() == CScene::MODE_GAME)
		{// ゲームモードの時
			CPlayer* pPlayer = CGame::GetPlayer(nCnt);
			if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
			{// ネコプレイヤーを取得
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{// カメラ番号とプレイヤー番号が一致する時

					if (m_bCatDisp == true)
					{// 変数がtrueの時強制的に表示する

						// 描画処理
						CModel::Draw(1.0f);
					}
					else
					{// 変数がfalseの時
						if (m_bCatUse == false && m_bAction == false)
						{// ネコが使用可能な障害物の場合普通に描画
							// 描画処理
							CModel::Draw(0.3f);
						}
						else
						{// ネコが使用できない障害物の場合薄く表示
							// 描画処理
							CModel::Draw(fAlpha);
						}
					}
				}
			}
			else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
			{// ネズミプレイヤーを取得
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{// カメラ番号とプレイヤー番号が一致する時
					if (m_bRatDisp == true)
					{// 変数がtrueの時強制的に表示する

						// 描画処理
						CModel::Draw(1.0f);
					}
					else
					{// 変数がfalseの時
						if (m_bRatUse == false && m_bAction == false)
						{// ネコが使用可能な障害物の場合普通に描画
							// 描画処理
							CModel::Draw(0.3f);
						}
						else
						{// ネコが使用できない障害物の場合薄く表示
							// 描画処理
							CModel::Draw(fAlpha);
						}
					}
				}
			}
		}
		else if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
		{
			CPlayer* pPlayer = CTutorial::GetPlayer(nCnt);
			if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
			{
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{
					// 描画処理
					CModel::Draw(fAlpha);
				}
			}
			else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
			{
				if (pPlayer->GetPlayerIdx() == GetDrawIdx())
				{
					// 描画処理
					CModel::Draw(fAlpha);
				}
			}
		}
	}
	//// 描画処理
	//CModel::Draw(fAlpha);

	if (m_pGimmickUI != NULL)
	{
		m_pGimmickUI->DrawLightOff();
	}

	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (m_pMultiGimmickUI[nCnt] != NULL)
		{
			m_pMultiGimmickUI[nCnt]->Draw();
		}
	}
}

//=====================================
// 情報の設定処理
//=====================================
void CObstacle::SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// 情報の設定処理
	SetPos(pos);							// 位置
	SetPosOld(pos);							// 前回の位置
	SetRot(rot);							// 向き
	SetScale(NONE_SCALE);					// 拡大率
	SetFileData((CXFile::TYPE)(INIT_OBSTACLE + type));	// モデル情報

	// 全ての値を初期化する
	m_type = type;		// 種類
}

//=======================================
// 生成処理
//=======================================
CObstacle* CObstacle::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type)
{
	// ローカルオブジェクトを生成
	CObstacle* pObstacle = nullptr;	// インスタンスを生成

	if (pObstacle == nullptr)
	{ // オブジェクトが NULL の場合

		switch (type)
		{
		case CObstacle::TYPE_HONEY:

			// 蜂蜜を生成する
			pObstacle = new CHoney;

			break;

		case CObstacle::TYPE_SLIME:

			// スライムを生成する
			pObstacle = new CSlime;

			break;

		case CObstacle::TYPE_HAIRBALL:

			// 毬を生成する
			pObstacle = new CHairBall;

			break;

		case CObstacle::TYPE::TYPE_PETBOTTLE:

			//ペットボトルを生成する
			pObstacle = new CPetbottle;

			break;

		case CObstacle::TYPE_TOYCAR:

			// おもちゃの車を生成する
			pObstacle = new CToyCar;

			break;

		case CObstacle::TYPE_ROOMBA:

			// ルンバを生成する
			pObstacle = new CRoomba;
			
			break;

		case CObstacle::TYPE_HIMO:		//起動系

			// ひもを生成する
			pObstacle = new CHimo;

			break;

		case CObstacle::TYPE_SPEAKER:	//起動系

			// スピーカーを生成する
			pObstacle = new CSpeaker;

			break;

		case CObstacle::TYPE_MOUSETRAP:

			// ネズミ捕りを生成する
			pObstacle = new CMouseTrap;

			break;

		case CObstacle::TYPE_LEASH:		//2人で起動系

			// リードを生成する
			pObstacle = new CLeash;

			break;

		case CObstacle::TYPE_PIN:		//起動系

			// 画鋲を生成する
			pObstacle = new CPin;

			break;

		case CObstacle::TYPE_FAN:		// 起動系

			// 扇風機を生成する
			pObstacle = new CElecFan;

			break;

		case CObstacle::TYPE_CUP:		// 起動系

			// コップを生成する
			pObstacle = new CCup;

			break;

		case CObstacle::TYPE_GARBAGECAN:		// 起動系

			// ゴミ箱を生成する
			pObstacle = new CGarbage;

			break;

		case CObstacle::TYPE_TV:		// テレビ

			// テレビを生成する
			pObstacle = new CTv;

			break;

		case CObstacle::TYPE_DYNAMITE:		// 爆弾

			// ダイナマイトを生成する
			pObstacle = new CDynamite;

			break;

		case CObstacle::TYPE_BOOK:

			// 本を生成する
			pObstacle = new CBook;

			break;

		case CObstacle::TYPE_REDKATEN:

			// カーテンを生成する
			pObstacle = new CCurtain;

			break;

		case CObstacle::TYPE_RATMECHA:

			// カーテンを生成する
			pObstacle = new CRatMecha;

			break;

		default:

			//停止
			assert(false);

			break;
		}
	}
	else
	{ // オブジェクトが NULL じゃない場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	if (pObstacle != nullptr)
	{ // オブジェクトが NULL じゃない場合

		// 初期化処理
		if (FAILED(pObstacle->Init()))
		{ // 初期化に失敗した場合

			// 停止
			assert(false);

			// NULL を返す
			return nullptr;
		}

		// 情報の設定処理
		pObstacle->SetData(pos, rot, type);
	}
	else
	{ // オブジェクトが NULL の場合

		// 停止
		assert(false);

		// NULL を返す
		return nullptr;
	}

	// 障害物のポインタを返す
	return pObstacle;
}

//=====================================
// 当たり判定処理
//=====================================
bool CObstacle::Collision(CPlayer* /*pPlayer*/, const D3DXVECTOR3& /*collSize*/)
{
	// false を返す
	return false;
}

//=====================================
// ヒット処理
//=====================================
bool CObstacle::Hit(CPlayer* /*pPlayer*/, const D3DXVECTOR3& /*collSize*/)
{
	// false を返す
	return false;
}

//=====================================
// ギミック起動UIの表示
//=====================================
void CObstacle::GimmickUI(bool Set, int Player_Idx)
{
	if (Set == true)
	{//UI表示の範囲内にいる場合
		if (m_pGimmickUI == NULL)
		{
			if (m_bAction == false)
			{
				//自分のUI表示状態をONにする
				m_pGimmickUIFalse[Player_Idx] = true;

				//UIの表示
				m_pGimmickUI = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
				m_pGimmickUI->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\UI_GimmickOn.png"));
				m_pGimmickUI->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));

				if (m_type == TYPE::TYPE_HIMO)
				{
					m_pGimmickUI->SetPos(D3DXVECTOR3(
						GetPos().x,
						GetPos().y - 400.0f,
						GetPos().z));
					m_pGimmickUI->SetPosOld(D3DXVECTOR3(
						GetPos().x,
						GetPos().y - 400.0f,
						GetPos().z));
					m_pGimmickUI->SetVertex();
				}
				else if (m_type == TYPE::TYPE_TV)
				{
					m_pGimmickUI->SetPos(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 310.0f,
						GetPos().z));
					m_pGimmickUI->SetPosOld(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 310.0f,
						GetPos().z));
					m_pGimmickUI->SetVertex();
				}
				else
				{
					m_pGimmickUI->SetPos(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 50.0f,
						GetPos().z));
					m_pGimmickUI->SetPosOld(D3DXVECTOR3(
						GetPos().x,
						GetPos().y + 50.0f,
						GetPos().z));
					m_pGimmickUI->SetVertex();
				}
			}
		}
	}
	else
	{//UI表示の範囲内にいない場合

		//自分のUI表示状態をOFFにする
		m_pGimmickUIFalse[Player_Idx] = false;
	}

	//全てのプレイヤーの表示状態がOFFのとき削除する
	if (m_pGimmickUIFalse[0] == false &&
		m_pGimmickUIFalse[1] == false &&
		m_pGimmickUIFalse[2] == false &&
		m_pGimmickUIFalse[3] == false)
	{
		if (m_pGimmickUI != NULL)
		{
			m_pGimmickUI->Uninit();
			m_pGimmickUI = NULL;
		}
	}
}

//=====================================
// ギミック起動UIの表示
//=====================================
void CObstacle::MultiGimmickUI(bool Set, int Player_Idx)
{
	for (int nCnt = 0; nCnt < 2; nCnt++)
	{
		if (Set == true)
		{//UI表示の範囲内にいる場合
			if (m_pMultiGimmickUI[nCnt] == NULL)
			{
				//自分のUI表示状態をONにする
				m_pGimmickUIFalse[Player_Idx] = true;

				//UIの表示
				m_pMultiGimmickUI[nCnt] = CBillboard::Create(TYPE_NONE, PRIORITY_UI);
				m_pMultiGimmickUI[nCnt]->BindTexture(CManager::Get()->GetTexture()->Regist("data\\TEXTURE\\UI_GimmickOn.png"));
				m_pMultiGimmickUI[nCnt]->SetSize(D3DXVECTOR3(50.0f, 50.0f, 0.0f));
				if (nCnt == 0)
				{
					m_pMultiGimmickUI[nCnt]->SetPos(D3DXVECTOR3(
						GetPosHead().x,
						GetPosHead().y + 50.0f,
						GetPosHead().z));
					m_pMultiGimmickUI[nCnt]->SetPosOld(D3DXVECTOR3(
						GetPosHead().x,
						GetPosHead().y + 50.0f,
						GetPosHead().z));
				}
				else if (nCnt == 1)
				{
					m_pMultiGimmickUI[nCnt]->SetPos(D3DXVECTOR3(
						GetPosToes().x,
						GetPosToes().y + 50.0f,
						GetPosToes().z));
					m_pMultiGimmickUI[nCnt]->SetPosOld(D3DXVECTOR3(
						GetPosToes().x,
						GetPosToes().y + 50.0f,
						GetPosToes().z));
				}
				m_pMultiGimmickUI[nCnt]->SetVertex();
			}
		}
		else
		{//UI表示の範囲内にいない場合

		 //自分のUI表示状態をOFFにする
			m_pGimmickUIFalse[Player_Idx] = false;
		}

		//全てのプレイヤーの表示状態がOFFのとき削除する
		if (m_pGimmickUIFalse[0] == false &&
			m_pGimmickUIFalse[1] == false &&
			m_pGimmickUIFalse[2] == false &&
			m_pGimmickUIFalse[3] == false)
		{
			if (m_pMultiGimmickUI[nCnt] != NULL)
			{
				m_pMultiGimmickUI[nCnt]->Uninit();
				m_pMultiGimmickUI[nCnt] = NULL;
			}
		}
	}
}

//=======================================
// 種類の設定処理
//=======================================
void CObstacle::SetType(const TYPE type)
{
	// 種類を設定する
	m_type = type;
}

//=======================================
// 種類の取得処理
//=======================================
CObstacle::TYPE CObstacle::GetType(void)
{
	// 種類を返す
	return m_type;
}