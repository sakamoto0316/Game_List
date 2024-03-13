//======================================================================================================================
//
// �N���n�ʃw�b�_�[ [mesh_elevation.h]
// Author�F��������
//
//======================================================================================================================
#ifndef _MESH_ELEVATION_H_			// ���̃}�N����`������Ă��Ȃ��ꍇ
#define _MESH_ELEVATION_H_			// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//-----------------------------------------------------
// �N���X��`(�N���n��)
//-----------------------------------------------------
class CElevation : public CObject
{
public:			// �N�ł��A�N�Z�X�ł���

	CElevation();		// �R���X�g���N�^
	~CElevation();		// �f�X�g���N�^

	// ���X�g�\���֌W
	void SetPrev(CElevation* pPrev);	// �O�̃|�C���^�̐ݒ菈��
	void SetNext(CElevation* pNext);	// ��̃|�C���^�̐ݒ菈��
	CElevation* GetPrev(void) const;	// �O�̃|�C���^�̐ݒ菈��
	CElevation* GetNext(void) const;	// ���̃|�C���^�̐ݒ菈��

	// �����o�֐�
	HRESULT Init(void);		// ����������
	void Uninit(void);		// �I������
	void Update(void);		// �X�V����
	void Draw(void);		// �`�揈��

	void SetData(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fSizeX, const float fSizeZ, const int nDiviX, const int nDiviZ);			// ���̐ݒ菈��

	void SetVertex(void);		// �t�B�[���h�̐ݒ菈��
	void SetNormalize(void);	// �@���̐ݒ菈��
	void SetIndex(void);		// �C���f�b�N�X�̐ݒ菈��
	float ElevationCollision(const D3DXVECTOR3& pos);					// �N���̓����蔻��
	float ElevationCollision(const D3DXVECTOR3& pos, bool& bRange);		// �N���̓����蔻��(�͈͔���t��)
	int NearVertexSearch(const D3DXVECTOR3& pos);			// �߂��̒��_��T������

	void BindTexture(int nIdx);		// �e�N�X�`���̊��蓖�ď���

	// �Z�b�g�E�Q�b�g�֌W
	D3DXVECTOR3 GetPos(void) const;			// �ʒu�̎擾����
	D3DXVECTOR3 GetSize(void) const;		// �T�C�Y�̎擾����
	int GetVtxX(void) const;				// X���̒��_���̎擾����
	int GetVtxZ(void) const;				// Z���̒��_���̎擾����
	int GetVtxNum(void) const;				// �S���_���̎擾����
	void SetVtxHeight(const int nNum, const float fHeight);	// ���_�̐ݒ菈��
	void AddVertex(const int nNum, const float fAdd);		// ���_�̉��Z����

	// �ÓI�����o�ϐ�
	static CElevation* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& rot, const float fSizeX, const float fSizeZ, const int nDiviX, const int nDiviZ, char* texturename);		// ��������
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
	int		m_nVtxX;			// ���̒��_��
	int		m_nVtxZ;			// ���s�̒��_��
	int		m_nDiviX;			// ���̕�����
	int		m_nDiviZ;			// ���s�̕�����
	int		m_nNumVtx;			// �����_��
	int		m_nNumIdx;			// ���C���f�b�N�X��
	int		m_nTexIdx;			// �e�N�X�`���̃C���f�b�N�X

	// ���X�g�\���֌W
	CElevation* m_pPrev;	// �O�ւ̃|�C���^
	CElevation* m_pNext;	// ���ւ̃|�C���^
};


#endif