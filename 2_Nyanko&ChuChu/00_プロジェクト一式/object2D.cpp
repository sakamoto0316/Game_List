//============================================
//
// �I�u�W�F�N�g2D�̃��C������[object2D.cpp]
// Author�F��������
//
//============================================
//********************************************
// �C���N���[�h�t�@�C��
//********************************************
#include "object2D.h"
#include "renderer.h"
#include "manager.h"
#include "objectAnim.h"
#include "objectScroll.h"
#include "texture.h"

//=========================================
// �R���X�g���N�^
//=========================================
CObject2D::CObject2D() : CObject(CObject::TYPE_NONE, CObject::PRIORITY_BG)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �I�[�o�[���[�h�R���X�g���N�^
//=========================================
CObject2D::CObject2D(CObject::TYPE type, PRIORITY priority) : CObject(type, priority)
{
	// �R���X�g���N�^�̔�
	Box();
}

//=========================================
// �f�X�g���N�^
//=========================================
CObject2D::~CObject2D()
{

}

//=========================================
// �R���X�g���N�^�̔�
//=========================================
void CObject2D::Box(void)
{
	// �S�Ă̒l���N���A����
	m_pVtxBuff = nullptr;		// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_posOld = m_pos;							// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
	m_fAngle = 0.0f;							// ����
	m_fLength = 0.0f;							// ����
	m_nTexIdx = NONE_TEXIDX;					// �e�N�X�`���̃C���f�b�N�X
}

//===========================================
// �I�u�W�F�N�g2D�̏���������
//===========================================
HRESULT CObject2D::Init(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL)))
	{ // �o�b�t�@�̐����Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �S�Ă̒l������������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu
	m_posOld = m_pos;							// �O��̈ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// ����
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
	m_fAngle = 0.0f;							// ����
	m_fLength = 0.0f;							// ����

	// ���_���̐ݒ菈��
	SetVertexAll();

	if (m_pVtxBuff == nullptr)
	{ // ���_�o�b�t�@�̃|�C���^��NULL�̏ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �l��Ԃ�
	return S_OK;
}

//===========================================
// �I�u�W�F�N�g2D�̏I������
//===========================================
void CObject2D::Uninit(void)
{
	if (m_pVtxBuff != nullptr)
	{ // ���_�o�b�t�@�̔j��

		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}

	// �j������
	Release();
}

//===========================================
// �I�u�W�F�N�g2D�̍X�V����
//===========================================
void CObject2D::Update(void)
{
	// ���_�ݒ菈��
	SetVertexRot();

	// �e�N�X�`���̐ݒ菈��
	SetVtxTexture();
}

//===========================================
// �I�u�W�F�N�g2D�̕`�揈��
//===========================================
void CObject2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0,
		m_pVtxBuff,								// ���_�o�b�t�@�ւ̃|�C���^
		0,
		sizeof(VERTEX_2D));						// ���_���\���̂̃T�C�Y

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CManager::Get()->GetTexture()->GetAddress(m_nTexIdx));

	//�|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	// �v���~�e�B�u�̎��
		0,										// �`�悷��ŏ��̒��_�C���f�b�N�X
		2);										// �`�悷��v���~�e�B�u��
}

//===========================================
// �e�N�X�`���̊��蓖�ď���
//===========================================
void CObject2D::BindTexture(const int nIdx)
{
	// �e�N�X�`�������蓖�Ă�
	m_nTexIdx = nIdx;
}

//===========================================
// �ʒu�ݒ菈��
//===========================================
void CObject2D::SetPos(const D3DXVECTOR3& pos)
{
	// �ʒu��ݒ肷��
	m_pos = pos;
}

//===========================================
// �ʒu�擾����
//===========================================
D3DXVECTOR3 CObject2D::GetPos(void) const
{
	// �ʒu��Ԃ�
	return m_pos;
}

//===========================================
// �O��̈ʒu�ݒ菈��
//===========================================
void CObject2D::SetPosOld(const D3DXVECTOR3& posOld)
{
	// �O��̈ʒu��ݒ肷��
	m_posOld = posOld;
}

