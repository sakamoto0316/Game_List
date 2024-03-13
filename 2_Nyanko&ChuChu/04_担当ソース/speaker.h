//===================================
//
// スピーカーヘッダー[Himo.h]
// Author 坂本翔唯
//
//===================================
#ifndef _SPEAKER_H_
#define _SPEAKER_H_

//***********************************
// インクルードファイル
//***********************************
#include "obstacle.h"

//-----------------------------------
// マクロ定義
//-----------------------------------
#define MAX_NOTE	 (64)		//音符が画面の中に存在できる最大数

//-----------------------------------
// 前方宣言
//-----------------------------------
class CNote;		// 音符

//-----------------------------------
// クラス定義(スピーカー)
//-----------------------------------
class CSpeaker : public CObstacle
{
public:			// 誰でもアクセスできる

	// 列挙型定義(状態)
	enum STATE
	{
		STATE_STOP = 0,		// 停止状態
		STATE_SHRINK,		// 縮み状態
		STATE_EXTEND,		// 伸び状態
		STATE_MAX			// この列挙型の総数
	};

	CSpeaker();				// コンストラクタ
	~CSpeaker();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// 情報の設定処理

	bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// 当たり判定処理
	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;			// ヒット処理
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;				// 円のヒット処理
	void Action(void) override;
	void MySetIdx(int Idx){ m_bmySet[Idx] = false; }
	static void NULLNote(int Idx) { m_apNote[Idx] = NULL; }

	// セット・ゲット関数
	//void SetBgm(bool bBgm);		// BGM状況設定
	//bool GetBgm(void);			// BGM状況取得

private:		// 自分だけアクセスできる

	// メンバ関数
	void State(void);		// 状態による処理
	void SetNote(void);

	// メンバ変数
	STATE m_state;				// 状態
	bool m_bmySet[MAX_NOTE];
	bool m_bAction;
	int m_nNoteCount;

	// 静的メンバ変数
	static CNote *m_apNote[MAX_NOTE];
	static int m_nNumBgmAll;		// BGM鳴らした総数
};

#endif