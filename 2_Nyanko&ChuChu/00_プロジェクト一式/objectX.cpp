//============================================================
//
// X�t�@�C������ [xfile.cpp]
// Author�F��������
//
//============================================================
//************************************************************
// �C���N���[�h�t�@�C��
//************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "texture.h"

//------------------------------------------------------------
// �R���X�g��`
//------------------------------------------------------------
const char* CXFile::c_apModelData[CXFile::TYPE_MAX] =		// ���f���̖��O
{
	// �I�u�W�F�N�g���f��
	"data\\MODEL\\Ripple.x",				// �g��
	"data\\MODEL\\Kari001.x",				// ���v���C���[
	"data\\MODEL\\WoodBlock.x",				// �ؔ�
	"data\\MODEL\\Cage.x",					// ���포��
	"data\\MODEL\\flowerFrac.x",			// �ԕr�̔j��
	"data\\MODEL\\plasticFrac.x",			// �v���X�`�b�N�P�[�X�̔j��
	"data\\MODEL\\attackFrac.x",			// �L�̍U���̔j��
	"data\\MODEL\\Honey.x",					// �I��
	"data\\MODEL\\ToyCarScrew.x",			// ��������̎�(�l�W)
	"data\\MODEL\\TitleWall.x",				// �^�C�g���̕�
	"data\\MODEL\\Red_Roomba_Sub.x",		// �����o�̃v���y��{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Tarai.x",					// ���炢
	"data\\MODEL\\Red_note4.x",				// 4������{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_note8.x",				// 8������{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_note16.x",			// 16������{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\mousetrap_iron.x",		// �l�Y�~�߂�̓S����
	"data\\MODEL\\TrapItem.x",				// �l�Y�~�߂�(�A�C�e��)
	"data\\MODEL\\Red_leashSet.x",			// �ݒu��Ԃ̃��[�h{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_pin_floor.x",			// �ݒu��Ԃ̉�e{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\pin_one.x",				// �j�Зp�̉�e
	"data\\MODEL\\Senpuki_Fan.x",			// ��@(�H��)
	"data\\MODEL\\consent.x",				// �R���Z���g
	"data\\MODEL\\arrow.x",					// ���S���
	"data\\MODEL\\Red_banana_peel.x",		// �o�i�i�̔�{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Book001.x",				// �{(��)
	"data\\MODEL\\Book002.x",				// �{(��)
	"data\\MODEL\\Book003.x",				// �{(��)
	"data\\MODEL\\lever000.x",				// ���o�[(�{��)
	"data\\MODEL\\lever001.x",				// ���o�[(�_)
	"data\\MODEL\\Red_Book000.x",			// �{(��){�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_Book001.x",			// �{(��){�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_Book002.x",			// �{(��){�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_Book003.x",			// �{(��){�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_ToyCarBody.x",		// ��������̎�(�{��){�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_ToyCarScrew.x",		// ��������̎�(�l�W){�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_HairBall.x",			// �{{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Red_Pettobotoru.x",		// �y�b�g�{�g��{�Ԃ̃A�E�g���C��}

	// �u���b�N���f��
	"data\\MODEL\\cardboard.x",				// �i�{�[��
	"data\\MODEL\\TissueBox.x",				// �e�B�b�V����
	"data\\MODEL\\PenHolder.x",				// �y������
	"data\\MODEL\\RemoCon.x",				// �����R��
	"data\\MODEL\\bear.x",					// �e�f�B�x�A
	"data\\MODEL\\Clock.x",					// ���v
	"data\\MODEL\\rubbish.x",				// �`����
	"data\\MODEL\\milk_carton.x",			// �����p�b�N
	"data\\MODEL\\obaphone.x",				// �I�o�t�H��
	"data\\MODEL\\wii.x",					// Wii
	"data\\MODEL\\ds.x",					// DS
	"data\\MODEL\\HeadPhone.x",				// �w�b�h�t�H��
	"data\\MODEL\\Pen.x",					// �y��
	"data\\MODEL\\AC_adapter.x",			// AC�A�_�v�^�[
	"data\\MODEL\\building_blocks.x",		// �ςݖ�
	"data\\MODEL\\obaglasses.x",			// �ዾ�P�[�X
	"data\\MODEL\\pencil.x",				// ���M
	"data\\MODEL\\picture_frames.x",		// �ʐ^����
	"data\\MODEL\\shelf.x",					// �˒I
	"data\\MODEL\\pullshelf.x",				// �����o���I
	"data\\MODEL\\Kitchen.x",				// �L�b�`��
	"data\\MODEL\\Reizouko.x",				// �①��
	"data\\MODEL\\Table000.x",				// �e�[�u��
	"data\\MODEL\\Table_Chair000.x",		// ���̈֎q
	"data\\MODEL\\corkboard.x",				// �R���N�{�[�h
	"data\\MODEL\\desk.x",					// �f�X�N
	"data\\MODEL\\deskbook.x",				// �f�X�N�p�̖{
	"data\\MODEL\\fire_extingisher.x",		// ���Ί�
	"data\\MODEL\\Katen.x",					// �J�[�e��
	"data\\MODEL\\KatenRail.x",				// �J�[�e���̃��[��
	"data\\MODEL\\Tansu002.x",				// ����
	"data\\MODEL\\TV_stand.x",				// �e���r�̃X�^���h
	"data\\MODEL\\WallPlus50.x",			// 50*100�̕�
	"data\\MODEL\\WallPlus100.x",			// 100*100�̕�
	"data\\MODEL\\door001.x",				// �h�A
	"data\\MODEL\\Small_shelf.x",			// �����ȒI
	"data\\MODEL\\bookshelf.x",				// �����̖{�I
	"data\\MODEL\\tableshelf.x",			// �e�[�u���̍����̒I
	"data\\MODEL\\sofa_sheet.x",			// �\�t�@�[�i���ʁj
	"data\\MODEL\\sofa_backrest.x",			// �\�t�@�[�i�w������j
	"data\\MODEL\\Chair_seat.x",			// ���̈֎q(����)
	"data\\MODEL\\Chair_backrest.x",		// ���̈֎q(�w������)
	"data\\MODEL\\lever000.x",				// ���o�[(�{��)
	"data\\MODEL\\window000.x",				// ��
	"data\\MODEL\\wall_clock.x",			// �Ǌ|�����v
	"data\\MODEL\\wall_interior000.x",		// �ǂ̃C���e���A(�I)
	"data\\MODEL\\WallCross100.x",			// ����

	// ��Q�����f��
	"data\\MODEL\\HoneyBottle.x",			// �I���̃{�g��
	"data\\MODEL\\Slime.x",					// �X���C��
	"data\\MODEL\\HairBall.x",				// �{
	"data\\MODEL\\Pettobotoru.x",			// �y�b�g�{�g��
	"data\\MODEL\\ToyCarBody.x",			// ��������̎�(�{��)
	"data\\MODEL\\Red_Roomba_Main.x",		// �����o�̖{��{�Ԃ̃A�E�g���C��}
	"data\\MODEL\\Himo.x",					// �Ђ�
	"data\\MODEL\\speaker.x",				// �X�s�[�J�[
	"data\\MODEL\\mousetrap.x",				// �l�Y�~�߂�
	"data\\MODEL\\leash.x",					// ���[�h
	"data\\MODEL\\pin_box.x",				// ��e
	"data\\MODEL\\Senpuki_Body.x",			// ��@(�{��)
	"data\\MODEL\\cup.x",					// �R�b�v
	"data\\MODEL\\GarbageBox.x",			// �S�~��
	"data\\MODEL\\TV.x",					// �e���r
	"data\\MODEL\\Dynamite.x",				// ���e
	"data\\MODEL\\Book000.x",				// �{(��)
	"data\\MODEL\\Red_Katen.x",				// �Ԃ̃J�[�e��
	"data\\MODEL\\chuchumecha.x",			// �l�Y�~���J

	// �l�Y�~���f��
	"data\\MODEL\\rat\\00_rat_body.x",		// ��
	"data\\MODEL\\rat\\01_rat_head.x",		// ��
	"data\\MODEL\\rat\\02_rat_Lhand.x",		// ����
	"data\\MODEL\\rat\\03_rat_Rhand.x",		// �E��
	"data\\MODEL\\rat\\04_rat_Lleg.x",		// ����
	"data\\MODEL\\rat\\05_rat_Rleg.x",		// �E��

	//�L���f��
	"data\\MODEL\\cat\\00_cat_body.x",		//��
	"data\\MODEL\\cat\\01_cat_head.x",		//��
	"data\\MODEL\\cat\\02_cat_Larm.x",		//���r
	"data\\MODEL\\cat\\03_cat_Lhand.x",		//����
	"data\\MODEL\\cat\\04_cat_Rarm.x",		//�E�r
	"data\\MODEL\\cat\\05_cat_Rhand.x",		//�E��
	"data\\MODEL\\cat\\06_cat_Lfoot.x",		//����
	"data\\MODEL\\cat\\07_cat_Lleg.x",		//����
	"data\\MODEL\\cat\\08_cat_Rfoot.x",		//�E��
	"data\\MODEL\\cat\\09_cat_Rleg.x",		//�E��
	"data\\MODEL\\cat\\flag.x",				//����

	// �l�Y�~���f��
	"data\\MODEL\\rat\\rat_Ghost.x",		// �H��̎p

	// 3D�e�L�X�g���f��
	"data\\MODEL\\cat_win.x",				// �˂��̂����e�L�X�g
	"data\\MODEL\\rat_win.x",				// �˂��݂̂����e�L�X�g

	// ���ւ̃��f��
	"data\\MODEL\\Entry\\floor.x",			// ���ւ̏�
	"data\\MODEL\\Entry\\entrance_wall.x",	// ���ւ̕�
	"data\\MODEL\\Entry\\shoe_box.x",		// �C��
	"data\\MODEL\\Entry\\door.x",			// ���ւ̃h�A
	"data\\MODEL\\Entry\\front_wall.x",		// ���ւ̉��̕�
	"data\\MODEL\\Entry\\shoes_floor.x",	// �C������̏�
	"data\\MODEL\\Entry\\side_wall.x",		// ���̕�
	"data\\MODEL\\boots.x",					//	�u�[�c
	"data\\MODEL\\sandal.x",				//	�T���_��
	"data\\MODEL\\leathershoes.x",			//	���U�[�V���[�Y

	// �����蔻�胂�f��
	"data\\MODEL\\Collision.x",				// �����蔻��G�f�B�b�g���f��
};

