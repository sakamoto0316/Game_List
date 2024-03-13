//===================================
//
// 生き返りの円の範囲ヘッダー[resurrection_fan.h]
// Author 佐藤根詩音
//
//===================================
#ifndef _RESURRECTION_FAN_H_
#define _RESURRECTION_FAN_H_

//***********************************
// インクルードファイル
//***********************************
#include "object3Dfan.h"

//-------------------------------------------
// マクロ定義
//-------------------------------------------
#define NUM_REZ_ANGLE		(120)		// 角度の数

//-----------------------------------
// クラス定義(サンプル)
//-----------------------------------
class CRessrectionFan : public CObject3DFan
{
public:			// 誰でもアクセスできる

	CRessrectionFan();			// コンストラクタ
	~CRessrectionFan();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXCOLOR& col);		// 情報の設定処理

	// セット・ゲット関数
	void SetResurrectionFan(int nFan);			// 角度の設定
	int GetResurrectionFan(void);				// 角度の取得

	// 静的メンバ関数
	static CRessrectionFan* Create(const D3DXVECTOR3& pos, const D3DXCOLOR& col);		// 生成処理

private:		// 自分だけアクセスできる
	int m_nRezTime;			// 回復時間
	bool m_bRez;			// 回復してるか

};

#endif