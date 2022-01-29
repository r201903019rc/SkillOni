#pragma once
namespace MUSIC {//音楽関係の管理
	//効果音の名前
	//効果音ラボより　https://soundeffect-lab.info/sound/anime/
	typedef enum {
		SE_break,
		SE_cancel,
		SE_cursor,
		SE_decision,
		SE_magic,
		SE_pickup,
		SE_put,
		SE_MAX,
	};

	//BGMの名前
	//魔王魂より(mp3だとなぜか鳴らなかったのでwavに変換してます)　https://maoudamashii.jokersounds.com/music_bgm.html
	typedef enum {
		BGM_running_witches,
		BGM_MAX,
	};

	//SEのリスト
	extern int SE_list[];
	//BGMのリスト
	extern int BGM_list[];
	//音量
	extern int SE_VOLUME;
	extern int BGM_VOLUME;
}

void MUSIC_Initialize();//namespace MUSIC内の変数の初期化、このヘッダをincludeしたら一度使いましょう
void MUSIC_Finalize();//メモリ開放処理、このヘッダをincludeしたcppの終了の際には実行しましょう

void SE_Play(int);//SEの名前(SE_〇〇)を引数にSEを流します
void BGM_Play(int);//BGMの名前(BGM_〇〇)を引数にBGMを流します
void Volume_Change();//SE_VOLUMEとBGM_VOLUMEの変化を適応します(その2つの変数の値をただ変更してもボリュームは変わりません)