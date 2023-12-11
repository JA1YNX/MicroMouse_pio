#include <Arduino.h>
/************************************************************
  ここでプログラムで使う定数で変更する可能性があるものを変更する

 ************************************************************/

 //ひだりしたのスタート地点をx[1]y[1]とする

 //モード
#define mode 0

//ゴールxひだりした
#define GOOLX 8
//ゴールyひだりした
#define GOOLY 8
//ステッピングモーターのデューティー比：基本的に変えない
#define FAST 1
//一ブロック分動かす距離：タイヤ直径によりそう
#define Speed 1000
//カーブの時の速さ
#define carv 1
//迷路のサイズ：壁の数じゃなくてブロックの数
#define MEIRO 16
//フォトトランジスタの境左：壁があるないのギリギリじゃなくて50くらい余裕を持たせる
#define LEDL 930
//フォトトランジスタの境正面：壁があるないのギリギリじゃなくて50くらい余裕を持たせる
#define LEDF 930
//フォトトランジスタの境右：壁があるないのギリギリじゃなくて50くらい余裕を持たせる
#define LEDR 930

//モード設定ピン
#define SW1 19

//LEDピン定義
#define LED_PINL 12
#define LED_PINF 13
#define LED_PINR 0

// SLA7078MRのピン定義
#define DIR_PIN1 2
#define STEP_PIN1 4
#define MS1_PIN1 18
#define MS2_PIN1 5
#define MS3_PIN1 17
#define ENABLE_PIN1 16

#define DIR_PIN2 27
#define STEP_PIN2 26
#define MS1_PIN2 35
#define MS2_PIN2 32
#define MS3_PIN2 33
#define ENABLE_PIN2 25

typedef struct zahyou {//座標
    int x = 1;
    int y = 1;
    int k = 0;//自分の向いている角度
} zahyou;

typedef struct wall {//自分の周りの壁情報
    bool f = 0;//front
    bool r = 0;//right
    bool l = 0;//left
} wall;

typedef struct wall_d {//自分の周りの壁情報
    int f = 0;//front
    int r = 0;//right
    int l = 0;//left
} wall_d;

typedef struct wall_y {
    bool y[30]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
} wall_y;

typedef struct wall_y_d {
    int y[30]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, };
} wall_y_d;

typedef struct walldef {
    wall_y y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, y16, y17, y18, y19, y20, y21, y22, y23, y24, y25, y26, y27, y28, y29, y30;
    wall_y x[30]{ y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, y16, y17, y18, y19, y20, y21, y22, y23, y24, y25, y26, y27, y28, y29, y30, };
} walldef;

typedef struct walldef_d {
    wall_y_d y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, y16, y17, y18, y19, y20, y21, y22, y23, y24, y25, y26, y27, y28, y29, y30;
    wall_y_d x[30]{ y1, y2, y3, y4, y5, y6, y7, y8, y9, y10, y11, y12, y13, y14, y15, y16, y17, y18, y19, y20, y21, y22, y23, y24, y25, y26, y27, y28, y29, y30, };
} walldef_d;

/************************************************************
  ここにmain.cppで使う関数やらクラスやらを書く
  書く優先順位は
  ↓前定義
  ↓クラス
  ↓メンバ関数
  ↓関数
 ************************************************************/

 //前定義
void pinset();
zahyou righthand();
zahyou adachi();
zahyou adachix();

//駆動系クラス
class motor {
private:
    void rotate(int chanel, bool dir, int step); //
public:
    wall mae(float way);//前進
    wall migi(float way);//右回転
    wall hidari(float way);//左回転
    wall stop();//停止
    wall go(int to, float way);//絶対方向に進む
    wall move(int k, float way);//相対方向に進む
};

//壁情報やら座標やら
class info {
private:
    zahyou here;//座標定義
    walldef wallf;//上の壁情報定義
    walldef wallr;//右の壁情報定義
    int adachi_set(zahyou xyk);//足立法周囲計算
public:
    walldef_d step;//道のり保存
    walldef gone;//過去に行ったかどうか
    wall getwall();//周囲の壁情報を取得digital
    wall_d getwall_d();//周囲の壁情報を取得analog
    bool getwall(zahyou xyk);//すべての壁情報取得
    void setwall(zahyou xyk, wall get); //壁情報設定
    zahyou position();//座標を取得
    zahyou setposition(zahyou imhere);//現在位置設定
    zahyou getposition(int x, int y, int k);//座標に変換
    void setstep();//道のり計算
    int adachi_get(zahyou xyk);//足立法周囲取得
    int adachi_getx(zahyou xyk);//足立法周囲取得帰還
    bool gone_get(zahyou xyk);//過去に行ったかどうか
};


