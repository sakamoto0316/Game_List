//===================================
//
// エントリーチームヘッダー[entry_team.h]
// Author 小原立暉
//
//===================================
#ifndef _ENTRY_TEAM_H_
#define _ENTRY_TEAM_H_

//***********************************
// インクルードファイル
//***********************************
#include "object2D.h"
#include "player.h"

//-----------------------------------
// クラス定義(CEntryTeam)
//-----------------------------------
class CEntryTeam : public CObject2D
{
public:			// 誰でもアクセスできる

	CEntryTeam();			// コンストラクタ
	~CEntryTeam();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const CPlayer::TYPE type);					// 情報の設定処理

	// セット・ゲット関係
	void SetType(const CPlayer::TYPE type);		// 種類の設定処理

	// 静的メンバ関数
	static CEntryTeam* Create(const D3DXVECTOR3& pos, const CPlayer::TYPE type);	// 生成処理

private:		// 自分だけアクセスできる

	// メンバ変数
	CPlayer::TYPE m_type;		// チームの種類
	float m_fMove;				//UIの変形量
	int m_nTimeCnt;				//UI変形のタイマー
};

#endif