//===================================
//
// 返事入力のリアクションヘッダー[sample.h]
// Author 坂本翔唯
//
//===================================
#ifndef _ANSWER_H_
#define _ANSWER_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "tutorial.h"

class CObject2D;

//-----------------------------------
// クラス定義(返事入力のリアクション)
//-----------------------------------
class CAnswer : public CObject/*親クラス*/
{
public:			// 誰でもアクセスできる

	CAnswer();			// コンストラクタ
	~CAnswer();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void/*引数*/);		// 情報の設定処理

	void SetAnswer(bool Set, int Idx) { m_abPressAnswer[Idx] = Set; }
	bool GetAnswer(int Idx) { return m_abPressAnswer[Idx]; }

	// 静的メンバ関数
	static CAnswer* Create(void/*引数*/);		// 生成処理

private:		// 自分だけアクセスできる
	CObject2D *m_apAnswer[4];
	bool m_abPressAnswer[4];
	CObject2D *m_apPlayerID[4];

	D3DXCOLOR m_Color;
};

#endif