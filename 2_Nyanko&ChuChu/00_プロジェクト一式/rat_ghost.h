//===================================
//
// �l�Y�~�̗H��̏���[rat_ghost.h]
// Author ����������
//
//===================================
#ifndef _RAT_GHOST_H_
#define _RAT_GHOST_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X(�l�Y�~�̗H��N���X)
//-----------------------------------
class CRatGhost : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CRatGhost();			// �R���X�g���N�^
	~CRatGhost();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CRatGhost* Create(const D3DXVECTOR3& pos);		// ��������

private:		// ���������A�N�Z�X�ł���

};

#endif