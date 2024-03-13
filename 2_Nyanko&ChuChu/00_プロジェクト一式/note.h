//===================================
//
// �����w�b�_�[[note.h]
// Author ��{�ėB
//
//===================================
#ifndef _NOTE_H_
#define _NOTE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

class CSpeaker;
//-----------------------------------
// �N���X��`(����)
//-----------------------------------
class CNote : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CNote();			// �R���X�g���N�^
	~CNote();		// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos);					// ���̐ݒ菈��
	void SetLife(int Life) { m_nLife = Life; }				// �����̐ݒ菈��
	void SetIndex(int Idx) { m_nIndex = Idx; }				// �g�p�ԍ��̐ݒ�
	void SetMove(D3DXVECTOR3 move) { m_move = move; }		// �ړ��ʂ̐ݒ�
	void SetMain(CSpeaker *Main) { m_Main = Main; }			// �����̎����g�p���Ă���I�u�W�F�N�g�̃|�C���^���擾����

	// �ÓI�����o�֐�
	static CNote* Create(const D3DXVECTOR3& pos);	// ��������

private:		// ���������A�N�Z�X�ł���

	float m_StartPosY;		// �����ʒu�̍���
	D3DXVECTOR3 m_move;		// �ړ���
	int m_nLife;			// ����
	int m_nIndex;			// �g�p�ԍ�
	int m_nRandHeight;		// �����̃����_������
	CSpeaker *m_Main;		// �����̎����g�p���Ă���I�u�W�F�N�g
};

#endif