//===================================
//
// �����蔻��w�b�_�[[collision.h]
// Author ��������
//
//===================================
#ifndef _COLLISION_H_			//���̃}�N����`������Ă��Ȃ�������
#define _COLLISION_H_			//2�d�C���N���[�h�h�~�̃}�N�����`����

//***********************************
// �C���N���[�h�t�@�C��
//***********************************
#include "main.h"
#include "obstacle.h"

//-----------------------------------
// �O���錾
//-----------------------------------
class CBlock;		// �u���b�N
class CPlayer;		// �v���C���[

//-----------------------------------
// ���O���(�����蔻��)
//-----------------------------------
namespace collision
{
	// �\���̒�`(�����蔻��)
	struct SCollision
	{
		bool bTop;		// ��̓����蔻��
		bool bBottom;	// ���̓����蔻��
		bool bRight;	// �E�̓����蔻��
		bool bLeft;		// ���̓����蔻��
		bool bFar;		// ���̓����蔻��
		bool bNear;		// ��O�̓����蔻��
	};

	// �ۉe�̓����蔻��
	void ShadowCollision(const D3DXVECTOR3& pos, int nIdx);							// �ۉe�̓����蔻��

	// ��Q���̓����蔻��
	bool ObstacleCollision(CPlayer* player, const float fWidth, const float fHeight, const float fDepth);	// ��Q���̏Փ˔���
	void ObstacleHit(CPlayer* pPlayer, const float fWidth, const float fHeight, const float fDepth);		// ��Q���̓����蔻��
	void ObstacleAction(CPlayer* pPlayer, const float Radius);				// ��Q���̋N������
	void ObstacleSearch(CPlayer* pPlayer, const float Radius);				// �N���\��Q����x�����o����Q���̃T�[�`

	// ��������\��̃u���b�N�̓����蔻��
	bool BlockCollision(CPlayer* player, const D3DXVECTOR3& collSize);							// �u���b�N�̓����蔻��
	void BlockRectangleCollision(const CBlock& block, CPlayer* player, const D3DXVECTOR3& collSize, bool* pJump);			// �u���b�N�̋�`�̓����蔻��
	void BlockCircleCollision(CBlock& block, CPlayer* player, const float fRadius, const float fHeight, bool* pJump);		// �u���b�N�̉~�`�̓����蔻��

	bool BlockHit(CPlayer* player, const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize);							// �u���b�N�̍U������
	void BlockRectangleHit(const CBlock& block, CPlayer* player, const D3DXVECTOR3& pos, const D3DXVECTOR3& collSize, bool* pHit);			// �u���b�N�̋�`�̍U������
	void BlockCircleHit(CBlock& block, CPlayer* player, const D3DXVECTOR3& pos, const float fRadius, const float fHeight, bool* pHit);		// �u���b�N�̉~�`�̍U������

	// �N���n�ʂ̓����蔻��
	bool ElevOutRangeCollision(D3DXVECTOR3* pPos, const D3DXVECTOR3& posOld, const float fWidth);			// �N���n�ʂ͈̔͊O�̓����蔻��

	//�ǂƂ̓����蔻��
	void WallCollision(CPlayer* player, const D3DXVECTOR3& collSize);

	// �A�C�e���Ƃ̓����蔻��
	void ItemCollision(CPlayer& pPlayer, const int nHave);		// �l�R�ƃA�C�e���Ƃ̓����蔻��

	// �ėp�I�ȓ����蔻��
	bool HexahedronCollision(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// �Z�ʑ̂̓����蔻��
	SCollision HexahedronClush(D3DXVECTOR3* pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& posOld, const D3DXVECTOR3& posOldBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// �Z�ʑ̂̓����蔻��(�ǂ̖ʂɏ�������̔���t��)
	SCollision HexahedronClushNotMove(const D3DXVECTOR3& pos, const D3DXVECTOR3& posBlock, const D3DXVECTOR3& min, const D3DXVECTOR3& minBlock, const D3DXVECTOR3& max, const D3DXVECTOR3& maxBlock);		// �Z�ʑ̂̓����蔻��(�ǂ̖ʂɏ�������̔���t�� && �ړ������Ȃ�)

}

#endif