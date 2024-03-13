//===========================================
//
// �����蔻��̃��C������[collision.cpp]
// Author ��������
//
//===========================================
//*******************************************
// �C���N���[�h�t�@�C��
//*******************************************
#include "game.h"
#include "tutorial.h"
#include "collision.h"
#include "shadowCircle.h"
#include "objectElevation.h"
#include "elevation_manager.h"
#include "obstacle_manager.h"
#include "block.h"
#include "block_manager.h"
#include "useful.h"
#include "Particle.h"
#include "map.h"
#include "wall.h"
#include "ground.h"
#include <cmath>
#include "objectX.h"
#include "item.h"
#include "item_manager.h"
#include "player.h"
#include "manager.h"
#include "sound.h"

//===============================
// �}�N����`
//===============================
#define COLLISION_ADD_DIFF_LENGTH		(0.01f)			// �͂��Ȍ덷�𖄂߂邽�߂̃}�N����`(�˂�������h�~)
#define COLLISION_CAT_SIZE				(D3DXVECTOR3(70.0f,250.0f,70.0f))		// �l�R�̓����蔻��̃T�C�Y
#define CAT_WIND_MAGNI					(0.3f)			// �l�R�̕��̔{��
#define RAT_WIND_MAGNI					(1.1f)			// �l�Y�~�̕��̔{��
#define CAT_STUN_TIME					(90)			// �l�R�̃X�^������
#define RAT_STUN_TIME					(60)			// �l�Y�~�̃X�^������

//===============================
// �ۉe�̓����蔻�菈��
//===============================
void collision::ShadowCollision(const D3DXVECTOR3& pos, int nIdx)
{
	// ���[�J���ϐ��錾
	CShadowCircle* pShadow = CShadowCircle::GetShadow(nIdx);	// �e�̃|�C���^
	D3DXVECTOR3 posPlayer = pos;				// �v���C���[�̈ʒu
	D3DXVECTOR3 posCand = NONE_D3DXVECTOR3;		// �e�̈ʒu�̌��

	if (pShadow != nullptr)
	{ // �e�̃|�C���^�� NULL ����Ȃ������ꍇ

		// �e�̈ʒu���擾����
		posCand = D3DXVECTOR3(posPlayer.x, pShadow->GetPos().y, posPlayer.z);

		// �ʒu��ݒ肷��
		pShadow->SetPos(posCand);
	}
}

//===============================
// ��Q���̓����蔻��
//===============================
bool collision::ObstacleCollision(CPlayer* player, const float fWidth, const float fHeight, const float fDepth)
{
	// ���[�J���ϐ��錾
	D3DXVECTOR3 collSize = D3DXVECTOR3(fWidth, fHeight, fDepth);	// �����蔻��̃T�C�Y
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q�����擾����
	bool bLand = false;				// ���n����

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		// �����蔻�菈��
		if (pObstacle->Collision(player, collSize) == true)
		{
			// ���n������o��
			bLand = true;
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacle->GetNext();
	}

	// ���n�����Ԃ�
	return bLand;
}

