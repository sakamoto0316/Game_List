//===================================
//
// ネズミ捕りの鉄部分ヘッダー[mousetrap_iron.h]
// Author 小原立暉
//
//===================================
#ifndef _MOUSETRAP_IRON_H_
#define _MOUSETRAP_IRON_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(ネズミ捕りの鉄部分)
//-----------------------------------
class CTrapIron : public CModel
{
public:			// 誰でもアクセスできる

	CTrapIron();			// コンストラクタ
	~CTrapIron();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理
	bool Move(void);		// 移動処理

	// 静的メンバ関数
	static CTrapIron* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);	// 生成処理

private:		// 自分だけアクセスできる

};

#endif