//===========================================
// �O��̈ʒu�擾����
//===========================================
D3DXVECTOR3 CObject2D::GetPosOld(void) const
{
	// �O��̈ʒu��Ԃ�
	return m_posOld;
}

//===========================================
// �����ݒ菈��
//===========================================
void CObject2D::SetRot(const D3DXVECTOR3& rot)
{
	// ������ݒ肷��
	m_rot = rot;
}

//===========================================
// �����擾����
//===========================================
D3DXVECTOR3 CObject2D::GetRot(void) const
{
	// ������Ԃ�
	return m_rot;
}

//===========================================
// �T�C�Y�ݒ菈��
//===========================================
void CObject2D::SetSize(const D3DXVECTOR3& size)
{
	// �T�C�Y��ݒ肷��
	m_size = size;
}

//===========================================
// �T�C�Y�擾����
//===========================================
D3DXVECTOR3 CObject2D::GetSize(void) const
{
	// �T�C�Y��Ԃ�
	return m_size;
}

//===========================================
// �����ݒ菈��
//===========================================
void CObject2D::SetLength(void)
{
	//�Ίp���̒������Z�o����
	m_fLength = sqrtf((m_size.x * 2) * (m_size.x * 2) + (m_size.y * 2) * (m_size.y * 2)) * 0.5f;
}

//===========================================
// �����ݒ菈��
//===========================================
float CObject2D::GetLength(void) const
{
	// ������Ԃ�
	return m_fLength;
}

//===========================================
// �����ݒ菈��
//===========================================
void CObject2D::SetAngle(void)
{
	//�Ίp���̊p�x���Z�o����
	m_fAngle = atan2f((m_size.x * 2), (m_size.y * 2));
}

//===========================================
// �����ݒ菈��
//===========================================
float CObject2D::GetAngle(void) const
{
	// ������ݒ肷��
	return m_fAngle;
}

//===========================================
// �e�N�X�`���̃C���f�b�N�X�̎擾����
//===========================================
int CObject2D::GetTexIdx(void) const
{
	// �e�N�X�`���̃C���f�b�N�X��Ԃ�
	return m_nTexIdx;
}

//===========================================
// �e�N�X�`���̃C���f�b�N�X�̎擾����
//===========================================
char *CObject2D::GetTexName(void)
{
	// �e�N�X�`���̃C���f�b�N�X��Ԃ�
	return CManager::Get()->GetTexture()->GetTexName(m_nTexIdx);
}

