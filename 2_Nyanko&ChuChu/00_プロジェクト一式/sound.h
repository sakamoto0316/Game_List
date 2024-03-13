//=============================================================================
//
// サウンド処理 [sound.h]
// Author 小原立暉
//
//=============================================================================
#ifndef _SOUND_H_					//このマクロ定義がされていなかったら
#define _SOUND_H_					//2重インクルード防止のマクロを定義する

#include "main.h"

// クラス定義(CSound)
class CSound
{
public:			// 誰でもアクセス出来る

	//-------------------------------------------------------------------------
	// サウンド一覧
	//-------------------------------------------------------------------------
	enum SOUND_LABEL
	{
		SOUND_LABEL_BGM_TITLE = 0,		// タイトルBGM
		SOUND_LABEL_BGM_ENTRY,			// エントリーBGM
		SOUND_LABEL_BGM_GAME,			// ゲームBGM
		SOUND_LABEL_BGM_RESULT,			// リザルトBGM
		SOUND_LABEL_BGM_RANKING,		// ランキングBGM
		SOUND_LABEL_BGM_SPEAKER,		// スピーカーBGM

		SOUND_LABEL_SE_SELECT,			// 選択音
		SOUND_LABEL_SE_DECIDE,			// 決定音
		SOUND_LABEL_SE_VICTORY,			//勝利音
		SOUND_LABEL_SE_CATATTACK,		//ネコが攻撃した時の音
		SOUND_LABEL_SE_CATATTACK_HIT,	//ネコの攻撃がネズミにヒットした音
		SOUND_LABEL_SE_CATWALK,			//ネコが歩く音
		SOUND_LABEL_SE_MOUSEWALK,		//ネズミが歩く音
		SOUND_LABEL_SE_MOUSETRAP_ADDICTED,	//ネズミ捕りにハマる音
		SOUND_LABEL_SE_THE_CUP_FALLS,	//コップが落ちた音
		SOUND_LABEL_SE_TV_SANDSTORM,	//テレビの砂嵐
		SOUND_LEBEL_SE_PUSH_SWITCH,		//スイッチを押した時の音
		SOUND_LABEL_SE_SETITEM,			//設置音
		SOUND_LABEL_SE_CLEANING,		//掃除機(ルンバ)
		SOUND_LABEL_SE_FAN,				//扇風機
		SOUND_LABEL_SE_THUMBTACK,		//画鋲
		SOUND_LABEL_SE_TUB,				//タライ
		SOUND_LABEL_SE_PETBOTTLES_ROLL,	//ペットボトルが転がる音
		SOUND_LABEL_SE_PETBOTTLES_FALL_DOWN, //ペットボトルが倒れる音
		SOUND_LABEL_SE_PICKED_UP,		//拾った音
		SOUND_LABEL_SE_CHECK,			// チュートリアルのチェック音
		SOUND_LABEL_SE_TITLE_START,		// タイトルのスタート音
		SOUND_LABEL_SE_TUTORIAL_BUBBLE,	// 吹き出しの出現音
		SOUND_LABEL_SE_REVIVAL_SAVE,	// 復活最中の音
		SOUND_LABEL_SE_REVIVAL,			// 復活音
		SOUND_LABEL_SE_HIMO,			// ひもの音
		SOUND_LABEL_SE_HAIRBALL,		// まりの音
		SOUND_LABEL_SE_HONEYBREAK,		// 蜂蜜の瓶が割れる音
		SOUND_LABEL_SE_HONEYLEAK,		// 蜂蜜が広がる音
		SOUND_LABEL_SE_HONEYWALK,		// 蜂蜜の上歩く音
		SOUND_LABEL_SE_BOOLDOWN,		// 本が落ちる音
		SOUND_LABEL_SE_BLOCKATTACK,		// ブロック叩く音
		SOUND_LABEL_SE_WATERBIRIBIRI,	// 水のビリビリ音
		SOUND_LABEL_SE_BANANADOWN,		// バナナ落ちる音
		SOUND_LABEL_SE_BANANATURUTURU,	// バナナ滑る音
		SOUND_LABEL_SE_LEASH,			// リード音
		SOUND_LABEL_SE_CHU,				// ネズミの鳴き声の音
		SOUND_LABEL_SE_FINISH,			// 終了の音
		SOUND_LABEL_SE_TITLEHOLE,		// 文字が穴に入る音(タイトル)
		SOUND_LABEL_SE_TITLEBLOW,		// 文字が吹き飛ばされる音(タイトル)
		SOUND_LABEL_SE_TITLECOLLIDE,	// 文字がぶつかる音(タイトル)
		SOUND_LABEL_SE_PIYOPIYO,		// 気絶音
		SOUND_LABEL_SE_NEZI,			// 車のねじ巻き音
		SOUND_LABEL_SE_JUMP,			// ネズミのジャンプ音
		SOUND_LABEL_SE_RATMECHA_RUN,	// ネズミメカの走行音
		SOUND_LABEL_SE_TUTORIAL_OK,		// チュートリアルの実行完了
		SOUND_LABEL_SE_DYNAMITE,		// ダイナマイト爆発音
		SOUND_LABEL_SE_CURTAIN_OPEN,	// カーテンの開く音
		SOUND_LABEL_SE_RATMECHA_BREAK,	// ネズミメカの破壊音
		SOUND_LABEL_SE_CATDAMAGE,		// ネコのダメージ音
		SOUND_LABEL_SE_COUNT_START,		// 最初のカウントダウン音
		SOUND_LABEL_SE_COUNT_END,		// 最後のカウントダウン音

		SOUND_LABEL_MAX					// この列挙型の総数
	};

	//-----------------------------------------------------------------------------
	// サウンド情報の構造体定義
	//-----------------------------------------------------------------------------
	struct SOUNDINFO
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウント
	};

	CSound();			// コンストラクタ
	~CSound();			// デストラクタ

	// メンバ関数
	HRESULT Init(HWND hWnd);
	void Uninit(void);
	HRESULT Play(SOUND_LABEL label);
	void Stop(SOUND_LABEL label);
	void Stop(void);

private:		// 自分だけアクセスできる

	// メンバ関数
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	// メンバ変数
	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ
	static SOUNDINFO m_aSoundInfo[CSound::SOUND_LABEL_MAX];	// サウンドの情報
};

#endif
