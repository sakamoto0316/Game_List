//===================================
//
// ���O�w�b�_�[[log.h]
// Author ��{�ėB
//
//===================================
#ifndef _LOG_H_
#define _LOG_H_

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
class CObject2D;
class CPlayer;

//-----------------------------------
// �N���X��`(�T���v��)
//-----------------------------------
class CLog : public CObject/*�e�N���X*/
{
public:			// �N�ł��A�N�Z�X�ł���

	CLog(int nPriority = 5);				// �R���X�g���N�^
	~CLog();			// �f�X�g���N�^

	enum STATE
	{
		STATE_IN = 0,
		STATE_DOWN,
		STATE_OUT,
		STATE_MAX,
	};

	enum TEXT
	{
		TEXT_00 = 0,	//�{�X���s���N�F�̎��͋߂Â�������Ȃ�
		TEXT_01,		//��̓���̃����O�ɂ͓�����Ȃ��ق����ǂ���������
		TEXT_02,		//��������I�H
		TEXT_03,		//�U���͒n��Ō���U���������_���[�W��������
		TEXT_04,		//�ԂƃI�����W�̃u���b�N�͐G���ƃ_���[�W�����炤��
		TEXT_05,		//��𒆂͖��G��ԂƂȂ�f�����ړ��ł��邼
		TEXT_06,		//���̂܂܂��Ɨ��Ƃ���邼
		TEXT_07,		//�ォ�痈�邼�I�]�g�ɂ����ӂ���I
		TEXT_08,		//��Âɉe������Ώ\�����킹���
		TEXT_09,		//L�X�e�B�b�N�ňړ�R�X�e�B�b�N�Ŏ��_���삾�I
		TEXT_10,		//�W�����v�ŕǂ����z���悤
		TEXT_11,		//�G���I�U���œ|�����I
		TYPE_MAX,
	};

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(CLog::TEXT Type);		// ���̐ݒ菈��
	void SetLogIdx(int nIdx) { m_nLogIdx = nIdx; }

	void SetMain(CPlayer *pMain) { m_pMain = pMain; }		// �����̎����g�p���Ă���I�u�W�F�N�g�̃|�C���^��ݒ肷��
	void DelCreateNumber(void) { m_CreateNumber--; }

	// �ÓI�����o�֐�
	static CLog* Create(CLog::TEXT Type);		// ��������
	static void InitCreateMax(void) { m_CreateMax = -1; }		// ��������

private:		// ���������A�N�Z�X�ł���
	void StateManager(void);
	bool DelNumber(void);		//�����ԍ��̏C��

	D3DXVECTOR3 LogPos;			// ���O�S�̂̈ʒu
	int m_CreateNumber;			// ���Ԗڂ̐����̃��O��
	static int m_CreateMax;		// �����̃��O���������邩
	STATE m_State;				// ���
	int m_nLife;				// ����
	int m_nLogIdx;				// ���O�̎g�p�ԍ�
	float m_fLogStopPosY;		// ���O����~����ʒu
	TEXT m_Type;				// ���O�̎��
	CObject2D *m_pLogBG;		// ���O�̔w�i�p�[�c
	CObject2D *m_pLogPlayerBG;	// ���O�̃v���C���[ID�p�[�c
	CObject2D *m_pLogMessage;	// ���O�̓��e�p�[�c
	CPlayer *m_pMain;			// �����̎����g�p���Ă���I�u�W�F�N�g�̃|�C���^
};
#endif