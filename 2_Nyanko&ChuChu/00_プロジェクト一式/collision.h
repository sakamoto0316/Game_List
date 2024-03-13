//===================================
//
// 当たり判定ヘッダー[collision.h]
// Author 小原立暉
//
//===================================
#ifndef _COLLISION_H_			//このマクロ定義がされていなかったら
#define _COLLISION_H_			//2重インクルード防止のマクロを定義する

//***********************************
// インクルードファイル
//***********************************
#include "main.h"
#include "obstacle.h"

//-----------------------------------
// 前方宣言
//-----------------------------------
class CBlock;		// ブロック
class CPlayer;		// プレイヤー

//-----------------------------------
// 名前空間(当たり判定)
//-----------------------------------
namespace collision
{
	// 構造体定義(当たり判定)
	struct SCollision
	{
		bool bTop;		// 上の当たり判定
		bool bBottom;	// 下の当たり判定
		bool bRight;	// 右の当たり判定
		bool bLeft;		// 左の当たり判定
		bool bFar;		// 奥の当たり判定
		bool bNear;		// 手前の当たり判定
	};

	// 丸影の当たり判定
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// 丸影の当たり判定

	// 障害物の当たり判定
	bool ObstacleCollision(CPlayer* player, const float fWidth, const float fHeight, const float fDepth);	// 障害物の衝突判定
	void ObstacleHit(CPlayer* pPlayer, const float fWidth, const float fHeight, const float fDepth);		// 障害物の当たり判定
	void ObstacleAction(CPlayer* pPlayer, const float Radius);				// 障害物の起動判定
	void ObstacleSearch(CPlayer* pPlayer, const float Radius);				// 起動可能障害物や警告を出す障害物のサーチ

	// 今後実装予定のブロックの当たり判定
	bool BlockCollision(CPlayer* player, const D3DXVECTOR3& collSize);							// ブロックの当たり判定
	void BlockRectangleCollision(const CBlock& block, CPlayer* player, const D3DXVECTOR3& collSize, bool* pJump);			// ブロックの矩形の当たり判定
	void BlockCircleCollision(CBlock& block, CPlayer* player, const float fRadius, const float fHeight, bool* pJump);		// ブロックの円形の当たり判定

	bool BlockHit(CPlayer* player, const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize);							// ブロックの攻撃判定
	void BlockRectangleHit(const CBlock& block, CPlayer* player, const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, bool* pHit);			// ブロックの矩形の攻撃判定
	void BlockCircleHit(CBlock& block, CPlayer* player, const D3DXVECTOR3& pos, const float fRadius, const float fHeight, bool* pHit);		// ブロックの円形の攻撃判定

	// 起伏地面の当たり判定
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// 起伏地面の範囲外の当たり判定

	//壁との当たり判定
	void WallCollision(CPlayer* player, const D3DXVECTOR3& collSize);

	// アイテムとの当たり判定
	void ItemCollision(CPlayer& pPlayer, const int nHave);		// ネコとアイテムとの当たり判定

	// 汎用的な当たり判定
	bool HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// 六面体の当たり判定
	SCollision HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// 六面体の当たり判定(どの面に乗ったかの判定付き)
	SCollision HexahedronClushNotMove(const D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// 六面体の当たり判定(どの面に乗ったかの判定付き && 移動させない)

}

#endif