//============================================
//
// �A�C�e���̘g�w�b�_�[[item_frame.h]
// Author�F��������
//
//============================================
#ifndef _ITEM_FRAME_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _ITEM_FRAME_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"
#include "player.h"

//--------------------------------------------
// �N���X��`(�A�C�e���̘g)
//--------------------------------------------
class CItemFrame : public CObject2D
{
public:				// �N�ł��A�N�Z�X�ł���

	CItemFrame();			// �R���X�g���N�^
	~CItemFrame();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CItemFrame* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, const CPlayer::TYPE type);	// ��������

private:			// ���������A�N�Z�X�ł���

};

#endif