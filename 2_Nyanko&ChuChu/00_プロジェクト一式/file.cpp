//============================================
//
// ファイルのメイン処理[file.cpp]
// Author：小原立暉
//
//============================================
//********************************************
// インクルードファイル
//********************************************
#include "manager.h"
#include "scene.h"
#include "file.h"
#include "object.h"

#include "obstacle_manager.h"
#include "block_manager.h"
#include "game.h"
#include "edit.h"

//--------------------------------------------
// 無名名前空間
//--------------------------------------------
namespace
{
	const char* TXT[CFile::TYPE_MAX] =
	{
		"data\\TXT\\Obstacle.txt",			// 障害物のテキスト
		"data\\TXT\\MapObstacle1.txt",		// マップの障害物1のテキスト
		"data\\TXT\\MapObstacle2.txt",		// マップの障害物2のテキスト
		"data\\TXT\\MapObstacle3.txt",		// マップの障害物3のテキスト
		"data\\TXT\\MapObstacleSample.txt",	// マップの障害物サンプルのテキスト
		"data\\TXT\\Block1.txt",			// マップのブロック1のテキスト
		"data\\TXT\\Block2.txt",			// マップのブロック2のテキスト
		"data\\TXT\\Block3.txt",			// マップのブロック3のテキスト
		"data\\TXT\\BlockSample.txt",		// マップのブロックサンプルのテキスト
		"data\\TXT\\Block.txt",				// ブロックのテキスト
		"data\\TXT\\Tutorial.txt",			// チュートリアルのデフォルトブロック
		"data\\TXT\\TutorialTable.txt",		//チュートリアルのテーブル用ブロック
		"data\\TXT\\TutorialKill.txt",		// チュートリアルのキル用ブロック
		"data\\TXT\\TutorialAction.txt",	// チュートリアルのアクション用ブロック
	};
}

//--------------------------------------------
// 静的メンバ変数宣言
//--------------------------------------------
const char* CFile::c_apBooleanDisp[2] =					// bool型の表示
{
	"FALSE",							// TRUE
	"TRUE",								// FALSE
};

//===========================================
// コンストラクタ
//===========================================
CFile::CFile()
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;		// 位置
		m_ObstacleInfo.rot[nCntInfo] = NONE_D3DXVECTOR3;		// 位置
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;	// 種類
		m_BlockInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;			// 位置
		m_BlockInfo.rotType[nCntInfo] = CBlock::ROTTYPE_FRONT;	// 向きの種類
		m_BlockInfo.type[nCntInfo] = CBlock::TYPE_CARDBOARD;	// 種類
	}

	// 総数をクリアする
	m_ObstacleInfo.nNum = 0;			// 障害物
	m_BlockInfo.nNum = 0;				// ブロック

	// 成功状況をクリアする
	m_ObstacleInfo.bSuccess = false;	// 障害物
	m_BlockInfo.bSuccess = false;		// ブロック
}

//===========================================
// デストラクタ
//===========================================
CFile::~CFile()
{

}

