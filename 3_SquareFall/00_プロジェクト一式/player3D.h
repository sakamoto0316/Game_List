//============================================
//
//	プレイヤーの処理 [player3D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _PLAYER3D_H_
#define _PLAYER3D_H_

#include "main.h"
#include "objectX.h"

#define NUM_PLAYER 0

//前方宣言
class CMap2D;
class CGuide;
class CItem;
class CEnemy;
class CLifeGauge;
class CObject2D;
class CNumber;
class CCombo;
class CBulletTypeUI;
class CObjectBillboard;

//オブジェクトプレイヤークラス
class CPlayer3D : public CObjectX
{
public:
	typedef enum
	{
		STATE_NORMAL = 0,
		STATE_DAMAGE,
		STATE_WAIT,
	}STATE_TYPE;

	typedef enum
	{
		SHOT_NORMAL = 0,
		SHOT_3WAY,
		SHOT_TRIPLE_3WAY,
		SHOT_8WAY,
		SHOT_BURST,
		SHOT_LESER,
		SHOT_MACHINEGUN,
		SHOT_EXPLOSION,
		SHOT_SPREAD_EXPLOSION,
		SHOT_CONTINUE_EXPLOSION,
	}SHOT_TYPE;

	CPlayer3D(int nPriority = 3);
	~CPlayer3D();

	static CPlayer3D *Create();
	HRESULT Init(void);
	void UICreate(void);
	void Uninit(void);
	void Update(void);
	void TitleUpdate(void);
	void GameUpdate(void);
	void Draw(void);

	void PlayPad(void);
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetFallMax(float Max) { m_FallMax = Max; }
	int GetIdxXModel(void) { return m_nIdxXModel; }
	int GetIdxTexture(int nCnt) { return m_nIdxTexture[nCnt]; }
	void SetNULL(void);
	void SetBullet(SHOT_TYPE type);												//進化時の弾の種類
	void AddUlt(void);															//必殺ゲージの加算
	bool GetUseUlt(void) { return m_bUseUlt; }									//必殺技を使っているかどうか
	void AddCombo(void) { m_nCombo++; }											//コンボ数の加算
	int GetCombo(void) { return m_nCombo; }										//コンボ数の取得
	void SetComboScore(int Score) { m_MaxConboScore = Score; }					//コンボスコアの設定
	int GetComboScore(void) { return m_MaxConboScore; }							//コンボスコアの取得
	void SetFallScore(int Score) { m_MaxFallScore = Score; }					//最高速度落下スコアの設定
	int GetFallScore(void) { return m_MaxFallScore; }							//最高速度落下スコアの取得
	void SetComboDepth(int Score) { m_DepthScore = (float)Score; }				//深さスコアの設定
	int GetComboDepth(void) { return (int)m_DepthScore; }						//深さスコアの取得
	void SetBulletTypeUI(const char *Texture, SHOT_TYPE Type);					//弾の種類のUIのセット
	CCombo *GetDebugCombo(void) { return m_pCombo; }							//デバッグ用
	void LifeBlinking(void);

private:
	void SizeVtx(void);															//モデルの大きさ指定
	void StateManager(void);													//状態管理
	void Move(void);															//移動処理
	void LandingEffect(D3DXVECTOR3 pos);										//着地時リアクション
	void UltimateTrigger(D3DXVECTOR3 pos);										//必殺技発動処理
	void Ultimate(D3DXVECTOR3 pos);												//必殺技処理
	void Shoot(D3DXVECTOR3 pos, D3DXVECTOR3 rot);								//弾発射処理
	void BurstShoot(D3DXVECTOR3 pos);											//バースト弾発射処理
	void Machinegun(D3DXVECTOR3 pos);											//マシンガン発射処理
	void SetWarning(D3DXVECTOR3 pos);													//ダメージヒット処理
	void HitDamage(int Damage);													//ダメージヒット処理
	void LevelUp(void);															//レベルアップ処理
	void Evolution(void);														//進化の処理
	bool CollisionBlock(D3DXVECTOR3 *pos, bool bX);								//ブロックとの当たり判定
	bool CollisionUI(D3DXVECTOR3 *pos, bool bX);								//ブロックとの当たり判定
	bool CollisionObjectSquareSpace(void);										//オブジェクトとの当たり判定(矩形の範囲)
	bool CollisionObjectSquareLine(D3DXVECTOR3 pos);							//オブジェクトとの当たり判定(矩形の4面)
	bool CollisionEnemyCircle(D3DXVECTOR3 pos, float nRadiusOut);				//円の当たり判定
	bool CollisionPointCircle(D3DXVECTOR3 pos, float nRadiusOut);				//経験値の当たり判定
	bool CollisionCircle(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut);	//円の当たり判定
	bool CollisionCircleOut(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn);	//円の当たり判定(外周のみ)
	void ResetBullet(void);														//残弾数のリセット
	void SetLevelNumber10(void);												//レベルの数値の10の位を生成する

