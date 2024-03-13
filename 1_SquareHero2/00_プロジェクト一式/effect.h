//============================================
//
//	�G�t�F�N�g���� [effect.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"
#include "objectBillboard.h"

//�I�u�W�F�N�g�v���C���[�N���X
class CEffect : public CObjectBillboard
{
public:

	CEffect(int nPriority = 4);
	~CEffect();

	static CEffect *Create();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	D3DXVECTOR3 GetMove(void) { return m_move; }
	void SetRadius(float Radius) { m_fRadius = Radius; }
	float GetRadius(void) { return m_fDel; }
	void SetDel(float Del) { m_fDel = Del; }
	float GetDel(void) { return m_fDel; }
	D3DXCOLOR GetColer(void) { return m_col; }
	void SetLife(int Life) { m_nLife = Life; m_nLifeMax = Life; }
	int GetLife(void) { return m_nLife; }
	int GetIdx(void) { return m_nIdxTexture; }
	void SetTexName(char *Name) { m_cTexName = Name; }

private:
	int m_nIdxTexture;						//�e�N�X�`���̔ԍ�
	static LPDIRECT3DTEXTURE9 m_pTexture;	//���L�e�N�X�`���ւ̃|�C���^
	D3DXVECTOR3 m_move;						//�ړ���
	float m_fRadius;						//���a(�傫��)
	float m_fDel;							//���a�����������Ă����l
	D3DXCOLOR m_col;						//�F
	int m_nLifeMax;							//�����̍ő�l
	int m_nLife;							//����
	char *m_cTexName;
};
#endif