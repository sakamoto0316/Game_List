//============================================
//
// キャラクターの画像ヘッダー[chara_image.h]
// Author：小原立暉
//
//============================================
#ifndef _CHARA_ICON_H_					// このマクロ定義がされていなかったら
#define _CHARA_ICON_H_					// 2重インクルード防止のマクロを定義する

//********************************************
// インクルードファイル
//********************************************
#include "object2D.h"
#include "player.h"

//--------------------------------------------
// クラス定義(キャラクターの画像)
//--------------------------------------------
class CCharaIcon : public CObject2D
{
public:				// 誰でもアクセスできる

	CCharaIcon();						// コンストラクタ
	~CCharaIcon();						// デストラクタ

	// メンバ関数
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(void);					// 描画処理

	void SetData(const D3DXVECTOR3& pos, const CPlayer::TYPE type);					// 情報の設定処理

	// 静的メンバ関数
	static CCharaIcon* Create(const D3DXVECTOR3& pos, const CPlayer::TYPE type);	// 生成処理

private:			// 自分だけアクセスできる

};

#endif