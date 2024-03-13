//============================================================
//
// X�t�@�C���w�b�_�[ [xfile.h]
// Author�F��������
//
//============================================================
#ifndef _XFILE_H_	// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _XFILE_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------
#define INIT_VTX_MIN	(D3DXVECTOR3( 9999.0f,  9999.0f,  9999.0f))		// ���f���̍ŏ��̒��_���W�̏����l
#define INIT_VTX_MAX	(D3DXVECTOR3(-9999.0f, -9999.0f, -9999.0f))		// ���f���̍ő�̒��_���W�̏����l
#define INIT_SIZE		(D3DXVECTOR3(0.0f, 0.0f, 0.0f))					// ���f���T�C�Y�̏����l
#define INIT_RAT		(CXFile::TYPE_RAT_BODY)							// �l�Y�~���f���̊J�n�ʒu
#define INIT_CAT		(CXFile::TYPE_CAT_BODY)							// �L���f���̊J�n�ʒu
#define INIT_BLOCK		(CXFile::TYPE_CARDBOARD)						// �u���b�N���f���̊J�n�ʒu
#define INIT_OBSTACLE	(CXFile::TYPE_HONEYBOTTLE)						// ��Q�����f���̊J�n�ʒu
#define INIT_ENTRANCE	(CXFile::TYPE_ENTRANCE_FLOOR)					// ���փ��f���̊J�n�ʒu

//------------------------------------------------------------
// �N���X��`(X�t�@�C��)
//------------------------------------------------------------
class CXFile
{
public:			// �N�ł��A�N�Z�X�ł���

	//************************************************************
	//	�񋓌^��` (TYPE)
	//************************************************************
	enum TYPE
	{
		// �ʏ탂�f��
		TYPE_RIPPLE = 0,			// �g��
		TYPE_KARIPLAYER,			// ���v���C���[
		TYPE_WOODBLOCK,				// �ؔ�
		TYPE_WEAPONCAGE,			// ���포��
		TYPE_FLOWERFRAC,			// �ԕr�̔j��
		TYPE_PLASTICFRAC,			// �v���X�`�b�N�P�[�X�j��
		TYPE_CAT_ATTACK,			// �l�R�̍U��
		TYPE_HONEY,					// �I��
		TYPE_TOYCARSCREW,			// ��������̎�(�l�W)
		TYPE_TITLEWALL,				// �^�C�g���̕�
		TYPE_RED_ROOMBA_SUB,		// �����o�̃v���y��{�Ԃ̃A�E�g���C��}
		TYPE_TARAI,					// ���炢
		TYPE_RED_NOTE4,				// 4������{�Ԃ̃A�E�g���C��}
		TYPE_RED_NOTE8,				// 8������{�Ԃ̃A�E�g���C��}
		TYPE_RED_NOTE16,			// 16������{�Ԃ̃A�E�g���C��}
		TYPE_TRAPIRON,				// �l�Y�~�߂�̓S����
		TYPE_TRAPITEM,				// �l�Y�~�߂�(�A�C�e��)
		TYPE_RED_LEASHSET,			// �ݒu��Ԃ̃��[�h{�Ԃ̃A�E�g���C��}
		TYPE_RED_PINSET,			// �ݒu��Ԃ̉�e{�Ԃ̃A�E�g���C��}
		TYPE_PINONE,				// �j�Зp�̉�e
		TYPE_FANBLADE,				// ��@(�H��)
		TYPE_CONSENT,				// �R���Z���g
		TYPE_DEATHARROW,			// ���S���
		TYPE_GARBAGE,				// �S�~
		TYPE_BOOKBLUE,				// �{(��)
		TYPE_BOOKGREEN,				// �{(��)
		TYPE_BOOKYELLOW,			// �{(��)
		TYPE_LEVERBODY,				// ���o�[(�{��)
		TYPE_LEVERSTICK,			// ���o�[(�_)
		TYPE_RED_BOOKRED,			// �{(��){�Ԃ̃A�E�g���C��}
		TYPE_RED_BOOKBLUE,			// �{(��){�Ԃ̃A�E�g���C��}
		TYPE_RED_BOOKGREEN,			// �{(��){�Ԃ̃A�E�g���C��}
		TYPE_RED_BOOKYELLOW,		// �{(��){�Ԃ̃A�E�g���C��}
		TYPE_RED_TOYCARBODY,		// ��������̎�(�{��){�Ԃ̃A�E�g���C��}
		TYPE_RED_TOYCARSCREW,		// ��������̎�(�l�W){�Ԃ̃A�E�g���C��}
		TYPE_RED_HAIRBALL,			// �{{�Ԃ̃A�E�g���C��}
		TYPE_RED_PETBOTTLE,			// �y�b�g�{�g��{�Ԃ̃A�E�g���C��}