motor m;//駆動関係
info i;//情報関係

//足立法周囲計算
int info::adachi_set(zahyou xyk)
{
    int ret = 0;
    xyk.k = 0;
    bool u, m, h, s;
    u = !i.getwall(i.getposition(xyk.x, xyk.y, 0));
    m = !i.getwall(i.getposition(xyk.x, xyk.y, 1));
    h = !i.getwall(i.getposition(xyk.x, xyk.y, 2));
    s = !i.getwall(i.getposition(xyk.x, xyk.y, 3));
    int stepu = i.step.x[xyk.x].y[xyk.y + 1];
    int stepm = i.step.x[xyk.x + 1].y[xyk.y];
    int steph = i.step.x[xyk.x - 1].y[xyk.y];
    int steps = i.step.x[xyk.x].y[xyk.y - 1];
    ret = min((u == 0 ? 99999999 : stepu), min((m == 0 ? 99999999 : stepm), min((h == 0 ? 99999999 : steph), (s == 0 ? 99999999 : steps)))) + 1;
    return ret;
}

//足立法周囲取得
int info::adachi_get(zahyou xyk)
{
    int ret = 0;
    xyk.k = 0;
    bool u, m, h, s;
    u = !i.getwall(i.getposition(xyk.x, xyk.y, 0));
    m = !i.getwall(i.getposition(xyk.x, xyk.y, 1));
    h = !i.getwall(i.getposition(xyk.x, xyk.y, 2));
    s = !i.getwall(i.getposition(xyk.x, xyk.y, 3));
    ret = min((u == 0 ? 99999999 : 0), min((m == 0 ? 99999999 : 1), min((h == 0 ? 99999999 : 2), (s == 0 ? 99999999 : 3))));
    return ret;
}

//足立法周囲取得帰還
int info::adachi_getx(zahyou xyk)
{
    int ret = 0;
    xyk.k = 0;
    bool u, m, h, s;
    u = !i.getwall(i.getposition(xyk.x, xyk.y, 0));
    m = !i.getwall(i.getposition(xyk.x, xyk.y, 1));
    h = !i.getwall(i.getposition(xyk.x, xyk.y, 2));
    s = !i.getwall(i.getposition(xyk.x, xyk.y, 3));
    ret = max((u == 0 ? 99999999 : 0), max((m == 0 ? 99999999 : 1), max((h == 0 ? 99999999 : 2), (s == 0 ? 99999999 : 3))));
    return ret;
}

//道のり計算
void info::setstep()
{
    int r_step = 0;
    step.x[GOOLX].y[GOOLY] = 1;
    step.x[GOOLX + 1].y[GOOLY + 1] = 1;
    step.x[GOOLX + 1].y[GOOLY] = 1;
    step.x[GOOLX].y[GOOLY + 1] = 1;
    int x = GOOLX - 1;
    int y = GOOLY - 1;
    while (!(r_step == MEIRO * MEIRO))
    {
        while (!(x == y))
        {
            while (y < GOOLY + x + 1)
            {
                r_step++;
                y++;
                if (y > MEIRO)
                {
                    break;
                }
                step.x[x].y[y] = adachi_set(getposition(x, y, 0));
            }
            while (x < y)
            {
                r_step++;
                x++;
                if (x > MEIRO)
                {
                    break;
                }
                step.x[x].y[y] = adachi_set(getposition(x, y, 0));
            }
            while (y > GOOLY)
            {
                r_step++;
                y--;
                if (y < 0)
                {
                    break;
                }
                step.x[x].y[y] = adachi_set(getposition(x, y, 0));
            }
            while (x > y)
            {
                r_step++;
                x--;
                if (x < 0)
                {
                    break;
                }
                step.x[x].y[y] = adachi_set(getposition(x, y, 0));
            }
        }
    }
}

//座標に変換
zahyou info::getposition(int x, int y, int k)
{
    zahyou ret;
    ret.x = x;
    ret.y = y;
    ret.k = k;
    return ret;
}

//状況取得
wall info::getwall()
{
    wall ret;
    ret.f = LEDF > analogRead(LED_PINF);
    ret.l = LEDL > analogRead(LED_PINL);
    ret.r = LEDR > analogRead(LED_PINR);
    return ret;
}

