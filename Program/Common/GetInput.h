#pragma once
#include <vector>

//==================================================
// Direct Input Cursor
//==================================================

#define DIC_LEFT			0x00
#define DIC_RIGHT			0x01
#define DIC_CENTER			0x02
#define DIC_EX1				0x03
#define DIC_EX2				0x04
#define DIC_EX3				0x05
#define DIC_EX4				0x06
#define DIC_EX5				0x07

//==================================================
// Direct Input Xbox Controller
//==================================================

#define DIXC_UP				0x00
#define DIXC_DOWN			0x01
#define DIXC_LEFT			0x02
#define DIXC_RIGHT			0x03
#define DIXC_MENU			0x04
#define DIXC_VIEW			0x05
#define DIXC_LEFTSTICK		0x06
#define DIXC_RIGHTSTICK		0x07
#define DIXC_LEFTBUTTON		0x08
#define DIXC_RIGHTBUTTON	0x09
#define DIXC_LB				DIXC_LEFTBUTTON
#define DIXC_RB				DIXC_RIGHTBUTTON
#define DIXC_A				0x0A
#define DIXC_B				0x0B
#define DIXC_X				0x0C
#define DIXC_Y				0x0D
#define DIXC_LEFTTRIGGER	DIXC_A
#define DIXC_RIGHTTRIGGER	DIXC_B
#define DIXC_LT				DIXC_LEFTTRIGGER
#define DIXC_RT				DIXC_RIGHTTRIGGER

// 入力の種類
enum InputType {
    INPUT_TYPE_NONE,
    KEYBOARD,
    MOUSE,
    JOYSTICK
};

/// @brief 入力を取得するクラス
class GetInput final {
public:
    GetInput(const GetInput &) = delete;
    GetInput &operator=(const GetInput &) = delete;
    GetInput(GetInput &&) = delete;
    GetInput &operator=(GetInput &&) = delete;

    /// @brief インスタンスの取得
    /// @return GetInputのインスタンス
    static GetInput *GetInstance() {
        static GetInput instance;
        return &instance;
    }

    //==================================================
    // 各種更新処理
    //==================================================
#pragma region update
    /// @brief キーの更新処理
	void UpdateKeys();

    /// @brief マウスの更新処理
	void UpdateMouse();

    /// @brief ジョイスティックの更新処理
	void UpdateJoystick();

    /// @brief 入力の種類の更新処理
    void UpdateInputType();
#pragma endregion

    //==================================================
    // キー入力の取得
    //==================================================
#pragma region key
    /// @brief 押されたキーの取得
    /// @return 押されたキー。押されていない場合は-1を返す
    int AnyKey();

    /// @brief 前フレームで押されたキーの取得
    /// @return 前フレームで押されたキー。押されていない場合は-1を返す
    int AnyPreKey();

    /// @brief トリガーされたキーの取得
    /// @return トリガーされたキー。押されていない場合は-1を返す
    int AnyTriggerKey();

    /// @brief リリースされたキーの取得
    /// @return リリースされたキー。押されていない場合は-1を返す
    int AnyReleaseKey();

    /// @brief キーの入力判定
    /// @param keyID キーのID
    /// @return キーが押されている:true キーが押されていない:false
    bool Keys(int keyID);

    /// @brief 前フレームでのキーの入力判定
    /// @param keyID キーのID
    /// @return キーが押されている:true キーが押されていない:false
    bool PreKeys(int keyID);

    /// @brief トリガーされたキーの入力判定
    /// @param keyID キーのID
    /// @return キーが押されている:true キーが押されていない:false
    bool TriggerKeys(int keyID);

    /// @brief リリースされたキーの入力判定
    /// @param keyID キーのID
    /// @return キーが押されている:true キーが押されていない:false
	bool ReleaseKeys(int keyID);

    /// @brief 押されたキーの入力判定
    /// @param keyID キーのID
	/// @return キーが押されている:true キーが押されていない:false
    bool Keys(std::vector<int> keyID);

    /// @brief 前フレームでのキーの入力判定
    /// @param keyID キーのID
    /// @return キーが押されている:true キーが押されていない:false
	bool PreKeys(std::vector<int> keyID);

