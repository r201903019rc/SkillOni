#pragma once
// オプション画面
namespace Option {
	extern int Move_Speed;//他ソースファイルで使用できるようにヘッダ側で宣言
}

void Option_Initialize(); // 初期化
void Option_Finalize(); // 終了処理
void Option_Update(); // 更新
void Option_Draw(); // 描画

void Option_Save();//データの保存
void Option_Read();//データの読み取り
void Option_Reset();//ファイルの形式がおかしかった時にリセットする