//===============================
// ��Q���̓����蔻��
//===============================
void collision::ObstacleHit(CPlayer* pPlayer, const float fWidth, const float fHeight, const float fDepth)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q��
	CObstacle* pObstacleNext = nullptr;				// ���̏�Q��
	D3DXVECTOR3 pos = pPlayer->GetPos();			// �ʒu
	D3DXVECTOR3 collSize = D3DXVECTOR3(fWidth, fHeight, fDepth);	// �����蔻��̃T�C�Y
	float fAngle;				// ������ԕ���
	bool bHitMove = false;		// �q�b�g��

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		// ��Q���̎��̃|�C���^���擾����
		pObstacleNext = pObstacle->GetNext();

		if (pObstacle->Hit(pPlayer, collSize) == true)
		{ // ��Q���̓����蔻�肪�ʂ����ꍇ

			switch (pObstacle->GetType())
			{
			case CObstacle::TYPE_HONEY:

				if (pPlayer->GetType() == CPlayer::TYPE_CAT)
				{ // �l�R�̏ꍇ

					// �ړ��ʂ�ݒ肷��
					pPlayer->SetSpeed(pPlayer->GetSpeedCopy() * 0.6f);
				}
				else
				{ // �l�Y�~�̏ꍇ

					// �ړ��ʂ�ݒ肷��
					pPlayer->SetSpeed(pPlayer->GetSpeedCopy() * 0.3f);
				}

				// �W�����v�󋵂�ݒ肷��
				pPlayer->SetEnableJump(true);

				// �q�b�g����
				bHitMove = true;

				break;

			case CObstacle::TYPE_SLIME:

				// �ړ��ʂ�ݒ肷��
				pPlayer->SetSpeed(pPlayer->GetSpeedCopy() * 0.7f);

				if (pPlayer->IsMove() == true)
				{
					CParticle::Create(pos, CParticle::TYPE_SLIME);
				}

				// �q�b�g����
				bHitMove = true;

				break;

			case CObstacle::TYPE_HAIRBALL:

				// �������Z�o����
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// �q�b�g����
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_PETBOTTLE:

				// �������Z�o����
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// �q�b�g����
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_TOYCAR:

			{ // �v���C���[���΂�����

				// �������Z�o����
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// ������я���
				pPlayer->Smash(fAngle);
			}

				break;

			case CObstacle::TYPE_ROOMBA:

				// �������Z�o����
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// ������я���
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_HIMO:

				// �q�b�g����
				if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
				{
					pPlayer->Stun(CAT_STUN_TIME);
				}
				else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					pPlayer->Stun(RAT_STUN_TIME);
				}

				break;


			case CObstacle::TYPE_SPEAKER:

				// �������Z�o����
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// �q�b�g����
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_MOUSETRAP:

				// �q�b�g����
				if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
				{
					pPlayer->Stun(CAT_STUN_TIME);
				}
				else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					pPlayer->Stun(RAT_STUN_TIME);
				}

				break;

			case CObstacle::TYPE_LEASH:

				// �q�b�g����
				if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
				{
					pPlayer->Stun(CAT_STUN_TIME);
				}
				else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					pPlayer->Stun(RAT_STUN_TIME);
				}

				break;

			case CObstacle::TYPE_PIN:

				// �q�b�g����
				if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
				{
					pPlayer->Stun(CAT_STUN_TIME);
				}
				else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					pPlayer->Stun(RAT_STUN_TIME);
				}

				break;

			case CObstacle::TYPE_FAN:

				// �������Z�o����
				fAngle = pObstacle->GetRot().y + D3DX_PI;

				// �����𐳋K������
				useful::RotNormalize(&fAngle);

				if (pPlayer->GetType() == CPlayer::TYPE_CAT)
				{ // �l�R�̏ꍇ

					// �ʒu�������o��
					pos.x += sinf(fAngle) * pPlayer->GetSpeedCopy() * CAT_WIND_MAGNI;
					pos.z += cosf(fAngle) * pPlayer->GetSpeedCopy() * CAT_WIND_MAGNI;
				}
				else if(pPlayer->GetType() == CPlayer::TYPE_RAT)
				{ // �l�Y�~�̏ꍇ

					// �ʒu�������o��
					pos.x += sinf(fAngle) * pPlayer->GetSpeedCopy() * RAT_WIND_MAGNI;
					pos.z += cosf(fAngle) * pPlayer->GetSpeedCopy() * RAT_WIND_MAGNI;
				}

				// �ʒu��ݒ肷��
				pPlayer->SetPos(pos);

				break;

			case CObstacle::TYPE_CUP:

				// �q�b�g����
				if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
				{
					pPlayer->Stun(CAT_STUN_TIME);
				}
				else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					pPlayer->Stun(RAT_STUN_TIME);
				}

				break;

			case CObstacle::TYPE_GARBAGECAN:

				// �C����
				pPlayer->Stun(120);
				pObstacle->SlideOn(pPlayer->GetPos(), pPlayer->GetMove(), pPlayer);
				break;

			case CObstacle::TYPE_DYNAMITE:

				// �������Z�o����
				fAngle = atan2f(pos.x - pObstacle->GetPos().x, pos.z - pObstacle->GetPos().z);

				// ������я���
				pPlayer->Smash(fAngle);

				break;

			case CObstacle::TYPE_BOOK:

				// �q�b�g����
				if (pPlayer->GetType() == CPlayer::TYPE::TYPE_CAT)
				{
					pPlayer->Stun(CAT_STUN_TIME);
				}
				else if (pPlayer->GetType() == CPlayer::TYPE::TYPE_RAT)
				{
					pPlayer->Stun(RAT_STUN_TIME);
				}

				break;

			case CObstacle::TYPE_RATMECHA:

				CParticle::Create(pObstacle->GetPos(), CParticle::TYPE_ENEMYDEATH); //�p�[�e�B�N��
				pObstacle->Uninit();

				break;

			default:

				//���ɂȂ�

				break;
			}
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacleNext;
	}

	if (bHitMove == false)
	{ // �q�b�g���Ă��Ȃ��ꍇ

		// ���x��ʏ�ɐݒ�
		pPlayer->SetSpeed(pPlayer->GetSpeedCopy());
	}
}