//状況取得
wall_d info::getwall_d()
{
    wall_d ret;
    ret.f = analogRead(LED_PINF);
    ret.l = analogRead(LED_PINL);
    ret.r = analogRead(LED_PINR);
    return ret;
}

//すべての壁情報取得
bool info::getwall(zahyou xyk)
{
    return xyk.k == 0 ? wallf.x[xyk.x].y[xyk.y] : wallr.x[xyk.x].y[xyk.y];
}

//壁情報設定
void info::setwall(zahyou xyk, wall get)
{
    switch (xyk.k)
    {
    case 0:
        wallf.x[xyk.x].y[xyk.x] = get.f;
        wallr.x[xyk.x].y[xyk.x] = get.r;
        wallr.x[xyk.x - 1].y[xyk.x] = get.l;
        break;
    case 1:
        wallf.x[xyk.x].y[xyk.y] = get.l;
        wallr.x[xyk.x].y[xyk.y] = get.f;
        wallf.x[xyk.x].y[xyk.y - 1] = get.r;
        break;
    case 2:
        wallf.x[xyk.x].y[xyk.y] = get.r;
        wallr.x[xyk.x].y[xyk.y] = get.f;
        wallf.x[xyk.x].y[xyk.y - 1] = get.l;
        break;
    case 3:
        wallf.x[xyk.x].y[xyk.y - 1] = get.f;
        wallr.x[xyk.x].y[xyk.y] = get.l;
        wallf.x[xyk.x - 1].y[xyk.y] = get.r;
        break;
    default:
        break;
    }
}

//座標を取得
zahyou info::position()
{
    zahyou ret;
    ret = here;
    return ret;
}

//現在位置設定
zahyou info::setposition(zahyou imhere)
{
    zahyou ret;
    here.x = imhere.x <= MEIRO ? imhere.x : imhere.x - 1;
    here.y = imhere.y <= MEIRO ? imhere.y : imhere.y - 1;
    here.k = imhere.k;
    ret = position();
    return ret;
}

//過去に行ったかどうか
bool info::gone_get(zahyou xyk)
{
    bool ret = 0;
    switch (xyk.k)
    {
    case 0:
    {
        ret = gone.x[position().x].y[position().y + 1];
        break;
    }
    case 1:
    {
        ret = gone.x[position().x + 1].y[position().y];
        break;
    }
    case 2:
    {
        ret = gone.x[position().x - 1].y[position().y];
        break;
    }
    case 3:
    {
        ret = gone.x[position().x].y[position().y - 1];
        break;
    }
    default:
    {
        break;
    }
    }
    return ret;
}

//相対方向に進む
wall motor::move(int k, float way)
{
    wall ret;
    switch (k)
    {
    case 0:
    {
        ret = mae(way);
        break;
    }
    case 1:
    {
        hidari(way);
        ret = mae(way);
        break;
    }
    case 2:
    {
        migi(way);
        ret = mae(way);
        break;
    }
    case 3:
    {
        migi(way * 2);
        ret = mae(way);
        break;
    }
    default:
    {
        break;
    }
    }
    return ret;
}

