//=============================================================================
//
// サウンド処理 [sound.cpp]
// Author 小原立暉
//
//=============================================================================
#include "sound.h"

//-----------------------------------------------------------------------------
// 静的メンバ変数宣言
//-----------------------------------------------------------------------------
CSound::SOUNDINFO CSound::m_aSoundInfo[CSound::SOUND_LABEL_MAX] =
{
	{ "data\\BGM\\TitleBGM.wav",-1 },		// タイトルBGM
	{ "data\\BGM\\EntryBGM.wav",-1 },		// エントリーBGM
	{ "data\\BGM\\GameBGM.wav",-1 },		// ゲームBGM
	{ "data\\BGM\\ResultBGM.wav",-1 },		// リザルトBGM
	{ "data\\BGM\\RankingBGM.wav",-1 },		// ランキングBGM
	{ "data\\BGM\\destiny_of_victory.wav",-1 },		// スピーカーBGM

	{ "data\\SE\\Select.wav",0 },			// 選択音
	{ "data\\SE\\Decide.wav",0 },			// 決定音
	{ "data\\SE\\victory.wav",0 },			// 勝利音
	{ "data\\SE\\CAT_Attack.wav",0},		// ネコの攻撃
	{ "data\\SE\\Cat_Attack_Hit.wav",0},	// ネコの攻撃がネズミにヒットしたときの音
	{ "data\\SE\\walk_cat.wav",0},			// ネコの歩行音
	{ "data\\SE\\walk_rat.wav",0},			// ネズミの歩行音
	{ "data\\SE\\mousetrap_HIT.wav",0},		// ネズミ取りにハマる音
	{ "data\\SE\\Cup_Falls.wav",0 },		// コップが落ちる音
	{ "data\\SE\\TV_sandstorm.wav",-1 },		// テレビの砂嵐
	{ "data\\SE\\press_the_switch.wav",0 },	// スイッチを押した時の音
	{ "data\\SE\\SetItem.wav",0},			// アイテム設置音
	{ "data\\SE\\cleaning.wav",-1 },		// 掃除機(ルンバ)
	{ "data\\SE\\Fan.wav",-1 },				// 扇風機
	{ "data\\SE\\med_bottle04.wav",0 },		// 画鋲
	{ "data\\SE\\Tarai_Hit.wav",0,},		// タライが頭に当たる
	{ "data\\SE\\bottle_roll.wav",-1 },		// ペットボトルが転がる音
	{ "data\\SE\\bottle_over.wav",0 },		// ペットボトルが倒れる音
	{ "data\\SE\\Pick_up.wav",0 },			// 拾った音
	{ "data\\SE\\tutorial_check.wav",0 },	// チュートリアルのチェック音
	{ "data\\SE\\TitleStart.wav",0 },		// タイトルのスタート音
	{ "data\\SE\\bubble.wav",0 },			// チュートリアルのふきだし出現音
	{ "data\\SE\\revival_gauge_save.wav",-1 },	// 復活最中の音
	{ "data\\SE\\mouse_revival.wav",0 },	// 復活音
	{ "data\\SE\\himo.wav",0 },				// ひも引っ張る音
	{ "data\\SE\\mari.wav",0 },				// まりの音
	{ "data\\SE\\honey_break.wav",0 },		// 蜂蜜の瓶が割れる音
	{ "data\\SE\\honey_leak.wav",0 },		// 蜂蜜が広がる音
	{ "data\\SE\\honey_walk.wav",0 },		// 蜂蜜の上歩く音
	{ "data\\SE\\book_down.wav",0 },		// 本が落ちる音
	{ "data\\SE\\block_attack.wav",0 },		// ブロック叩く音
	{ "data\\SE\\electricity_Biting.wav",-1 },	// 水のビリビリ音
	{ "data\\SE\\banana_down.wav",0 },		// バナナ落ちる音
	{ "data\\SE\\banana_turuturu.wav",0 },	// バナナ落ちる音
	{ "data\\SE\\leash.wav",0 },			// リード音
	{ "data\\SE\\Chu.wav",0 },				// ネズミの鳴き声の音
	{ "data\\SE\\finish.wav",0 },			// 終了の音
	{ "data\\SE\\rat_Chuchu.wav",0 },		// 文字が穴に入る音(タイトル)
	{ "data\\SE\\title_blown_away.wav",0 },	// 文字が吹き飛ばされる音(タイトル)
	{ "data\\SE\\START_collide.wav",0 },	// 文字がぶつかる音(タイトル)
	{ "data\\SE\\confusion.wav",0 },		// 気絶音
	{ "data\\SE\\screw_winding.wav",-1 },	// 車のねじ巻き音
	{ "data\\SE\\jump.wav",0 },				// ネズミのジャンプ音
	{ "data\\SE\\Ratmecha_Run.wav",-1 },	// ネズミメカの走行音
	{ "data\\SE\\Tutorial_OK.wav",0 },		// チュートリアルの実行完了音
	{ "data\\SE\\dynamite_explosion.wav",0 },	// ダイナマイトの爆発音
	{ "data\\SE\\CurtainOpen.wav",0 },		// カーテンの開く音
	{ "data\\SE\\Ratmecha_Break.wav",0 },	// ネズミメカの破壊音
	{ "data\\SE\\CatDamage.wav",0 },		// ネコのダメージ音
	{ "data\\SE\\CountStart.wav",0 },		// 最初のカウントダウン音
	{ "data\\SE\\CountEnd.wav",0 },			// 最後のカウントダウン音
};

