//===================================
//
// �Ђ��w�b�_�[[Himo.h]
// Author ��{�ėB
//
//===================================
#ifndef _HIMO_H_
#define _HIMO_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "obstacle.h"

//-----------------------------------
// �}�N����`
//-----------------------------------
#define MAX_TARAI (10)			// �^���C�̍ő吔

class CTarai;
//-----------------------------------
// �N���X��`(�Ђ�)
//-----------------------------------
class CHimo : public CObstacle
{
public:			// �N�ł��A�N�Z�X�ł���

	CHimo();				// �R���X�g���N�^
	~CHimo();				// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize) override;		// �q�b�g����
	bool HitCircle(CPlayer* pPlayer, const float Radius) override;
	void Action(void) override;										// �M�~�b�N�N������

	void NULLTarai(int Idx) { m_apTarai[Idx] = NULL; }

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void TaraiCheck(void);		// �^���C�̑��݊m�F����
	void SetTarai(void);		// ���炢�̐�������
	void CountJudge(void);		// �^���C�̃J�E���g���f����

	// �����o�ϐ�
	CTarai *m_apTarai[MAX_TARAI];
	int m_nTaraiCount;
	float m_fDownPosY;
	float m_fUpPosY;
	bool m_bFall;
};

#endif