//絶対方向に進む
wall motor::go(int to, float way)
{
    wall ret;
    switch (to)
    {
    case 0:
    {
        switch (i.position().k)
        {
        case 0:
        {
            ret = move(0, way);
            break;
        }
        case 1:
        {
            ret = move(2, way);
            break;
        }
        case 2:
        {
            ret = move(1, way);
            break;
        }
        case 3:
        {
            ret = move(3, way);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case 1:
    {
        switch (i.position().k)
        {
        case 0:
        {
            ret = move(1, way);
            break;
        }
        case 1:
        {
            ret = move(0, way);
            break;
        }
        case 2:
        {
            ret = move(3, way);
            break;
        }
        case 3:
        {
            ret = move(2, way);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case 2:
    {
        switch (i.position().k)
        {
        case 0:
        {
            ret = move(2, way);
            break;
        }
        case 1:
        {
            ret = move(3, way);
            break;
        }
        case 2:
        {
            ret = move(0, way);
            break;
        }
        case 3:
        {
            ret = move(1, way);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    case 3:
    {
        switch (i.position().k)
        {
        case 0:
        {
            ret = move(3, way);
            break;
        }
        case 1:
        {
            ret = move(2, way);
            break;
        }
        case 2:
        {
            ret = move(1, way);
            break;
        }
        case 3:
        {
            ret = move(0, way);
            break;
        }
        default:
        {
            break;
        }
        }
        break;
    }
    default:
    {
        break;
    }
    }
    return ret;
}

//モーター駆動
void motor::rotate(int chanel, bool dir, int step)
{
    digitalWrite(chanel == 1 ? DIR_PIN1 : DIR_PIN2, dir);
    ledcWrite(chanel, (int)(abs(step) * 10));
}

//前進
wall motor::mae(float way)
{
    wall ret;
    zahyou imhere = i.position();
    switch (imhere.k)
    {
    case 0:
    {
        imhere.y++;
        break;
    }
    case 1:
    {
        imhere.x++;
        break;
    }
    case 2:
    {
        imhere.x--;
        break;
    }
    case 3:
    {
        imhere.y--;
        break;
    }
    default:
    {
        break;
    }
    }
    rotate(1, 1, FAST);
    rotate(2, 0, FAST);
    delay(Speed * way);
    stop();
    ret = i.getwall();
    i.setwall(imhere, ret);
    i.setposition(imhere);
    i.gone.x[imhere.x].y[imhere.y] = 1;
    return ret;

}

//右回転
wall motor::migi(float way)
{
    wall ret;
    zahyou imhere = i.position();
    switch (imhere.k)
    {
    case 0:
    {
        imhere.k = 1;
        break;
    }
    case 1:
    {
        imhere.k = 3;
        break;
    }
    case 2:
    {
        imhere.k = 1;
        break;
    }
    case 3:
    {
        imhere.k = 2;
        break;
    }
    default:
    {
        break;
    }
    }
    rotate(1, 0, FAST);
    rotate(2, 0, FAST);
    delay(Speed * way * carv);
    stop();
    ret = i.getwall();
    i.setwall(imhere, ret);
    i.setposition(imhere);
    i.gone.x[imhere.x].y[imhere.y] = 1;
    return ret;

}

//左回転
wall motor::hidari(float way)
{
    wall ret;
    zahyou imhere = i.position();
    switch (imhere.k)
    {
    case 0:
    {
        imhere.k = 2;
        break;
    }
    case 1:
    {
        imhere.k = 0;
        break;
    }
    case 2:
    {
        imhere.k = 3;
        break;
    }
    case 3:
    {
        imhere.k = 1;
        break;
    }
    default:
    {
        break;
    }
    }
    rotate(1, 1, FAST);
    rotate(2, 1, FAST);
    delay(Speed * way * carv);
    stop();
    ret = i.getwall();
    i.setwall(imhere, ret);
    i.setposition(imhere);
    i.gone.x[imhere.x].y[imhere.y] = 1;
    return ret;

}

//停止
wall motor::stop()
{
    wall ret;
    rotate(1, 1, 0);
    rotate(2, 0, 0);
    ret = i.getwall();
    return ret;
}

//右手法
zahyou righthand()
{
    zahyou ret;
    wall now;
    if ((!i.getwall().r) && (!i.gone_get(i.position())))
    {
        now = m.move(1, 1);
        Serial.print("migi\n");
    }
    else if ((!i.getwall().f) && (!i.gone_get(i.position())))
    {
        now = m.move(0, 1);
        Serial.print("mae\n");
    }
    else if (!i.getwall().l)
    {
        now = m.move(2, 1);
        Serial.print("hidari\n");
    }
    else
    {
        now = m.move(3, 1);
        Serial.print("usiro\n");
    }
    Serial.print("l:");
    Serial.print(now.l);
    Serial.print("f:");
    Serial.print(now.f);
    Serial.print("r:");
    Serial.print(now.r);
    Serial.print("\n");
    ret = i.position();
    return ret;
}

//足立法
zahyou adachi()
{
    zahyou ret;
    i.setstep();
    while (!((i.position().x == GOOLX || i.position().x == GOOLX + 1) && (i.position().y == GOOLY || i.position().y == GOOLY)))
    {
        m.go(i.adachi_get(i.position()), 1);
    }
    ret = i.position();
    return ret;
}

//足立法帰還
zahyou adachix()
{
    zahyou ret;
    i.setstep();
    while (!(i.position().x == 1 && i.position().y == 1))
    {
        m.go(i.adachi_getx(i.position()), 1);
    }
    ret = i.position();
    return ret;
}

/*
  ピンやらの初期化
  ここに書くものはマイコン側の設定を行うものだけ
  変数とかほかの情報保存のための定義は今のとこグローバル変数として定義する
*/
void pinset()
{
    pinMode(SW1, INPUT);
    //Serial.begin(9600);
    pinMode(LED_PINL, OUTPUT);
    pinMode(LED_PINF, OUTPUT);
    pinMode(LED_PINR, OUTPUT);
    // ピンのモードを設定
    pinMode(DIR_PIN1, OUTPUT);
    pinMode(STEP_PIN1, OUTPUT);
    pinMode(MS1_PIN1, OUTPUT);
    pinMode(MS2_PIN1, OUTPUT);
    pinMode(MS3_PIN1, OUTPUT);
    pinMode(ENABLE_PIN1, OUTPUT);

    // モータードライバを有効にする
    digitalWrite(ENABLE_PIN1, LOW);

    // マイクロステッピングモードを設定（ここでは1/16ステップモード）
    digitalWrite(MS1_PIN1, HIGH);
    digitalWrite(MS2_PIN1, LOW);
    digitalWrite(MS3_PIN1, LOW);


    // ピンのモードを設定
    pinMode(DIR_PIN2, OUTPUT);
    pinMode(STEP_PIN2, OUTPUT);
    pinMode(MS1_PIN2, OUTPUT);
    pinMode(MS2_PIN2, OUTPUT);
    pinMode(MS3_PIN2, OUTPUT);
    pinMode(ENABLE_PIN2, OUTPUT);

    // モータードライバを有効にする
    digitalWrite(ENABLE_PIN2, LOW);

    // マイクロステッピングモードを設定（ここでは1/16ステップモード）
    digitalWrite(MS1_PIN2, HIGH);
    digitalWrite(MS2_PIN2, LOW);
    digitalWrite(MS3_PIN2, LOW);



    ledcSetup(1, 500, 10);
    ledcAttachPin(STEP_PIN1, 1);


    ledcSetup(2, 500, 10);
    ledcAttachPin(STEP_PIN2, 2);

    digitalWrite(LED_PINL, HIGH);
    digitalWrite(LED_PINF, HIGH);
    digitalWrite(LED_PINR, HIGH);
}
/************************************************************

 ************************************************************/

void setup()
{
    Serial.begin(9600);
    pinset();
}
int count = 0;
void loop()
{
    count++;
    wall now;
    zahyou now_z;
    Serial.print(count);
    Serial.print("\n");
    if (!digitalRead(SW1))
    {
        Serial.print("l:");
        Serial.print(i.getwall_d().l);
        Serial.print("f:");
        Serial.print(i.getwall_d().f);
        Serial.print("r:");
        Serial.print(i.getwall_d().r);
        Serial.print("\n");

        now = m.mae(1);
        Serial.print("l:");
        Serial.print(now.l);
        Serial.print("f:");
        Serial.print(now.f);
        Serial.print("r:");
        Serial.print(now.r);
        Serial.print("\n");

        now = m.migi(1);
        Serial.print("l:");
        Serial.print(now.l);
        Serial.print("f:");
        Serial.print(now.f);
        Serial.print("r:");
        Serial.print(now.r);
        Serial.print("\n");

        now = m.hidari(1);
        Serial.print("l:");
        Serial.print(now.l);
        Serial.print("f:");
        Serial.print(now.f);
        Serial.print("r:");
        Serial.print(now.r);
        Serial.print("\n");
        delay(500);
    }
    else
    {
        switch (mode)
        {
        case 0:
        {
            now_z = righthand();
            Serial.print("x:");
            Serial.print(now_z.x);
            Serial.print("y:");
            Serial.print(now_z.y);
            Serial.print("k:");
            Serial.print(now_z.k);
            Serial.print("\n");
            break;
        }
        case 1:
        {
            while (!((i.position().x == GOOLX || i.position().x == GOOLX + 1) && (i.position().y == GOOLY || i.position().y == GOOLY)))
            {
                now_z = righthand();
                Serial.print("x:");
                Serial.print(now_z.x);
                Serial.print("y:");
                Serial.print(now_z.y);
                Serial.print("k:");
                Serial.print(now_z.k);
                Serial.print("\n");
            }
            now_z = adachi();
            Serial.print("x:");
            Serial.print(now_z.x);
            Serial.print("y:");
            Serial.print(now_z.y);
            Serial.print("k:");
            Serial.print(now_z.k);
            Serial.print("\n");
            break;
        }
        default:
        {
            break;
        }
        }
    }
}
