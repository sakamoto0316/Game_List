//============================================
//
// アイテムの枠ヘッダー[item_frame.h]
// Author：小原立暉
//
//============================================
#ifndef _ITEM_FRAME_H_					// このマクロ定義がされていなかったら
#define _ITEM_FRAME_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object2D.h"
#include "player.h"

//--------------------------------------------
// クラス定義(アイテムの枠)
//--------------------------------------------
class CItemFrame : public CObject2D
{
public:				// 誰でもアクセスできる

	CItemFrame();			// コンストラクタ
	~CItemFrame();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type);				// 情報の設定処理

	// 静的メンバ関数
	static CItemFrame* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type);	// 生成処理

private:			// 自分だけアクセスできる

};

#endif