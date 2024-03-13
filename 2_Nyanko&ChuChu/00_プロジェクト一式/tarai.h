//===================================
//
// ���炢�w�b�_�[[tarai.h]
// Author ��{�ėB
//
//===================================
#ifndef _TARAI_H_
#define _TARAI_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

class CObject3D;
class CHimo;

//-----------------------------------
// �N���X��`(����)
//-----------------------------------
class CTarai : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	CTarai();			// �R���X�g���N�^
	~CTarai();		// �f�X�g���N�^

						// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, CHimo* pHimo);				// ���̐ݒ菈��
	void SetIndex(int Idx) { m_nIndex = Idx; }			// �g�p�ԍ��̐ݒ�

	// �ÓI�����o�֐�
	static CTarai* Create(const D3DXVECTOR3& pos, CHimo* pHimo);	// ��������

private:		// ���������A�N�Z�X�ł���

	CHimo* m_pHimo;			// �R�̃|�C���^(�����͂��Ȃ�)
	D3DXVECTOR3 m_move;
	int m_nIndex;
	CObject3D *m_pShadow;
};

#endif