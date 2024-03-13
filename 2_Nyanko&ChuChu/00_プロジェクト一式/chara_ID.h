//============================================
//
// キャラクターのIDヘッダー[chara_ID.h]
// Author：小原立暉
//
//============================================
#ifndef _CHARA_ID_H_					// このマクロ定義がされていなかったら
#define _CHARA_ID_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object2D.h"

//--------------------------------------------
// クラス定義(キャラクターの画像)
//--------------------------------------------
class CCharaID : public CObject2D
{
public:				// 誰でもアクセスできる

	CCharaID();						// コンストラクタ
	~CCharaID();						// デストラクタ

	// メンバ関数
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	void SetData(const D3DXVECTOR3& pos, const int nID);			// 情報の設定処理

	// 静的メンバ関数
	static CCharaID* Create(const D3DXVECTOR3& pos, const int nID);	// 生成処理

private:			// 自分だけアクセスできる

};

#endif