//===========================================
// セーブ処理
//===========================================
HRESULT CFile::Save(const TYPE type)
{
	switch (type)
	{
	case TYPE_OBSTACLE:

		// 障害物のセーブ処理
		if (FAILED(SaveObstacle(TXT[TYPE_OBSTACLE])))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE1:

		// 障害物のセーブ処理
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLE1])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE2:

		// 障害物のセーブ処理
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLE2])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE3:

		// 障害物のセーブ処理
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLE3])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLESAMPLE:

		// 障害物のセーブ処理
		if (FAILED(SaveObstacle(TXT[TYPE_MAP_OBSTACLESAMPLE])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK1:

		// 障害物のセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCK1])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK2:

		// 障害物のセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCK2])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK3:

		// 障害物のセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCK3])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCKSAMPLE:

		// 障害物のセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_MAP_BLOCKSAMPLE])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_BLOCK:

		// ブロックのセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_BLOCK])))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

	case TYPE_TUTORIAL_DEFULT:

		// ブロックのセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_DEFULT])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_TABLE:

		// ブロックのセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_TABLE])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_KILL:

		// ブロックのセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_KILL])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_ACTION:

		// ブロックのセーブ処理
		if (FAILED(SaveBlock(TXT[TYPE_TUTORIAL_ACTION])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// ロード処理
//===========================================
HRESULT CFile::Load(const TYPE type)
{
	switch (type)
	{
	case TYPE_OBSTACLE:

		// 障害物のロード処理
		if (FAILED(LoadObstacle(TXT[TYPE_OBSTACLE])))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE1:

		// 障害物のロード処理
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLE1])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE2:

		// 障害物のロード処理
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLE2])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLE3:

		// 障害物のロード処理
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLE3])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_OBSTACLESAMPLE:

		// 障害物のロード処理
		if (FAILED(LoadObstacle(TXT[TYPE_MAP_OBSTACLESAMPLE])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK1:

		// 障害物のロード処理
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCK1])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK2:

		// 障害物のロード処理
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCK2])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCK3:

		// 障害物のロード処理
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCK3])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_MAP_BLOCKSAMPLE:

		// 障害物のロード処理
		if (FAILED(LoadBlock(TXT[TYPE_MAP_BLOCKSAMPLE])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_BLOCK:

		// ブロックのロード処理
		if (FAILED(LoadBlock(TXT[TYPE_BLOCK])))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_DEFULT:

		// ブロックのロード処理
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_DEFULT])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_TABLE:

		// ブロックのロード処理
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_TABLE])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}
		break;

	case TYPE_TUTORIAL_KILL:

		// ブロックのロード処理
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_KILL])))
		{ // 失敗した場合

		  // 失敗を返す
			return E_FAIL;
		}

		break;

	case TYPE_TUTORIAL_ACTION:

		// ブロックのロード処理
		if (FAILED(LoadBlock(TXT[TYPE_TUTORIAL_ACTION])))
		{ // 失敗した場合

			// 失敗を返す
			return E_FAIL;
		}

		break;

	default:

		// 停止
		assert(false);

		break;
	}

	// 結果を返す
	return S_OK;
}

//===========================================
// マップの設定処理
//===========================================
void CFile::FalseSuccess(void)
{
	// 成功状況をクリアする
	m_ObstacleInfo.bSuccess = false;	// 障害物
	m_BlockInfo.bSuccess = false;		// ブロック
}

//===========================================
// マップの設定処理
//===========================================
void CFile::SetMap(void)
{
	if (m_BlockInfo.bSuccess == true)
	{ // 成功状況が true の場合

		for (int nCntBlock = 0; nCntBlock < m_BlockInfo.nNum; nCntBlock++)
		{
			// ブロックの生成処理
			CBlock::Create(m_BlockInfo.pos[nCntBlock], m_BlockInfo.rotType[nCntBlock], m_BlockInfo.type[nCntBlock]);
		}
	}

	if (m_ObstacleInfo.bSuccess == true)
	{ // 成功状況が true の場合

		for (int nCntObst = 0; nCntObst < m_ObstacleInfo.nNum; nCntObst++)
		{
			// 障害物の生成処理
			CObstacle::Create(m_ObstacleInfo.pos[nCntObst], m_ObstacleInfo.rot[nCntObst], m_ObstacleInfo.type[nCntObst]);
		}
	}
}

//===========================================
// 初期化処理
//===========================================
HRESULT CFile::Init(void)
{
	for (int nCntInfo = 0; nCntInfo < MAX_FILE_DATA; nCntInfo++)
	{
		m_ObstacleInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;		// 位置
		m_ObstacleInfo.rot[nCntInfo] = NONE_D3DXVECTOR3;		// 位置
		m_ObstacleInfo.type[nCntInfo] = CObstacle::TYPE_HONEY;	// 種類
		m_BlockInfo.pos[nCntInfo] = NONE_D3DXVECTOR3;			// 位置
		m_BlockInfo.rotType[nCntInfo] = CBlock::ROTTYPE_FRONT;	// 向きの種類
		m_BlockInfo.type[nCntInfo] = CBlock::TYPE_CARDBOARD;	// 種類
	}

	// 総数をクリアする
	m_ObstacleInfo.nNum = 0;			// 障害物
	m_BlockInfo.nNum = 0;				// ブロック

	// 成功状況をクリアする
	m_ObstacleInfo.bSuccess = false;	// 障害物
	m_BlockInfo.bSuccess = false;		// ブロック

	// 成功を返す
	return S_OK;
}

