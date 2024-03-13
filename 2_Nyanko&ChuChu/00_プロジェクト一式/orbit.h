//=====================================================================================
//
//	�O�Ճw�b�_�[ [orbit.h]
//	Author�F��������
//
//=====================================================================================
#ifndef _ORBIT_H_			// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _ORBIT_H_			// ��d�C���N���[�h�h�~�̃}�N�����`����

//*************************************************************************************
// �C���N���[�h�t�@�C��
//*************************************************************************************
#include "object.h"

//-------------------------------------------------------------------------------------
//	�}�N����`
//-------------------------------------------------------------------------------------
#define MAX_ORBIT_VTX		(160)			// �O�Ղ̍ō����_��

//-------------------------------------------------------------------------------------
// �N���X��`(�O��)
//-------------------------------------------------------------------------------------
class COrbit : CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	//-------------------------------------------------------------------------------------
	//	�񋓌^��` (MATRIXPLACE)
	//-------------------------------------------------------------------------------------
	typedef enum
	{
		MATRIXPLACE_BOTTOM = 0,		// ��
		MATRIXPLACE_TOP,			// ��
		MATRIXPLACE_MAX				// ���̗񋓌^�̑���
	}MATRIXPLACE;

	COrbit();						// �R���X�g���N�^
	virtual ~COrbit();				// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	void BindTexture(int nIdx);		// �e�N�X�`���̊��蓖�ď���

	// �Z�b�g�E�Q�b�g�֌W
	void SetParentData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot);		// �e�̈ʒu�̐ݒ菈��
	void PosSet(const D3DXVECTOR3& pos);									// �S���_�̈ʒu�̐ݒ�

	// �ÓI�����o�֐�
	static COrbit* Create(const D3DXVECTOR3 pos, const D3DXVECTOR3& rot, const int nTexIdx);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;				// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;					// �e�N�X�`���ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;							// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_posParent;						// �e�̈ʒu
	D3DXVECTOR3 m_rotParent;						// �e�̌���
	D3DXVECTOR3 m_aPosPoint[MAX_ORBIT_VTX];			// �v�Z��̊e���_���W
	D3DXCOLOR m_aColPoint[MAX_ORBIT_VTX];			// �v�Z��̊e���_�J���[
};

#endif