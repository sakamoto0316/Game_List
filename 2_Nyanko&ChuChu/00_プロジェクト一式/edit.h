//===================================
//
// �G�f�B�b�g�w�b�_�[[edit.h]
// Author ��������
//
//===================================
#ifndef _EDIT_H_
#define _EDIT_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "obstacle.h"
#include "block.h"

//-----------------------------------
// �N���X��`(�G�f�B�b�g)
//-----------------------------------
class CEdit : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_OBSTACLE = 0,		// ��Q��
		TYPE_BLOCK,				// �u���b�N
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CEdit();			// �R���X�g���N�^
	~CEdit();			// �f�X�g���N�^

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(void);				// ���̐ݒ菈��

	// �ÓI�����o�֐�
	static CEdit* Create(void);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void TypeProcess(void);		// ��ނ��Ƃ̏���
	void Move(void);			// �ړ�����
	void Adjust(void);			// ����������
	void HeightMove(void);		// �c�ړ�����
	void HeightAdjust(void);	// �c����������
	void RotMove(void);			// �����̈ړ�����
	void BlockRotMove(void);	// �u���b�N�̌����̈ړ�����
	void Set(void);				// �ݒu����
	void Reset(void);			// ���Z�b�g����
	void Delete(void);			// ��������
	void Type(void);			// ��ނ̕ύX����

	// ���ꂼ��̎�ނ��Ƃ̃����o�֐�
	void ObstacleProcess(void);	// ��Q���̏���
	void BlockProcess(void);	// �u���b�N�̏���

	// ���ꂼ��̏�������
	void DeleteObstacle(void);	// ��Q���̏�������
	void DeleteBlock(void);		// �u���b�N�̏�������

	// �����o�ϐ��錾
	TYPE m_type;					// ���
	CObstacle::TYPE m_obstacleType;	// ��Q���̎��
	CBlock::TYPE m_blockType;		// �u���b�N�̎��
	CBlock::ROTTYPE m_rotType;		// �����̎��
};

#endif