//===================================
//
// コンセントヘッダー[consent.h]
// Author 坂本翔唯
//
//===================================
#ifndef _CONSENT_H_
#define _CONSENT_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

class CCup;

//-----------------------------------
// クラス定義(音符)
//-----------------------------------
class CConsent : public CModel
{
public:			// 誰でもアクセスできる

	CConsent();		// コンストラクタ
	~CConsent();		// デストラクタ

					// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理
	void Draw(const float fAlpha);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理
	void SetLife(int Life) { m_nLife = Life; }				// 寿命の設定処理
	void SetIndex(int Idx) { m_nIndex = Idx; }				// 使用番号の設定
	void SetMove(D3DXVECTOR3 move) { m_move = move; }		// 移動量の設定
	void SetMain(CCup *main) { m_pMain = main; }		// 移動量の設定

	// 静的メンバ関数
	static CConsent* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	float m_StartPosY;		// 初期位置の高さ
	D3DXVECTOR3 m_move;		// 移動量
	int m_nLife;			// 寿命
	int m_nIndex;			// 使用番号
	CCup *m_pMain;			// 自分自身を使用しているモデル
};

#endif