//------------------------------------------------------------
// ���f���̏��
//------------------------------------------------------------
CXFile::SXFile CXFile::m_apModel[CXFile::TYPE_MAX] = {};

//============================================================
// �R���X�g���N�^
//============================================================
CXFile::CXFile()
{
	for (int nCnt = 0; nCnt < CXFile::TYPE_MAX; nCnt++)
	{
		// ���f���̏�������������
		m_apModel[nCnt].pMesh = nullptr;			// ���b�V�� (���_���) �ւ̃|�C���^
		m_apModel[nCnt].pBuffMat = nullptr;			// �}�e���A���ւ̃|�C���^
		m_apModel[nCnt].dwNumMat = 0;				// �}�e���A���̐�
		m_apModel[nCnt].vtxMin = INIT_VTX_MIN;		// �ŏ��̒��_���W
		m_apModel[nCnt].vtxMax = INIT_VTX_MAX;		// �ő�̒��_���W
		m_apModel[nCnt].collsize = INIT_SIZE;		// �����蔻��̃T�C�Y
		m_apModel[nCnt].fRadius = 0.0f;				// ���a

		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			m_apModel[nCnt].m_nTexIdx[nCntMat] = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X
		}
	}
}

//============================================================
// �f�X�g���N�^
//============================================================
CXFile::~CXFile()
{

}

