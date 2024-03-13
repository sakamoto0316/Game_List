//===================================
//
// 説明ヘッダー[explanation.h]
// Author 坂本翔唯
//
//===================================
#ifndef _EXPLANATION_H_
#define _EXPLANATION_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "tutorial.h"

#define IMAGE_MAX (5)

class CObject2D;
//-----------------------------------
// クラス定義(返事入力のリアクション)
//-----------------------------------
class CExplanation : public CObject/*親クラス*/
{
public:			// 誰でもアクセスできる

	CExplanation();			// コンストラクタ
	~CExplanation();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(CTutorial::TUTORIAL Tutorial);		// 情報の設定処理

	// 静的メンバ関数
	static CExplanation* Create(CTutorial::TUTORIAL Tutorial);		// 生成処理

private:		// 自分だけアクセスできる
	CObject2D *m_pBG;
	CObject2D *m_pCatKing;
	CObject2D *m_pCatBG;
	CObject2D *m_pCatText;
	CObject2D *m_pRatKing;
	CObject2D *m_pRatBG;
	CObject2D *m_pRatText;
	CObject2D *m_apImage[IMAGE_MAX];
	D3DXCOLOR m_ColorKing;
	D3DXCOLOR m_ColorText;

	float m_fStartAlpha;
};

#endif