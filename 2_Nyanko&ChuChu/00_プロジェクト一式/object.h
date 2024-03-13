//============================================
//
// �I�u�W�F�N�g�w�b�_�[[object.h]
// Author�F��������
//
//============================================
#ifndef _OBJECT_H_		//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "main.h"

//--------------------------------------------
// �N���X(�I�u�W�F�N�g�N���X)
//--------------------------------------------
class CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// ���
	enum TYPE
	{
		TYPE_NONE = 0,			// ����
		TYPE_SCENE,				// �V�[��
		TYPE_TITLELOGO,			// �^�C�g��
		TYPE_PRESSENTER,		// �v���X�G���^�[
		TYPE_EDITUI,			// �G�f�B�b�gUI
		TYPE_2DUI,				// 2DUI
		TYPE_TIME,				// �^�C��
		TYPE_STUN,				// �C��
		TYPE_SKYBOX,			// �X�J�C�{�b�N�X
		TYPE_SHADOW,			// �e
		TYPE_SCORE,				// �X�R�A
		TYPE_RIPPLE,			// �g��
		TYPE_RANKINGWORD,		// �����L���O�̕���
		TYPE_RANKINGTABLE,		// ������X�R�A
		TYPE_RANKINGPRECE,		// ����
		TYPE_PAUSE,				// �|�[�Y
		TYPE_ORBIT,				// �O��
		TYPE_FIELD,				// �n��
		TYPE_3DPOLYGON,			// 3D�|���S��
		TYPE_NEWRECORD,			// �V�L�^
		TYPE_MESH,				// ���b�V��
		TYPE_LOGOMARK,			// ���S�}�[�N
		TYPE_LOCUS,				// �c��
		TYPE_FRACTION,			// �j��
		TYPE_EFFECT,			// �G�t�F�N�g
		TYPE_DESTRUCTION,		// ���g
		TYPE_COLLPOLY,			// �����蔻��|���S��
		TYPE_CHARA,				// �L�����N�^�[
		TYPE_PLAYER,			// �v���C���[
		TYPE_OBSTACLE,			// ��Q��
		TYPE_EDIT,				// �G�f�B�b�g
		TYPE_WEAPONSELECTUI,	// ����I�����UI
		TYPE_WEAPONCAGE,		// ���포��
		TYPE_WEAPONBALLOON,		// ����̂ӂ�����
		TYPE_BLOCK,				// �u���b�N
		TYPE_MAP,				// �}�b�v
		TYPE_SLASH,				// �a�����o
		TYPE_PLAYERID,			// �v���C���[��ID
		TYPE_COUNTDOWN,			// �J�E���g�_�E��
		TYPE_TITLEWALL,			// �^�C�g���̕�
		TYPE_ENTRYUI,			// �G���g���[UI
		TYPE_ENTRYRANDOM,		// �G���g���[�̃����_���w��
		TYPE_3DTEXT,			// 3D�e�L�X�g
		TYPE_DANGERMARK,		// �댯�}�[�N
		TYPE_ITEM,				// �A�C�e��
		TYPE_CHARAINFO,			// �L�����N�^�[�̏��UI
		TYPE_WATER,				// ��
		TYPE_FINISHUI,			// �I���J�E���g�_�E����UI
		TYPE_CONFETTI,			// ������
		TYPE_RECOVERINGUI,		// �񕜒���UI
		TYPE_ITEMUI,			// �A�C�e��UI
		TYPE_DEATHARROW,		// ���S���
		TYPE_ENTRYMESSAGEUI,	// �G���g���[�̐���UI
		TYPE_ENTRYBG,			// �G���g���[��ʂ̔w�i
		TYPE_SCREENFRAME,		// ��ʂ̘g
		TYPE_MAX				// ���̗񋓌^�̑���
	};

	// �D�揇��
	enum PRIORITY
	{
		PRIORITY_BG = 0,			// �w�i�֌W
		PRIORITY_BLOCK,				// �u���b�N�E��Q���n
		PRIORITY_EFFECT,			// �G�t�F�N�g�n
		PRIORITY_SHADOW,			// �e�֌W
		PRIORITY_ENTITY,			// �G�E�A�C�e���֌W
		PRIORITY_PLAYER,			// �v���C���[�֌W
		PRIORITY_UI,				// UI�֌W
		PRIORITY_PAUSE,				// �|�[�Y(��ΑO�ɏo�����)
		PRIORITY_MAX				// ���̗񋓌^�̑���
	};

	CObject();													// �R���X�g���N�^
	CObject(TYPE type, PRIORITY priority = PRIORITY_ENTITY);	// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CObject();											// �f�X�g���N�^

	// �����o�֐�
	virtual HRESULT Init(void) = 0;	// ����������
	virtual void Uninit(void) = 0;	// �I������
	virtual void Update(void) = 0;	// �X�V����
	virtual void Draw(void) = 0;	// �`�揈��

	// �Z�b�g�E�Q�b�g�֌W
	static CObject* GetTop(PRIORITY priority);		// �I�u�W�F�N�g�̎擾����

	CObject* GetNext(void);				// ���̃|�C���^�̎擾����

	void SetType(const TYPE type);		// ��ނ̐ݒ菈��
	TYPE GetType(void) const;			// ��ނ̎擾����

	static int GetDrawIdx(void) { return m_DrawIdx; }

	// �ÓI�����o�֐�
	static void ReleaseAll(void);		// �S�Ă̔j������
	static void UpdateAll(void);		// �S�Ă̍X�V����
	static void DrawAll(void);			// �S�Ă̕`�揈��

	static void AnyAllClear(const TYPE type);		// �ėp�I�ȑS��������
	static void AnyAllClear(const PRIORITY priority, const TYPE type);		// �ėp�I�ȑS��������
	static void DeathDecision(const int nCnt);		// ���S���ʏ���

	static void UpdateNormal(void);		// �ʏ�X�V����
	static void UpdateCountdown(void);	// �J�E���g�_�E�����̍X�V����
	static void UpdateGame(void);		// �Q�[���̍X�V����

	static void DrawNormal(void);		// �ʏ�`�揈��
	static void DrawGame(void);			// �Q�[���̕`�揈��

protected:		// �����Ɣh���N���X�������A�N�Z�X�ł���

	// �����o�֐�
	void Release(void);					// �j������

private:		// ���������A�N�Z�X�ł���

	// �����o�֐�
	void Death(void);					// ���S����

	// �����o�ϐ�
	CObject* m_pPrev;					// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject* m_pNext;					// ���̃I�u�W�F�N�g�ւ̃|�C���^
	TYPE m_type;						// ���
	PRIORITY m_priority;				// �I�u�W�F�N�g�̗D�揇��
	bool m_bDeath;						// ���S�t���O
	static int m_DrawIdx;				// �`��ԍ�
	
	// �ÓI�����o�ϐ�
	static CObject* m_apTop[PRIORITY_MAX];				// �擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject* m_apCur[PRIORITY_MAX];				// �Ō���I�u�W�F�N�g�ւ̃|�C���^
	static int m_nNumAll;								// �I�u�W�F�N�g�̑���
};

#endif