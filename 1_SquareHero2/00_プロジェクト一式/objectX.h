//============================================
//
//	�I�u�W�F�N�gX�t�@�C�� [objectX.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _OBJECTX_H_
#define _OBJECTX_H_

#include "main.h"
#include "object.h"

//�I�u�W�F�N�gX�N���X
class CObjectX : public CObject
{
public:
	CObjectX(int nPriority = 7);
	~CObjectX();

	static CObjectX *Create(char *pModelName);

	virtual HRESULT Init(void);
	virtual HRESULT Init(char* pModelName);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void Draw(float fAlpha);
	void BindFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD pdwNumMat);

	void SetVerTex(void);							//���_���W�̐ݒ�
	void SetAnim(D3DXVECTOR2 Tex);					//�e�N�X�`�����W�̐ݒ�
	void SetColor(D3DXCOLOR col);					//���_�J���[�̐ݒ�

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetPosOld(D3DXVECTOR3 pos) { m_posOld = pos; }
	D3DXVECTOR3 GetPosOld(void) { return m_posOld; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetWight(float Wight) { m_Wight = Wight; }
	float GetWight(void) { return m_Wight; }
	void SetHeight(float Height) { m_Height = Height; }
	float GetHeight(void) { return m_Height; }
	void SetMatColor(D3DXCOLOR SetColor) { m_MatColor = SetColor; m_bUseColor = true; }
	void SetMatAlpha(float SetAlpha) { m_StateMat.MatD3D.Diffuse.a = SetAlpha; }
	void SetDefColor(void) { m_bUseColor = false; }
	void SetScaling(D3DXVECTOR3 Scaling) { m_Scaling = Scaling; }

	void SetXModelIdx(int Idx);
	int GetXModelIdx(void) { return m_IdxModelNumber; }
	void SetTextureIdx(int nCnt, int Idx);
	int GetTextureIdx(int nCnt) { return m_IdxTextureNumber[nCnt]; }

protected:
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X

private:
	int m_IdxModelNumber;					//���f���̔ԍ�
	int m_IdxTextureNumber[64];				//�e�N�X�`���̔ԍ�
	float m_Wight;							//��
	float m_Height;							//����
	LPDIRECT3DTEXTURE9 *m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPD3DXMESH m_pMesh;						//���b�V��(���_���)�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;				//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;						//�}�e���A���̐�
	D3DXVECTOR3 m_pos;						//���_�̈ʒu
	D3DXVECTOR3 m_posOld;					//�ߋ��̈ʒu
	D3DXVECTOR3 m_rot;						//����
	D3DXVECTOR3 m_Scaling;					//�傫��
	D3DXMATERIAL m_StateMat;				//��ԊǗ����̐F
	D3DXCOLOR m_MatColor;					//�}�e���A���̐F
	bool m_bUseColor;						//�F��ύX���Ă��邩�ǂ���
};
#endif