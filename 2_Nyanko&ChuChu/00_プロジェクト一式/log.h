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

	CLog();				// �R���X�g���N�^
	~CLog();			// �f�X�g���N�^

	enum STATE
	{
		STATE_IN = 0,
		STATE_DOWN,
		STATE_OUT,
		STATE_MAX,
	};

	enum TYPE
	{
		TYPE_DEATH = 0,
		TYPE_STUN,
		TYPE_REVIVAL,
		TYPE_MAX,
	};

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(int DrawIdx, int LogIdx, int nCreateNumber, CLog::TYPE Type);		// ���̐ݒ菈��
	void SetLogIdx(int nIdx) { m_nLogIdx = nIdx; }

	void SetMain(CPlayer *pMain) { m_pMain = pMain; }		// �����̎����g�p���Ă���I�u�W�F�N�g�̃|�C���^��ݒ肷��
	void DelCreateNumber(void) { m_CreateNumber--; }

	// �ÓI�����o�֐�
	static CLog* Create(int DrawIdx, int LogIdx, int nCreateNumber, CLog::TYPE Type);		// ��������

private:		// ���������A�N�Z�X�ł���
	void StateManager(void);

	D3DXVECTOR3 LogPos;			// ���O�S�̂̈ʒu
	int m_nPlayerNumber;		// �ǂ̃v���C���[�̃��O��
	int m_CreateNumber;			// ���Ԗڂ̐����̃��O��
	STATE m_State;				// ���
	int m_nLife;				// ����
	int m_nLogIdx;				// ���O�̎g�p�ԍ�
	float m_fLogStopPosY;			// ���O����~����ʒu
	TYPE m_Type;				// ���O�̎��
	CObject2D *m_pLogBG;		// ���O�̔w�i�p�[�c
	CObject2D *m_pLogPlayerID;	// ���O�̃v���C���[ID�p�[�c
	CObject2D *m_pLogMessage;	// ���O�̓��e�p�[�c
	CPlayer *m_pMain;			// �����̎����g�p���Ă���I�u�W�F�N�g�̃|�C���^
};
#endif