		// �u���b�N���f��
		TYPE_CARDBOARD,				// �i�{�[��
		TYPE_TISSUEBOX,				// �e�B�b�V����
		TYPE_PENHOLDER,				// �y������
		TYPE_REMOCON,				// �����R��
		TYPE_BEAR,					// �u���b�N
		TYPE_CLOCK,					// ���v
		TYPE_RUBBISH,				// �`����
		TYPE_MILKPACK,				// �����p�b�N
		TYPE_OBAPHONE,				// �I�o�t�H��
		TYPE_WII,					// Wii
		TYPE_DS,					// DS
		TYPE_HEADPHONE,				// �w�b�h�t�H��
		TYPE_PEN,					// �y��
		TYPE_ACADAPTER,				// AC�A�_�v�^�[
		TYPE_BUILDINGBLOCK,			// �ςݖ�
		TYPE_GLASSES,				// �ዾ�P�[�X
		TYPE_PENCIL,				// ���M
		TYPE_PICTUREFRAME,			// �ʐ^����
		TYPE_SHELF,					// �˒I
		TYPE_PULLSHELF,				// �����o���I
		TYPE_KITCHEN,				// �L�b�`��
		TYPE_REIZOUKO,				// �①��
		TYPE_TABLE,					// �e�[�u��
		TYPE_CHAIR,					// ���̈֎q
		TYPE_CORKBOARD,				// �R���N�{�[�h
		TYPE_DESK,					// �f�X�N
		TYPE_DESKBOOK,				// �f�X�N�p�̖{
		TYPE_EXTIMGISHER,			// ���Ί�
		TYPE_KATEN,					// �J�[�e��
		TYPE_KATENRAIL,				// �J�[�e���̃��[��
		TYPE_TANSU02,				// ����
		TYPE_TV_STAND,				// �e���r�̃X�^���h
		TYPE_WALL_PLUS50,			// 50*100�̕�
		TYPE_WALL_PLUS100,			// 100*100�̕�
		TYPE_DOOR001,				// �h�A
		TYPE_SMALL_SHELF,			// �����ȒI
		TYPE_BOOKSHELF,				// �����̖{�I
		TYPE_TALBESHELF,			// �e�[�u���̍����̒I
		TYPE_SOFA_SHEET,			// �\�t�@�[�i���ʁj
		TYPE_SOFA_BACKTEST,			// �\�t�@�[�i�w������j
		TYPE_CHAIR_SHEET,			// ���̈֎q(����)
		TYPE_CHAIR_BACKREST,		// ���̈֎q(�w������)
		TYPE_LEVERBODYBLOCK,		// ���o�[(�{��)
		TYPE_WINDOW,				// ��
		TYPE_WALLCLOCK,				// �Ǌ|�����v
		TYPE_INTERIOR000,			// �ǂ̃C���e���A(�I)
		TYPE_WALLCROSS,				// ����

		// ��Q�����f��
		TYPE_HONEYBOTTLE,			// �I���̃{�g��
		TYPE_SLIME,					// �X���C��
		TYPE_HAIRBALL,				// �{
		TYPE_PETBOTTLE,				// �y�b�g�{�g��
		TYPE_TOYCARBODY,			// ��������̎�(�{��)
		TYPE_RED_ROOMBA_MAIN,		// �����o�̖{��{�Ԃ̃A�E�g���C��}
		TYPE_HIMO,					// �Ђ�
		TYPE_SPEAKER,				// �X�s�[�J�[
		TYPE_MOUSETRAP,				// �l�Y�~�߂�
		TYPE_LEASH,					// ���[�h
		TYPE_PIN,					// ��e
		TYPE_ELECFAN,				// ��@(�{��)
		TYPE_CUP,					// �R�b�v
		TYPE_GARBAGECAN,			// �S�~��
		TYPE_TV,					// �e���r
		TYPE_DYNAMITE,				// ���e
		TYPE_BOOKRED,				// �{(��)
		TYPE_REDKATEN,				// �Ԃ̃J�[�e��
		TYPE_RATMECHA,				// �l�Y�~���J

