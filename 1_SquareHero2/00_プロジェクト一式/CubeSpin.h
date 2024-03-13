//============================================
//
//	�L���[�u�X�s�� [CubeSpin.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _CUBESPIN_H_
#define _CUBESPIN_H_

#include "main.h"
#include "objmeshCube.h"

class CObject3D;
class CCubeDamage;

//�I�u�W�F�N�g���b�V���t�B�[���h�N���X
class CCubeSpin : public CObject
{
public:
	CCubeSpin(int NumCube, int nPriority = 4);
	~CCubeSpin();

	static CCubeSpin* Create(int NumCube);

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetDamage(float Damage) { m_fDamage = Damage; }
	void SetPos(D3DXVECTOR3 pos) { m_pos = pos; }
	void SetMove(D3DXVECTOR3 move) { m_move = move; }
	void SetSpinDistance(float Dis) { m_fSpinDistance = Dis; }
	float GetSpinDistance(void) { return m_fSpinDistance; }
	void SetSpinDisMove(float Move) { m_fSpinDisMove = Move; }
	float GetSpinDisMove(void) { return m_fSpinDisMove; }
	void SetSpinSpeedX(float Speed) { m_fSpinSpeed.x = Speed; }
	void SetSpinSpeedY(float Speed) { m_fSpinSpeed.y = Speed; }
	void SetSpinSpeedZ(float Speed) { m_fSpinSpeed.z = Speed; }
	D3DXVECTOR3 GetSpinSpeed(void) { return m_fSpinSpeed; }
protected:

private:
	int m_nNumCube;				//�L���[�u�̐�
	float m_fDamage;			//�_���[�W��
	D3DXVECTOR3 m_pos;			//�ʒu
	D3DXVECTOR3 m_move;			//�ړ���
	int m_nLife;				//����
	float m_fSpinDistance;		//��]�̒��S����̋���
	float m_fSpinDisMove;		//��]�̒��S����̋����̈ړ���
	D3DXVECTOR3 m_fSpinSpeed;	//��]���x
	CCubeDamage* m_apCubeDamage[128];	//�L���[�u�_���[�W�̃|�C���^
};
#endif