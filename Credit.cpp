// スタッフロール

#include "Utilities.h" // 必要なもの
#include "Credit.h" // スタッフロール

/*
各仕事に誰が所属しているかのデータはint型配列のprogramer,graphicer,composerに収納されていますので、役職に変更があるときはそこをいじってください。
各仕事に所属する人数が変わるときには、各役職の人数が記録されているPROGREMER_NAM,GRAPHICER_NUM,COMPOSER_NUMも同時に書き換えてください。

表示される個人名を変えたいときはname[CREATERS][16]の中身をいじってください。
*/
namespace Credit {
	const int CREATERS = 11;//このゲームの制作メンバーの全体数
	const int WORKS = 4;//3つの仕事(プログラマ,グラフィッカ,コンポーザ)+スペシャルサンクス

	const int PROGRAMER_NUM = 8;//プログラマの人数
	const int GRAPHICER_NUM = 6;//グラフィッカーの人数
	const int COMPOSER_NUM = 1;//コンポーザーの人数
	const int SPECIAL_NUM = 2;//スペシャルサンクスの数

	//メンバー管理用enum
	enum {
		// 4年
		Exe,
		Rodita,
		// 3年
		Agu,
		Arumiker,
		Nonobe,
		Raim,
		Rayan,
		// 2年
		Aohi,
		TKG,
		Vea,
		Yuya,
	};
	//各仕事のメンバー(担当している仕事を変えたいときはここを変える、上の管理用enumの値を入れてください。各役職の人数に変化があるときは上のconst intの値も)
		//プログラマの方々
	int programer[PROGRAMER_NUM] = {
	Arumiker,Exe,Nonobe,Rodita,Raim,Rayan,TKG,Vea
	};
	//グラフィッカ―の方々
	int graphicer[GRAPHICER_NUM] = {
	Agu,Aohi,Yuya,Vea,Arumiker,Raim
	};
	//コンポーザーの方々
	int composer[COMPOSER_NUM] = {
	Aohi
	};
	//表示される名前(各個人の名前を変更したいときはここを変える)
	char name[CREATERS][16] = {
		// 4年
			"Exe",
			"Robita",
			// 3年
				"Agu",
				"あるみけー",
				"Nonobe",
				"らいむ",
				"Rayan",
				// 2年
					"Aohi",
					"TKG",
					"Vea",
					"Yuya",
	};//制作メンバー
	//仕事名
	char work[WORKS][32] = {
		"プログラマ","グラフィッカ","コンポーザ","スペシャルサンクス"
	};
	//スペシャルサンクス一覧
	char sp_thanks[SPECIAL_NUM][16] = { "神奈川大学","GCC" };

	//雑多な変数や定数たち
	const int space = 50;//字間
	const int WHITE = GetColor(255, 255, 255);//文字色、白
	const int BLACK = GetColor(0, 0, 0);//文字色、黒
	const int move_speed = 3;//文字の動く速度

	int move_name = 150;//名前演出の初期表示位置
	int move_work = -100;//仕事演出の初期表示位置
	int skeleton = 50;//文字の初期透過度(0.完全に透明～255.透過なし)
	int back_handle;//背景用ハンドル
	int block_handle;//背景用ハンドル
}
using namespace Credit;

// 初期化
void Credit_Initialize() {
	//不具合で名前が埋まっていない人がいた時用に一応初期化
	for (int i = 0; i < CREATERS; i++) {
		if (name[i][0] == NULL) { sprintfDx(name[i], "名無しの権兵衛"); }
	}
	//背景画像のハンドル取得
	back_handle = LoadGraph("Graphics/gallery/back.png");
	block_handle = LoadGraph("Graphics/gallery/window.png");
	//フォントの変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	SetFontSize(32);
}
// 終了処理
void Credit_Finalize() {
	Credit_reset();
	//フォントをデフォルトに
	ChangeFontType(DX_FONTTYPE_NORMAL);
	SetFontSize(16);
}
// 更新
void Credit_Update() {
	// Xで戻る
	if (Keyboard_Get(KEY_INPUT_X) == 1) {
		SE_Play(MUSIC::SE_cancel);
		SceneMgr_Change(S_Menu); //シーンをメニューに戻す
	}
	else if (Keyboard_Get(KEY_INPUT_Z) == 1) {
		SE_Play(MUSIC::SE_decision);
		//もう一度再生
		Credit_reset();
	}

	//文字の移動処理
	if (move_work < 50) { move_work += move_speed; }
	if (move_name > 0) { move_name -= move_speed; }
	//文字の透過をだんだん薄くする
	skeleton += 5;
}
// 描画
void Credit_Draw() {
	//背景描画
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, back_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);//透過処理オン
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, block_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//透過処理オフ
//文字描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);//透過処理オン
	DrawString(20, 20,
		"[X] 戻る\n制作者の名前が見れます。",WHITE);
	DrawString(50, 100, "魔女狩りごっこ　製作スタッフ", WHITE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//透過処理オフ

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, skeleton);//透過処理オン
	//仕事名
	DrawString(move_work, 145, work[0], WHITE);//プログラマ
	DrawString(200 + move_work, 145, work[1], WHITE);//グラフィッカ
	DrawString(200 + move_work, 145 + (1 * space) + (GRAPHICER_NUM * space), work[2], WHITE);//コンポーザ
	DrawString(450 + move_work, 145, work[3], WHITE);//スペシャルサンクス

	//プログラマの方々
	for (int i = 0; i < PROGRAMER_NUM; i++) {
		DrawString(75 + move_name, 180 + (i * space), name[programer[i]], WHITE);
	}
	//グラフィッカの方々
	for (int i = 0; i < GRAPHICER_NUM; i++) {
		DrawString(275 + move_name, 180 + (i * space), name[graphicer[i]], WHITE);
	}
	//コンポーザの方々
	for (int i = 0; i < COMPOSER_NUM; i++) {
		DrawString(275 + move_name, 180 + (1 * space) + (GRAPHICER_NUM * space) + (i * space), name[composer[i]], WHITE);
	}
	//スペシャルサンクス
	for (int i = 0; i < SPECIAL_NUM; i++) {
		DrawString(525 + move_name, 180 + (i * space), sp_thanks[i], WHITE);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//透過処理オフ

	

}
//変数のリセット
void Credit_reset() {
	move_work = -100;
	move_name = 150;
	skeleton = 50;
	return;
}