//===============================
// ��Q���̋N������
//===============================
void collision::ObstacleAction(CPlayer* pPlayer, const float Radius)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();	// �擪�̏�Q��
	CPlayer::TYPE type = pPlayer->GetType();					// ���

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (type == CPlayer::TYPE::TYPE_CAT)
		{
			if (pObstacle->GetCatUse() == true)
			{
				if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH ||
					pObstacle->GetType() == CObstacle::TYPE::TYPE_REDKATEN)
				{//���l���A�N�V�����̂Ƃ�
					pObstacle->HitMultiCircle(pPlayer, Radius, true);
				}
				else
				{//���[�h�ȊO�̂Ƃ�
					if (pObstacle->HitCircle(pPlayer, Radius) == true)
					{ // ��Q���̓����蔻�肪�ʂ����ꍇ

						if (pObstacle->GetType() == CObstacle::TYPE::TYPE_BOOK)
						{ // �N���Ƀv���C���[�̏�񂪕K�v�ȏꍇ

							// �A�N�V��������
							pObstacle->Action(pPlayer);
						}
						else
						{ // ��L�ȊO

							// �A�N�V��������
							pObstacle->Action();
						}

						// �l�Y�~���A�N�V�������s��������(�`���[�g���A���p)
						pPlayer->SetUseAction(true);
					}
				}
			}
		}
		else if(type == CPlayer::TYPE::TYPE_RAT)
		{
			if (pObstacle->GetRatUse() == true)
			{
				if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH ||
					pObstacle->GetType() == CObstacle::TYPE::TYPE_REDKATEN)
				{//���[�h�̂Ƃ�
					pObstacle->HitMultiCircle(pPlayer, Radius, true);
				}
				else
				{//���[�h�ȊO�̂Ƃ�

					if (pObstacle->HitCircle(pPlayer, Radius) == true)
					{ // ��Q���̓����蔻�肪�ʂ����ꍇ

						if (pObstacle->GetType() == CObstacle::TYPE::TYPE_BOOK)
						{ // �N���Ƀv���C���[�̏�񂪕K�v�ȏꍇ

							// �A�N�V��������
							pObstacle->Action(pPlayer);
						}
						else
						{ // ��L�ȊO

							// �A�N�V��������
							pObstacle->Action();
						}

						//�l�Y�~���A�N�V�������s��������(�`���[�g���A���p)
						pPlayer->SetUseAction(true);
					}
				}
			}
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacle->GetNext();
	}
}

//===========================================
// �N���\��Q����x�����o����Q���̃T�[�`
//===========================================
void collision::ObstacleSearch(CPlayer* pPlayer, const float Radius)
{
	// ���[�J���ϐ��錾
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// �擪�̏�Q��
	CPlayer::TYPE type = pPlayer->GetType();						// ���
	int nIdx = pPlayer->GetPlayerIdx();								// �C���f�b�N�X
	float fAngle;													// ������ԕ���

	while (pObstacle != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (type == CPlayer::TYPE::TYPE_CAT)
		{
			if (pObstacle->GetCatUse() == true)
			{
				if (pObstacle->HitCircle(pPlayer, Radius) == true)
				{ // ��Q���̓����蔻�肪�ʂ����ꍇ
					pObstacle->GimmickUI(true, nIdx);
				}
				else
				{
					pObstacle->GimmickUI(false, nIdx);
				}
			}
			else
			{
				pObstacle->GimmickUI(false, nIdx);
			}
		}
		else if (type == CPlayer::TYPE::TYPE_RAT)
		{
			if (pObstacle->GetRatUse() == true)
			{
				if (pObstacle->HitCircle(pPlayer, Radius) == true)
				{ // ��Q���̓����蔻�肪�ʂ����ꍇ
					if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH)
					{//���[�h�̂Ƃ�
						pObstacle->MultiGimmickUI(true, nIdx);
					}
					else
					{//���[�h�ȊO�̂Ƃ�
						pObstacle->GimmickUI(true, nIdx);
					}
				}
				else
				{
					if (pObstacle->GetType() == CObstacle::TYPE::TYPE_LEASH)
					{//���[�h�̂Ƃ�
						pObstacle->MultiGimmickUI(false, nIdx);
						pObstacle->HitMultiCircle(pPlayer, Radius, false);
					}
					else
					{//���[�h�ȊO�̂Ƃ�
						pObstacle->GimmickUI(false, nIdx);
					}
				}
			}
			else
			{
				pObstacle->GimmickUI(false, nIdx);
			}
		}

		// ���̃I�u�W�F�N�g��������
		pObstacle = pObstacle->GetNext();
	}
}

//===============================
// �u���b�N�̓����蔻��
//===============================
bool collision::BlockCollision(CPlayer* player, const D3DXVECTOR3& collSize)
{
	// �擪�̃u���b�N�̏����擾����
	CBlock* pBlock = CBlockManager::Get()->GetTop();
	bool bJump = false;			// �W�����v��

	while (pBlock != nullptr)
	{ // �u���b�N�� NULL �̏ꍇ

		switch (pBlock->GetCollision())
		{
		case CBlock::COLLISION_SQUARE:

			// ��`�̓����蔻��
			BlockRectangleCollision(*pBlock, player, collSize, &bJump);

			break;

		case CBlock::COLLISION_CIRCLE:

			// �~�̓����蔻��
			BlockCircleCollision(*pBlock, player, collSize.x, collSize.y, &bJump);

			break;
		}

		// ���̃u���b�N�̏����擾����
		pBlock = pBlock->GetNext();
	}

	// �W�����v�󋵂�Ԃ�
	return bJump;
}