//============================================================
// ���f���̏���������
//============================================================
HRESULT CXFile::Init(void)
{
	for (int nCnt = 0; nCnt < CXFile::TYPE_MAX; nCnt++)
	{
		// ���f���̏�������������
		m_apModel[nCnt].pMesh = nullptr;			// ���b�V�� (���_���) �ւ̃|�C���^
		m_apModel[nCnt].pBuffMat = nullptr;			// �}�e���A���ւ̃|�C���^
		m_apModel[nCnt].dwNumMat = 0;				// �}�e���A���̐�
		m_apModel[nCnt].vtxMin = INIT_VTX_MIN;		// �ŏ��̒��_���W
		m_apModel[nCnt].vtxMax = INIT_VTX_MAX;		// �ő�̒��_���W
		m_apModel[nCnt].collsize = INIT_SIZE;		// �����蔻��̃T�C�Y
		m_apModel[nCnt].fRadius = 0.0f;				// ���a

		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			m_apModel[nCnt].m_nTexIdx[nCntMat] = NONE_TEXIDX;		// �e�N�X�`���̃C���f�b�N�X
		}
	}

	// x�t�@�C���̓ǂݍ���
	if (FAILED(LoadXFile()))
	{ // x�t�@�C���̓ǂݍ��݂Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// �����蔻��̍쐬
	SetCollision();

	// �e�N�X�`���̓ǂݍ���
	if (FAILED(LoadTexture()))
	{ // �e�N�X�`���̓ǂݍ��݂Ɏ��s�����ꍇ

		// ��~
		assert(false);

		// ���s��Ԃ�
		return E_FAIL;
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
// ���f���̏I������
//============================================================
void CXFile::Uninit(void)
{
	// �e�N�X�`���̔j��
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		if (m_apModel[nCntModel].pMesh != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pMesh) ��NULL�ł͂Ȃ��ꍇ

			m_apModel[nCntModel].pMesh->Release();
			m_apModel[nCntModel].pMesh = nullptr;
		}

		if (m_apModel[nCntModel].pBuffMat != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pBuffMat) ��NULL�ł͂Ȃ��ꍇ

			m_apModel[nCntModel].pBuffMat->Release();
			m_apModel[nCntModel].pBuffMat = nullptr;
		}
	}

