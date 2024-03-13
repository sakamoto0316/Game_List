//============================================
//
//	カメラの処理 [camera.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//カメラクラス
class CCamera
{
public:
	CCamera();
	~CCamera();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void SetCameraPosY(float PosY) { m_EventPosY = PosY; }
	void ResetCamera(void);
	void SetBib(bool Set) { m_bBib = Set; }
	float GetPosY(void) { return m_posR.y; }

private:
	D3DXMATRIX m_mtxView;		//ビューマトリックス
	D3DXMATRIX m_mtxProjection;	//プロジェクションマトリックス
	D3DXVECTOR3 m_posV;			//視点
	D3DXVECTOR3 m_posR;			//注視点
	D3DXVECTOR3 m_vecU;			//上方向ベクトル
	D3DXVECTOR3 m_rot;			//現在の向き
	D3DXVECTOR3 m_rotOld;		//過去の向き
	D3DXVECTOR3 m_posVDest;		//目的の視点
	D3DXVECTOR3 m_posRDest;		//目的の注視点
	float m_CameraDistance;		//注視点とカメラの距離
	float m_EventPosY;			//イベント時のカメラの高さ
	bool m_bBib;				//カメラが振動するかどうか
	float m_fBibPowor;			//カメラ振動の強さ
};

#endif