    /// @brief トリガーされたキーの入力判定
    /// @param keyID キーのID
    /// @return キーが押されている:true キーが押されていない:false
    bool TriggerKeys(std::vector<int> keyID);

    /// @brief リリースされたキーの入力判定
    /// @param keyID キーのID
    /// @return キーが押されている:true キーが押されていない:false
	bool ReleaseKeys(std::vector<int> keyID);
#pragma endregion

    //==================================================
    // マウス入力の取得
    //==================================================
#pragma region mouse
    /// @brief マウスのX座標の取得
    /// @return マウスのX座標
	int MouseX();

    /// @brief マウスのY座標の取得
     /// @return マウスのY座標
	int MouseY();

    /// @brief 前フレームでのマウスのX座標の取得
    /// @return マウスのX座標
	int MousePreX();

    /// @brief 前フレームでのマウスのY座標の取得
    /// @return マウスのY座標
	int MousePreY();

    /// @brief 押されたマウスボタンの取得
    /// @return 押されたマウスボタン。押されていない場合は-1を返す
    int AnyMousePushButton();

    /// @brief 前フレームで押されたマウスボタンの取得
    /// @return 前フレームで押されたマウスボタン。押されていない場合は-1を返す
    int AnyMousePrePushButton();

    /// @brief トリガーされたマウスボタンの取得
    /// @return トリガーされたマウスボタン。押されていない場合は-1を返す
    int AnyMouseTriggerButton();

    /// @brief リリースされたマウスボタンの取得
    /// @return リリースされたマウスボタン。押されていない場合は-1を返す
    int AnyMouseReleaseButton();

    /// @brief マウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
	bool MousePushButton(int buttonID);

    /// @brief 前フレームでのマウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
	bool MousePrePushButton(int buttonID);

    /// @brief トリガーされたマウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
	bool MouseTriggerButton(int buttonID);

    /// @brief リリースされたマウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
    bool MouseReleaseButton(int buttonID);

    /// @brief マウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
	bool MousePushButton(std::vector<int> buttonID);

    /// @brief 前フレームでのマウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
	bool MousePrePushButton(std::vector<int> buttonID);

    /// @brief トリガーされたマウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
	bool MouseTriggerButton(std::vector<int> buttonID);

    /// @brief リリースされたマウスボタンの入力判定
    /// @param buttonID マウスボタンのID
    /// @return マウスボタンが押されている:true マウスボタンが押されていない:false
	bool MouseReleaseButton(std::vector<int> buttonID);

    /// @brief マウスの移動判定
    /// @return マウスが移動している:true マウスが移動していない:false
	bool IsMouseMove();
#pragma endregion

    //==================================================
    // ジョイスティック入力の取得
    //==================================================
#pragma region joystick
    /// @brief ジョイスティックの数の取得
    /// @return ジョイスティックの数
	int JoysticksNum();

    /// @brief ジョイスティックの左アナログスティックのX座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの左アナログスティックのX座標
	int JoystickAnalogLeftX(int stickNo);

    /// @brief ジョイスティックの左アナログスティックのY座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの左アナログスティックのY座標
	int JoystickAnalogLeftY(int stickNo);

    /// @brief 前フレームでのジョイスティックの左アナログスティックのX座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの左アナログスティックのX座標
	int JoystickAnalogLeftPreX(int stickNo);

    /// @brief 前フレームでのジョイスティックの左アナログスティックのY座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの左アナログスティックのY座標
	int JoystickAnalogLeftPreY(int stickNo);

    /// @brief ジョイスティックの右アナログスティックのX座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの右アナログスティックのX座標
	int JoystickAnalogRightX(int stickNo);

    /// @brief ジョイスティックの右アナログスティックのY座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの右アナログスティックのY座標
	int JoystickAnalogRightY(int stickNo);

    /// @brief 前フレームでのジョイスティックの右アナログスティックのX座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの右アナログスティックのX座標
	int JoystickAnalogRightPreX(int stickNo);