	static LPD3DXMESH m_pMesh;				//メッシュ(頂点情報)へのポインタ
	static LPD3DXBUFFER m_pBuffMat;			//マテリアルへのポインタ
	static DWORD m_dwNumMat;				//マテリアルの数
	static int m_nIdxXModel;				//Xモデルの番号
	static int m_nIdxTexture[64];			//Xモデルテクスチャの番号
	D3DXVECTOR3 m_vtxMin;					//モデルの最小
	D3DXVECTOR3 m_vtxMax;					//モデルの最大
	D3DXVECTOR3 m_posOld;					//過去の位置	
	D3DXVECTOR3 m_move;						//移動量	
	bool m_bFallMax; 						//プレイヤーが最大速度で落下しているかどうか
	float m_FallMax; 						//プレイヤーが落下する最大速度
	int m_FallCount; 						//最大速度で落下している時にだすパーティクルのためのカウント
	float m_stop;							//減衰係数	
	D3DXVECTOR3 m_GuideRot;					//ガイドの向き	
	bool m_bJump;							//ジャンプしたかどうかの判断
	int m_nLife;							//ライフ
	int m_Ultimate;							//必殺
	float m_UltimateSpin;					//現在の必殺技のエフェクト回転
	float m_UltimateLine;					//現在の必殺技の効果範囲
	D3DXVECTOR3 m_UltimatePos;				//必殺技の発動位置
	bool m_bUseUlt;							//必殺の発動中かどうか
	int m_nBulletMax;						//弾の総弾数
	int m_nBullet;							//現在の弾の数
	int m_nBurstCount;						//バースト弾のカウント
	int m_nBurstCoolTime;					//バースト弾の次の弾が出るまでのクールタイム
	int m_BulletCoolTime;					//次の弾が撃てるようになるまでのクールタイム
	bool m_bMachingun;						//マシンガンの発射状態がオンかオフか
	float m_fMachingunJump;					//マシンガンの反動によるジャンプの値
	int m_nLevelUp;							//レベルアップまでに必要な経験値
	int m_nLevelPoint;						//現在の経験値
	int m_nLevel;							//現在のレベル
	int m_EvolutionCount;					//進化の回数
	STATE_TYPE m_State;						//状態
	SHOT_TYPE m_BulletType;					//銃の種類
	SHOT_TYPE m_MyBulletType[3];			//現在使える銃の種類
	int m_SelectBulletType;					//現在使っている銃の種類
	int m_SelectBulletTypeMax;				//現在使っている銃の種類の最大数
	int m_StateCount;						//状態の長さを管理するカウント
	bool m_bLevelNumber10;					//10の位を表示しているかどうか
	int m_nCombo;							//地面に着地せずに敵を倒した数
	int UltOKParticleCount;					//必殺技が使える状態のときにだすパーティクルのカウント
	int m_LifeRedCount;						//ライフが低い時の点滅用カウント
	int m_LifeNormalCount;					//ライフが低い時の点滅用カウント
	bool m_bLifeRed;						//ライフが低い時の点滅用bool
	int m_MaxConboScore;					//コンボの最大数によって獲得できるスコア
	int m_MaxFallScore;						//最高速度で落下している時間によって獲得できるスコア
	float m_DepthScore;						//ゲーム終了時にいる深さによって獲得できるスコア
	bool m_bWarning;						//ボスの距離による警告

	static CGuide *m_pGuide;				//ガイド用エフェクト
	static CObject2D *m_pUIPlayer;			//プレイヤーのUI
	static CObject2D *m_pUIPlayerBG;		//プレイヤーのUI
	static CObject2D *m_pUIPlayerFG;		//プレイヤーのUIの前面ポリゴン
	static CObject2D *m_pUIBullet;			//バレットのUI
	static CObject2D *m_pUIBulletBG;		//バレットのUI
	static CObject2D *m_pUIBulletFG;		//バレットのUIの前面ポリゴン
	static CObject2D *m_pLifeUI;			//体力UI
	static CLifeGauge *m_pLifeGauge;		//体力ゲージ
	static CObject2D *m_pLifeFG;			//体力ゲージの前面ポリゴン
	static CObject2D *m_pUltimateUI;		//必殺UI
	static CLifeGauge *m_pUltimateGauge;	//必殺ゲージ
	static CLifeGauge *m_pUltimateFG;		//必殺ゲージの前面ポリゴン
	static CObject2D *m_pBulletUI;			//弾数UI
	static CLifeGauge *m_pBulletGauge;		//弾数ゲージ
	static CLifeGauge *m_pBulletFG;			//弾数ゲージの前面ポリゴン
	static CNumber* m_pBulletNumber[3];		//残弾数UI
	static CLifeGauge *m_LevelGauge;		//レベルゲージ
	static CLifeGauge *m_LevelFG;			//レベルゲージの前面ポリゴン
	static CNumber *m_LevelNumber1;			//レベルを数字で表示するUI
	static CNumber *m_LevelNumber10;		//レベルを数字で表示するUI
	static CObject2D *m_pLvPolygon;			//レベルのLv.の部分のポリゴン
	static CCombo *m_pCombo;				//コンボ数表記
	static CBulletTypeUI *m_pBulletTypeUI[3];//現在使える銃のUI
	static CBulletTypeUI *m_pSelectBulletTypeUI;//コンボ用UI
	static CObject2D *m_pWarning;			//警告マーク
	static CObject2D* m_pWarningTex[2];		//警告ポリゴン
	static CObjectBillboard* m_NotBullet;	//弾が無くなった時の表示
};
#endif