// �f�o�b�O���[�h
#ifdef _DEBUG

	// �e�N�X�`���̔j��
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		if (m_apModel[nCntModel].pMesh != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pMesh) ��NULL�ł͂Ȃ��ꍇ

			// ��~
			assert(false);
		}

		if (m_apModel[nCntModel].pBuffMat != nullptr)
		{ // �ϐ� (m_apModel[nCntModel].pBuffMat) ��NULL�ł͂Ȃ��ꍇ

			// ��~
			assert(false);
		}
	}

#endif
}

//============================================================
//	x�t�@�C���̓ǂݍ���
//============================================================
HRESULT CXFile::LoadXFile(void)
{
	// �ϐ���錾
	HRESULT hr;		// �ُ�I���̊m�F�p

	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		// x�t�@�C���̓ǂݍ���
		hr = D3DXLoadMeshFromX
		( // ����
			c_apModelData[nCntModel],		// ���f���̑��΃p�X
			D3DXMESH_SYSTEMMEM,				// ���b�V���쐬�p�I�v�V����
			pDevice,						// �f�o�C�X�ւ̃|�C���^
			NULL,							// �אڐ��f�[�^
			&m_apModel[nCntModel].pBuffMat,	// �}�e���A���ւ̃|�C���^
			NULL,							// �G�t�F�N�g�f�[�^
			&m_apModel[nCntModel].dwNumMat,	// �}�e���A���̐�
			&m_apModel[nCntModel].pMesh		// ���b�V�� (���_���) �ւ̃|�C���^
		);

		if (FAILED(hr))
		{ // x�t�@�C���̓ǂݍ��݂Ɏ��s�����ꍇ

			// ��~
			assert(false);

			// ���s��Ԃ�
			return E_FAIL;
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
//	�����蔻��̍쐬
//============================================================
void CXFile::SetCollision(void)
{
	// �ϐ���錾
	int         nNumVtx;		// ���f���̒��_��
	DWORD       dwSizeFVF;		// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y
	BYTE        *pVtxBuff;		// ���f���̒��_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3 vtx;			// ���f���̒��_���W

	// �����蔻��̍쐬
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���̍ő吔���J��Ԃ�

		// ���f���̒��_�����擾
		nNumVtx = m_apModel[nCntModel].pMesh->GetNumVertices();

		// ���f���̒��_�t�H�[�}�b�g�̃T�C�Y���擾
		dwSizeFVF = D3DXGetFVFVertexSize(m_apModel[nCntModel].pMesh->GetFVF());

		// ���f���̒��_�o�b�t�@�����b�N
		m_apModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{ // ���f���̒��_�����J��Ԃ�

			// ���f���̒��_���W����
			vtx = *(D3DXVECTOR3*)pVtxBuff;

			// ���_���W (x) �̐ݒ�
			if (vtx.x < m_apModel[nCntModel].vtxMin.x)
			{ // ����̒��_���W (x) ���A����̒��_���W (x) �����������ꍇ

				// ����̒��_��� (x) ����
				m_apModel[nCntModel].vtxMin.x = vtx.x;
			}
			else if (vtx.x > m_apModel[nCntModel].vtxMax.x)
			{ // ����̒��_���W (x) ���A����̒��_���W (x) �����傫���ꍇ

				// ����̒��_��� (x) ����
				m_apModel[nCntModel].vtxMax.x = vtx.x;
			}

			// ���_���W (y) �̐ݒ�
			if (vtx.y < m_apModel[nCntModel].vtxMin.y)
			{ // ����̒��_���W (y) ���A����̒��_���W (y) �����������ꍇ

				// ����̒��_��� (y) ����
				m_apModel[nCntModel].vtxMin.y = vtx.y;
			}
			else if (vtx.y > m_apModel[nCntModel].vtxMax.y)
			{ // ����̒��_���W (y) ���A����̒��_���W (y) �����傫���ꍇ

				// ����̒��_��� (y) ����
				m_apModel[nCntModel].vtxMax.y = vtx.y;
			}

			// ���_���W (z) �̐ݒ�
			if (vtx.z < m_apModel[nCntModel].vtxMin.z)
			{ // ����̒��_���W (z) ���A����̒��_���W (z) �����������ꍇ

				// ����̒��_��� (z) ����
				m_apModel[nCntModel].vtxMin.z = vtx.z;
			}
			else if (vtx.z > m_apModel[nCntModel].vtxMax.z)
			{ // ����̒��_���W (z) ���A����̒��_���W (z) �����傫���ꍇ

				// ����̒��_��� (z) ����
				m_apModel[nCntModel].vtxMax.z = vtx.z;
			}

			// ���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
			pVtxBuff += dwSizeFVF;
		}

		// ���f���̒��_�o�b�t�@���A�����b�N
		m_apModel[nCntModel].pMesh->UnlockVertexBuffer();

		// ���f���T�C�Y�����߂�
		m_apModel[nCntModel].collsize = m_apModel[nCntModel].vtxMax - m_apModel[nCntModel].vtxMin;

		// ���f���̉~�̓����蔻����쐬
		m_apModel[nCntModel].fRadius = ((m_apModel[nCntModel].collsize.x * 0.5f) + (m_apModel[nCntModel].collsize.z * 0.5f)) * 0.5f;
	}
}

//============================================================
//	�e�N�X�`���̓ǂݍ���
//============================================================
HRESULT CXFile::LoadTexture(void)
{
	// �f�o�C�X���擾����
	D3DXMATERIAL     *pMat;						// �}�e���A���ւ̃|�C���^

	// �e�N�X�`���̓ǂݍ���
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // ���f���Ɏg�p���郂�f���̍ő吔���J��Ԃ�

		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)m_apModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_apModel[nCntModel].dwNumMat; nCntMat++)
		{ // �}�e���A���̐����J��Ԃ�

			if (pMat[nCntMat].pTextureFilename != nullptr)
			{ // �e�N�X�`���t�@�C�������݂���ꍇ

				// �e�N�X�`���̓ǂݍ��ݏ���
				m_apModel[nCntModel].m_nTexIdx[nCntMat] = CManager::Get()->GetTexture()->Regist(pMat[nCntMat].pTextureFilename);
			}
		}
	}

	// ������Ԃ�
	return S_OK;
}

//============================================================
// X�t�@�C���̎擾����
//============================================================
CXFile::SXFile CXFile::GetXFile(TYPE type)
{
	if (type >= 0 && type < TYPE_MAX)
	{ // ��ނ��K����̏ꍇ

		// ���f���̏���Ԃ�
		return m_apModel[type];
	}
	else
	{ // ��ނ��K��O�̏ꍇ

		// ��~
		assert(false);

		// 0�Ԗڂ�Ԃ�
		return m_apModel[0];
	}
}