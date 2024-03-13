//============================================
//
//	�I�u�W�F�N�g���b�V���L���[�u [objmeshCube.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _OBJMESHCUBE_H_
#define _OBJMESHCUBE_H_

#include "main.h"
#include "object.h"

//�I�u�W�F�N�g���b�V���t�B�[���h�N���X
class CObjmeshCube : public CObject
{
public:
	CObjmeshCube(int nPriority = 4);
	~CObjmeshCube();

	static CObjmeshCube* Create(void);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);

	void SetVerPos(D3DXVECTOR3 Pos0, D3DXVECTOR3 Pos1, D3DXVECTOR3 Pos2, D3DXVECTOR3 Pos3);	//���_���W�̐ݒ�
	void SetVerSize(void);																	//���_�ʒu�̐ݒ�
	void SetAnim(D3DXVECTOR2 Tex);															//�e�N�X�`�����W�̐ݒ�
	void SetColor(D3DXCOLOR col);															//���_�J���[�̐ݒ�
	void SetColorType(int Type);															//���_�J���[�̐ݒ�
	D3DXCOLOR GetColor(void) { return m_Color; }											//���_�J���[�̎擾
	void SetColorA(float A) { m_Color.a = A; SetColor(m_Color); }							//���_�s�����x�̐ݒ�
	void SetTexture(const char* name);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; m_posOld = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetUninitPos(D3DXVECTOR3 pos) { UninitPos = pos; }
	D3DXVECTOR3 GetUninitPos(void) { return UninitPos; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetSize(D3DXVECTOR3 Size) { m_Size = Size; SetVerSize(); }
	D3DXVECTOR3 GetSize(void) { return m_Size; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }
	virtual int GetIdx(void) { return m_nIdxTexture; }
	void SetPlusMove(bool Set) { m_PlusMove = Set; }
	bool GetPlusMove(void) { return m_PlusMove; }
	void SetBoolLife(bool Set) { m_bLife = Set; }
	bool GetBoolLife(void) { return m_bLife; }
	void SetLife(int Life) { m_nLife = Life; }
	int GetLife(void) { return m_nLife; }
	void SetDel(float Del) { m_fDel = Del; }

protected:
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 g_pIdxBuff;		//�C���f�b�N�X�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

private:
	int m_nIdxTexture;
	D3DXVECTOR3 m_pos;						//���݂̈ʒu
	D3DXVECTOR3 m_posOld;					//�ߋ��̈ʒu
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_Size;						//�傫��
	D3DXVECTOR3 m_move;						//�ړ���
	D3DXCOLOR m_Color;						//�F
	bool m_PlusMove;						//���̕����ֈړ����Ă��邩�ǂ���
	bool m_bLife;							//������L���[�u���ۂ�
	D3DXVECTOR3 UninitPos;					//�L���[�u�̍폜�ʒu
	int m_nLife;							//�L���[�u�̎���
	float m_fDel;							//�L���[�u�̐F�̌�����
};
#endif