//===========================================
// 終了処理
//===========================================
void CFile::Uninit(void)
{

}

//===========================================
// 障害物のセーブ処理
//===========================================
HRESULT CFile::SaveObstacle(const char *cFileName)
{
	// ローカル変数宣言
	CObstacle* pObstacle = CObstacleManager::Get()->GetTop();		// 先頭の障害物を代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(cFileName, "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pObstacle != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_OBSTACLE\n");	// 障害物の設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pObstacle->GetPos().x, pObstacle->GetPos().y, pObstacle->GetPos().z);			// 位置を書き込む

			fprintf(pFile, "\tROT = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pObstacle->GetRot().x, pObstacle->GetRot().y, pObstacle->GetRot().z);			// 向きを書き込む

			fprintf(pFile, "\tTYPE = ");		// 種類の設定を書き込む
			fprintf(pFile, "%d\n", pObstacle->GetType());			// 種類を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_OBSTACLE\n\n");	// 障害物の設定の終了を書き込む

			// 次のオブジェクトを代入する
			pObstacle = pObstacle->GetNext();
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// ブロックのセーブ処理
//===========================================
HRESULT CFile::SaveBlock(const char *cFileName)
{
	// ローカル変数宣言
	CBlock* pBlock = CBlockManager::Get()->GetTop();		// 先頭のブロックを代入する

	// ポインタを宣言
	FILE *pFile;				// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(cFileName, "w");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		while (pBlock != nullptr)
		{ // オブジェクトへのポインタが NULL じゃなかった場合

			// 文字列を書き込む
			fprintf(pFile, "SET_BLOCK\n");		// ブロックの設定を書き込む

			fprintf(pFile, "\tPOS = ");			// 位置の設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pBlock->GetPos().x, pBlock->GetPos().y, pBlock->GetPos().z);			// 位置を書き込む

			fprintf(pFile, "\tROT = ");			// 向きの設定を書き込む
			fprintf(pFile, "%.1f %.1f %.1f\n", pBlock->GetRot().x, pBlock->GetRot().y, pBlock->GetRot().z);			// 向きを書き込む

			fprintf(pFile, "\tTYPE = ");		// 種類の設定を書き込む
			fprintf(pFile, "%d\n", pBlock->GetType());			// 種類を書き込む

			// 文字列を書き込む
			fprintf(pFile, "END_SET_BLOCK\n\n");	// ブロックの設定の終了を書き込む

			// 次のオブジェクトを代入する
			pBlock = pBlock->GetNext();
		}

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// 障害物のロード処理
//===========================================
HRESULT CFile::LoadObstacle(const char *cFileName)
{
	// 変数を宣言
	int nEnd;							// テキスト読み込み終了の確認用
	char aString[MAX_STRING];			// テキストの文字列の代入用
	m_ObstacleInfo.nNum = 0;			// 総数
	m_ObstacleInfo.bSuccess = false;	// 成功状況

	// ポインタを宣言
	FILE *pFile;						// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(cFileName, "r");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		do
		{ // 読み込んだ文字列が EOF ではない場合ループ

			// ファイルから文字列を読み込む
			nEnd = fscanf(pFile, "%s", &aString[0]);	// テキストを読み込みきったら EOF を返す

			if (strcmp(&aString[0], "SET_OBSTACLE") == 0)
			{ // 読み込んだ文字列が SET_OBSTACLE の場合

				do
				{ // 読み込んだ文字列が END_SET_OBSTACLE ではない場合ループ

				  // ファイルから文字列を読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // 読み込んだ文字列が POS の場合

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%f%f%f",
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].x,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].y,
							&m_ObstacleInfo.pos[m_ObstacleInfo.nNum].z);		// 位置を読み込む
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // 読み込んだ文字列が POS の場合

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%f%f%f",
							&m_ObstacleInfo.rot[m_ObstacleInfo.nNum].x,
							&m_ObstacleInfo.rot[m_ObstacleInfo.nNum].y,
							&m_ObstacleInfo.rot[m_ObstacleInfo.nNum].z);		// 位置を読み込む
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // 読み込んだ文字列が TYPE の場合

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%d",
							&m_ObstacleInfo.type[m_ObstacleInfo.nNum]);		// 位置を読み込む
					}

				} while (strcmp(&aString[0], "END_SET_OBSTACLE") != 0);		// 読み込んだ文字列が END_SET_OBSTACLE ではない場合ループ

				// データの総数を増やす
				m_ObstacleInfo.nNum++;
			}
		} while (nEnd != EOF);				// 読み込んだ文字列が EOF ではない場合ループ

		// ファイルを閉じる
		fclose(pFile);

		// 成功状況を true にする
		m_ObstacleInfo.bSuccess = true;
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//===========================================
// ブロックのロード処理
//===========================================
HRESULT CFile::LoadBlock(const char *cFileName)
{
	// 変数を宣言
	int nEnd;							// テキスト読み込み終了の確認用
	char aString[MAX_STRING];			// テキストの文字列の代入用
	m_BlockInfo.nNum = 0;				// 総数
	m_BlockInfo.bSuccess = false;		// 成功状況

	// ポインタを宣言
	FILE *pFile;						// ファイルポインタ

	// ファイルを読み込み形式で開く
	pFile = fopen(cFileName, "r");

	if (pFile != nullptr)
	{ // ファイルが開けた場合

		do
		{ // 読み込んだ文字列が EOF ではない場合ループ

			// ファイルから文字列を読み込む
			nEnd = fscanf(pFile, "%s", &aString[0]);	// テキストを読み込みきったら EOF を返す

			if (strcmp(&aString[0], "SET_BLOCK") == 0)
			{ // 読み込んだ文字列が SET_BLOCK の場合

				do
				{ // 読み込んだ文字列が END_SET_BLOCK ではない場合ループ

				  // ファイルから文字列を読み込む
					fscanf(pFile, "%s", &aString[0]);

					if (strcmp(&aString[0], "POS") == 0)
					{ // 読み込んだ文字列が POS の場合

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%f%f%f",
							&m_BlockInfo.pos[m_BlockInfo.nNum].x,
							&m_BlockInfo.pos[m_BlockInfo.nNum].y,
							&m_BlockInfo.pos[m_BlockInfo.nNum].z);		// 位置を読み込む
					}
					else if (strcmp(&aString[0], "ROT") == 0)
					{ // 読み込んだ文字列が ROT の場合
						float fRotType = 0.0f;

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%s", &aString[0]);				// 向きを読み込む (不要)
						fscanf(pFile, "%f", &fRotType);					// 向きを読み込む
						fscanf(pFile, "%s", &aString[0]);				// 向きを読み込む (不要)

						if (fRotType <= -1.57f)
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_RIGHT;
						}
						else if (fRotType <= 0.1f)
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_FRONT;
						}
						else if (fRotType <= 1.7f)
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_LEFT;
						}
						else
						{
							m_BlockInfo.rotType[m_BlockInfo.nNum] = CBlock::ROTTYPE::ROTTYPE_BACK;
						}
					}
					else if (strcmp(&aString[0], "TYPE") == 0)
					{ // 読み込んだ文字列が TYPE の場合

						fscanf(pFile, "%s", &aString[0]);				// = を読み込む (不要)
						fscanf(pFile, "%d",
							&m_BlockInfo.type[m_BlockInfo.nNum]);		// 位置を読み込む
					}

				} while (strcmp(&aString[0], "END_SET_BLOCK") != 0);		// 読み込んだ文字列が END_SET_BLOCK ではない場合ループ

				// データの総数を増やす
				m_BlockInfo.nNum++;
			}
		} while (nEnd != EOF);				// 読み込んだ文字列が EOF ではない場合ループ

		// ファイルを閉じる
		fclose(pFile);

		// 成功状況を true にする
		m_BlockInfo.bSuccess = true;
	}
	else
	{ // ファイルが開けなかった場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}