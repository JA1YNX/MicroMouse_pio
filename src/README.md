# re_MOUSE23****.cpp reference

ここでmain.cppに使われている主要な関数と変数の型の使い方と解説をする  
ここに書かれているものは変更した可能性があるので注意しすること  

# index

### [プログラムを書く時の注意点](#プログラムを書くときの注意点)

### [TYPE](#variable_type)  
[zahyou](#zahyou)  
[wall](#wall)  
[wall_d](#wall_d)  
[walldef](#walldef_d)  

### [GLOBAL](#global)  
[setup()](#void_setup();)  
[loop()](#void_loop();)  
[pinset()](#void_pinset();)  
[righthand()](#zahyou_righthand();)  
[adachi()](#zahyou_adachi();)  
[adachix()](#zahyou_adachix();)  

### [MOTOR](#motor)
[rotate(int chanel, bool dir, int step)](#void_rotate(int_chanel,_bool_dir,_int_step);)  
[mae(float far)](#wall_mae(float_far);)  
[migi(float far)](#wall_migi(float_far);)  
[hidari(float far)](#wall_hidari(float_far);)  
[stop();](#wall_stop();)  
[go(int to, float far)](#wall_go(int_to,_float_far);)  
[move(int k, float far)](#wall_move(int_k,_float_far);)  

### [INFO](#info)
[here](#zahyou_here;)  
[wallf](#walldef_wallf;)  
[wallr](#walldef_wallr;)  
[adachi_set(zahyou xyk)](#int_adachi_set(zahyou_xyk);)  
[getwall()](#wall_getwall();)  
[getwall_d()](#wall_d_getwall_d();)  
[getwall(zahyou xyk)](#bool_getwall(zahyou_xyk);)  
[setwall(zahyou xyk, wall get)](#void_setwall(zahyou_xyk,_wall_get);)  
[position()](#zahyou_position();)  
[setposition(zahyou imhere)](#zahyou_setposition(zahyou_imhere);)  
[getposition(int x, int y, int k)](#zahyou_getposition(int_x,_int_y,_int_k);)  
[setstep()](#void_setstep();)  
[adachi_get(zahyou xyk)](#int_adachi_get(zahyou_xyk);)  
[adachi_getx(zahyou xyk)](#int_adachi_getx(zahyou_xyk);)  
[gone_get(zahyou xyk)](#bool_gone_get(zahyou_xyk);)  

## プログラムを書くときの注意点

・switch文を使うときはcaseの中を{}で囲むこと  
・新しく関数を作る時に座標を引数にする場合は[zashyou](#zahyou)を使うこと  
・[void loop](#void_loop();)の中身は最低限にすること  
・グローバル変数や関数はなるべく使わないこと  
・プログラムを書くときは  
　↓define系  
　↓型定義  
　↓クラス定義  
　↓クラス初期化  
　↓グローバル関数宣言  
　↓メンバ関数定義  
　↓グローバル関数定義  
　↓メインループ  
　の順で書くこと  
・変更する可能性のあるものは始めにdefineで定義すること  

## variable type

##### zahyou

座標の受け渡しに使う  
.x  int  
.y  int  
.k  int  

##### wall

壁情報（digital）の受け渡しに使う  
.f  bool  
.r  bool  
.l  bool  

##### wall_d

壁情報（analig）の受け渡しに使う  
.f  int  
.r  int  
.l  int  

##### walldef

すべてのブロック（difital）の受け渡しに使う  
.x[ ].y[ ]  bool  

##### walldef_d

すべてのブロック（analog）の受け渡しに使う  
.x[ ].y[ ]  int  

## function

### global

##### void setup();

arduinoで必要になる関数  
プログラム実行時に一度だけ実行される  

##### void loop();

arduunoで必要になる関数  
setupの後に永遠に繰り返される  

##### void pinset();

#deifneで定義されるピン番号の入出力を一括で定義する  
ピンを変えるときは#defineの値を変える

##### zahyou righthand();

右手法の一ループ分  
右前左後の優先順位で壁がないところに向かって進む  

##### zahyou adachi();

足立法  
事前に収集したマップ情報から最短経路でゴールまで進む  
必ずrighthand()でマップ情報を作ってから実行する  

##### zahyou adachix();

足立法  
事前に収集したマップ情報から最短経路でスタートまで進む  
必ずrighthand()でマップ情報を作ってから実行する  

### motor

#### private

##### void rotate(int chanel, bool dir, int step);

モーター回転  
chanel  ledcsetupで設定した回したいモーターのチャンネル  
dir  回転方向1正転0逆転  
step  デューティ比基本的に1なのでFASTを代入する

#### public

##### wall mae(float far);

前進させる  
far 進むブロック数  
.f  正面の壁の有無  
.r  右側の壁の有無  
.l  左側の壁の有無  

##### wall migi(float far);

その場で右回転  
far 回転する角度1で90°  
.f  正面の壁の有無  
.r  右側の壁の有無  
.l  左側の壁の有無    

##### wall hidari(float far);

その場で左回転  
far 回転する角度1で90°  
.f  正面の壁の有無  
.r  右側の壁の有無  
.l  左側の壁の有無  

##### wall stop();

左右のモーターを停止させる  
.f  正面の壁の有無  
.r  右側の壁の有無  
.l  左側の壁の有無  

##### wall go(int to, float far);

スタート時の向きを基準にして進む  
to  進む向き0上方向1右方向2左方向3下方向  
far  進むブロック数  
.f  正面の壁の有無  
.r  右側の壁の有無  
.l  左側の壁の有無  

##### wall move(int k, float far);

その時点の向きを基準にして進む  
to  進む向き0前方向1右方向2左方向3後方向  
far  進むブロック数  
.f  正面の壁の有無  
.r  右側の壁の有無  
.l  左側の壁の有無  

### info

#### private

##### zahyou here;

すべての基準になる自分の座標を保存するもの  
必ずsetposition()で設定する  

##### walldef wallf;

マップ情報横方向の壁の有無  

##### walldef wallr;

マップ情報縦方向の壁の有無  

##### int adachi_set(zahyou xyk);

足立法で必要になる上下左右のゴールまでの距離で一番近いもの＋１を返す  
xyk  自分のいる座標  

#### public

##### wall getwall();

周囲の壁の有無を調べる  
.f  正面の壁の有無  bool  
.r  右側の壁の有無  bool  
.l  左側の壁の有無  bool  

##### wall_d getwall_d();

各方向のセンサの値を調べる  
.f  正面の値  int  
.r  右側の値  int  
.l  左側の値  int  

##### bool getwall(zahyou xyk);

すべての壁情報から指定のものを取得  
xyk  必要な壁情報の座標とその方向0上1右2左3下  

##### void setwall(zahyou xyk, wall get);

指定の座標に壁の有無を設定  
xyk  座標とその方向0上1右2左3下  
get  周囲の壁の有無  

##### zahyou position();

現在の座標を取得  
.x  int  
.y  int  
.k  int  

##### zahyou setposition(zahyou imhere);

zahyou hereに自分のいる座標を代入する  
.x  int  
.y  int  
.k  int  

##### zahyou getposition(int x, int y, int k);

ばらばらの変数から座標型に変換  
x  x座標  
y  y座標  
k  向き  
.x  int  
.y  int  
.k  int  

##### void setstep();

スタート地点からゴールまでの最短の道のりをwalldef_d stepに設定する  

##### int adachi_get(zahyou xyk);

現在の位置にいるときに最短で進むべき方向を返す  
xyk  現在位置  

##### int adachi_getx(zahyou xyk);

現在の位置にいるときに最短でゴールまでの進むべき方向を返す  
xyk  現在位置

##### bool gone_get(zahyou xyk);

過去に通ったことがあるか確認する  
xyk  現在位置　　