//=============================================================================
// コンストラクタ
//=============================================================================
CSound::CSound()
{
	
}

//=============================================================================
// デストラクタ
//=============================================================================
CSound::~CSound()
{

}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSound::Init(HWND hWnd)
{
	HRESULT hr;

	// COMライブラリの初期化
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// XAudio2オブジェクトの作成
	hr = XAudio2Create(&m_pXAudio2, 0);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "XAudio2オブジェクトの作成に失敗！", "警告！", MB_ICONWARNING);

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// マスターボイスの生成
	hr = m_pXAudio2->CreateMasteringVoice(&m_pMasteringVoice);
	if (FAILED(hr))
	{
		MessageBox(hWnd, "マスターボイスの生成に失敗！", "警告！", MB_ICONWARNING);

		if (m_pXAudio2 != NULL)
		{
			// XAudio2オブジェクトの開放
			m_pXAudio2->Release();
			m_pXAudio2 = NULL;
		}

		// COMライブラリの終了処理
		CoUninitialize();

		return E_FAIL;
	}

	// サウンドデータの初期化
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		HANDLE hFile;
		DWORD dwChunkSize = 0;
		DWORD dwChunkPosition = 0;
		DWORD dwFiletype;
		WAVEFORMATEXTENSIBLE wfx;
		XAUDIO2_BUFFER buffer;

		// バッファのクリア
		memset(&wfx, 0, sizeof(WAVEFORMATEXTENSIBLE));
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));

		// サウンドデータファイルの生成
		hFile = CreateFile(m_aSoundInfo[nCntSound].pFilename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
		if (hFile == INVALID_HANDLE_VALUE)
		{
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(1)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}
		if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		{// ファイルポインタを先頭に移動
			MessageBox(hWnd, "サウンドデータファイルの生成に失敗！(2)", "警告！", MB_ICONWARNING);
			return HRESULT_FROM_WIN32(GetLastError());
		}

		// WAVEファイルのチェック
		hr = CheckChunk(hFile, 'FFIR', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &dwFiletype, sizeof(DWORD), dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		if (dwFiletype != 'EVAW')
		{
			MessageBox(hWnd, "WAVEファイルのチェックに失敗！(3)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// フォーマットチェック
		hr = CheckChunk(hFile, ' tmf', &dwChunkSize, &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		hr = ReadChunkData(hFile, &wfx, dwChunkSize, dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "フォーマットチェックに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// オーディオデータ読み込み
		hr = CheckChunk(hFile, 'atad', &m_aSizeAudio[nCntSound], &dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(1)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}
		m_apDataAudio[nCntSound] = (BYTE*)malloc(m_aSizeAudio[nCntSound]);
		hr = ReadChunkData(hFile, m_apDataAudio[nCntSound], m_aSizeAudio[nCntSound], dwChunkPosition);
		if (FAILED(hr))
		{
			MessageBox(hWnd, "オーディオデータ読み込みに失敗！(2)", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// ソースボイスの生成
		hr = m_pXAudio2->CreateSourceVoice(&m_apSourceVoice[nCntSound], &(wfx.Format));
		if (FAILED(hr))
		{
			MessageBox(hWnd, "ソースボイスの生成に失敗！", "警告！", MB_ICONWARNING);
			return S_FALSE;
		}

		// バッファの値設定
		memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
		buffer.AudioBytes = m_aSizeAudio[nCntSound];
		buffer.pAudioData = m_apDataAudio[nCntSound];
		buffer.Flags = XAUDIO2_END_OF_STREAM;
		buffer.LoopCount = m_aSoundInfo[nCntSound].nCntLoop;

		// オーディオバッファの登録
		m_apSourceVoice[nCntSound]->SubmitSourceBuffer(&buffer);

		// ファイルをクローズ
		CloseHandle(hFile);
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSound::Uninit(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);

			// ソースボイスの破棄
			m_apSourceVoice[nCntSound]->DestroyVoice();
			m_apSourceVoice[nCntSound] = NULL;

			// オーディオデータの開放
			free(m_apDataAudio[nCntSound]);
			m_apDataAudio[nCntSound] = NULL;
		}
	}

	// マスターボイスの破棄
	m_pMasteringVoice->DestroyVoice();
	m_pMasteringVoice = NULL;

	if (m_pXAudio2 != NULL)
	{
		// XAudio2オブジェクトの開放
		m_pXAudio2->Release();
		m_pXAudio2 = NULL;
	}

	// COMライブラリの終了処理
	CoUninitialize();
}

//=============================================================================
// セグメント再生(再生中なら停止)
//=============================================================================
HRESULT CSound::Play(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;
	XAUDIO2_BUFFER buffer;

	// バッファの値設定
	memset(&buffer, 0, sizeof(XAUDIO2_BUFFER));
	buffer.AudioBytes = m_aSizeAudio[label];
	buffer.pAudioData = m_apDataAudio[label];
	buffer.Flags = XAUDIO2_END_OF_STREAM;
	buffer.LoopCount = m_aSoundInfo[label].nCntLoop;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);

	if (xa2state.BuffersQueued != 0)
	{// 再生中

		// 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}

	// オーディオバッファの登録
	m_apSourceVoice[label]->SubmitSourceBuffer(&buffer);

	// 再生
	m_apSourceVoice[label]->Start(0);

	return S_OK;
}

//=============================================================================
// セグメント停止(ラベル指定)
//=============================================================================
void CSound::Stop(SOUND_LABEL label)
{
	XAUDIO2_VOICE_STATE xa2state;

	// 状態取得
	m_apSourceVoice[label]->GetState(&xa2state);
	if (xa2state.BuffersQueued != 0)
	{// 再生中

		// 一時停止
		m_apSourceVoice[label]->Stop(0);

		// オーディオバッファの削除
		m_apSourceVoice[label]->FlushSourceBuffers();
	}
}

//=============================================================================
// セグメント停止(全て)
//=============================================================================
void CSound::Stop(void)
{
	// 一時停止
	for (int nCntSound = 0; nCntSound < SOUND_LABEL_MAX; nCntSound++)
	{
		if (m_apSourceVoice[nCntSound] != NULL)
		{
			// 一時停止
			m_apSourceVoice[nCntSound]->Stop(0);
		}
	}
}

//=============================================================================
// チャンクのチェック
//=============================================================================
HRESULT CSound::CheckChunk(HANDLE hFile, DWORD format, DWORD *pChunkSize, DWORD *pChunkDataPosition)
{
	HRESULT hr = S_OK;
	DWORD dwRead;
	DWORD dwChunkType;
	DWORD dwChunkDataSize;
	DWORD dwRIFFDataSize = 0;
	DWORD dwFileType;
	DWORD dwBytesRead = 0;
	DWORD dwOffset = 0;

	if (SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを先頭に移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	while (hr == S_OK)
	{
		if (ReadFile(hFile, &dwChunkType, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		if (ReadFile(hFile, &dwChunkDataSize, sizeof(DWORD), &dwRead, NULL) == 0)
		{// チャンクデータの読み込み
			hr = HRESULT_FROM_WIN32(GetLastError());
		}

		switch (dwChunkType)
		{
		case 'FFIR':
			dwRIFFDataSize = dwChunkDataSize;
			dwChunkDataSize = 4;
			if (ReadFile(hFile, &dwFileType, sizeof(DWORD), &dwRead, NULL) == 0)
			{// ファイルタイプの読み込み
				hr = HRESULT_FROM_WIN32(GetLastError());
			}
			break;

		default:
			if (SetFilePointer(hFile, dwChunkDataSize, NULL, FILE_CURRENT) == INVALID_SET_FILE_POINTER)
			{// ファイルポインタをチャンクデータ分移動
				return HRESULT_FROM_WIN32(GetLastError());
			}
		}

		dwOffset += sizeof(DWORD) * 2;
		if (dwChunkType == format)
		{
			*pChunkSize = dwChunkDataSize;
			*pChunkDataPosition = dwOffset;

			return S_OK;
		}

		dwOffset += dwChunkDataSize;
		if (dwBytesRead >= dwRIFFDataSize)
		{
			return S_FALSE;
		}
	}

	return S_OK;
}

//=============================================================================
// チャンクデータの読み込み
//=============================================================================
HRESULT CSound::ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset)
{
	DWORD dwRead;

	if (SetFilePointer(hFile, dwBufferoffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
	{// ファイルポインタを指定位置まで移動
		return HRESULT_FROM_WIN32(GetLastError());
	}

	if (ReadFile(hFile, pBuffer, dwBuffersize, &dwRead, NULL) == 0)
	{// データの読み込み
		return HRESULT_FROM_WIN32(GetLastError());
	}

	return S_OK;
}

