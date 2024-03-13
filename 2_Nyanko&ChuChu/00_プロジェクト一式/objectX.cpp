//============================================================
//
// Xファイル処理 [xfile.cpp]
// Author：小原立暉
//
//============================================================
//************************************************************
// インクルードファイル
//************************************************************
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "texture.h"

//------------------------------------------------------------
// コンスト定義
//------------------------------------------------------------
const char* CXFile::c_apModelData[CXFile::TYPE_MAX] =		// モデルの名前
{
	// オブジェクトモデル
	"data\\MODEL\\Ripple.x",				// 波紋
	"data\\MODEL\\Kari001.x",				// 仮プレイヤー
	"data\\MODEL\\WoodBlock.x",				// 木箱
	"data\\MODEL\\Cage.x",					// 武器小屋
	"data\\MODEL\\flowerFrac.x",			// 花瓶の破片
	"data\\MODEL\\plasticFrac.x",			// プラスチックケースの破片
	"data\\MODEL\\attackFrac.x",			// 猫の攻撃の破片
	"data\\MODEL\\Honey.x",					// 蜂蜜
	"data\\MODEL\\ToyCarScrew.x",			// おもちゃの車(ネジ)
	"data\\MODEL\\TitleWall.x",				// タイトルの壁
	"data\\MODEL\\Red_Roomba_Sub.x",		// ルンバのプロペラ{赤のアウトライン}
	"data\\MODEL\\Tarai.x",					// たらい
	"data\\MODEL\\Red_note4.x",				// 4分音符{赤のアウトライン}
	"data\\MODEL\\Red_note8.x",				// 8分音符{赤のアウトライン}
	"data\\MODEL\\Red_note16.x",			// 16分音符{赤のアウトライン}
	"data\\MODEL\\mousetrap_iron.x",		// ネズミ捕りの鉄部分
	"data\\MODEL\\TrapItem.x",				// ネズミ捕り(アイテム)
	"data\\MODEL\\Red_leashSet.x",			// 設置状態のリード{赤のアウトライン}
	"data\\MODEL\\Red_pin_floor.x",			// 設置状態の画鋲{赤のアウトライン}
	"data\\MODEL\\pin_one.x",				// 破片用の画鋲
	"data\\MODEL\\Senpuki_Fan.x",			// 扇風機(羽根)
	"data\\MODEL\\consent.x",				// コンセント
	"data\\MODEL\\arrow.x",					// 死亡矢印
	"data\\MODEL\\Red_banana_peel.x",		// バナナの皮{赤のアウトライン}
	"data\\MODEL\\Book001.x",				// 本(青)
	"data\\MODEL\\Book002.x",				// 本(緑)
	"data\\MODEL\\Book003.x",				// 本(黄)
	"data\\MODEL\\lever000.x",				// レバー(本体)
	"data\\MODEL\\lever001.x",				// レバー(棒)
	"data\\MODEL\\Red_Book000.x",			// 本(赤){赤のアウトライン}
	"data\\MODEL\\Red_Book001.x",			// 本(青){赤のアウトライン}
	"data\\MODEL\\Red_Book002.x",			// 本(緑){赤のアウトライン}
	"data\\MODEL\\Red_Book003.x",			// 本(黄){赤のアウトライン}
	"data\\MODEL\\Red_ToyCarBody.x",		// おもちゃの車(本体){赤のアウトライン}
	"data\\MODEL\\Red_ToyCarScrew.x",		// おもちゃの車(ネジ){赤のアウトライン}
	"data\\MODEL\\Red_HairBall.x",			// 毬{赤のアウトライン}
	"data\\MODEL\\Red_Pettobotoru.x",		// ペットボトル{赤のアウトライン}

	// ブロックモデル
	"data\\MODEL\\cardboard.x",				// 段ボール
	"data\\MODEL\\TissueBox.x",				// ティッシュ箱
	"data\\MODEL\\PenHolder.x",				// ペン立て
	"data\\MODEL\\RemoCon.x",				// リモコン
	"data\\MODEL\\bear.x",					// テディベア
	"data\\MODEL\\Clock.x",					// 時計
	"data\\MODEL\\rubbish.x",				// チリ紙
	"data\\MODEL\\milk_carton.x",			// 牛乳パック
	"data\\MODEL\\obaphone.x",				// オバフォン
	"data\\MODEL\\wii.x",					// Wii
	"data\\MODEL\\ds.x",					// DS
	"data\\MODEL\\HeadPhone.x",				// ヘッドフォン
	"data\\MODEL\\Pen.x",					// ペン
	"data\\MODEL\\AC_adapter.x",			// ACアダプター
	"data\\MODEL\\building_blocks.x",		// 積み木
	"data\\MODEL\\obaglasses.x",			// 眼鏡ケース
	"data\\MODEL\\pencil.x",				// 鉛筆
	"data\\MODEL\\picture_frames.x",		// 写真立て
	"data\\MODEL\\shelf.x",					// 戸棚
	"data\\MODEL\\pullshelf.x",				// 引き出し棚
	"data\\MODEL\\Kitchen.x",				// キッチン
	"data\\MODEL\\Reizouko.x",				// 冷蔵庫
	"data\\MODEL\\Table000.x",				// テーブル
	"data\\MODEL\\Table_Chair000.x",		// 机の椅子
	"data\\MODEL\\corkboard.x",				// コルクボード
	"data\\MODEL\\desk.x",					// デスク
	"data\\MODEL\\deskbook.x",				// デスク用の本
	"data\\MODEL\\fire_extingisher.x",		// 消火器
	"data\\MODEL\\Katen.x",					// カーテン
	"data\\MODEL\\KatenRail.x",				// カーテンのレール
	"data\\MODEL\\Tansu002.x",				// たんす
	"data\\MODEL\\TV_stand.x",				// テレビのスタンド
	"data\\MODEL\\WallPlus50.x",			// 50*100の壁
	"data\\MODEL\\WallPlus100.x",			// 100*100の壁
	"data\\MODEL\\door001.x",				// ドア
	"data\\MODEL\\Small_shelf.x",			// 小さな棚
	"data\\MODEL\\bookshelf.x",				// 横長の本棚
	"data\\MODEL\\tableshelf.x",			// テーブルの高さの棚
	"data\\MODEL\\sofa_sheet.x",			// ソファー（座面）
	"data\\MODEL\\sofa_backrest.x",			// ソファー（背もたれ）
	"data\\MODEL\\Chair_seat.x",			// 机の椅子(座面)
	"data\\MODEL\\Chair_backrest.x",		// 机の椅子(背もたれ)
	"data\\MODEL\\lever000.x",				// レバー(本体)
	"data\\MODEL\\window000.x",				// 窓
	"data\\MODEL\\wall_clock.x",			// 壁掛け時計
	"data\\MODEL\\wall_interior000.x",		// 壁のインテリア(棚)
	"data\\MODEL\\WallCross100.x",			// 横柱

	// 障害物モデル
	"data\\MODEL\\HoneyBottle.x",			// 蜂蜜のボトル
	"data\\MODEL\\Slime.x",					// スライム
	"data\\MODEL\\HairBall.x",				// 毬
	"data\\MODEL\\Pettobotoru.x",			// ペットボトル
	"data\\MODEL\\ToyCarBody.x",			// おもちゃの車(本体)
	"data\\MODEL\\Red_Roomba_Main.x",		// ルンバの本体{赤のアウトライン}
	"data\\MODEL\\Himo.x",					// ひも
	"data\\MODEL\\speaker.x",				// スピーカー
	"data\\MODEL\\mousetrap.x",				// ネズミ捕り
	"data\\MODEL\\leash.x",					// リード
	"data\\MODEL\\pin_box.x",				// 画鋲
	"data\\MODEL\\Senpuki_Body.x",			// 扇風機(本体)
	"data\\MODEL\\cup.x",					// コップ
	"data\\MODEL\\GarbageBox.x",			// ゴミ箱
	"data\\MODEL\\TV.x",					// テレビ
	"data\\MODEL\\Dynamite.x",				// 爆弾
	"data\\MODEL\\Book000.x",				// 本(赤)
	"data\\MODEL\\Red_Katen.x",				// 赤のカーテン
	"data\\MODEL\\chuchumecha.x",			// ネズミメカ

	// ネズミモデル
	"data\\MODEL\\rat\\00_rat_body.x",		// 体
	"data\\MODEL\\rat\\01_rat_head.x",		// 頭
	"data\\MODEL\\rat\\02_rat_Lhand.x",		// 左手
	"data\\MODEL\\rat\\03_rat_Rhand.x",		// 右手
	"data\\MODEL\\rat\\04_rat_Lleg.x",		// 左足
	"data\\MODEL\\rat\\05_rat_Rleg.x",		// 右足

	//猫モデル
	"data\\MODEL\\cat\\00_cat_body.x",		//体
	"data\\MODEL\\cat\\01_cat_head.x",		//頭
	"data\\MODEL\\cat\\02_cat_Larm.x",		//左腕
	"data\\MODEL\\cat\\03_cat_Lhand.x",		//左手
	"data\\MODEL\\cat\\04_cat_Rarm.x",		//右腕
	"data\\MODEL\\cat\\05_cat_Rhand.x",		//右手
	"data\\MODEL\\cat\\06_cat_Lfoot.x",		//左腿
	"data\\MODEL\\cat\\07_cat_Lleg.x",		//左足
	"data\\MODEL\\cat\\08_cat_Rfoot.x",		//右腿
	"data\\MODEL\\cat\\09_cat_Rleg.x",		//右足
	"data\\MODEL\\cat\\flag.x",				//白旗

	// ネズミモデル
	"data\\MODEL\\rat\\rat_Ghost.x",		// 幽霊の姿

	// 3Dテキストモデル
	"data\\MODEL\\cat_win.x",				// ねこのかちテキスト
	"data\\MODEL\\rat_win.x",				// ねずみのかちテキスト

	// 玄関のモデル
	"data\\MODEL\\Entry\\floor.x",			// 玄関の床
	"data\\MODEL\\Entry\\entrance_wall.x",	// 玄関の壁
	"data\\MODEL\\Entry\\shoe_box.x",		// 靴箱
	"data\\MODEL\\Entry\\door.x",			// 玄関のドア
	"data\\MODEL\\Entry\\front_wall.x",		// 玄関の奥の壁
	"data\\MODEL\\Entry\\shoes_floor.x",	// 靴履き場の床
	"data\\MODEL\\Entry\\side_wall.x",		// 横の壁
	"data\\MODEL\\boots.x",					//	ブーツ
	"data\\MODEL\\sandal.x",				//	サンダル
	"data\\MODEL\\leathershoes.x",			//	レザーシューズ

	// 当たり判定モデル
	"data\\MODEL\\Collision.x",				// 当たり判定エディットモデル
};

