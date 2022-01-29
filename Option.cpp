// オプション画面

#include "Utilities.h" // 必要な物
#include "Option.h" // オプション画面

using namespace MUSIC;//音楽関係変数の宣言

namespace Option {//デバッグ用
	int back_handle;//背景用ハンドル
	int block_handle;//背景用ハンドル

	int select_now = 0;//選択中の項目
	bool file_load_ok = true;//ファイルが読み込めたかどうか
	char filename[] = "SaveData/OptionData.txt";

	const int first_BGM_volume = 30;//BGMの音量初期値
	const int first_SE_volume = 50;//SEの音量初期値
	const int first_Move_Speed = 12;//キャラ速度の初期値

	int Move_Speed=12;//キャラ速度の変更
}
using namespace Option;
// 初期化
void Option_Initialize() {
	MUSIC_Initialize();
	BGM_Play(BGM_running_witches);//音楽流す
	//ファイル読み込み
	//すでにオプション画面に一度アクセスしていて、すでにファイルが開けないとわかっているときは開かない
	//その際はゲームを起動している間だけは音量が維持されるが、値は保存されないのでゲームを消したら初期値に戻る
	if (file_load_ok == true) {Option_Read();}
	
	//画像取得
	back_handle = LoadGraph("Graphics/gallery/back.png");
	block_handle = LoadGraph("Graphics/gallery/window.png");
	//フォントの変更
	ChangeFontType(DX_FONTTYPE_ANTIALIASING);
	SetFontSize(32);
}

// 終了処理
void Option_Finalize() {
	MUSIC_Finalize();
	Volume_Change();
	//ファイルが存在するときのみ保存処理
	if (file_load_ok == true) { Option_Save(); }
	//フォントをデフォルトに
	ChangeFontType(DX_FONTTYPE_NORMAL);
	SetFontSize(16);
}

// 更新
void Option_Update() {
	// Xでメニューに戻る
	if (Keyboard_Get(KEY_INPUT_X) == 1) {
		SE_Play(MUSIC::SE_cancel);
		SceneMgr_Change(S_Menu); //シーンをメニューに戻す
	}

	//項目選択
	if (Keyboard_Get(KEY_INPUT_UP) == 1) {
		if (select_now > 0) { select_now--; }
		SE_Play(SE_cursor);
	}
	else if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {
		if (select_now < 2) { select_now++; }
		SE_Play(SE_cursor);
	}
	
	//各項目の処理
	switch (select_now) {
	case 0://BGMのボリュームを変える
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
			if (BGM_VOLUME - 10 >= 0) { BGM_VOLUME -= 10; Volume_Change(); }
			SE_Play(SE_cursor);
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
			if (BGM_VOLUME+10 < 255) { BGM_VOLUME+=10;  Volume_Change();}
			SE_Play(SE_cursor);
		}
		break;
	case 1://SEのボリュームを変える
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
			if (SE_VOLUME-10 >= 0) {
				SE_VOLUME-=10;//音を小さく
				Volume_Change();//音量の変更を適応
			}
			SE_Play(SE_cursor);
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
			if (SE_VOLUME+10 < 250) { 
				SE_VOLUME+=10;//音を大きく
				Volume_Change();//音量の変更を適応
			}
			SE_Play(SE_cursor);
		}
		break;
	case 2://キャラの速度を変える
		if (Keyboard_Get(KEY_INPUT_LEFT) == 1) {
			if (Move_Speed - 1 >= 0) {
				Move_Speed -= 1;//速度を小さく
			}
			SE_Play(SE_cursor);
		}
		else if (Keyboard_Get(KEY_INPUT_RIGHT) == 1) {
			if (Move_Speed + 1 < 64) {
				Move_Speed += 1;//を小さく
			}
			SE_Play(SE_cursor);
		}
	default:
		break;
	}

}

// 描画
void Option_Draw() {
	//背景描画
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, back_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);//透過処理オン
	DrawExtendGraph(0, 0, SCREEN_SIZE_WIDTH, SCREEN_SIZE_HEIGHT, block_handle, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);//透過処理オフ
	//文字描画
	DrawString(50, 40,
		"[X] メニュー画面に戻る",
		GetColor(255, 255, 255));
	DrawString(50, 90,
		"オプション画面", GetColor(255, 255, 255));

	//現在選択中の項目
	DrawString(150, 150 + (select_now * 50), "→",
		GetColor(255, 255, 255));
	//ボリューム変更
	DrawFormatString(200, 150, GetColor(255, 255, 255), "BGMの音量 : %d", BGM_VOLUME);
	DrawFormatString(200, 200, GetColor(255, 255, 255), "SEの音量  : %d", SE_VOLUME);
	DrawFormatString(200, 250, GetColor(255, 255, 255), "デバッグ用-キャラの速度 : %d\n(数字が小さいほど早くなります)", Move_Speed);

}

//データ読み込み
void Option_Read() {
	FILE* fp;
	//ファイルを開く
	if ((fopen_s(&fp,filename, "r")) != 0) {
		//読み込めなかった場合はreturn(オプションの機能自体は使えるがゲームを消したら初期値に戻る)
		file_load_ok = false;
		printfDx("error about read of option.");
		return;
	}
	else{ file_load_ok = true; }

	//ファイルに保存されているデータを読み込む
	//読み込みの際、データがうまく読み込めない、もしくはデータの値が0未満か250以上ならデータをリセットする
	
	if (((fscanf_s(fp, ("%d %d %d"), &BGM_VOLUME, &SE_VOLUME,&Move_Speed))==-1)||
		((BGM_VOLUME < 0) || (BGM_VOLUME > 250)) ||
		((SE_VOLUME < 0) || (SE_VOLUME > 250))||
		((Move_Speed<0)||(Move_Speed>64))
		) {
			fclose(fp);//いったんファイルを閉じる
			printfDx("data_error. Data Reset\n");//エラー文
			Option_Reset(); 
			Volume_Change();//ゲーム側に反映
			return;
	
	}
	Volume_Change();//データをゲーム側に反映
	fclose(fp);
	return;
}
//データ書き出し
void Option_Save() {
	FILE* fp;
	//ファイルを開く
	fopen_s(&fp, filename, "w");
	//データを書き込み
	fprintf_s(fp, ("%d %d %d"), BGM_VOLUME, SE_VOLUME,Move_Speed);
	fclose(fp);
	return;
}

//データファイルのリセット
void Option_Reset() {
	//ファイルを開く
	FILE* fp;
	fopen_s(&fp, filename, "w");
	//書き込み
	fprintf_s(fp, "%d %d %d", first_BGM_volume, first_SE_volume,first_Move_Speed);
	//変数も初期化
	BGM_VOLUME = first_BGM_volume;
	SE_VOLUME = first_SE_volume;
	Move_Speed = first_Move_Speed;
	//ファイルを閉じる
	fclose(fp);
	return;
}