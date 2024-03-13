//===================================
//
// �u���b�N�w�b�_�[[block.h]
// Author ��������
//
//===================================
#ifndef _BLOCK_H_
#define _BLOCK_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"

//-----------------------------------
// �N���X��`(�n�`�p�u���b�N)
//-----------------------------------
class CBlock : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// ���
	enum STATE
	{
		STATE_NONE = 0,		// �������Ȃ�
		STATE_SWAY,			// �h���
		STATE_MAX			// ���̗񋓌^�̑���
	};

	// �����̎��
	enum ROTTYPE
	{
		ROTTYPE_FRONT = 0,		// ����
		ROTTYPE_RIGHT,			// �E
		ROTTYPE_BACK,			// ���
		ROTTYPE_LEFT,			// ��
		ROTTYPE_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(�����蔻��̎��)
	enum COLLISION
	{
		COLLISION_SQUARE = 0,		// �l�p
		COLLISION_CIRCLE,			// �~
		COLLISION_MAX				// ���̗񋓌^�̑���
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_CARDBOARD = 0,		// �i�{�[��
		TYPE_TISSUE,			// �e�B�b�V����
		TYPE_PENHOLDER,			// �y������
		TYPE_REMOCON,			// �����R��
		TYPE_BEAR,				// �e�f�B�x�A
		TYPE_CLOCK,				// ���v
		TYPE_RUBBISH,			// �`����
		TYPE_MILKPACK,			// �����p�b�N
		TYPE_OBAPHONE,			// �I�o�t�H��
		TYPE_WII,				// Wii
		TYPE_DS,				// DS
		TYPE_HEADPHONE,			// �w�b�h�t�H��
		TYPE_PEN,				// �y��
		TYPE_ACADAPTER,			// AC�A�_�v�^�[
		TYPE_BUILDINGBLOCK,		// �ςݖ�
		TYPE_GLASSES,			// �ዾ�P�[�X
		TYPE_PENCIL,			// ���M
		TYPE_PICTUREFRAME,		// �ʐ^����
		TYPE_SHELF,				// �˒I
		TYPE_PULLSHELF,			// �����o���I
		TYPE_KITCHEN,			// �L�b�`��
		TYPE_REIZOUKO,			// �①��
		TYPE_TABLE,				// �e�[�u��
		TYPE_CHAIR,				// ���̈֎q
		TYPE_CORKBOARD,			// �R���N�{�[�h
		TYPE_DESK,				// �f�X�N
		TYPE_DESKBOOK,			// �f�X�N�p�̖{
		TYPE_EXTIMGISHER,		// ���Ί�
		TYPE_KATEN,				// �J�[�e��
		TYPE_KATENRAIL,			// �J�[�e���̃��[��
		TYPE_TANSU02,			// ����
		TYPE_TV_STAND,			// �e���r��
		TYPE_WALL_PLUS50,		// 50*100�̕�
		TYPE_WALL_PLUS100,		// 100*100�̕�
		TYPE_DOOR001,			// �h�A
		TYPE_SMALL_SHELF,		// �����ȒI
		TYPE_BOOKSHELF,			// �����̖{�I
		TYPE_TALBESHELF,		// �e�[�u���̍����̒I
		TYPE_SOFA_SHEET,		// �\�t�@�[�i���ʁj
		TYPE_SOFA_BACKTEST,		// �\�t�@�[�i�w������j
		TYPE_CHAIR_SHEET,		// ���̈֎q(����)
		TYPE_CHAIR_BACKREST,	// ���̈֎q(�w������)
		TYPE_LEVERBODYBLOCK,	// ���o�[(�{��)
		TYPE_WINDOW,			// ��
		TYPE_WALLCLOCK,			// �Ǌ|�����v
		TYPE_INTERIOR000,		// �ǂ̃C���e���A(�I)
		TYPE_WALLCROSS,			// ����
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	CBlock();			// �R���X�g���N�^
	~CBlock();			// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CBlock* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CBlock* pNext);		// ��̃|�C���^�̐ݒ菈��
	CBlock* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CBlock* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void UninitAll(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type);			// ���̐ݒ菈��

	// �Z�b�g�E�Q�b�g�֌W
	void SetCollision(const COLLISION collsion);	// �����蔻��̎�ނ̐ݒ菈��
	//void SetOnRat(const bool bOnRat, const int nPlayerIdx);		// �l�Y�~�̏���Ă���󋵐ݒ�
	void SetState(STATE state);						// ��Ԑݒ�

	COLLISION GetCollision(void) const;				// �����蔻��̎�ނ̎擾����
	ROTTYPE GetRotType(void) const;					// �����̎�ނ̎擾����
	TYPE GetType(void) const;						// ��ނ̎擾����
	STATE GetState(void) const;						// ��Ԃ̎擾����
	D3DXVECTOR3 GetVtxMax(void) const;				// �ő�l�̎擾����
	D3DXVECTOR3 GetVtxMin(void) const;				// �ŏ��l�̎擾����
	//bool GetOnRat(void) const;						// �l�Y�~�̏���Ă���󋵎擾

	// �ÓI�����o�֐�
	static CBlock* Create(const D3DXVECTOR3& pos, const ROTTYPE rotType, const TYPE type);	// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void CollisionSetting(void);		// �����ɂ��ő�l�E�ŏ��l�̐ݒ菈��
	void UpdateState(void);				// ��ԍX�V����
	void Sway(void);					// �h�炷����

	// �����o�ϐ�
	COLLISION m_collision;	// �����蔻��̎��
	ROTTYPE m_rotType;		// �����̎��
	TYPE m_type;			// ���
	STATE m_state;			// ���
	D3DXVECTOR3 m_vtxMax;	// �ő�l
	D3DXVECTOR3 m_vtxMin;	// �ŏ��l
	//bool m_bOnRat;			// �l�Y�~������Ă��邩
	//int m_nPlayerIdx;		// �v���C���[�ԍ�
	int m_nAngleSwitch;		// �p�x��+-�؂�ւ�
	int m_nSwayCount;		// �h�炷�b��

	// ���X�g�\���֌W
	CBlock* m_pPrev;	// �O�ւ̃|�C���^
	CBlock* m_pNext;	// ���ւ̃|�C���^
};

#endif