//------------------------------------------------------------
// モデルの情報
//------------------------------------------------------------
CXFile::SXFile CXFile::m_apModel[CXFile::TYPE_MAX] = {};

//============================================================
// コンストラクタ
//============================================================
CXFile::CXFile()
{
	for (int nCnt = 0; nCnt < CXFile::TYPE_MAX; nCnt++)
	{
		// モデルの情報を初期化する
		m_apModel[nCnt].pMesh = nullptr;			// メッシュ (頂点情報) へのポインタ
		m_apModel[nCnt].pBuffMat = nullptr;			// マテリアルへのポインタ
		m_apModel[nCnt].dwNumMat = 0;				// マテリアルの数
		m_apModel[nCnt].vtxMin = INIT_VTX_MIN;		// 最小の頂点座標
		m_apModel[nCnt].vtxMax = INIT_VTX_MAX;		// 最大の頂点座標
		m_apModel[nCnt].collsize = INIT_SIZE;		// 当たり判定のサイズ
		m_apModel[nCnt].fRadius = 0.0f;				// 半径

		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			m_apModel[nCnt].m_nTexIdx[nCntMat] = NONE_TEXIDX;		// テクスチャのインデックス
		}
	}
}

//============================================================
// デストラクタ
//============================================================
CXFile::~CXFile()
{

}

