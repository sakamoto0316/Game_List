//===================================
//
// �J�����w�b�_�[[camera.h]
// Author ��������
//
//===================================
#ifndef _MULTICAMERA_H_			//���̃}�N����`������Ă��Ȃ�������
#define _MULTICAMERA_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"

//-----------------------------------
// �N���X��`(�J����)
//-----------------------------------
class CMultiCamera
{
public:			// �N�ł��A�N�Z�X�o����

				// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_NONE = 0,		// �ʏ���
		TYPE_VIBRATE,		// �U�����
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CMultiCamera();		// �R���X�g���N�^
	~CMultiCamera();		// �f�X�g���N�^

					// �����o�֐�
	HRESULT Init(int nIdex);		// ����������
	void Uninit(void);				// �I������
	void Update(void);				// �X�V����
	void Set(int nIdex);			// �ݒ菈��

	void Rotation(void);			// ��荞�ݏ���
	void Reset(void);				// ���̃��Z�b�g����

	void SetPosV(const D3DXVECTOR3 posV);		// ���_�̈ʒu�̐ݒ菈��
	D3DXVECTOR3 GetPosV(void) const;			// ���_�̈ʒu�̎擾����

	void SetPosR(const D3DXVECTOR3 posR);		// �����_�̈ʒu�̐ݒ菈��
	D3DXVECTOR3 GetPosR(void) const;			// �����_�̈ʒu�̎擾����

	void SetRot(const D3DXVECTOR3& rot);		// �����̐ݒ菈��
	D3DXVECTOR3 GetRot(void) const;				// �����̎擾����

	void SetDistance(const float fDis);			// �����̐ݒ菈��
	float GetDistance(void) const;				// �����̎擾����

	void SetIdx(const int Idx) { m_nDrawIdx = Idx; }	// �����̐ݒ菈��
	int GetIdx(void) { return m_nDrawIdx; }		// �����̔ԍ��̎擾����

	void SetType(const TYPE type);				// ��ނ̐ݒ菈��

	void ChangeControl(void);					// �J�����̑���󋵂̐؂�ւ�����

private:		// ���������A�N�Z�X�o����

				// �����o�֐�
	void Move(void);				// �ړ�����
	void MovePosV(void);			// ���_���쏈��
	void MovePosR(void);			// �����_���쏈��
	void MoveRange(void);			// �������쏈��
	void Chase(void);				// �ǐՏ���
	void NoneCamera(void);			// �ʏ��Ԃ̃J��������
	void Vibrate(void);				// �U������
	void Control(void);				// ���쏈��
	void PosSet(void);				// �ʒu�̐ݒ菈��

	// �^�C�g���֌W
	void TitleCamera(void);			// �^�C�g����ʂ̃J��������
	void TitleNoneCamera(void);		// �^�C�g����ʂ̒ʏ폈��
	void TitleHoleInCamera(void);	// �^�C�g����ʂ̌����菈��

	// �Q�[���֌W
	void GameCamera(void);			// �Q�[����ʂ̃J��������
	void PlayCamera(void);			// �v���C���̃J��������
	void TypeProcess(void);			// �J�����̎�ނ��Ƃ̏���
	void MagicWall(void);			// �J�������}�b�v�O�ɏo���Ƃ��ɖ߂�����

									// �����o�ϐ�
	D3DXMATRIX m_mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX m_mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X
	D3DXVECTOR3 m_posV;				// ���_
	D3DXVECTOR3 m_posVDest;			// �ړI�̎��_
	D3DXVECTOR3 m_posR;				// �����_
	D3DXVECTOR3 m_posRDest;			// �ړI�̒����_
	D3DXVECTOR3 m_VecU;				// ������x�N�g��
	D3DXVECTOR3 m_rot;				// ����
	D3DVIEWPORT9 m_viewport;		// �r���[�|�[�g
	int m_nDrawIdx;					// �`��ԍ�
	TYPE m_type;					// ���
	float m_rotDest;				// �ړI�̌���
	float m_Dis;					// ����
	float m_DisDest;				// �ړI�̋���
	int m_nSwingCount;				// �h��̃J�E���g
	bool m_bControl;				// �����
};

#endif