//===============================
// �u���b�N�̋�`�̓����蔻��
//===============================
void collision::BlockRectangleCollision(const CBlock& block, CPlayer* player, const D3DXVECTOR3& collSize, bool* pJump)
{
	// �u���b�N�̓����蔻��ɕK�v�ȕϐ���錾
	D3DXVECTOR3 pos = player->GetPos();										// �ʒu
	D3DXVECTOR3 posOld = player->GetPosOld();								// �O��̈ʒu
	D3DXVECTOR3 move = player->GetMove();									// �ړ���
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// �ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, 0.0f, -collSize.z);		// �ŏ��l

	if (block.GetPos().y + block.GetVtxMax().y >= pos.y + vtxMin.y &&
		block.GetPos().y + block.GetVtxMin().y <= pos.y + vtxMax.y &&
		block.GetPos().z + block.GetVtxMax().z >= pos.z + vtxMin.z &&
		block.GetPos().z + block.GetVtxMin().z <= pos.z + vtxMax.z)
	{ // X���̔���ɓ����ꍇ

		if (block.GetPosOld().x + block.GetVtxMax().x <= posOld.x + vtxMin.x &&
			block.GetPos().x + block.GetVtxMax().x >= pos.x + vtxMin.x)
		{ // �E�ɂԂ������ꍇ

			if (block.GetPos().y + block.GetVtxMax().y - 5.0f <= pos.y + vtxMin.y)
			{ // �����̒i���̏ꍇ

				// �ʒu��ݒ肷��
				pos.y = block.GetPos().y + block.GetVtxMax().y - (vtxMin.y - COLLISION_ADD_DIFF_LENGTH);
			}
			else
			{ // ��L�ȊO

				// �ʒu��ݒ肷��
				pos.x = block.GetPos().x + block.GetVtxMax().x - (vtxMin.x - COLLISION_ADD_DIFF_LENGTH);
			}
		}
		else if (block.GetPosOld().x + block.GetVtxMin().x >= posOld.x + vtxMax.x &&
			block.GetPos().x + block.GetVtxMin().x <= pos.x + vtxMax.x)
		{ // ���ɂԂ������ꍇ

			if (block.GetPos().y + block.GetVtxMax().y - 5.0f <= pos.y + vtxMin.y)
			{ // �����̒i���̏ꍇ

				// �ʒu��ݒ肷��
				pos.y = block.GetPos().y + block.GetVtxMax().y - (vtxMin.y - COLLISION_ADD_DIFF_LENGTH);
			}
			else
			{ // ��L�ȊO

				// �ʒu��ݒ肷��
				pos.x = block.GetPos().x + block.GetVtxMin().x - (vtxMax.x + COLLISION_ADD_DIFF_LENGTH);
			}
		}
	}

	if (block.GetPos().x + block.GetVtxMax().x >= pos.x + vtxMin.x &&
		block.GetPos().x + block.GetVtxMin().x <= pos.x + vtxMax.x &&
		block.GetPos().y + block.GetVtxMax().y >= pos.y + vtxMin.y &&
		block.GetPos().y + block.GetVtxMin().y <= pos.y + vtxMax.y)
	{ // Z���̔���ɓ����ꍇ

		if (block.GetPosOld().z + block.GetVtxMax().z <= posOld.z + vtxMin.z &&
			block.GetPos().z + block.GetVtxMax().z >= pos.z + vtxMin.z)
		{ // ���ɂԂ������ꍇ

			if (block.GetPos().y + block.GetVtxMax().y - 5.0f <= pos.y + vtxMin.y)
			{ // �����̒i���̏ꍇ

				// �ʒu��ݒ肷��
				pos.y = block.GetPos().y + block.GetVtxMax().y - (vtxMin.y - COLLISION_ADD_DIFF_LENGTH);
			}
			else
			{ // ��L�ȊO

				// �ʒu��ݒ肷��
				pos.z = block.GetPos().z + block.GetVtxMax().z - (vtxMin.z - COLLISION_ADD_DIFF_LENGTH);
			}
		}
		else if (block.GetPosOld().z + block.GetVtxMin().z >= posOld.z + vtxMax.z &&
			block.GetPos().z + block.GetVtxMin().z <= pos.z + vtxMax.z)
		{ // ��O�ɂԂ������ꍇ

			if (block.GetPos().y + block.GetVtxMax().y - 5.0f <= pos.y + vtxMin.y)
			{ // �����̒i���̏ꍇ

				// �ʒu��ݒ肷��
				pos.y = block.GetPos().y + block.GetVtxMax().y - (vtxMin.y - COLLISION_ADD_DIFF_LENGTH);
			}
			else
			{ // ��L�ȊO

				// �ʒu��ݒ肷��
				pos.z = block.GetPos().z + block.GetVtxMin().z - (vtxMax.z + COLLISION_ADD_DIFF_LENGTH);
			}
		}
	}

	if (block.GetPos().x + block.GetVtxMax().x >= pos.x + vtxMin.x &&
		block.GetPos().x + block.GetVtxMin().x <= pos.x + vtxMax.x &&
		block.GetPos().z + block.GetVtxMax().z >= pos.z + vtxMin.z &&
		block.GetPos().z + block.GetVtxMin().z <= pos.z + vtxMax.z)
	{ // Y���̔���ɓ����ꍇ

		if (block.GetPosOld().y + block.GetVtxMax().y <= posOld.y + vtxMin.y &&
			block.GetPos().y + block.GetVtxMax().y >= pos.y + vtxMin.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.y = block.GetPos().y + block.GetVtxMax().y - (vtxMin.y - COLLISION_ADD_DIFF_LENGTH);

			// �d�͂�0.0f�ɂ���
			move.y = 0.0f;

			// true�ɂ���
			*pJump = true;
		}
		else if (block.GetPosOld().y + block.GetVtxMin().y >= posOld.y + vtxMax.y &&
			block.GetPos().y + block.GetVtxMin().y <= pos.y + vtxMax.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos.y = block.GetPos().y + block.GetVtxMin().y - (vtxMax.y + COLLISION_ADD_DIFF_LENGTH);

			// �d�͂�0.0f�ɂ���
			move.y = 0.0f;
		}
	}

	// �ʒu�ƈړ��ʂ�K�p����
	player->SetPos(pos);		// �ʒu
	player->SetMove(move);		// �ړ���
}

