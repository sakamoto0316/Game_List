//===================================
//
// �X���C���w�b�_�[[slime.h]
// Author ��������
//
//===================================
#ifndef _SLIME_H_
#define _SLIME_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �N���X��`(�X���C��)
//-----------------------------------
class CSlime : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CSlime();				// �R���X�g���N�^
	~CSlime();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �q�b�g����

private:		// ���������A�N�Z�X�ł���
};

#endif