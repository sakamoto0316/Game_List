//===================================
//
// 死亡矢印ヘッダー[death_arrow.h]
// Author 佐藤根詩音
//
//===================================
#ifndef _DEATH_ARROW_H_
#define _DEATH_ARROW_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

//-----------------------------------
// クラス(死亡矢印クラス)
//-----------------------------------
class CDeathArrow : public CModel
{
public:			// 誰でもアクセスできる

	CDeathArrow();			// コンストラクタ
	~CDeathArrow();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx);		// 情報の設定処理

	//セット・ゲット関係

	// 静的メンバ関数
	static CDeathArrow* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx);		// 生成処理

private:		// 自分だけアクセスできる
	D3DXVECTOR3 m_pos;		// 位置
	D3DXVECTOR3 m_rot;		// 向き
	int m_nPlayerIdx;		// プレイヤー番号

};

#endif