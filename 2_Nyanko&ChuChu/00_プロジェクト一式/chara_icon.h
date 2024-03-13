//============================================
//
// �L�����N�^�[�̉摜�w�b�_�[[chara_image.h]
// Author�F��������
//
//============================================
#ifndef _CHARA_ICON_H_					// ���̃}�N����`������Ă��Ȃ�������
#define _CHARA_ICON_H_					// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"
#include "player.h"

//--------------------------------------------
// �N���X��`(�L�����N�^�[�̉摜)
//--------------------------------------------
class CCharaIcon : public CObject2D
{
public:				// �N�ł��A�N�Z�X�ł���

	CCharaIcon();						// �R���X�g���N�^
	~CCharaIcon();						// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);					// ����������
	void Uninit(void);					// �I������
	void Update(void);					// �X�V����
	void Draw(void);					// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const CPlayer::TYPE type);					// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCharaIcon* Create(const D3DXVECTOR3& pos, const CPlayer::TYPE type);	// ��������

private:			// ���������A�N�Z�X�ł���

};

#endif