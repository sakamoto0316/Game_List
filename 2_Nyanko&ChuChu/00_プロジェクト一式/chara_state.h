//============================================
//
// キャラクターの状態アイコンヘッダー[chara_state.h]
// Author：小原立暉
//
//============================================
#ifndef _CHARA_STATE_H_					// このマクロ定義がされていなかったら
#define _CHARA_STATE_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object2D.h"

//--------------------------------------------
// クラス定義(キャラクターの状態)
//--------------------------------------------
class CCharaState : public CObject2D
{
public:				// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_NONE = 0,		// 通常状態
		STATE_STUN,			// 気絶状態
		STATE_GHOST,		// ゴースト状態
		STATE_MAX			// この列挙型の総数
	};

	CCharaState();			// コンストラクタ
	~CCharaState();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nID);					// 情報の設定処理

	// 静的メンバ関数
	static CCharaState* Create(const D3DXVECTOR3& pos, const int nID);		// 生成処理

private:			// 自分だけアクセスできる

	// メンバ関数
	void State(void);	// 状態処理

	// メンバ変数
	STATE m_state;		// 状態
	int m_nPlayerIdx;	// プレイヤーのインデックス
	bool m_bDisp;		// 描画状況
};

#endif