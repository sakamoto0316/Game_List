#ifndef _WALL_H_	//���̃}�N������`����Ă��Ȃ����
#define _WALL_H_	//��d�C���N���[�h�h�~�}�N��

#include "main.h"
#include "Object3D.h"

class CWall :public CObject3D
{
public:
	CWall();
	CWall(PRIORITY priority);
	~CWall();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CWall* Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, CObject::PRIORITY pritype);

private:

	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_rot;
	D3DXVECTOR3 m_size;

};
#endif // !_WALL_H_