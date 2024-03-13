//===================================
//
// �����w�b�_�[[explanation.h]
// Author ��{�ėB
//
//===================================
#ifndef _EXPLANATION_H_
#define _EXPLANATION_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "tutorial.h"

#define IMAGE_MAX (5)

class CObject2D;
//-----------------------------------
// �N���X��`(�Ԏ����͂̃��A�N�V����)
//-----------------------------------
class CExplanation : public CObject/*�e�N���X*/
{
public:			// �N�ł��A�N�Z�X�ł���

	CExplanation();			// �R���X�g���N�^
	~CExplanation();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(CTutorial::TUTORIAL Tutorial);		// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CExplanation* Create(CTutorial::TUTORIAL Tutorial);		// ��������

private:		// ���������A�N�Z�X�ł���
	CObject2D *m_pBG;
	CObject2D *m_pCatKing;
	CObject2D *m_pCatBG;
	CObject2D *m_pCatText;
	CObject2D *m_pRatKing;
	CObject2D *m_pRatBG;
	CObject2D *m_pRatText;
	CObject2D *m_apImage[IMAGE_MAX];
	D3DXCOLOR m_ColorKing;
	D3DXCOLOR m_ColorText;

	float m_fStartAlpha;
};

#endif