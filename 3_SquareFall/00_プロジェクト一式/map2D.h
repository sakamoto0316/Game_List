//============================================
//
//	マップの自動生成処理 [map2D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _MAP2D_H_
#define _MAP2D_H_

#include "main.h"
#include "object.h"

#define SET_BLOCK_WIGHT (20)
#define SET_BLOCK_HEIGHT (25)
#define DATA_NAME ("data\\TXT\\Stage02")	//スタートメッセージがあるかどうかの確認

//前方宣言
class CNormal_Block;
class CBreak_Block3D;
class CEnemy3D;
class CItem;

//マップクラス
class CMap2D
{
public:
	CMap2D();
	~CMap2D();

	static CMap2D *Create();
	void Uninit(void);
	void Update(void);

	void SetDepth(float Depth) { m_DepthOld = m_Depth; m_Depth = Depth; }
	float GetDepth(void) { return m_Depth; }
	void SetDepthOld(float DepthOld) { m_DepthOld = DepthOld; }
	float GetDepthOld(void) { return m_DepthOld; }
	void SetBreakPos(D3DXVECTOR3 BreakPos) { m_BreakPos = BreakPos; }
	void SetDirectionPos(D3DXVECTOR3 DirectionPos) { m_DirectionPos = DirectionPos; }
	D3DXVECTOR3 GetBreakPos(void) { return m_BreakPos; }
	void AddCreateEnemy(void) { CreateEnemy++; }
	void DeleteEventEnemy(void) { m_EventEnemy--; }
	int GetEventEnemy(void) { return m_EventEnemy; }
	int GetMapLevel(void) { return m_MapLevel; }
	void CleanBlockUse(void);

protected:

private:
	void CreateMap(void);
	void CreateSideMap(void);
	void CreateEventMap(void);
	void EventStart(void);
	void EventUpdate(void);
	void EndDirection(void);
	void SetBlock(void);
	void LoadBlock(char *Name, D3DXVECTOR3 pos);
	void SetLevelUP(void);
	void BreakBlck(void);
	void ColorCircle(D3DXVECTOR3 pos);
	bool CollisionCircleOut(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2, float nRadiusOut, float nRadiusIn);
	void CMap2D::CollisionSquare(D3DXVECTOR3 pos);

	int m_MapLevel;					//マップの難易度
	float m_DepthOld;				//過去の深さ
	float m_Depth;					//現在の深さ
	bool m_bCreate;					//マップ生成を行ったかどうか
	bool m_bSpownMove;				//敵が同じ場所に出現しないため、出現してから移動したかを判断するフラグ
	float m_fCreatePoint;			//マップ生成を行った位置
	int m_BreakSelect;				//ブロックの破壊範囲
	int m_EnemySelect;				//出現する敵の種類
	int m_EnemySelect2;				//出現する敵の種類
	int CreateEnemy;				//マップ生成の際に敵を出す数
	int CreateEnemyCount;			//マップ生成の際に敵を出した数
	int CreateNumber;				//マップ生成の回数
	D3DXVECTOR3 m_BreakPos;			//破壊を開始する位置
	D3DXVECTOR3 m_BreakEnd;			//破壊を開始する位置
	int m_TestCount;				//テスト用カウント
	int m_CreateNumber;				//生成番号
	int m_WightNumber;				//横の番号
	int m_HeightNumber;				//縦の番号
	int m_EventEnemy;				//イベント中の敵の数
	float m_EventStartLine;			//イベントの部屋かどうかの基準ライン
	D3DXVECTOR3 m_EventEndBreakPos;	//イベント終了時のブロック破壊位置
	int m_EndDirectionTime;			//イベント終了時の演出時間
	bool m_bEndDirection;			//イベント終了時の演出を出しているかどうか
	D3DXVECTOR3 m_DirectionPos;		//演出発動位置
	int m_nCntCreateEventMap;		//イベントマップの発生回数
	int m_nCreateEventMap;			//生成したイベントマップの番号

	float m_fCirclePos;				//色切り替えの円の位置
	bool m_bColorCircle;			//色切り替えの円を使用しているかどうか

	CNormal_Block *m_pNormalBlock;
	CBreak_Block3D *m_pBreakBlock3D;
	CEnemy3D *m_pEnemy;
	CItem *m_pItem;
};
#endif