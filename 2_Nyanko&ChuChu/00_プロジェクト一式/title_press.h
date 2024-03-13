//===================================
//
// プレスエンターヘッダー[title_press.h]
// Author 小原立暉
//
//===================================
#ifndef _TITLE_PRESS_H_
#define _TITLE_PRESS_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CObject2D;		// 2Dポリゴン

//-----------------------------------
// クラス定義(PRESSENTER)
//-----------------------------------
class CTitlePress : public CObject
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_PRESS = 0,		// プレス
		TYPE_BUTTON,		// ボタン
		TYPE_MAX			// この列挙型の総数
	};

	// 構造体定義(プレスエンター)
	struct SPress
	{
		D3DXVECTOR3 move;		// 移動量
		float fRotMove;			// 向きの移動量
		CObject2D* pPress;		// ポリゴンの情報
		int nStateCount;		// 状態カウント
		float fAlpha;			// 透明度
		float fAlphaDest;		// 目的の透明度
	};

	CTitlePress();			// コンストラクタ
	~CTitlePress();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);		// 情報の設定処理

	// 静的メンバ関数
	static CTitlePress* Create(void);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Alpha(const float fAdd);		// 透明度の処理
	void Smash(const int nType);		// 吹き飛ばし処理

	// メンバ変数
	SPress m_aPress[TYPE_MAX];			// プレスの情報構造体
	bool m_bSe;							// SEの再生状況
};

#endif