		//�l�Y�~���f��
		TYPE_RAT_BODY,				// ��
		TYPE_RAT_HEAD,				// ��
		TYPE_RAT_LHAND,				// ����
		TYPE_RAT_RHAND,				// �E��
		TYPE_RAT_LLEG,				// ����
		TYPE_RAT_RLEG,				// �E��

		//�L���f��
		TYPE_CAT_BODY,				//��
		TYPE_CAT_HEAD,				//��
		TYPE_CAT_LARM,				//���r
		TYPE_CAT_LHAND,				//����
		TYPE_CAT_RAEM,				//�E�r
		TYPE_CAT_RHAND,				//�E��
		TYPE_CAT_LFOOT,				//����
		TYPE_CAT_LLEG,				//����
		TYPE_CAT_RFOOT,				//�E��
		TYPE_CAT_RLEG,				//�E��
		TYPE_CAT_FLAG,				//����

		// �l�Y�~���f��
		TYPE_RAT_GHOST,				// �H�샂�f��

		// 3D�e�L�X�g���f��
		TYPE_WINCAT_TEXT,			// �˂��̂����e�L�X�g
		TYPE_WINRAT_TEXT,			// �˂��݂̂����e�L�X�g

		// ���ւ̃��f��
		TYPE_ENTRANCE_FLOOR,		// ���ւ̏�
		TYPE_ENTRANCE_WALL,			// ���ւ̕�
		TYPE_SHOEBOX,				// �C��
		TYPE_ENTRANCE_DOOR,			// ���ւ̃h�A
		TYPE_ENTRANCE_FRONT,		// ���ւ̉��̕�
		TYPE_ENTRANCE_SHOEFLOOR,	// �C������̏�
		TYPE_ENTRANCE_SIDEWALL,		// ���̕�
		TYPE_BOOTS,					// �u�[�c
		TYPE_SANDAL,				// �T���_��
		TYPE_LESTHERSHOES,			// ���U�[�V���[�Y

		// �����蔻�胂�f��
		TYPE_COLLISION,				// �����蔻��̃G�f�B�b�g���f��

		// �G�f�B�b�g���f��
		TYPE_MAX,					// �S���f���̑���
	};

	//************************************************************
	//	�\���̒�` (SXFile)
	//************************************************************
	struct SXFile
	{
		LPD3DXMESH	 pMesh;						// ���b�V�� (���_���) �ւ̃|�C���^
		LPD3DXBUFFER pBuffMat;					// �}�e���A���ւ̃|�C���^
		DWORD		 dwNumMat;					// �}�e���A���̐�
		D3DXVECTOR3	 vtxMin;					// �ŏ��̒��_���W
		D3DXVECTOR3	 vtxMax;					// �ő�̒��_���W
		D3DXVECTOR3	 collsize;					// �����蔻��̃T�C�Y
		float		 fRadius;					// ���a
		int			 m_nTexIdx[MAX_MATERIAL];	// �e�N�X�`���̃C���f�b�N�X
	};

	CXFile();			// �R���X�g���N�^
	~CXFile();			// �f�X�g���N�^

	// �����o�֐�
	static HRESULT Init(void);		// X�t�@�C���̏���������
	static void Uninit(void);		// X�t�@�C���̏I������

	// �Z�b�g�E�Q�b�g�֐�
	static SXFile GetXFile(TYPE type);	// X�t�@�C���̎擾����

private:

	// �����o�֐�
	static HRESULT LoadXFile(void);		// x�t�@�C���̓ǂݍ���
	static void SetCollision(void);		// �����蔻��̍쐬
	static HRESULT LoadTexture(void);	// �e�N�X�`���̓ǂݍ���

	// �ÓI�����o�ϐ�
	static const char *c_apModelData[CXFile::TYPE_MAX];			// ���f���̖��O
	static SXFile m_apModel[CXFile::TYPE_MAX];					// ���f���̏��
};

#endif