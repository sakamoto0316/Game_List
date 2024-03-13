//===========================================
//
// �t�F�[�h�w�b�_�[[fade.h]
// Author ��������
//
//===========================================
#ifndef _FADE_H_				// ���̃}�N����`������Ă��Ȃ�������
#define _FADE_H_				// 2�d�C���N���[�h�h�~�̃}�N�����`����

//-------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------
#include "main.h"

// �N���X��`(�t�F�[�h)
class CFade
{
public:

	//-------------------------------------------
	// �񋓌^��`(�t�F�[�h�̏��)
	//-------------------------------------------
	enum FADE
	{
		FADE_NONE = 0,					//�������Ă��Ȃ����
		FADE_IN,						//�t�F�[�h�C�����
		FADE_OUT,						//�t�F�[�h�A�E�g���
		FADE_MAX
	};

	CFade();							// �R���X�g���N�^
	~CFade();							// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(CScene::MODE modeNext);	// ����������
	void Uninit(void);						// �I������
	void Update(void);						// �X�V����
	void Draw(void);						// �`�揈��
	void SetFade(CScene::MODE modeNext);	// �t�F�[�h�̐ݒ菈��
	FADE GetFade(void);						// �t�F�[�h�̎擾����

	// �ÓI�����o�֐�
	static CFade* Create(CScene::MODE modeNext);	// ��������

private:

	// �����o�ϐ�
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// �t�F�[�h�̒��_�o�b�t�@�ւ̃|�C���^
	FADE m_fade;						// �t�F�[�h�̏��
	CScene::MODE m_modeNext;			// ���̉��(���[�h)
	D3DXCOLOR m_color;					// �|���S��(�t�F�[�h)�̐F
};

#endif