//===================================
//
// プレイヤーヘッダー[player.h]
// Author 小原立暉
//
//===================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

//********************************************
// インクルードファイル
//********************************************
#include "character.h"
#include "item.h"
#include "log.h"

#define LOG_MAX (16)

//--------------------------------------------
// 前方宣言
//--------------------------------------------
class CMotion;				// モーション
class CPlayerID;			// プレイヤーのID
class CStun;				// 気絶
class CRatGhost;			// 幽霊ネズミ
class CRessrectionFan;		// 円の範囲
class CRecoveringUI;		// 回復中のUI
class CSpeechMessage;		// 伝達メッセージ
class CDeathArrow;			// 死亡矢印

//--------------------------------------------
// クラス(プレイヤークラス)
//--------------------------------------------
class CPlayer : public CCharacter
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_CAT = 0,		// ネコ
		TYPE_RAT,			// ネズミ
		TYPE_MAX			// この列挙型の総数
	};

	// 列挙型定義(気絶用状態)
	enum STUNSTATE
	{
		STUNSTATE_NONE = 0,	// 無状態
		STUNSTATE_SMASH,	// 吹き飛び状態
		STUNSTATE_STUN,		// 気絶状態
		STUNSTATE_WAIT,		// 無敵状態
		STUNSTATE_MAX,		// この列挙型の総数
	};

	// 列挙型定義(通常用状態)
	enum STATE
	{
		STATE_NONE = 0,		// 無状態
		STATE_INVINCIBLE,	// 無敵状態
		STATE_DEATH,		// 死状態
		STATE_MAX			// この列挙型の総数
	};

	CPlayer();				// コンストラクタ
	CPlayer(CObject::TYPE type, PRIORITY priority = PRIORITY_PLAYER);				// オーバーロードコンストラクタ
	virtual ~CPlayer();		// デストラクタ
	void Box(void);			// コンストラクタの箱

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	virtual void Hit(void) = 0;						// ヒット処理
	void Smash(const float fAngle);					// 吹き飛び状態
	bool Stun(int StunTime);						// 気絶状態
	virtual void MotionManager(void) = 0;			// モーションマネージャー
	virtual void GetItem(const CItem::TYPE type);	// アイテムの取得処理
	virtual int GetItemCount(void) const;			// アイテムの取得処理
	virtual void SetEnableJump(const bool bJump);	// ジャンプの設定処理

	virtual void SetData(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// 情報の設定処理
	void CameraUpdate(void);			// カメラ情報の更新

	// セット・ゲット関係
	void SetMotion(CMotion* pMotion);			// モーションの設定処理
	CMotion* GetMotion(void) const;				// モーションの取得処理

	CPlayerID* GetPlayerID(void) const;			// プレイヤーIDの情報の取得処理

	void SetStun(const D3DXVECTOR3& pos);		// 気絶演出の設定処理
	CStun* GetStun(void) const;					// 気絶演出の取得処理
	void DeleteStun(void);						// 気絶演出の消去処理

	void SetRatGhost(const D3DXVECTOR3& pos);	// 幽霊ネズミの設定処理
	CRatGhost* GetRatGhost(void);				// 幽霊ネズミの取得処理
	void DeleteRatGhost(void);					// 幽霊ネズミの消去処理

	void SetRessrectionFan(const D3DXVECTOR3& pos, const D3DXCOLOR& col);	// 円の範囲の設定処理
	CRessrectionFan* GetRessrectionFan(void);	// 円の範囲の取得処理
	void DeleteRessrectionFan(void);			// 円の範囲の消去処理

	void SetRecoveringUI(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);	// 回復中UIの設定処理
	CRecoveringUI* GetRecoveringUI(void);		// 回復中UIの取得処理
	void DeleteRecoveringUI(void);				// 回復中UIの消去処理

	void SetSpeechMessage(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const int nLife, const int type);				// 伝達メッセージの設定処理
	CSpeechMessage* GetSpeechMessage(void);		// 伝達メッセージの取得処理
	void DeleteSpeechMessage(void);				// 伝達メッセージの消去処理

	void SetDeathArrow(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld, const D3DXVECTOR3& rot, const int nIdx, const int PlayerIdx);		// 死亡矢印の設定処理
	CDeathArrow* GetDeathArrow(const int nIdx);			// 死亡矢印の取得処理
	void DeleteDeathArrow(const int nIdx);				// 死亡矢印の消去処理

	//void SetMove(const D3DXVECTOR3& move);		// 移動量の設定処理
	//D3DXVECTOR3 GetMove(void) const;			// 移動量の取得処理

	void SetSizeColl(const D3DXVECTOR3& size);	// 当たり判定サイズの設定処理
	D3DXVECTOR3 GetSizeColl(void) const;		// 当たり判定サイズの取得処理

	void SetType(const TYPE type);				// 種類の設定処理
	TYPE GetType(void) const;					// 種類の取得処理

	int GetPlayerIdx(void) const;				// プレイヤーのIDの取得処理

	void SetSpeed(const float fSpeed);			// 速度の設定処理
	float GetSpeed(void) const;					// 速度の取得処理

	void SetSpeedCopy(const float fSpeed);		// 速度のコピーの設定処理
	float GetSpeedCopy(void) const;				// 速度のコピーの取得処理

	void SetStunHeight(const float fHeight);	// 気絶の出る高さの設定処理

	void SetEnableAttack(const bool bAttack);	// 攻撃判定の設定処理
	bool IsAttack(void) const;					// 攻撃判定の取得処理

	void SetEnableMove(const bool bMove);		// 移動状況の設定処理
	bool IsMove(void) const;					// 移動状況の取得処理

	void SetTutorial(const bool bTutorial) { m_bTutorial = bTutorial; }	// 移動状況の設定処理
	bool GetTutorial(void) { return m_bTutorial; }						// 移動状況の取得処理

	void SetResurrectionTime(const int nRezTime);	// 死んだネズミの復活時間の合計設定
	void AddResurrectionTime(const int nRezTime);	// 死んだネズミの復活時間の合計追加
	int GetResurrectionTime(void);					// 死んだネズミの復活時間の合計取得

	void SetStunState(STUNSTATE StunState) { m_StunState = StunState; }	// 気絶状態の設定処理
	STUNSTATE GetStunState(void) { return m_StunState; }				// 気絶状態の取得処理

	void SetDispRecoveringUI(const bool bRez);	// 回復中UIの表示判定
	bool IsDispRecoveringUI(void);				// 回復中UIの表示取得

	void SetState(STATE State);							// 状態の設定処理
	STATE GetState(void) { return m_State; }			// 状態の取得処理

	void SetLogPlayer(int LogPlayer) { m_nLogPlayer = LogPlayer; }		// 状態の設定処理
	int GetLogPlayer(void) { return m_nLogPlayer; }						// 状態の取得処理

	void SetSE(bool bSe);			// SEの再生設定
	bool GetSE(void);				// SEの再生取得

	//チュートリアル用ゲット関数-----------------------------------------
	void SetBMove(bool Set) { m_bMove = Set; }			// 移動状態の設定処理
	bool GetBMove(void) { return m_bMove; }				// 移動状態の取得処理
	virtual bool GetAttack_Jump(void) { return false; }	// アタックジャンプ状態の取得処理
	void SetRatKill(bool Set) { m_bKill = Set; }		// キルの設定処理
	bool GetRatKill(void) { return m_bKill; }			// キルの取得処理
	void SetRatStun(bool Set) { m_bStun = Set; }		// スタンの設定処理
	bool GetRatStun(void) { return m_bStun; }			// スタンの取得処理
	void SetRatRescue(bool Set) { m_bRescue = Set; }	// 救助の設定処理
	bool GetRatRescue(void) { return m_bRescue; }		// 救助の取得処理
	void SetUseAction(bool Set) { m_bAction = Set; }	// 起動の設定処理
	bool GetUseAction(void) { return m_bAction; }		// 起動の取得処理
	virtual bool GetItem_MultiAction(void) { return false; }	// アイテム使用と連携起動の取得処理
	//-------------------------------------------------------------------

	void SetStateCount(const int nCount) { m_StateCount = nCount; };		// 状態カウントの設定処理

	void SetLog(int PlayerIdx, CLog::TYPE Type);				// ログの生成と生成番号の加算
	void DelLogNumber(int nLogIdex);			// ログの生成番号の減算

	// 静的メンバ関数
	static CPlayer* Create(const D3DXVECTOR3& pos, const int nID, const TYPE type);		// 生成処理

protected:		// 自分と派生クラスだけがアクセスできる

	// メンバ関数
	void MoveControl(void);		// 移動操作処理
	void Move(void);			// 移動処理
	void RotNormalize(void);	// 向きの補正処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void StunStateManager(void);		// 気絶状態の管理
	void StateManager(void);			// 状態の管理

	// メンバ変数
	CMotion* m_pMotion;			// モーションの情報
	CPlayerID* m_pPlayerID;		// プレイヤーのID
	CStun* m_pStun;				// 気絶の情報
	CRatGhost* m_pRatGhost;		// 幽霊ネズミの情報
	CRessrectionFan* m_pRessrectionFan;		// 円の範囲の情報
	CRecoveringUI* m_pRecoveringUI;			// 回復中のUIの情報
	CSpeechMessage* m_pSpeechMessage;		// 伝達メッセージの情報
	CDeathArrow* m_pDeathArrow[MAX_PLAY];	// 死亡矢印の情報
	D3DXVECTOR3 m_sizeColl;		// 当たり判定のサイズ
	D3DXCOLOR m_col;			// 色
	TYPE m_type;				// 種類
	int m_nPlayerIdx;			// プレイヤーのインデックス
	float m_fSpeed;				// 速度
	float m_fSpeedCopy;			// 速度のコピー
	float m_fRotDest;			// 目標
	float m_fStunHeight;		// 気絶が出る高さ
	bool m_bAttack;				// 攻撃したか
	bool m_bMove;				// 移動しているか
	bool m_bDeath;				// 死亡しているか
	bool m_bDisp;				// 表示するか
	bool m_bDispSmash;			// 吹き飛び用の表示するか
	STUNSTATE m_StunState;		// 気絶の状態管理
	int m_StunStateCount;		// 状態管理用カウント
	STATE m_State;				// 状態管理
	int m_StateCount;			// 状態管理用カウント
	D3DXVECTOR3 m_CameraRot;	// カメラの向き
	int m_nResurrectionTime;	// 復活するまでの時間
	CLog *m_apLog[LOG_MAX];		// ログ
	int m_nLogPlayer;			// ログに表示するプレイヤーの番号
	int m_nLogNumber;			// ログの生成番号
	bool m_bTutorial;			// チュートリアル状態かどうか
	bool m_bStun;				// スタンを行ったかどうか
	bool m_bKill;				// キルを行ったかどうか
	bool m_bRescue;				// 救助を行ったかどうか
	bool m_bAction;				// 起動を行ったかどうか
	bool m_bSe;					// SE再生したかどうか
	bool m_bCatSe;				// ネコ用SE再生状況
	bool m_bRatSe;				// ネズミ用SE再生状況
};

#endif