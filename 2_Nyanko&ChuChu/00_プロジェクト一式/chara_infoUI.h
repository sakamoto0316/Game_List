//============================================
//
// キャラクターの情報UIヘッダー[chara_infoUI.h]
// Author：小原立暉
//
//============================================
#ifndef _CHARA_INFOUI_H_			// このマクロ定義がされていなかったら
#define _CHARA_INFOUI_H_			// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object.h"
#include "player.h"

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CCharaIcon;		// キャラクターのアイコン
class CCharaID;			// キャラクターのID
class CCharaState;		// キャラクターの状態アイコン

//--------------------------------------------
// クラス定義(キャラクターの情報UI)
//--------------------------------------------
class CCharaInfoUI : public CObject
{
public:				// 誰でもアクセスできる

	CCharaInfoUI();					// コンストラクタ
	~CCharaInfoUI();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type);						// 情報の設定処理

	// 静的メンバ関数
	static CCharaInfoUI* Create(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type);			// 生成処理

private:			// 自分だけアクセスできる

	// メンバ変数
	CCharaIcon* m_pIcon;	// アイコンの情報
	CCharaID* m_pID;		// IDの情報
	CCharaState* m_pState;	// 状態の情報
};

#endif