//============================================================
// モデルの初期化処理
//============================================================
HRESULT CXFile::Init(void)
{
	for (int nCnt = 0; nCnt < CXFile::TYPE_MAX; nCnt++)
	{
		// モデルの情報を初期化する
		m_apModel[nCnt].pMesh = nullptr;			// メッシュ (頂点情報) へのポインタ
		m_apModel[nCnt].pBuffMat = nullptr;			// マテリアルへのポインタ
		m_apModel[nCnt].dwNumMat = 0;				// マテリアルの数
		m_apModel[nCnt].vtxMin = INIT_VTX_MIN;		// 最小の頂点座標
		m_apModel[nCnt].vtxMax = INIT_VTX_MAX;		// 最大の頂点座標
		m_apModel[nCnt].collsize = INIT_SIZE;		// 当たり判定のサイズ
		m_apModel[nCnt].fRadius = 0.0f;				// 半径

		for (int nCntMat = 0; nCntMat < MAX_MATERIAL; nCntMat++)
		{
			m_apModel[nCnt].m_nTexIdx[nCntMat] = NONE_TEXIDX;		// テクスチャのインデックス
		}
	}

	// xファイルの読み込み
	if (FAILED(LoadXFile()))
	{ // xファイルの読み込みに失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 当たり判定の作成
	SetCollision();

	// テクスチャの読み込み
	if (FAILED(LoadTexture()))
	{ // テクスチャの読み込みに失敗した場合

		// 停止
		assert(false);

		// 失敗を返す
		return E_FAIL;
	}

	// 成功を返す
	return S_OK;
}

//============================================================
// モデルの終了処理
//============================================================
void CXFile::Uninit(void)
{
	// テクスチャの破棄
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // モデルの最大数分繰り返す

		if (m_apModel[nCntModel].pMesh != nullptr)
		{ // 変数 (m_apModel[nCntModel].pMesh) がNULLではない場合

			m_apModel[nCntModel].pMesh->Release();
			m_apModel[nCntModel].pMesh = nullptr;
		}

		if (m_apModel[nCntModel].pBuffMat != nullptr)
		{ // 変数 (m_apModel[nCntModel].pBuffMat) がNULLではない場合

			m_apModel[nCntModel].pBuffMat->Release();
			m_apModel[nCntModel].pBuffMat = nullptr;
		}
	}

// デバッグモード
#ifdef _DEBUG

	// テクスチャの破棄
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // モデルの最大数分繰り返す

		if (m_apModel[nCntModel].pMesh != nullptr)
		{ // 変数 (m_apModel[nCntModel].pMesh) がNULLではない場合

			// 停止
			assert(false);
		}

		if (m_apModel[nCntModel].pBuffMat != nullptr)
		{ // 変数 (m_apModel[nCntModel].pBuffMat) がNULLではない場合

			// 停止
			assert(false);
		}
	}