//===============================
// �u���b�N�̉~�`�̓����蔻��
//===============================
void collision::BlockCircleCollision(CBlock& block, CPlayer* player, const float fRadius, const float fHeight, bool* pJump)
{
	// �ʒu�ƑO��̈ʒu�ƈړ��ʂ��擾����
	D3DXVECTOR3 pos = player->GetPos();
	D3DXVECTOR3 posOld = player->GetPosOld();
	D3DXVECTOR3 move = player->GetMove();

	if (pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y &&
		pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
	{ // �u���b�N�ƏՓ˂����ꍇ

		if (useful::CylinderInner(pos, block.GetPos(), block.GetFileData().fRadius + fRadius) == true)
		{ // �~���̓����ɂ����ꍇ

			if (posOld.y >= block.GetPos().y + block.GetFileData().vtxMax.y &&
				pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y)
			{ // �ォ��̓����蔻��

				// �ʒu��ݒ肷��
				pos.y = block.GetPos().y + block.GetFileData().vtxMax.y;

				// �ړ��ʂ�0�ɂ���
				move.y = 0.0f;

				// true�ɂ���
				*pJump = true;
			}
			else if (posOld.y + fHeight <= block.GetPos().y + block.GetFileData().vtxMin.y &&
				pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
			{ // ������̓����蔻��

				// �ʒu��ݒ肷��
				pos.y = block.GetPos().y + block.GetFileData().vtxMin.y - fHeight;

				// �ړ��ʂ�0�ɂ���
				move.y = 0.0f;
			}
		}

		// �~���̓����蔻�菈��
		useful::CylinderCollision(&pos, block.GetPos(), block.GetFileData().fRadius + fRadius);
	}

	// �ʒu�ƈړ��ʂ�K�p����
	player->SetPos(pos);
	player->SetMove(move);
}

//===============================
// �u���b�N�̍U������
//===============================
bool collision::BlockHit(CPlayer* player, const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize)
{
	// �����蔻��̕ϐ���錾
	SCollision collision = {};

	// �擪�̃u���b�N�̏����擾����
	CBlock* pBlock = CBlockManager::Get()->GetTop();
	CPlayer *pPlayer = nullptr;		// �v���C���[�̏��
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// �ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, -collSize.y, -collSize.z);		// �ŏ��l
	bool bHit = false;			// �W�����v��
	bool bSe = false;			// SE�炵����
	float fAngle = 0.0f;		// ������Ԍ���

	while (pBlock != nullptr)
	{ // �u���b�N�� NULL �̏ꍇ

		switch (pBlock->GetCollision())
		{
		case CBlock::COLLISION_SQUARE:

			// ��`�̍U������
			BlockRectangleHit(*pBlock, player, pos, collSize, &bHit);

			break;

		case CBlock::COLLISION_CIRCLE:

			// �~�̍U������
			BlockCircleHit(*pBlock, player, pos, collSize.x, collSize.y, &bHit);

			break;
		}

		if (bHit == true)
		{ // �U��������������

			for (int nCnt = 0; nCnt < MAX_PLAY; nCnt++)
			{
				if (CManager::Get()->GetMode() == CScene::MODE_TUTORIAL)
				{
					// �v���C���[�̏����擾����
					pPlayer = CTutorial::GetPlayer(nCnt);
				}
				else if(CManager::Get()->GetMode() == CScene::MODE_GAME)
				{
					// �v���C���[�̏����擾����
					pPlayer = CGame::GetPlayer(nCnt);
				}

				if (pPlayer != nullptr &&
					pPlayer->GetType() == CPlayer::TYPE_RAT)
				{ // �l�Y�~�̎�

					// �Z�ʑ̂̓����蔻��
					collision = HexahedronClushNotMove
					(
						pPlayer->GetPos(),
						pBlock->GetPos(),
						vtxMin,
						pBlock->GetVtxMin(),
						vtxMax,
						pBlock->GetVtxMax()
					);

					if (collision.bTop == true)
					{ // ��ɓ������Ă�Ƃ�

						D3DXVECTOR3 DestPos = pPlayer->GetPos() - pos;		// �ړI�̈ʒu

						// �ړI�̌��������߂�
						fAngle = atan2f(DestPos.x, DestPos.z) + 50.0f;

						// ������я���
						pPlayer->Smash(fAngle);
					}
				}
			}

			if (bSe == false && player->GetSE() == false)
			{ // SE���炳��ĂȂ�������

				// SE�Đ�����
				player->SetSE(true);

				bSe = true;		// �炵����Ԃɂ���
			}

			// �h����Ԃɂ���
			pBlock->SetState(pBlock->STATE_SWAY);

			bHit = false;
		}

		// ���̃u���b�N�̏����擾����
		pBlock = pBlock->GetNext();
	}
	
	// �q�b�g�󋵂�Ԃ�
	return bHit;
}

//===============================
// �u���b�N�̋�`�̍U������
//===============================
void collision::BlockRectangleHit(const CBlock& block, CPlayer* player, const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, bool* pHit)
{
	// �����蔻��̕ϐ���錾
	SCollision collision = {};

	// �u���b�N�̓����蔻��ɕK�v�ȕϐ���錾
	D3DXVECTOR3 move = player->GetMove();									// �ړ���
	D3DXVECTOR3 vtxMax = D3DXVECTOR3(collSize.x, collSize.y, collSize.z);	// �ő�l
	D3DXVECTOR3 vtxMin = D3DXVECTOR3(-collSize.x, -collSize.y, -collSize.z);		// �ŏ��l

	if (block.GetVtxMax().y < 500.0f)
	{ // �u���b�N���l�Y�~�����鍂������Ȃ��Ƃ�

		// �Z�ʑ̂̓����蔻��
		collision = HexahedronClushNotMove
		(
			pos,
			block.GetPos(),
			vtxMin,
			block.GetVtxMin(),
			vtxMax,
			block.GetVtxMax()
		);
	}

	if (collision.bTop == true)
	{ // ��ɏ�����ꍇ

		// true�ɂ���
		*pHit = true;
	}
}

//===============================
// �u���b�N�̉~�`�̍U������
//===============================
void collision::BlockCircleHit(CBlock& block, CPlayer* player, const D3DXVECTOR3& pos, const float fRadius, const float fHeight, bool* pHit)
{
	// �ʒu�ƑO��̈ʒu�ƈړ��ʂ��擾����
	D3DXVECTOR3 posOld = player->GetPosOld();
	D3DXVECTOR3 move = player->GetMove();

	if (pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y &&
		pos.y + fHeight >= block.GetPos().y + block.GetFileData().vtxMin.y)
	{ // �u���b�N�ƏՓ˂����ꍇ

		if (useful::CylinderInner(pos, block.GetPos(), block.GetFileData().fRadius + fRadius) == true)
		{ // �~���̓����ɂ����ꍇ

			if (posOld.y >= block.GetPos().y + block.GetFileData().vtxMax.y &&
				pos.y <= block.GetPos().y + block.GetFileData().vtxMax.y)
			{ // �ォ��̓����蔻��

				// true�ɂ���
				*pHit = true;
			}
		}
	}
}

//===============================
// �N���n�ʂ͈̔͊O�̓����蔻��
//===============================
bool collision::ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth)
{
	// ���[�J���ϐ��錾
	CElevation* pElev = CElevationManager::Get()->GetTop();		// �擪�̋N���n�ʂ��擾����
	bool bCollision = false;									// �����蔻���

	while (pElev != nullptr)
	{ // �u���b�N�̏�� NULL ����Ȃ��ꍇ

		if (pElev->GetPos().z + (pElev->GetSize().z * 0.5f) >= pPos->z &&
			pElev->GetPos().z - (pElev->GetSize().z * 0.5f) <= pPos->z &&
			pElev->GetPos().y > pPos->y)
		{ // �N���n�ʂ�艺�ɂ���ꍇ

			if (posOld.x + fWidth <= pElev->GetPos().x - (pElev->GetSize().x * 0.5f) &&
				pPos->x + fWidth >= pElev->GetPos().x - (pElev->GetSize().x * 0.5f))
			{ // ���̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x - (pElev->GetSize().x * 0.5f) - fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
			else if (posOld.x - fWidth >= pElev->GetPos().x + (pElev->GetSize().x * 0.5f) &&
				pPos->x - fWidth <= pElev->GetPos().x + (pElev->GetSize().x * 0.5f))
			{ // �E�̓����蔻��

				// �ʒu��ݒ肷��
				pPos->x = pElev->GetPos().x + (pElev->GetSize().x * 0.5f) + fWidth;

				// �����蔻��󋵂� true �ɂ���
				bCollision = true;
			}
		}

		// ���̃I�u�W�F�N�g��������
		pElev = pElev->GetNext();
	}

	// �����蔻��󋵂�Ԃ�
	return bCollision;
}
//===============================
//�ǂƂ̓����蔻��
//===============================
void collision::WallCollision(CPlayer* player, const D3DXVECTOR3& collSize)
{
	// �ʒu�ƑO��̈ʒu�ƈړ��ʂ��擾����
	D3DXVECTOR3 pos = player->GetPos();
	D3DXVECTOR3 posOld = player->GetPosOld();
	D3DXVECTOR3 move = player->GetMove();

	if (pos.x + collSize.x >= MAP_SIZE.x)
	{ // �E����o�����ɂȂ����ꍇ

		// �ʒu��ݒ肷��
		pos.x = MAP_SIZE.x - collSize.x;

		// �ړ��ʂ�ݒ肷��
		move.x = 0.0f;
	}

	if (pos.x - collSize.x <= -MAP_SIZE.x)
	{ // ������o�����ɂȂ����ꍇ

		// �ʒu��ݒ肷��
		pos.x = -MAP_SIZE.x + collSize.x;

		// �ړ��ʂ�ݒ肷��
		move.x = 0.0f;
	}

	if (pos.z + collSize.z >= MAP_SIZE.z)
	{ // ������o�����ɂȂ����ꍇ

		// �ʒu��ݒ肷��
		pos.z = MAP_SIZE.z - collSize.z;

		// �ړ��ʂ�ݒ肷��
		move.z = 0.0f;
	}

	if (pos.z - collSize.z <= -MAP_SIZE.z)
	{ // ��O����o�����ɂȂ����ꍇ

		// �ʒu��ݒ肷��
		pos.z = -MAP_SIZE.z + collSize.z;

		// �ړ��ʂ�ݒ肷��
		move.z = 0.0f;
	}

	// �ʒu�ƈړ��ʂ�K�p����
	player->SetPos(pos);
	player->SetMove(move);
}

//======================
// �l�R�ƃA�C�e���Ƃ̓����蔻��
//======================
void collision::ItemCollision(CPlayer& pPlayer, const int nHave)
{
	// �����Ɏg���ϐ���錾
	CItem* pItem = CItemManager::Get()->GetTop();	// �ŏ��̃A�C�e���̏����擾����
	CItem* pItemNext;								// ���̃A�C�e��
	D3DXVECTOR3 pos = pPlayer.GetPos();				// �ʒu
	D3DXVECTOR3 Max = COLLISION_CAT_SIZE;													// �ő�l
	D3DXVECTOR3 Min = D3DXVECTOR3(-COLLISION_CAT_SIZE.x, 0.0f, -COLLISION_CAT_SIZE.z);		// �ŏ��l

	while (pItem != nullptr)
	{ // �A�C�e���� NULL ����Ȃ��ꍇ

		// ���̃A�C�e�����擾����
		pItemNext = pItem->GetNext();

		if (nHave < 2 &&
			useful::RectangleCollisionXY(pos, pItem->GetPos(), Max, pItem->GetFileData().vtxMax, Min, pItem->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionXZ(pos, pItem->GetPos(), Max, pItem->GetFileData().vtxMax, Min, pItem->GetFileData().vtxMin) == true &&
			useful::RectangleCollisionYZ(pos, pItem->GetPos(), Max, pItem->GetFileData().vtxMax, Min, pItem->GetFileData().vtxMin) == true)
		{ // ������ɓ������ꍇ

			// �A�C�e���̎擾����
			pPlayer.GetItem(pItem->GetType());

			// �擾���炷
			CManager::Get()->GetSound()->Play(CSound::SOUND_LABEL_SE_PICKED_UP);

			// �I������
			pItem->Uninit();

			// �A�C�e���o�����ĂȂ���Ԃɂ���
			CGame::SetItemSpawn(false);
		}

		// ���̃A�C�e����ݒ肷��
		pItem = pItemNext;
	}
}

//======================
// �Z�ʑ̂̓����蔻��
//======================
bool collision::HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// true ��Ԃ�
			return true;
		}
	}

	// false ��Ԃ�
	return false;
}

