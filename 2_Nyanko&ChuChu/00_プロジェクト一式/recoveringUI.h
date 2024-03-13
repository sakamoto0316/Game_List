//===================================
//
// �񕜒�UI�w�b�_�[[recoveringUI.h]
// Author ����������
//
//===================================
#ifndef _RECOVERINGUI_H_
#define _RECOVERINGUI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "objectbillboard.h"

//-----------------------------------
// �N���X��`(�T���v��)
//-----------------------------------
class CRecoveringUI : public CBillboard
{
public:			// �N�ł��A�N�Z�X�ł���

	// UI�̓����x���
	enum ALPHA
	{
		ALPHA_OPACITY = 0,		// �s����
		ALPHA_TRANSPARENT,		// ����
		ALPHA_MAX
	};

	CRecoveringUI();			// �R���X�g���N�^
	~CRecoveringUI();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);		// ���̐ݒ菈��
	
	void SetDisplayUI(bool bRez);	// UI�̕\����Ԃ̐ݒ�
	bool GetDisplayUI(void);		// UI�̕\����Ԃ̎擾

	// �ÓI�����o�֐�
	static CRecoveringUI* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& posOld);		// ��������

private:		// ���������A�N�Z�X�ł���
	bool m_bDisp;			// �\�����邩
	float m_fAlpha;			// �����x
	ALPHA m_alpha;			// �����x�̏��

};

#endif