#endif
}

//============================================================
//	xファイルの読み込み
//============================================================
HRESULT CXFile::LoadXFile(void)
{
	// 変数を宣言
	HRESULT hr;		// 異常終了の確認用

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = CManager::Get()->GetRenderer()->GetDevice();

	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // モデルの最大数分繰り返す

		// xファイルの読み込み
		hr = D3DXLoadMeshFromX
		( // 引数
			c_apModelData[nCntModel],		// モデルの相対パス
			D3DXMESH_SYSTEMMEM,				// メッシュ作成用オプション
			pDevice,						// デバイスへのポインタ
			NULL,							// 隣接性データ
			&m_apModel[nCntModel].pBuffMat,	// マテリアルへのポインタ
			NULL,							// エフェクトデータ
			&m_apModel[nCntModel].dwNumMat,	// マテリアルの数
			&m_apModel[nCntModel].pMesh		// メッシュ (頂点情報) へのポインタ
		);

		if (FAILED(hr))
		{ // xファイルの読み込みに失敗した場合

			// 停止
			assert(false);

			// 失敗を返す
			return E_FAIL;
		}
	}

	// 成功を返す
	return S_OK;
}

//============================================================
//	当たり判定の作成
//============================================================
void CXFile::SetCollision(void)
{
	// 変数を宣言
	int         nNumVtx;		// モデルの頂点数
	DWORD       dwSizeFVF;		// モデルの頂点フォーマットのサイズ
	BYTE        *pVtxBuff;		// モデルの頂点バッファへのポインタ
	D3DXVECTOR3 vtx;			// モデルの頂点座標

	// 当たり判定の作成
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // モデルの最大数分繰り返す

		// モデルの頂点数を取得
		nNumVtx = m_apModel[nCntModel].pMesh->GetNumVertices();

		// モデルの頂点フォーマットのサイズを取得
		dwSizeFVF = D3DXGetFVFVertexSize(m_apModel[nCntModel].pMesh->GetFVF());

		// モデルの頂点バッファをロック
		m_apModel[nCntModel].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{ // モデルの頂点数分繰り返す

			// モデルの頂点座標を代入
			vtx = *(D3DXVECTOR3*)pVtxBuff;

			// 頂点座標 (x) の設定
			if (vtx.x < m_apModel[nCntModel].vtxMin.x)
			{ // 今回の頂点座標 (x) が、現状の頂点座標 (x) よりも小さい場合

				// 今回の頂点情報 (x) を代入
				m_apModel[nCntModel].vtxMin.x = vtx.x;
			}
			else if (vtx.x > m_apModel[nCntModel].vtxMax.x)
			{ // 今回の頂点座標 (x) が、現状の頂点座標 (x) よりも大きい場合

				// 今回の頂点情報 (x) を代入
				m_apModel[nCntModel].vtxMax.x = vtx.x;
			}

			// 頂点座標 (y) の設定
			if (vtx.y < m_apModel[nCntModel].vtxMin.y)
			{ // 今回の頂点座標 (y) が、現状の頂点座標 (y) よりも小さい場合

				// 今回の頂点情報 (y) を代入
				m_apModel[nCntModel].vtxMin.y = vtx.y;
			}
			else if (vtx.y > m_apModel[nCntModel].vtxMax.y)
			{ // 今回の頂点座標 (y) が、現状の頂点座標 (y) よりも大きい場合

				// 今回の頂点情報 (y) を代入
				m_apModel[nCntModel].vtxMax.y = vtx.y;
			}

			// 頂点座標 (z) の設定
			if (vtx.z < m_apModel[nCntModel].vtxMin.z)
			{ // 今回の頂点座標 (z) が、現状の頂点座標 (z) よりも小さい場合

				// 今回の頂点情報 (z) を代入
				m_apModel[nCntModel].vtxMin.z = vtx.z;
			}
			else if (vtx.z > m_apModel[nCntModel].vtxMax.z)
			{ // 今回の頂点座標 (z) が、現状の頂点座標 (z) よりも大きい場合

				// 今回の頂点情報 (z) を代入
				m_apModel[nCntModel].vtxMax.z = vtx.z;
			}

			// 頂点フォーマットのサイズ分ポインタを進める
			pVtxBuff += dwSizeFVF;
		}

		// モデルの頂点バッファをアンロック
		m_apModel[nCntModel].pMesh->UnlockVertexBuffer();

		// モデルサイズを求める
		m_apModel[nCntModel].collsize = m_apModel[nCntModel].vtxMax - m_apModel[nCntModel].vtxMin;

		// モデルの円の当たり判定を作成
		m_apModel[nCntModel].fRadius = ((m_apModel[nCntModel].collsize.x * 0.5f) + (m_apModel[nCntModel].collsize.z * 0.5f)) * 0.5f;
	}
}

