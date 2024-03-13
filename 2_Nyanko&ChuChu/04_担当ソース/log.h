//===================================
//
// ログヘッダー[log.h]
// Author 坂本翔唯
//
//===================================
#ifndef _LOG_H_
#define _LOG_H_

//***********************************
// インクルードファイル
//***********************************
class CObject2D;
class CPlayer;

//-----------------------------------
// クラス定義(サンプル)
//-----------------------------------
class CLog : public CObject/*親クラス*/
{
public:			// 誰でもアクセスできる

	CLog();				// コンストラクタ
	~CLog();			// デストラクタ

	enum STATE
	{
		STATE_IN = 0,
		STATE_DOWN,
		STATE_OUT,
		STATE_MAX,
	};

	enum TYPE
	{
		TYPE_DEATH = 0,
		TYPE_STUN,
		TYPE_REVIVAL,
		TYPE_MAX,
	};

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(int DrawIdx, int LogIdx, int nCreateNumber, CLog::TYPE Type);		// 情報の設定処理
	void SetLogIdx(int nIdx) { m_nLogIdx = nIdx; }

	void SetMain(CPlayer *pMain) { m_pMain = pMain; }		// 自分の事を使用しているオブジェクトのポインタを設定する
	void DelCreateNumber(void) { m_CreateNumber--; }

	// 静的メンバ関数
	static CLog* Create(int DrawIdx, int LogIdx, int nCreateNumber, CLog::TYPE Type);		// 生成処理

private:		// 自分だけアクセスできる
	void StateManager(void);

	D3DXVECTOR3 LogPos;			// ログ全体の位置
	int m_nPlayerNumber;		// どのプレイヤーのログか
	int m_CreateNumber;			// 何番目の生成のログか
	STATE m_State;				// 状態
	int m_nLife;				// 寿命
	int m_nLogIdx;				// ログの使用番号
	float m_fLogStopPosY;			// ログが停止する位置
	TYPE m_Type;				// ログの種類
	CObject2D *m_pLogBG;		// ログの背景パーツ
	CObject2D *m_pLogPlayerID;	// ログのプレイヤーIDパーツ
	CObject2D *m_pLogMessage;	// ログの内容パーツ
	CPlayer *m_pMain;			// 自分の事を使用しているオブジェクトのポインタ
};
#endif