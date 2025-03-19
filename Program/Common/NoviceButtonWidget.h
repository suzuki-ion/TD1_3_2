#pragma once
#include "Structures.h"
#include "CustomNovice.h"
#include <vector>

enum SelectUseJoystick {
    JOYSTICK_NONE,
    JOYSTICK_LEFT_X,
    JOYSTICK_LEFT_Y,
    JOYSTICK_RIGHT_X,
    JOYSTICK_RIGHT_Y
};

// Novice用ボタンの構造体
struct NoviceButton {
    // ボタン描画位置
    Vector2 pos;
    // ボタンの横幅
    float width = 0;
    // ボタンの縦幅
    float height = 0;
    // ボタンの識別番号
    int id = 0;
    // ボタン通常時に描画する画像
    // (不使用なら -1 に設定しておく)
    int graphHandle2Usually = -1;
    // ボタン選択時に描画する画像
    // (不使用なら -1 に設定しておく。ちなみにその場合、通常時の画像が使われる。)
    int graphHandle2Select = -1;
    // ボタン決定時に描画する画像
    // (不使用なら -1 に設定しておく。ちなみにその場合、選択時の画像が使われる。)
    int graphHandle2Pushed = -1;
    // ボタン選択時の音
    // (不使用なら -1 に設定しておく)
    int soundHandle2Select = -1;
    // ボタン決定時の音
    // (不使用なら -1 に設定しておく)
    int soundHandle2Pushed = -1;
    // 文字描画時に使用するフォント
    // (不使用なら -1 に設定しておく)
    int fontGh = -1;
    // 文字の横幅
    int fontWidth = 1;
    // 文字の縦幅
    int fontHeight = 1;
    // 文字描画時の横幅
    int fontDrawWidth = 1;
    // 文字描画時の縦幅
    int fontDrawHeight = 1;
    // 文字の表示方法
    int fontDrawMethod = 0;
    // 文字の描画時のずらし座標
    Vector2 fontDrawShift;
    // 文字間のマージン
    Vector2Int fontMargin;
    // ボタン通常時の描画色
    unsigned int color2Usually = 0xFFFFFF80;
    // ボタン選択時の描画色
    unsigned int color2Select = WHITE;
    // ボタン決定時の描画色
    unsigned int color2Pushed = 0xFF8080FF;
    // ボタンに表示する文字
    std::string str = "\0";
    // 個別の選択用キー
    std::vector<int> selectKeys;
    // 個別の決定用キー
    std::vector<int> pushedKeys;
};

class NoviceButtonWidget {
    // マウスの位置
    Vector2Int mousePos_;
    // 前までのマウスの位置
    Vector2Int preMousePos_;
    // ボタン選択時にループするかのフラグ
    bool isSelectLoop_ = false;
    // マウスでも操作できるかのフラグ
    bool isSelectButton2Mouse_ = false;
    // 選択してるボタンの値
    int selectButton_ = 0;
    // 決定したボタンの値
    int pushedButton_ = -1;

    // ひとつ前のボタンを選択するためのキー
    std::vector<int> preButtonSelectKeys_;
    // ひとつ後のボタンを選択するためのキー
    std::vector<int> nextButtonSelectKeys_;
    // ボタン決定キー
    std::vector<int> pushButtonKeys_;

    // ひとつ前のボタンを選択するためのコントローラーのボタン
    std::vector<int> preButtonSelectControllerButtons_;
    // ひとつ後のボタンを選択するためのコントローラーのボタン
    std::vector<int> nextButtonSelectControllerButtons_;
    // ボタン決定キー
    std::vector<int> pushButtonControllerButtons_;

    // ひとつ前のボタンを選択するために使うジョイスティックの方向
    SelectUseJoystick useJoystick_ = JOYSTICK_NONE;
    // ひとつ前のボタンを選択する入力値
    int preUseJoystickValue_ = 0;
    // ひとつ後のボタンを選択する入力値
    int nextUseJoystickValue_ = 0;

    // 処理を除外するボタンのID
    std::vector<int> excludeButtonID_;

    // ボタンの情報格納用配列
    std::vector<NoviceButton> buttons_;
    // 以前のボタン検索結果
    NoviceButton *preSearchButton_ = nullptr;

