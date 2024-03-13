//===================================
//
// エディットヘッダー[edit.h]
// Author 小原立暉
//
//===================================
#ifndef _EDIT_H_
#define _EDIT_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"
#include "obstacle.h"
#include "block.h"

//-----------------------------------
// クラス定義(エディット)
//-----------------------------------
class CEdit : public CModel
{
public:			// 誰でもアクセスできる

	// 列挙型定義(種類)
	enum TYPE
	{
		TYPE_OBSTACLE = 0,		// 障害物
		TYPE_BLOCK,				// ブロック
		TYPE_MAX				// この列挙型の総数
	};

	CEdit();			// コンストラクタ
	~CEdit();			// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(void);				// 情報の設定処理

	// 静的メンバ関数
	static CEdit* Create(void);		// 生成処理

private:		// 自分だけアクセスできる

	// メンバ関数
	void TypeProcess(void);		// 種類ごとの処理
	void Move(void);			// 移動処理
	void Adjust(void);			// 微調整処理
	void HeightMove(void);		// 縦移動処理
	void HeightAdjust(void);	// 縦微調整処理
	void RotMove(void);			// 向きの移動処理
	void BlockRotMove(void);	// ブロックの向きの移動処理
	void Set(void);				// 設置処理
	void Reset(void);			// リセット処理
	void Delete(void);			// 消去処理
	void Type(void);			// 種類の変更処理

	// それぞれの種類ごとのメンバ関数
	void ObstacleProcess(void);	// 障害物の処理
	void BlockProcess(void);	// ブロックの処理

	// それぞれの消去処理
	void DeleteObstacle(void);	// 障害物の消去処理
	void DeleteBlock(void);		// ブロックの消去処理

	// メンバ変数宣言
	TYPE m_type;					// 種類
	CObstacle::TYPE m_obstacleType;	// 障害物の種類
	CBlock::TYPE m_blockType;		// ブロックの種類
	CBlock::ROTTYPE m_rotType;		// 向きの種類
};

#endif