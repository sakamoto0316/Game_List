#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

class CSound
{
public:
	CSound();
	~CSound();

	//*****************************************************************************
	// サウンド一覧
	//*****************************************************************************
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,			// BGM0						
		SOUND_LABEL_BGM_TUTORIAL,			// BGM1
		SOUND_LABEL_BGM_GAME,				// BGM2
		SOUND_LABEL_BGM_RESULT,				// BGM3
		SOUND_LABEL_SE_ATTACK_NORMAL,		// 攻撃
		SOUND_LABEL_SE_ATTACK_NOBULLET,		// 弾切れの時の音
		SOUND_LABEL_SE_BREAK_BLOCK,			// ブロック破壊
		SOUND_LABEL_SE_PLAYER_DAMAGE,		// プレイヤーダメージ
		SOUND_LABEL_SE_ENEMY_DAMAGE,		// 敵ダメージ
		SOUND_LABEL_SE_ULT,					// 必殺技
		SOUND_LABEL_SE_CAMERA_WAVE,			// 地響き
		SOUND_LABEL_SE_SELECT_PUSH,			// 選択音
		SOUND_LABEL_SE_ENTER_PUSH,			// 決定音
		SOUND_LABEL_SE_PLAYER_TEXT,			// プレイヤーの説明出現音
		SOUND_LABEL_SE_PLAYER_JUMP,			// プレイヤーのジャンプ音
		SOUND_LABEL_SE_WARNING,				// 警告音
		SOUND_LABEL_SE_LEVELUP,				// レベルアップ音
		SOUND_LABEL_MAX,
	} SOUND_LABEL;

	//*****************************************************************************
	// メンバ関数宣言
	//*****************************************************************************
	HRESULT InitSound(HWND hWnd);
	void UninitSound(void);
	HRESULT PlaySound(SOUND_LABEL label);
	void StopSound(SOUND_LABEL label);
	void StopSound(void);

private:

	//*****************************************************************************
	// サウンド情報の構造体定義
	//*****************************************************************************
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	} SOUNDINFO;

	//*****************************************************************************
	// メンバ関数宣言
	//*****************************************************************************
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	//*****************************************************************************
	// メンバ変数宣言
	//*****************************************************************************
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	// サウンドの情報
	static SOUNDINFO m_aSoundInfo[SOUND_LABEL_MAX];
};
#endif
