//===================================
//
// 音符ヘッダー[note.h]
// Author 坂本翔唯
//
//===================================
#ifndef _NOTE_H_
#define _NOTE_H_

//***********************************
// インクルードファイル
//***********************************
#include "model.h"

class CSpeaker;
//-----------------------------------
// クラス定義(音符)
//-----------------------------------
class CNote : public CModel
{
public:			// 誰でもアクセスできる

	CNote();			// コンストラクタ
	~CNote();		// デストラクタ

	// メンバ関数
	HRESULT Init(void);		// 初期化処理
	void Uninit(void);		// 終了処理
	void Update(void);		// 更新処理
	void Draw(void);		// 描画処理

	void SetData(const D3DXVECTOR3& pos);					// 情報の設定処理
	void SetLife(int Life) { m_nLife = Life; }				// 寿命の設定処理
	void SetIndex(int Idx) { m_nIndex = Idx; }				// 使用番号の設定
	void SetMove(D3DXVECTOR3 move) { m_move = move; }		// 移動量の設定
	void SetMain(CSpeaker *Main) { m_Main = Main; }			// 自分の事を使用しているオブジェクトのポインタを取得する

	// 静的メンバ関数
	static CNote* Create(const D3DXVECTOR3& pos);	// 生成処理

private:		// 自分だけアクセスできる

	float m_StartPosY;		// 初期位置の高さ
	D3DXVECTOR3 m_move;		// 移動量
	int m_nLife;			// 寿命
	int m_nIndex;			// 使用番号
	int m_nRandHeight;		// 高さのランダム処理
	CSpeaker *m_Main;		// 自分の事を使用しているオブジェクト
};

#endif