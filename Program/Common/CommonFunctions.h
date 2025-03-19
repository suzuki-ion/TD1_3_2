#pragma once
#include "Structures.h"

/// <summary>
/// 値を交換する
/// </summary>
/// <typeparam name="Type">交換する値の型</typeparam>
/// <param name="a">交換する値1</param>
/// <param name="b">交換する値2</param>
template <typename Type>
void Swap(Type *a, Type *b);

/// <summary>
/// 指定した範囲で乱数を生成
/// </summary>
/// <param name="min">乱数の整数型最小値</param>
/// <param name="max">乱数の整数型最大値</param>
/// <returns>指定した範囲の乱数</returns>
int CustomRangeRand(int min, int max);

/// <summary>
/// DegreeからRadianに変換
/// </summary>
/// <param name="degree">float型のdegree</param>
/// <returns>radian</returns>
float ConvertDeg2Rad(float degree);

/// <summary>
/// RadianからDegreeに変換
/// </summary>
/// <param name="radian">float型のradian</param>
/// <returns>degree</returns>
float ConvertRad2Deg(float radian);

/// <summary>
/// ベクトルの長さを求める
/// </summary>
/// <param name="x">ベクトル座標 X</param>
/// <param name="y">ベクトル座標 Y</param>
/// <returns>float型の値</returns>
float Length(float x, float y);

/// <summary>
/// ベクトルの長さを正規化する
/// </summary>
/// <param name="x">ベクトル座標 X</param>
/// <param name="y">ベクトル座標 Y</param>
/// <returns>成功: 正規化したベクトル  失敗: 0</returns>
Vector2 Normalize(float x, float y);

/// <summary>
/// ベクトルの内積を求める
/// </summary>
/// <param name="x1">ベクトル座標1 X</param>
/// <param name="y1">ベクトル座標1 Y</param>
/// <param name="x2">ベクトル座標2 X</param>
/// <param name="x2">ベクトル座標2 Y</param>
/// <returns>float型の内積の値</returns>
float DotProduct(float x1, float y1, float x2, float y2);

/// <summary>
/// ベクトル1からベクトル2への外積を求める
/// </summary>
/// <param name="x1">ベクトル座標1 X</param>
/// <param name="y1">ベクトル座標1 Y</param>
/// <param name="x2">ベクトル座標2 X</param>
/// <param name="x2">ベクトル座標2 Y</param>
/// <returns>float型の外積の値</returns>
float CrossProduct(float x1, float y1, float x2, float y2);

/// <summary>
/// 渡された小数値を指定の範囲に収める
/// </summary>
/// <param name="t">指定の範囲に収める値</param>
/// <param name="min">最低値</param>
/// <param name="max">最大値</param>
/// <returns>minとmaxの間に収めたt</returns>
float Clamp(float t, float min, float max);

/// <summary>
/// 円と円の当たり判定
/// </summary>
/// <param name="x1">円1の座標 X</param>
/// <param name="y1">円1の座標 Y</param>
/// <param name="radius1">円1の半径</param>
/// <param name="x2">円2の座標 X</param>
/// <param name="y2">円2の座標 Y</param>
/// <param name="radius2">円2の半径</param>
/// <returns>当たってる:true 当たってない:false</returns>
int IsCircle2CircleHit(float x1, float y1, float radius1, float x2, float y2, float radius2);

/// <summary>
/// 矩形と矩形の当たり判定
/// </summary>
/// <param name="x1">矩形1の左上座標 X</param>
/// <param name="y1">矩形1の左上座標 Y</param>
/// <param name="width1">矩形1の横幅</param>
/// <param name="height1">矩形1の縦幅</param>
/// <param name="x2">矩形2の左上座標 X</param>
/// <param name="y2">矩形2の左上座標 Y</param>
/// <param name="width2">矩形2の横幅</param>
/// <param name="height2">矩形2の縦幅</param>
int IsRect2RectHit(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);

/// <summary>
/// 点と円の当たり判定
/// </summary>
/// <param name="posX">点の座標 X</param>
/// <param name="posY">点の座標 Y</param>
/// <param name="circleX">円の座標 X</param>
/// <param name="circleY">円の座標 Y</param>
/// <param name="circleRadius">円の半径</param>
/// <returns>当たってる:true 当たってない:false</returns>
int IsPos2CircleHit(float posX, float posY, float circleX, float circleY, float circleRadius);

/// <summary>
/// 点と矩形の当たり判定
/// </summary>
/// <param name="posX">点の座標 X</param>
/// <param name="posY">点の座標 Y</param>
/// <param name="rectX">矩形の左上座標 X</param>
/// <param name="rectY">矩形の左上座標 Y</param>
/// <param name="rectWidth">矩形の横幅</param>
/// <param name="rectHeight">矩形の縦幅</param>
int IsPos2RectHit(float posX, float posY, float rectX, float rectY, float rectWidth, float rectHeight);

