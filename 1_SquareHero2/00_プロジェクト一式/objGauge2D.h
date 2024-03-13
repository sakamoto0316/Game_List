//============================================
//
//	�I�u�W�F�N�g�Q�[�W2D [objGauge2D.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _OBJGAUGE2D_H_
#define _OBJGAUGE2D_H_

#include "main.h"
#include "object.h"

//�I�u�W�F�N�g2D�N���X
class CObjGauge2D : public CObject
{
public:
	CObjGauge2D(int nPriority);
	~CObjGauge2D();

	static CObjGauge2D* Create(int nPriority = 4);

	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void BindTexture(LPDIRECT3DTEXTURE9 pTexture);

	void SetVerTex(void);							//���_���W�̐ݒ�
	void SetAnim(D3DXVECTOR2 Tex);					//�e�N�X�`�����W�̐ݒ�
	void SetScroll(D3DXVECTOR2 Tex);				//�e�N�X�`�����W�̐ݒ�
	void SetColor(D3DXCOLOR col);					//���_�J���[�̐ݒ�
	void SetTexture(const char* name);

	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	D3DXVECTOR3 GetPos(void) { return m_pos; }
	void SetRot(D3DXVECTOR3 rot) { m_rot = rot; }
	D3DXVECTOR3 GetRot(void) { return m_rot; }
	void SetWight(float Wight) { m_Wight = Wight; }
	float GetWight(void) { return m_Wight; }
	void SetHeight(float Height) { m_Height = Height; }
	float GetHeight(void) { return m_Height; }
	virtual void SetIdx(int Idx) { m_nIdxTexture = Idx; }
	virtual int GetIdx(void) { return m_nIdxTexture; }
	void SetAddDraw(bool Set) { m_AddDarw = Set; }
	void SetGaugeWight(float nCMax, float nCMeter);
	void SetNULL(void);

protected:
	void SetVtxBuff(LPDIRECT3DVERTEXBUFFER9 Height) { m_pVtxBuff = Height; }
	LPDIRECT3DVERTEXBUFFER9 GetVtxBuff(void) { return m_pVtxBuff; }

private:
	int m_nIdxTexture;
	float m_Wight;							//��
	float m_Ratio;							//����
	float m_Height;							//����
	bool m_AddDarw;							//�`��̎��ɉ��Z���������邩�ǂ���
	D3DXVECTOR3 m_pos;						//���_�̈ʒu
	D3DXVECTOR3 m_rot;						//����
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
};
#endif