//===================================
//
// �R���Z���g�w�b�_�[[consent.h]
// Author ��{�ėB
//
//===================================
#ifndef _CONSENT_H_
#define _CONSENT_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

class CCup;

//-----------------------------------
// �N���X��`(����)
//-----------------------------------
class CConsent : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CConsent();		// �R���X�g���N�^
	~CConsent();		// �f�X�g���N�^

					// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��
	void Draw(const float fAlpha);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��
	void SetLife(int Life) { m_nLife = Life; }				// �����̐ݒ菈��
	void SetIndex(int Idx) { m_nIndex = Idx; }				// �g�p�ԍ��̐ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }		// �ړ��ʂ̐ݒ�
	void SetMain(CCup *main) { m_pMain = main; }		// �ړ��ʂ̐ݒ�

	// �ÓI�����o�֐�
	static CConsent* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	float m_StartPosY;		// �����ʒu�̍���
	D3DXVECTOR3 m_move;		// �ړ���
	int m_nLife;			// ����
	int m_nIndex;			// �g�p�ԍ�
	CCup *m_pMain;			// �������g���g�p���Ă��郂�f��
};

#endif