/// <summary>
/// 円と矩形の当たり判定
/// </summary>
/// <param name="circleX">円の座標 X</param>
/// <param name="circleY">円の座標 Y</param>
/// <param name="radius">円の半径</param>
/// <param name="rectX">矩形の左上座標 X</param>
/// <param name="rectY">矩形の左上座標 Y</param>
/// <param name="width">矩形の横幅</param>
/// <param name="height">矩形の縦幅</param>
int IsCircle2RectHit(float circleX, float circleY, float radius, float rectX, float rectY, float width, float height);

/// <summary>
/// 円とカプセルの当たり判定
/// </summary>
/// <param name="circleX">円の座標 X</param>
/// <param name="circleY">円の座標 Y</param>
/// <param name="circleRadius">円の半径</param>
/// <param name="capsuleX1">カプセルの座標1 X</param>
/// <param name="capsuleY1">カプセルの座標1 Y</param>
/// <param name="capsuleX2">カプセルの座標2 X</param>
/// <param name="capsuleY2">カプセルの座標2 Y</param>
/// <param name="capsuleRadius">カプセルの半径</param>
/// <returns>当たってる:true 当たってない:false</returns>
int IsCircle2CapsuleHit(float circleX, float circleY, float circleRadius, float capsuleX1, float capsuleY1, float capsuleX2, float capsuleY2, float capsuleRadius);

/// <summary>
/// 円が指定されたエリア外にいることの検知
/// </summary>
/// <param name="circleX">円の座標 X</param>
/// <param name="circleY">円の座標 Y</param>
/// <param name="radius">円の半径</param>
/// <param name="areaX">エリアの左上座標 X</param>
/// <param name="areaY">エリアの左上座標 Y</param>
/// <param name="areaWidth">エリアの横幅</param>
/// <param name="areaHeight">エリアの縦幅</param>
/// <returns>エリアから  出ている:true 出ていない:false</returns>
int IsOutsideAreaCircle(float circleX, float circleY, float radius, float areaX, float areaY, float areaWidth, float areaHeight);

/// <summary>
/// 矩形が指定されたエリア外にいることの検知
/// </summary>
/// <param name="rectX">矩形の左上座標 X</param>
/// <param name="rectY">矩形の左上座標 Y</param>
/// <param name="rectWidth">矩形の横幅</param>
/// <param name="rectWidth">矩形の縦幅</param>
/// <param name="areaX">エリアの左上座標 X</param>
/// <param name="areaY">エリアの左上座標 Y</param>
/// <param name="areaWidth">エリアの横幅</param>
/// <param name="areaHeight">エリアの縦幅</param>
/// <returns>エリアから  出ている:true 出ていない:false</returns>
int IsOutsideAreaRect(float rectX, float rectY, float rectWidth, float rectHeight, float areaX, float areaY, float areaWidth, float areaHeight);

/// <summary>
/// 点の回転をする
/// </summary>
/// <param name="rotateX">回転させる点の座標 X</param>
/// <param name="rotateY">回転させる点の座標 Y</param>
/// <param name="originX">回転の中心座標 X</param>
/// <param name="originY">回転の中心座標 Y</param>
/// <param name="theta">回転角(rad)</param>
/// <returns>回転後の点のVector2構造体型座標</returns>
Vector2 RotatePos(float rotateX, float rotateY, float originX, float originY, float theta);

/// <summary>
/// 渡されたX座標をワールド座標系のX座標に変換
/// </summary>
/// <param name="posX">変換する座標 X</param>
/// <param name="worldOriginPosX">ワールド座標系の原点座標 X</param>
/// <returns>ワールド座標系のX座標</returns>
float ConvertWCX(float posX, float worldOriginPosX);

/// <summary>
/// 渡されたY座標をワールド座標系のY座標に変換
/// </summary>
/// <param name="posY">変換する座標 Y</param>
/// <param name="worldOriginPosY">ワールド座標系の原点座標 Y</param>
/// <returns>ワールド座標系のX座標</returns>
float ConvertWCY(float posY, float worldOriginPosY);

/// <summary>
/// 渡されたint型の値を 0.0f ～ 1.0f の時間に変換
/// </summary>
/// <param name="nowT">現在の時間</param>
/// <param name="endT">終了時間</param>
/// <returns>0.0f ～ 1.0f の時間 t</returns>
float ConvertInt2Time(int nowT, int endT);

/// <summary>
/// 渡されたfloat型の値を 0.0f ～ 1.0f の時間に変換
/// </summary>
/// <param name="nowT">現在の時間</param>
/// <param name="endT">終了時間</param>
/// <returns>0.0f ～ 1.0f の時間 t</returns>
float ConvertFloat2Time(float nowT, float endT);

/// <summary>
/// 桁数を取得する
/// </summary>
/// <param name="num">桁数を取得したい整数</param>
/// <returns>桁数</returns>
int GetDigit(int num);

/// <summary>
/// 回転行列生成用関数
/// </summary>
/// <param name="rotate">回転</param>
/// <returns>回転行列</returns>
Matrix3x3 MakeRotateMatrix(float theta);

/// <summary>
/// 拡縮行列生成用関数
/// </summary>
/// <param name="scale">拡縮</param>
/// <returns>拡縮行列</returns>
Matrix3x3 MakeScaleMatrix(Vector2 scale);

