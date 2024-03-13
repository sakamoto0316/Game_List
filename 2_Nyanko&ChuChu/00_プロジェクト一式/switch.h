//===================================
//
// スイッチヘッダー[switch.h]
// Author 小原立暉
//
//===================================
#ifndef _SWITCH_H_
#define _SWITCH_H_

//***********************************
// インクルードファイル
//***********************************
#include "object.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CModel;		// モデル
class CBillboard;	// ビルボード

//-----------------------------------
// クラス定義(スイッチ)
//-----------------------------------
class CSwitch : public CObject
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_BASE = 0,		// 土台
		TYPE_LEVER,			// レバー
		TYPE_MAX			// この列挙型の総数
	};

	CSwitch();				// コンストラクタ
	~CSwitch();				// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理
	virtual void Draw(const float fAlpha);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);				// 情報の設定処理
	void ChangeBoot(void);	// 起動状況の入れ替え処理

	// セット・ゲット関数
	void SetGimmickUI(bool Set, int Player_Idx);	// ギミックUIの設定処理
	CModel* GetModel(const TYPE type);		// モデルの取得処理
	void SetBoot(const bool bBoot);			// 起動状況の設定処理
	bool GetBoot(void) const;				// 起動状況の取得処理

	// 静的メンバ関数
	static CSwitch* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void StateManager(void);						// 状態マネージャー

	// メンバ変数
	CModel* m_apModel[TYPE_MAX];		// モデルの情報
	CBillboard *m_pGimmickUI;			// ギミックUIの情報
	bool m_aUIFalse[MAX_PLAY];			// 全部[False]の時にUIを削除する
	D3DXVECTOR3 m_posCopy;				// 位置のコピー
	float m_fRotDest;					// 目的の向き
	float m_fPosYDest;					// 目的の位置(Y軸)
	bool m_bBoot;						// 起動状況
};

#endif