    bool IsPreButtonSelect();
    bool IsNextButtonSelect();
    bool IsPushButton();

public:
    NoviceButtonWidget();

    /// <summary>
    /// 以前のボタン検索結果取得用
    /// </summary>
    /// <returns>以前のボタン検索結果</returns>
    NoviceButton *PreSearchButton() { return preSearchButton_; };

    /// <summary>
    /// キー・コントローラー共通の動作設定
    /// </summary>
    void SetButtonOption2Common(
        bool isSelectLoop
    );

    /// <summary>
    /// キーの動作設定
    /// </summary>
    /// <param name="preButtonSelectKeys">ひとつ前のボタンを選択するためのキー</param>
    /// <param name="nextButtonSelectKeys">ひとつ後のボタンを選択するためのキー</param>
    /// <param name="pushButtonKeys">ボタン決定キー</param>
    /// <param name="isSelectButton2Mouse">マウスでもボタンを選択できるようにするかどうか</param>
    void SetButtonOption2Keys(
        std::vector<int> preButtonSelectKeys,
        std::vector<int> nextButtonSelectKeys,
        std::vector<int> pushButtonKeys,
        bool isSelectButton2Mouse
    );

    /// <summary>
    /// コントローラーの動作設定
    /// </summary>
    /// <param name="preButtonSelectControllerButtons">ひとつ前のボタンを選択するためのコントローラーのボタン</param>
    /// <param name="nextButtonSelectControllerButtons">ひとつ後のボタンを選択するためのコントローラーのボタン</param>
    /// <param name="pushButtonControllerButtons">ボタン決定キー</param>
    /// <param name="preUseJoystick">ひとつ前のボタンを選択するために使うジョイスティックの方向</param>
    /// <param name="preUseJoystickValue">ひとつ前のボタンを選択する入力値</param>
    /// <param name="nextUseJoystick">ひとつ後のボタンを選択するために使うジョイスティックの方向</param>
    /// <param name="nextUseJoystickValue">ひとつ後のボタンを選択する入力値</param>
    void SetButtonOption2Controller(
        std::vector<int> preButtonSelectControllerButtons,
        std::vector<int> nextButtonSelectControllerButtons,
        std::vector<int> pushButtonControllerButtons,
        SelectUseJoystick useJoystick,
        int preUseJoystickValue,
        int nextUseJoystickValue
    );

    /// <summary>
    /// ボタンを追加する関数
    /// </summary>
    /// <param name="addButton">追加するボタンの情報</param>
    void AddButton(NoviceButton addButton);
    
    /// <summary>
    /// ボタンの検索(情報取得用)
    /// </summary>
    /// <param name="id">検索したいボタンのID</param>
    /// <returns>ボタンの情報へのポインタ。見つからなかった場合は nullptr が返ってくる。</returns>
    NoviceButton *SearchButton(int id);

    /// <summary>
    /// ボタン全削除用関数
    /// </summary>
    void ClearButton();

    /// <summary>
    /// 押してるボタンのID取得用
    /// </summary>
    /// <returns>押してるボタンのID。押していなければ -1 を返す。</returns>
    int GetPushedButtonID() const;
    /// <summary>
    /// 押してるボタンの情報取得用
    /// </summary>
    /// <returns>押してるボタンへのポインタ。押してなければ nullptr を返す。</returns>
    NoviceButton *GetPushedButton();

    /// <summary>
    /// 選択してるボタンのID取得用
    /// </summary>
    /// <returns>選択してるボタンのID。選択していなければ -1 を返す。</returns>
    int GetSelectButtonID() const;
    /// <summary>
    /// 選択してるボタンの情報取得用
    /// </summary>
    /// <returns>選択してるボタンへのポインタ。選択してなければ nullptr を返す。</returns>
    NoviceButton *GetSelectButton();

    /// <summary>
    /// 選択してるボタンリセット用
    /// </summary>
    /// <param name="selectButton">リセットする際の値。初期値は 0</param>
    void ResetSelect(int selectButton = 0);

    /// <summary>
    /// ボタンの処理
    /// </summary>
    void Update();

    /// <summary>
    /// ボタンの描画
    /// </summary>
    /// <param name="shiftPos">ボタン全てに対して適応されるずらし座標</param>
    void Draw(const Vector2 &shiftPos = { 0.0f, 0.0f });
};