/// <summary>
/// 移動行列生成用関数
/// </summary>
/// <param name="scale">移動</param>
/// <returns>移動行列</returns>
Matrix3x3 MakeTranslateMatrix(Vector2 translate);

/// <summary>
/// アフィン行列生成用関数
/// </summary>
/// <param name="scale">拡縮</param>
/// <param name="rotate">回転</param>
/// <param name="translate">平行移動</param>
/// <returns>アフィン行列</returns>
Matrix3x3 MakeAffineMatrix(Vector2 scale, float rotate, Vector2 translate);

/// <summary>
/// 2次元ベクトルを同時座標系として変換する
/// </summary>
/// <param name="vector">変換するベクトル</param>
/// <param name="matrix">行列</param>
/// <returns>変換後のベクトル</returns>
Vector2 Transform(Vector2 vector, Matrix3x3 matrix);

/// <summary>
/// 3x3行列の積
/// </summary>
/// <param name="matrix1">3x3行列 1</param>
/// <param name="matrix2">3x3行列 2</param>
/// <returns>3x3行列の積</returns>
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2);

/// <summary>
/// 3x3の転置行列を求める関数
/// </summary>
/// <param name="matrix">転置行列を求めたい3x3行列</param>
/// <returns>3x3転置行列</returns>
Matrix3x3 Transpose(Matrix3x3 matrix);

/// <summary>
/// 3x3の逆行列を求める関数
/// </summary>
/// <param name="matrix">逆行列を求めたい3x3行列</param>
/// <returns>3x3逆行列</returns>
Matrix3x3 InverseMatrix(Matrix3x3 matrix);

/// <summary>
/// 正射影行列生成用関数
/// </summary>
/// <param name="left">カメラに映す範囲の左座標</param>
/// <param name="top">カメラに映す範囲の上座標</param>
/// <param name="right">カメラに映す範囲の右座標</param>
/// <param name="bottom">カメラに映す範囲の下座標</param>
/// <returns>3x3正射影行列</returns>
Matrix3x3 MakeOrthhogprahicsMatrix(float left, float top, float right, float bottom);

/// <summary>
/// ビューポート行列生成用関数
/// </summary>
/// <param name="left">画面の左座標</param>
/// <param name="top">画面の上座標</param>
/// <param name="width">画面の横幅</param>
/// <param name="height">画面の縦幅</param>
/// <returns></returns>
Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height);

/// <summary>
/// WVPVp行列を生成するレンダリングパイプライン関数
/// </summary>
/// <param name="worldMatrix">ワールド行列</param>
/// <param name="cameraWorldMatrix">カメラのワールド行列</param>
/// <param name="orthoLeft">正射影行列 カメラに映す範囲の左座標</param>
/// <param name="orthoTop">正射影行列 カメラに映す範囲の上座標</param>
/// <param name="orthoRight">正射影行列 カメラに映す範囲の右座標</param>
/// <param name="orthoBottom">正射影行列 カメラに映す範囲の下座標</param>
/// <param name="viewportLeft">ビューポート行列 画面の左座標</param>
/// <param name="viewportTop">ビューポート行列 画面の上座標</param>
/// <param name="viewportWidth">ビューポート行列 画面の横幅</param>
/// <param name="viewportHeight">ビューポート行列 画面の縦幅</param>
/// <returns>WVPVp行列</returns>
Matrix3x3 RenderingPipeline(Matrix3x3 worldMatrix, Matrix3x3 cameraWorldMatrix, float orthoLeft, float orthoTop, float orthoRight, float orthoBottom, float viewportLeft, float viewportTop, float viewportWidth, float viewportHeight);

/// <summary>
/// 矩形を構成する4点を生成する関数
/// </summary>
/// <param name="pivot">ローカル座標の原点</param>
/// <param name="leftTop">左上座標</param>
/// <param name="rightTop">右上座標</param>
/// <param name="leftBottom">左下座標</param>
/// <param name="rightBottom">右下座標</param>
/// <param name="width">横幅</param>
/// <param name="height">縦幅</param>
void MakeQuadPos(const Vector2 &pivot, Vector2 &leftTop, Vector2 &rightTop, Vector2 &leftBottom, Vector2 &rightBottom, float width, float height);

/// <summary>
/// 設定したキーがトリガーされたことの検知用
/// </summary>
/// <param name="keysID">判定するキー</param>
/// <param name="keys">押されてるキーの情報</param>
/// <param name="preKeys">押されてたキーの情報</param>
/// <returns>true:トリガーされている false:トリガーされていない</returns>
bool IsTriggerKeys(std::vector<int> keysID, char *keys, char *preKeys);

/// <summary>
/// ファイルが存在するかの検知
/// </summary>
/// <param name="fileName">ファイルへのパス</param>
bool IsFileExists(const std::string &fileName);

/// <summary>
/// 文字列が指定した文字列で終わるかの検知
/// </summary>
bool StringEndsWith(const std::string &str, const std::string &end);