    /// @brief 前フレームでのジョイスティックの右アナログスティックのY座標の取得
    /// @param stickNo ジョイスティックの番号
    /// @return ジョイスティックの右アナログスティックのY座標
	int JoystickAnalogRightPreY(int stickNo);

    /// @brief 押されたジョイスティックボタンの取得
    /// @param stickNo ジョイスティックの番号
    /// @return 押されたジョイスティックボタン。押されていない場合は-1を返す
    int AnyJoystickPushButton(int stickNo);

    /// @brief 前フレームで押されたジョイスティックボタンの取得
    /// @param stickNo ジョイスティックの番号
    /// @return 前フレームで押されたジョイスティックボタン。押されていない場合は-1を返す
    int AnyJoystickPrePushButton(int stickNo);

    /// @brief トリガーされたジョイスティックボタンの取得
    /// @param stickNo ジョイスティックの番号
    /// @return トリガーされたジョイスティックボタン。押されていない場合は-1を返す
    int AnyJoystickTriggerButton(int stickNo);

    /// @brief リリースされたジョイスティックボタンの取得
    /// @param stickNo ジョイスティックの番号
    /// @return リリースされたジョイスティックボタン。押されていない場合は-1を返す
    int AnyJoystickReleaseButton(int stickNo);

    /// @brief ジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickPushButton(int stickNo, int buttonID);

    /// @brief 前フレームでのジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickPrePushButton(int stickNo, int buttonID);

    /// @brief トリガーされたジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickTriggerButton(int stickNo, int buttonID);

    /// @brief リリースされたジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickReleaseButton(int stickNo, int buttonID);

    /// @brief ジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickPushButton(int stickNo, std::vector<int> buttonID);

    /// @brief 前フレームでのジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickPrePushButton(int stickNo, std::vector<int> buttonID);

    /// @brief トリガーされたジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickTriggerButton(int stickNo, std::vector<int> buttonID);

    /// @brief リリースされたジョイスティックボタンの入力判定
    /// @param stickNo ジョイスティックの番号
    /// @param buttonID ジョイスティックボタンのID
    /// @return ジョイスティックボタンが押されている:true ジョイスティックボタンが押されていない:false
	bool JoystickReleaseButton(int stickNo, std::vector<int> buttonID);
#pragma endregion

    //==================================================
    // 入力の種類の取得
    //==================================================
#pragma region inputType
    /// @brief 入力の種類の判定
    /// @param inputType 入力の種類
    /// @return 入力の種類が一致:true 入力の種類が一致しない:false
    bool IsInputType(InputType inputType);

    /// @brief 入力の種類の判定
    /// @param inputType1 入力の種類1
    /// @param inputType2 入力の種類2
    /// @return 入力の種類が一致:true 入力の種類が一致しない:false
    bool IsInputType(InputType inputType1, InputType inputType2);

    /// @brief 入力の種類の取得
    /// @return 入力の種類
    InputType NowInputType();
#pragma endregion

private:
    GetInput() = default;
    ~GetInput() = default;

    char keys_[256] = {};
    char preKeys_[256] = {};

    int mouseX_ = 0;
    int mouseY_ = 0;
    int mousePreX_ = 0;
    int mousePreY_ = 0;
    char mousePushButton_[8] = {};
    char mousePrePushButton_[8] = {};
    bool isMouseMove_ = false;

    int joysticksNum_ = 0;
    std::vector<int> joystickAnalogLeftX_ = {};
    std::vector<int> joystickAnalogLeftY_ = {};
    std::vector<int> joystickAnalogLeftPreX_ = {};
    std::vector<int> joystickAnalogLeftPreY_ = {};
    std::vector<int> joystickAnalogRightX_ = {};
    std::vector<int> joystickAnalogRightY_ = {};
    std::vector<int> joystickAnalogRightPreX_ = {};
    std::vector<int> joystickAnalogRightPreY_ = {};
    std::vector<char> joystickPushButton_[20] = {};
    std::vector<char> joystickPrePushButton_[20] = {};

    InputType nowInputType_ = INPUT_TYPE_NONE;
};

bool GetInput(InputType inputType, int keyID);
bool GetInput(InputType inputType, std::vector<int> keyID);
InputType GetNowInputType();