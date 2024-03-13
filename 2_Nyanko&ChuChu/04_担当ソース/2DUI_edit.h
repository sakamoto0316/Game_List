//============================================
//
//	2D�G�f�B�b�g [2DUI_edit.h]
//	Author:sakamoto kai
//
//============================================
#ifndef _2DUI_EDIT_H_
#define _2DUI_EDIT_H_

#include "main.h"
#include "object.h"

#define LOADUI_NAME ("data\\TXT\\Set2DUI")	//�X�^�[�g���b�Z�[�W�����邩�ǂ����̊m�F

//�O���錾
class CObject2D;

//�}�b�v�N���X
class C2DUIEdit
{
public:
	//-------------------------------------------------------------------------
	// �T�E���h�ꗗ
	//-------------------------------------------------------------------------
	enum UI_LABEL
	{
		UI_LABEL_BGM_TITLE = 0,		// �^�C�g��BGM
		UI_LABEL_BGM_GAME,			// �Q�[��BGM
		UI_LABEL_BGM_RESULT,		// ���U���gBGM
		UI_LABEL_MAX				// ���̗񋓌^�̑���
	};

	struct UIINFO
	{
		char *pFilename;	// �t�@�C����
		char *pCommentname;	// �R�����g��
	};

	C2DUIEdit();
	~C2DUIEdit();

	static C2DUIEdit *Create();
	void Uninit(void);
	void Update(void);

	void LoadData(char *Name, D3DXVECTOR3 pos);

	D3DXVECTOR3 GetEditPos(void) { return m_EditPos; }
protected:

private:
	void DeleteObject(D3DXVECTOR3 pos);
	void DebugObject(void);
	void SaveData(void);

	static  CObject2D *m_pEditUI;
	int ObjectType;
	D3DXVECTOR3 m_EditPos;		//���W
	D3DXVECTOR3 m_EditRot;		//����
	D3DXVECTOR3 m_EditSize;		//����
	char *m_cTextureName;		//�e�N�X�`���̖��O
	int m_nSideCount;			//�ړ��J�E���g
	float m_nSideDistance;		//�T�C�Y�ύX�l
	static UIINFO m_aTextureInfo[UI_LABEL_MAX];	// �T�E���h�̏��
};
#endif