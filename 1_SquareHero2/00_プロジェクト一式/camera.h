//============================================
//
//	�J�����̏��� [camera.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//�J�����N���X
class CCamera
{
public:
	CCamera();
	~CCamera();

	//�J�����̃��[�h
	enum CAMERAMODE
	{
		CAMERAMODE_CONTROL = 0,	//����
		CAMERAMODE_FOLLOW,		//�Ǐ]
		CAMERAMODE_DOWNVIEW,	//�����낵
		CAMERAMODE_SIDEVIEW,	//2D
		CAMERAMODE_EVENTBOSS,	//�C�x���g���̃{�X����
		CAMERAMODE_MAX,
	};

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void SetCamera(void);
	void SetCameraPos(D3DXVECTOR3 Pos) { m_posV = Pos; m_posR = Pos; }
	D3DXVECTOR3 GetCameraPos(void) { return m_posR;}
	void SetCameraPosY(float PosY) { m_EventPosY = PosY; }
	void ResetCamera(void);
	void SetBib(bool Set) { m_bBib = Set; }
	float GetPosY(void) { return m_posR.y; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetCameraMode(CAMERAMODE Mode) { CameraMode = Mode; }
	CAMERAMODE GetCameraMode(void) { return CameraMode; }
	void SetFollowTime(int Time) { m_FollowTime = Time; }
	D3DXVECTOR3 GetPosV(void) { return m_posV; }
	D3DXVECTOR3 GetPosR(void) { return m_posR; }
	void SetAttention(bool Set) { m_bAttention = Set; }
	bool GetAttention(void) { return m_bAttention; }

private:
	void ControlCamera(void);
	void FollowCamera(void);
	void DownviewCamera(void);
	void SideviewCamera(void);
	void EventBossCamera(void);

	D3DXMATRIX m_mtxView;		//�r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;	//�v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_move;			//�ړ���
	D3DXVECTOR3 m_posV;			//���_
	D3DXVECTOR3 m_posR;			//�����_
	D3DXVECTOR3 m_vecU;			//������x�N�g��
	D3DXVECTOR3 m_rot;			//���݂̌���
	D3DXVECTOR3 m_rotOld;		//�ߋ��̌���
	D3DXVECTOR3 m_posVDest;		//�ړI�̎��_
	D3DXVECTOR3 m_posRDest;		//�ړI�̒����_
	D3DXVECTOR3 m_PlayerPos;	//�v���C���[�̈ʒu
	D3DXVECTOR3 m_DelCameraPos;	//���X�|�[���J�����ʒu
	CAMERAMODE CameraMode;		//�J�����̏��
	D3DXVECTOR3 m_fRotMove;		//�����̃J�����ړ����x
	float m_CameraDistance;		//�����_�ƃJ�����̋���
	float m_EventPosY;			//�C�x���g���̃J�����̍���
	bool m_bFollowY;			//�J�����̏㉺�Ǐ]�����邩�ǂ���
	bool m_bBib;				//�J�������U�����邩�ǂ���
	float m_fBibPowor;			//�J�����U���̋���
	int m_FollowTime;			//��荞�ݎ���
	int m_FollowDistance;		//�Ǐ]���̃J��������
	bool m_bAttention;			//���ڏ��
};

#endif