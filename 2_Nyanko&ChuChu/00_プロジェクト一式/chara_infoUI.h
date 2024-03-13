//============================================
//
// �L�����N�^�[�̏��UI�w�b�_�[[chara_infoUI.h]
// Author�F��������
//
//============================================
#ifndef _CHARA_INFOUI_H_			// ���̃}�N����`������Ă��Ȃ�������
#define _CHARA_INFOUI_H_			// 2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object.h"
#include "player.h"

//--------------------------------------------
// �O���錾
//--------------------------------------------
class CCharaIcon;		// �L�����N�^�[�̃A�C�R��
class CCharaID;			// �L�����N�^�[��ID
class CCharaState;		// �L�����N�^�[�̏�ԃA�C�R��

//--------------------------------------------
// �N���X��`(�L�����N�^�[�̏��UI)
//--------------------------------------------
class CCharaInfoUI : public CObject
{
public:				// �N�ł��A�N�Z�X�ł���

	CCharaInfoUI();					// �R���X�g���N�^
	~CCharaInfoUI();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type);						// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CCharaInfoUI* Create(const D3DXVECTOR3& pos, const int nPlayerID, const CPlayer::TYPE type);			// ��������

private:			// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	CCharaIcon* m_pIcon;	// �A�C�R���̏��
	CCharaID* m_pID;		// ID�̏��
	CCharaState* m_pState;	// ��Ԃ̏��
};

#endif