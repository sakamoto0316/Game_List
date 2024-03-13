//===================================
//
// カウントダウンヘッダー[countdown.h]
// Author 小原立暉
//
//===================================
#ifndef _COUNTDOWN_H_
#define _COUNTDOWN_H_

//***********************************
// インクルードファイル
//***********************************
#include "number.h"

//-----------------------------------
// クラス定義(カウントダウン)
//-----------------------------------
class CCountdown : public CNumber
{
public:			// 誰でもアクセスできる

	CCountdown();			// コンストラクタ
	~CCountdown();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nCount, bool bEnd);					// 情報の設定処理

	// 静的メンバ関数
	static CCountdown* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nCount, bool bEnd);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void Calculate(void);		// 計算処理
	void Cycle(void);			// 回転処理
	void Scaling(void);			// 拡大処理

	// メンバ変数
	D3DXVECTOR3 m_sizeDest;		// 目的のサイズ
	D3DXVECTOR3 m_sizeInit;		// 初期サイズ
	int m_nFrame;				// 経過フレーム数
	int m_nSecond;				// 秒数
	int m_nProgressCount;		// 経過させるカウント
	bool m_bEnd;				// 終了状況
};

#endif