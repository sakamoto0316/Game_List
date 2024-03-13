//===================================
//
// 扇風機のファンヘッダー[fan_blade.h]
// Author 小原立暉
//
//===================================
#ifndef _FAN_BLADE_H_
#define _FAN_BLADE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス定義(扇風機のファン)
//-----------------------------------
class CFanBlade : public CModel
{
public:			// 誰でもアクセスできる

	CFanBlade();			// コンストラクタ
	~CFanBlade();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理
	void Draw(const float fAlpha);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);				// 情報の設定処理

	// セット・ゲット関係
	void SetRotMoveDest(const float fRotMove);			// 目的の向きの移動量の設定処理

	// 静的メンバ関数
	static CFanBlade* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	float m_fRotMove;		// 向きの移動量
	float m_fRotMoveDest;	// 目的の向きの移動量
};

#endif