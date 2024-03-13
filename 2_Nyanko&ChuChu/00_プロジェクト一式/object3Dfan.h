//===================================
//
// オブジェクト3Dファンヘッダー[object3Dfan.h]
// Author 小原立暉
//
//===================================
#ifndef _OBJECT3DFAN_H_
#define _OBJECT3DFAN_H_

#include "object.h"

//--------------------------------------------
// クラス(オブジェクト3Dクラス)
//--------------------------------------------
class CObject3DFan : public CObject
{
public:			// 誰でもアクセスできる

	CObject3DFan();			// コンストラクタ
	CObject3DFan(CObject::TYPE type, PRIORITY priority = PRIORITY_PLAYER);			// オーバーロードコンストラクタ
	virtual ~CObject3DFan();		// デストラクタ
	void Box(void);			// コンストラクタの箱

	// メンバ関数
	virtual HRESULT Init(void);		// 初期化処理
	virtual void Uninit(void);		// 終了処理
	virtual void Update(void);		// 更新処理
	virtual void Draw(void);		// 描画処理

	void BindTexture(int nIdx);		// テクスチャの割り当て処理

	// 頂点操作系
	void SetVertex(void);						// 頂点情報の設定
	void SetVtxColor(const D3DXCOLOR& col);		// 頂点カラーの設定処理
	void SetVtxColor(const D3DXCOLOR& normalCol, const D3DXCOLOR& rezCol, int nEndRezVtx);		// 頂点カラーの細かい設定処理

	// セット・ゲット関係
	void SetPos(const D3DXVECTOR3& pos);	// 位置設定処理
	D3DXVECTOR3 GetPos(void) const;			// 位置取得処理

	void SetPosOld(const D3DXVECTOR3& posOld);	// 前回の位置設定処理
	D3DXVECTOR3 GetPosOld(void) const;			// 前回の位置取得処理

	void SetRot(const D3DXVECTOR3& rot);	// 向き設定処理
	D3DXVECTOR3 GetRot(void) const;			// 向き取得処理

	void SetSize(const D3DXVECTOR3& size);	// サイズ設定処理
	D3DXVECTOR3 GetSize(void) const;		// サイズ取得処理

	void SetNumAngle(const int nNum);		// 角度の総数の設定処理
	int GetNumAngle(void) const;			// 角度の総数の取得処理

	void SetRadius(const float fRadius);	// 半径の設定処理
	float GetRadius(void) const;			// 半径の取得処理

	void SetColor(const D3DXCOLOR col);		// 色の設定処理
	D3DXCOLOR GetColor(void) const;			// 色の取得処理

	// 静的メンバ関数
	static CObject3DFan* Create(void);			// 生成処理

private:

	// メンバ変数
	D3DXVECTOR3 m_pos;							// 位置
	D3DXVECTOR3 m_posOld;						// 前回の位置
	D3DXVECTOR3 m_rot;							// 向き
	D3DXVECTOR3 m_size;							// サイズ
	D3DXCOLOR m_col;							// 色
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファのポインタ
	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
	int m_nNumAngle;							// 角度の数
	float m_fRadius;							// 半径
	int m_nTexIdx;								// テクスチャのインデックス
};

#endif