//======================
// �Z�ʑ̂̓����蔻��(�ǂ̖ʂɏ�������̔���t��)
//======================
collision::SCollision collision::HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	// �����蔻��̕ϐ���錾
	SCollision collision = { false,false,false,false,false,false };

	if (posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posOldBlock.x + maxBlock.x <= posOld.x + min.x &&
			posBlock.x + maxBlock.x >= pos->x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + maxBlock.x - (min.x - COLLISION_ADD_DIFF_LENGTH);

			// �E�̓����蔻��� true �ɂ���
			collision.bRight = true;
		}
		else if (posOldBlock.x + minBlock.x >= posOld.x + max.x &&
			posBlock.x + minBlock.x <= pos->x + max.x)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->x = posBlock.x + minBlock.x - (max.x + COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bLeft = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.y + maxBlock.y >= pos->y + min.y &&
		posBlock.y + minBlock.y <= pos->y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posOldBlock.z + maxBlock.z <= posOld.z + min.z &&
			posBlock.z + maxBlock.z >= pos->z + min.z)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + maxBlock.z - (min.z - COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bFar = true;
		}
		else if (posOldBlock.z + minBlock.z >= posOld.z + max.z &&
			posBlock.z + minBlock.z <= pos->z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->z = posBlock.z + minBlock.z - (max.z + COLLISION_ADD_DIFF_LENGTH);

			// ��O�̓����蔻��� true �ɂ���
			collision.bNear = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos->x + min.x &&
		posBlock.x + minBlock.x <= pos->x + max.x &&
		posBlock.z + maxBlock.z >= pos->z + min.z &&
		posBlock.z + minBlock.z <= pos->z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posOldBlock.y + maxBlock.y <= posOld.y + min.y &&
			posBlock.y + maxBlock.y >= pos->y + min.y)
		{ // ��ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + maxBlock.y - (min.y - COLLISION_ADD_DIFF_LENGTH);

			// ��̓����蔻��� true �ɂ���
			collision.bTop = true;
		}
		else if (posOldBlock.y + minBlock.y >= posOld.y + max.y &&
			posBlock.y + minBlock.y <= pos->y + max.y)
		{ // ���ɂԂ������ꍇ

			// �ʒu��ݒ肷��
			pos->y = posBlock.y + minBlock.y - (max.y + COLLISION_ADD_DIFF_LENGTH);

			// ���̓����蔻��� true �ɂ���
			collision.bBottom = true;
		}
	}

	// �����蔻��̕ϐ���Ԃ�
	return collision;
}

