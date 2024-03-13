//======================================================================================================================
//
// ���b�V���w�b�_�[ [mesh.h]
// Author�F��������
//
//======================================================================================================================
#ifndef _MESH_H_			// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _MESH_H_			// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"
#include "objectX.h"

// �N���X��`(���b�V��)
class CMesh : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	// �\���̒�`(������)
	struct SGrid
	{
		int x;			// �ʒu(X��)
		int y;			// �ʒu(Y��)
		int z;			// �ʒu(Z��)
	};

	// �񋓌^��`(���)
	enum TYPE
	{
		TYPE_FIELD = 0,		// �t�B�[���h
		TYPE_WALL,			// ��
		TYPE_CYLINDER,		// ��
		TYPE_DOME,			// �h�[��
		TYPE_MAX			// ���̗񋓌^�̑���
	};

	CMesh();			// �R���X�g���N�^
	CMesh(CObject::TYPE type, CObject::PRIORITY priority = PRIORITY_BG);			// �I�[�o�[���[�h�R���X�g���N�^
	virtual ~CMesh();	// �f�X�g���N�^
	void Box(void);		// �R���X�g���N�^�̔�

	// ���X�g�\���֌W
	void SetPrev(CMesh* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CMesh* pNext);	// ��̃|�C���^�̐ݒ菈��
	CMesh* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CMesh* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	virtual HRESULT Init(void);		// ����������
	virtual void Uninit(void);		// �I������
	virtual void Update(void);		// �X�V����
	virtual void Draw(void);		// �`�揈��

	void DrawProcess(void);			// �`�揈���̒��g

	void SetDataField(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const SGrid& Divi);			// �t�B�[���h�̏��ݒ菈��
	void SetDataWall(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const SGrid& Divi);			// �ǂ̏��ݒ菈��
	void SetDataCylinder(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize, const int nCircum, const int nHeight);			// ���̏��ݒ菈��
	void SetDataDome(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fCircumSize, const float fHeightSize, const int nCircum, const int nHeight);				// �h�[���̏��ݒ菈��

	void SetVertexField(void);		// �t�B�[���h�̐ݒ菈��
	void SetVertexWall(void);		// �ǂ̐ݒ菈��
	void SetVertexCylinder(void);	// ���̐ݒ菈��
	void SetVertexDome(void);		// �h�[���̐ݒ菈��

	void SetVtxColor(const D3DXCOLOR& col);			// ���_�J���[�̐ݒ菈��

	void SetIndex(const int nNumVtx1, const int nNumVtx2);		// �C���f�b�N�X�̐ݒ菈��

	void BindTexture(int nIdx);		// �e�N�X�`���̊��蓖�ď���

	// �Z�b�g�E�Q�b�g�֌W
	void SetPos(const D3DXVECTOR3& pos);		// �ʒu�̐ݒ菈��
	D3DXVECTOR3 GetPos(void) const;				// �ʒu�̎擾����

	void SetRot(const D3DXVECTOR3& rot);		// �����̐ݒ菈��
	D3DXVECTOR3 GetRot(void) const;				// �����̎擾����

	void SetSize(const D3DXVECTOR3& size);		// �g�嗦�̐ݒ菈��
	D3DXVECTOR3 GetSize(void) const;			// �g�嗦�̎擾����

	void SetLighting(const bool bLighting);		// ���C�e�B���O�̐ݒ菈��

	// �ÓI�����o�ϐ�
	static CMesh* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const D3DXVECTOR3& size, const SGrid& Divi, const TYPE type, char* texturename, const bool bLighting);		// ��������
	static void TxtSet(void);					// �e�L�X�g�ǂݍ��ݏ���

private:		// ���������A�N�Z�X�ł���

	// �����o�ϐ�
	D3DXVECTOR3	m_pos;			// �ʒu
	D3DXVECTOR3	m_rot;			// ����
	D3DXVECTOR3	m_size;			// �T�C�Y
	D3DXVECTOR3	m_sizeDivi;		// 1������̖ʂ̃T�C�Y
	D3DXMATRIX	m_mtxWorld;		// ���[���h�}�g���b�N�X
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		// ���_�o�b�t�@�̃|�C���^
	LPDIRECT3DINDEXBUFFER9  m_pIdxBuff;		// �C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	TYPE	m_type;				// ���
	SGrid	m_vtx;				// ���_��
	SGrid	m_divi;				// ������
	int		m_nNumVtx;			// �����_��
	int		m_nNumIdx;			// ���C���f�b�N�X��
	int		m_nTexIdx;			// �e�N�X�`���̃C���f�b�N�X
	bool	m_bLightOff;		// ���C�e�B���O��

	// ���X�g�\���֌W
	CMesh* m_pPrev;	// �O�ւ̃|�C���^
	CMesh* m_pNext;	// ���ւ̃|�C���^
};


#endif