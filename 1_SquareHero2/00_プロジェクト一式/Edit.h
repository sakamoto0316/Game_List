//============================================
//
//	�G�f�B�b�g [Edit.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _EDIT_H_
#define _EDIT_H_

#include "main.h"
#include "object.h"

#define DATA_NAME ("data\\TXT\\Stage.txt")

//�O���錾
class CObjmeshCube;

//�}�b�v�N���X
class CEdit
{
public:
	CEdit();
	~CEdit();

	static CEdit* Create();
	void Uninit(void);
	void Update(void);

protected:

private:
	void CollisionBlock(void);	//�I�u�W�F�N�g�Ƃ̓����蔻��
	void SaveData(void);

	float MoveWidth;		//�ړ���
	CObjmeshCube* m_pEditBlock;
};
#endif