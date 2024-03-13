//===================================
//
// ��@�̕��w�b�_�[[fan_wind.h]
// Author ��������
//
//===================================
#ifndef _FAN_WIND_H_
#define _FAN_WIND_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "object3D.h"

//-----------------------------------
// �N���X��`(CFanWind)
//-----------------------------------
class CFanWind : public CObject3D
{
public:

	CFanWind();				// �R���X�g���N�^
	~CFanWind();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CFanWind* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size);	// ��������

private:

};

#endif