//===========================================
// ���_���̐ݒ�
//===========================================
void CObject2D::SetVertex(void)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_���̐ݒ�(�X���L�胔�@�[�W����)
//===========================================
void CObject2D::SetVertexRot(void)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_���̐ݒ�(���Q�[�W�\���o�[�W����)
//===========================================
void CObject2D::SetVtxWidthGage(void)
{
	VERTEX_2D* pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_���̐ݒ�(�����S�Q�[�W�\���o�[�W����)
//===========================================
void CObject2D::SetVtxUnderHeightGage(void)
{
	VERTEX_2D* pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_���̐ݒ�(�x�^�ł�)
//===========================================
void CObject2D::SetVtxHardCoding(const D3DXVECTOR3& LeftUp, const D3DXVECTOR3& RightUp, const D3DXVECTOR3& LeftDown, const D3DXVECTOR3& RightDown)
{
	VERTEX_2D* pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x + LeftUp.x, m_pos.y + LeftUp.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + RightUp.x, m_pos.y + RightUp.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x + LeftDown.x, m_pos.y + LeftDown.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + RightDown.x, m_pos.y + RightDown.y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���_�̐F�ݒ菈��
//===========================================
void CObject2D::SetVtxColor(const D3DXCOLOR& col)
{
	VERTEX_2D* pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �e�N�X�`���̐ݒ�
//===========================================
void CObject2D::SetVtxTexture(void)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ���]�e�N�X�`���̐ݒ�
//===========================================
void CObject2D::SetVtxTextureRev(void)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �e�N�X�`���̐ݒ�(�A�j���[�V�����o�[�W����)
//===========================================
void CObject2D::SetVtxTextureAnim(float fTexPattern,int nPattern)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(nPattern * fTexPattern, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(nPattern * fTexPattern + fTexPattern, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(nPattern * fTexPattern, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(nPattern * fTexPattern + fTexPattern, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �e�N�X�`���̐ݒ�(�X�N���[���o�[�W����)
//===========================================
void CObject2D::SetVtxTextureScroll(D3DXVECTOR2& tex)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(tex.x, tex.y);
	pVtx[1].tex = D3DXVECTOR2(tex.x + 1.0f, tex.y);
	pVtx[2].tex = D3DXVECTOR2(tex.x, tex.y + 1.0f);
	pVtx[3].tex = D3DXVECTOR2(tex.x + 1.0f, tex.y + 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �e�N�X�`���̐ݒ�(���̃e�N�X�`���C�Ӑݒ�)
//===========================================
void CObject2D::SetVtxTextureWidth(const float tex)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(tex, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(tex, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �e�N�X�`���̐ݒ�(�����S�̏c�̃e�N�X�`���C�Ӑݒ�)
//===========================================
void CObject2D::SetVtxTextureUnderHeight(const float tex)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, tex);
	pVtx[1].tex = D3DXVECTOR2(1.0f, tex);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// �S�Ă̒��_���̐ݒ�
//===========================================
void CObject2D::SetVertexAll(void)
{
	VERTEX_2D * pVtx;											//���_���ւ̃|�C���^

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.y = m_pos.y + cosf(m_rot.z - D3DX_PI + m_fAngle) * m_fLength;
	pVtx[0].pos.z = 0.0f;
	pVtx[1].pos.x = m_pos.x + sinf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.y = m_pos.y + cosf(m_rot.z + D3DX_PI - m_fAngle) * m_fLength;
	pVtx[1].pos.z = 0.0f;
	pVtx[2].pos.x = m_pos.x + sinf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.y = m_pos.y + cosf(m_rot.z - m_fAngle) * m_fLength;
	pVtx[2].pos.z = 0.0f;
	pVtx[3].pos.x = m_pos.x + sinf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.y = m_pos.y + cosf(m_rot.z + m_fAngle) * m_fLength;
	pVtx[3].pos.z = 0.0f;

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//���_�o�b�t�@���A�����b�N����
	m_pVtxBuff->Unlock();
}

//===========================================
// ��������
//===========================================
CObject2D* CObject2D::Create(const TYPE type2D, const CObject::TYPE type, const PRIORITY priority)
{
	// ���[�J���I�u�W�F�N�g�𐶐�
	CObject2D* pObject2D = nullptr;	// �I�u�W�F�N�g2D�̃C���X�^���X�𐶐�

	if (pObject2D == nullptr)
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		switch (type2D)
		{
		case TYPE_NONE:		// �ʏ�

			// �I�u�W�F�N�g�𐶐�
			pObject2D = new CObject2D(type, priority);

			break;

		case TYPE_ANIM:		// �A�j���[�V����

			// �I�u�W�F�N�g�𐶐�
			pObject2D = new CAnim(type, priority);

			break;

		case TYPE_SCROLL:	// �X�N���[��

			// �I�u�W�F�N�g�𐶐�
			pObject2D = new CScroll(type, priority);

			break;

		default:

			// ��~
			assert(false);

			break;
		}
	}
	else
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	if (pObject2D != nullptr)
	{ // �I�u�W�F�N�g�� NULL ����Ȃ��ꍇ

		// ����������
		pObject2D->Init();
	}
	else
	{ // �I�u�W�F�N�g�� NULL �̏ꍇ

		// ��~
		assert(false);

		// NULL ��Ԃ�
		return nullptr;
	}

	// �I�u�W�F�N�g2D�̃|�C���^��Ԃ�
	return pObject2D;
}