//============================================================
//	テクスチャの読み込み
//============================================================
HRESULT CXFile::LoadTexture(void)
{
	// デバイスを取得する
	D3DXMATERIAL     *pMat;						// マテリアルへのポインタ

	// テクスチャの読み込み
	for (int nCntModel = 0; nCntModel < CXFile::TYPE_MAX; nCntModel++)
	{ // モデルに使用するモデルの最大数分繰り返す

		// マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)m_apModel[nCntModel].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_apModel[nCntModel].dwNumMat; nCntMat++)
		{ // マテリアルの数分繰り返す

			if (pMat[nCntMat].pTextureFilename != nullptr)
			{ // テクスチャファイルが存在する場合

				// テクスチャの読み込み処理
				m_apModel[nCntModel].m_nTexIdx[nCntMat] = CManager::Get()->GetTexture()->Regist(pMat[nCntMat].pTextureFilename);
			}
		}
	}

	// 成功を返す
	return S_OK;
}

//============================================================
// Xファイルの取得処理
//============================================================
CXFile::SXFile CXFile::GetXFile(TYPE type)
{
	if (type >= 0 && type < TYPE_MAX)
	{ // 種類が規定内の場合

		// モデルの情報を返す
		return m_apModel[type];
	}
	else
	{ // 種類が規定外の場合

		// 停止
		assert(false);

		// 0番目を返す
		return m_apModel[0];
	}
}