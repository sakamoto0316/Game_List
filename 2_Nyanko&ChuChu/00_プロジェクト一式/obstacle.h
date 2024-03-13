//===================================
//
// ��Q���w�b�_�[[obstacle.h]
// Author ��������
//
//===================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "model.h"
#include "player.h"

class CBillboard;

//-----------------------------------
// �N���X��`(��Q��)
//-----------------------------------
class CObstacle : public CModel
{
public:			// �N�ł��A�N�Z�X�ł���

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_HONEY = 0,		// �I��
		TYPE_SLIME,			// �X���C��
		TYPE_HAIRBALL,		// �{
		TYPE_PETBOTTLE,		// �y�b�g�{�g��
		TYPE_TOYCAR,		// ��������̎�
		TYPE_ROOMBA,		// �����o
		TYPE_HIMO,			// �Ђ�
		TYPE_SPEAKER,		// �X�s�[�J�[
		TYPE_MOUSETRAP,		// �l�Y�~�߂�
		TYPE_LEASH,			// ���[�h
		TYPE_PIN,			// ��e
		TYPE_FAN,			// ��@
		TYPE_CUP,			// �R�b�v
		TYPE_GARBAGECAN,	// �S�~
		TYPE_TV,			// �e���r
		TYPE_DYNAMITE,		// �_�C�i�}�C�g
		TYPE_BOOK,			// �{
		TYPE_REDKATEN,		// �Ԃ̃J�[�e��
		TYPE_RATMECHA,		// �l�Y�~���J
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CObstacle();			// �R���X�g���N�^
	CObstacle(CObject::TYPE type, PRIORITY priority = PRIORITY_BLOCK);			// �R���X�g���N�^
	virtual ~CObstacle();	// �f�X�g���N�^
	void Box(void);			// �R���X�g���N�^�̔�

	// ���X�g�\���֌W
	void SetPrev(CObstacle* pPrev);		// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CObstacle* pNext);		// ��̃|�C���^�̐ݒ菈��
	CObstacle* GetPrev(void) const;		// �O�̃|�C���^�̐ݒ菈��
	CObstacle* GetNext(void) const;		// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��
	virtual void Draw(const float fAlpha);		// �`�揈��

	virtual void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);			// ���̐ݒ菈��

	virtual bool Collision(CPlayer* pPlayer, const D3DXVECTOR3& collSize);				// �����蔻�菈��
	virtual bool Hit(CPlayer* pPlayer, const D3DXVECTOR3& collSize);		// �q�b�g����
	virtual bool HitCircle(CPlayer* /*pPlayer*/, const float /*Radius*/) { return false; }			// �q�b�g����
	virtual void Action(void) {}											// �M�~�b�N�N������
	virtual void Action(CPlayer* /*pPlayer*/) {}							// �M�~�b�N�N������(�v���C���[��񂪕K�v�ȏꍇ)
	virtual void HitMultiCircle(CPlayer* /*pPlayer*/, const float /*Radius*/, bool /*bInput*/) {}	// �q�b�g����
	virtual void MultiAction(void) {}										// �M�~�b�N�����N������
	void GimmickUI(bool Set, int Player_Idx);								// �M�~�b�N�N��UI�̕\��
	void MultiGimmickUI(bool Set, int Player_Idx);							// �M�~�b�N�N��UI�̕\��

	// �Z�b�g�E�Q�b�g�֌W
	void SetType(const TYPE type);		// ��ނ̐ݒ菈��
	TYPE GetType(void);					// ��ނ̎擾����

	void SetCatDisp(const bool Set) { m_bCatDisp = Set; }	// �l�R�̕\���ݒ菈��
	void SetRatDisp(const bool Set) { m_bRatDisp = Set; }	// �l�Y�~�̕\���ݒ菈��
	void SetCatUse(const bool Set) { m_bCatUse = Set; }		// �N���\�̐ݒ菈��
	bool GetCatUse(void) { return m_bCatUse; }				// �N���\�̎擾����
	void SetRatUse(const bool Set) { m_bRatUse = Set; }		// �N���\�̐ݒ菈��
	bool GetRatUse(void) { return m_bRatUse; }				// �N���\�̎擾����
	void SetAction(const bool Set) { m_bAction = Set; }		// �N����Ԃ̐ݒ菈��
	bool GetAction(void) { return m_bAction; }				// �N����Ԃ̎擾����
	void SetAlpha(float fAlpha) { m_fAlpha = fAlpha; }		// �s�����x�̐ݒ菈��
	float GetAlpha(void) { return m_fAlpha; }				// �s�����x�̎擾����

	virtual D3DXVECTOR3 GetPosHead(void) { return NONE_D3DXVECTOR3; }
	virtual D3DXVECTOR3 GetPosToes(void) { return NONE_D3DXVECTOR3; }
	virtual void SlideOn(D3DXVECTOR3 /*pos*/, D3DXVECTOR3 /*move*/, CPlayer* /*pPlayer*/) {}

	// �ÓI�����o�֐�
	static CObstacle* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const TYPE type);		// ��������

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	TYPE m_type;		// ���
	CBillboard *m_pGimmickUI;
	CBillboard *m_pMultiGimmickUI[2];
	bool m_pGimmickUIFalse[MAX_PLAY];	//�S��[False]�̎���UI���폜����
	bool m_bCatUse;						//�L���N���ł��邩�ǂ���
	bool m_bCatDisp;					//�L�������₷���`��ɂ���
	bool m_bRatUse;						//�l�Y�~���N���ł��邩�ǂ���
	bool m_bRatDisp;					//�l�Y�~�������₷���`��ɂ���
	bool m_bAction;						//�N�����Ă��邩�ǂ���
	float m_fAlpha;						//�s�����x

	// ���X�g�\���֌W
	CObstacle* m_pPrev;	// �O�ւ̃|�C���^
	CObstacle* m_pNext;	// ���ւ̃|�C���^
};

#endif