//======================
// �Z�ʑ̂̓����蔻��(�ǂ̖ʂɏ�������̔���t�� && �ړ������Ȃ�)
//======================
collision::SCollision collision::HexahedronClushNotMove(const D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock)
{
	// �����蔻��̕ϐ���錾
	SCollision collision = { false,false,false,false,false,false };

	if (posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // X���̔���ɓ����ꍇ

		if (posBlock.x + maxBlock.x >= pos.x + min.x)
		{ // �E�ɂԂ������ꍇ

			// �E�̓����蔻��� true �ɂ���
			collision.bRight = true;
		}
		else if (posBlock.x + minBlock.x <= pos.x + max.x)
		{ // ���ɂԂ������ꍇ

			// ���̓����蔻��� true �ɂ���
			collision.bLeft = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.y + maxBlock.y >= pos.y + min.y &&
		posBlock.y + minBlock.y <= pos.y + max.y)
	{ // Z���̔���ɓ����ꍇ

		if (posBlock.z + maxBlock.z >= pos.z + min.z)
		{ // ���ɂԂ������ꍇ

			// ���̓����蔻��� true �ɂ���
			collision.bFar = true;
		}
		else if (posBlock.z + minBlock.z <= pos.z + max.z)
		{ // ��O�ɂԂ������ꍇ

			// ��O�̓����蔻��� true �ɂ���
			collision.bNear = true;
		}
	}

	if (posBlock.x + maxBlock.x >= pos.x + min.x &&
		posBlock.x + minBlock.x <= pos.x + max.x &&
		posBlock.z + maxBlock.z >= pos.z + min.z &&
		posBlock.z + minBlock.z <= pos.z + max.z)
	{ // Y���̔���ɓ����ꍇ

		if (posBlock.y + maxBlock.y >= pos.y + min.y)
		{ // ��ɂԂ������ꍇ

			// ��̓����蔻��� true �ɂ���
			collision.bTop = true;
		}
		else if (posBlock.y + minBlock.y <= pos.y + max.y)
		{ // ���ɂԂ������ꍇ

			// ���̓����蔻��� true �ɂ���
			collision.bBottom = true;
		}
	}

	// �����蔻��̕ϐ���Ԃ�
	return collision;
}