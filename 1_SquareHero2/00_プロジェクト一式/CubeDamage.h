//============================================
//
//	�L���[�u�_���[�W [CubeDamage.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _CUBEDAMAGE_H_
#define _CUBEDAMAGE_H_

#include "main.h"
#include "objmeshCube.h"

class CObject3D;

//�I�u�W�F�N�g���b�V���t�B�[���h�N���X
class CCubeDamage : public CObjmeshCube
{
public:
	CCubeDamage(int nPriority = 4);
	~CCubeDamage();

	//�L���[�u�̎��
	enum CUBETYPE
	{
		CUBETYPE_EXPLOSION = 0,
		CUBETYPE_NORMAL,
		CUBETYPE_BREAK,
		CUBETYPE_MAX,
	};

	static CCubeDamage* Create(void);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void UninitExplosion(void);
	bool CollisionDamageBlock(D3DXVECTOR3 pPos, D3DXVECTOR3 Size, float* Damage);
	bool CollisionShadow(void);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	void SetCubeType(CUBETYPE Set);
	CUBETYPE GetCubeType(void) { return m_CubeType; }
	void SetDamage(float Damage) { m_fDamage = Damage; }
	void SetSpinCount(D3DXVECTOR3 Cnt) { m_fSpinCount = Cnt; }
	D3DXVECTOR3 GetSpinCount(void) { return m_fSpinCount; }
	void SetSpinSpeedX(float Speed) { m_fSpinSpeed.x = Speed; }
	void SetSpinSpeedY(float Speed) { m_fSpinSpeed.y = Speed; }
	void SetSpinSpeedZ(float Speed) { m_fSpinSpeed.z = Speed; }
	D3DXVECTOR3 GetSpinSpeed(void) { return m_fSpinSpeed; }
	void SetUseSpin(bool Set) { m_bSpin = Set; }
	bool GetUseSpin(void) { return m_bSpin; }
	void SetSpinPos(D3DXVECTOR3 Pos) { SpinPos = Pos; }
	D3DXVECTOR3 GetSpinPos(void) { return SpinPos; }
	void SetMove(D3DXVECTOR3 Move) { m_Move = Move; }
	D3DXVECTOR3 GetMove(void) { return m_Move; }
	void SetSpinDistance(float Dis) { m_fSpinDistance = Dis; }
	float GetSpinDistance(void) { return m_fSpinDistance; }
	void SetSpinDisMove(float Move) { m_fSpinDisMove = Move; }
	float GetSpinDisMove(void) { return m_fSpinDisMove; }
	static void SetExplosionCount(int Count) { m_nExplosionCount = Count; }
	static int GetExplosionNum(void) { return m_nExplosionNum; }
	void SetLife(int Life) { m_nLife = Life; }
	int GetLife(void) { return m_nLife; }
	void SetSpinSinCos(int Set) { SpinSinCos = Set; }
	bool CollisionBlock(void);	//�I�u�W�F�N�g�Ƃ̓����蔻��
protected:

private:
	void ExplosionSet(void);

	float m_fDamage;				//�_���[�W��
	D3DXVECTOR3 m_posOld;			//�ߋ��̈ʒu
	D3DXVECTOR3 m_pos;				//�ʒu
	D3DXVECTOR3 m_Move;				//�ړ���
	D3DXVECTOR3 SpinPos;			//��]�̒��S�ʒu
	float m_fSpinDistance;			//��]�̒��S����̋���
	float m_fSpinDisMove;			//��]�̒��S����̋����̈ړ���
	D3DXVECTOR3 m_fSpinCount;		//��]�n�̓����̎��Ɏg�p
	D3DXVECTOR3 m_fSpinSpeed;		//��]���x
	D3DXVECTOR3 m_fBOOLSpin;		//��]�������Ă��邩�ۂ�
	bool m_bSpin;					//��]�n�̓����̎��Ɏg�p
	CUBETYPE m_CubeType;			//�u���b�N�̎��
	CObject3D* m_pShadow;			//�e
	static int m_nExplosionCount;	//�����܂ł̃J�E���g
	static int m_nExplosionNum;		//�����L���[�u�̌�
	int m_nExplosionIdx;			//�����L���[�u�̔ԍ�
	int m_nLife;					//�L���[�u�̎���
	int SpinSinCos;					//�X�s���̎��
};
#endif