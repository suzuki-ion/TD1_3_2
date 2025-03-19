#pragma once
#include "GetInput.h"

/// @brief 入力の種類
enum InputConfigType {
    CONFIG_DECIDE,
    CONFIG_CANCEL,
    CONFIG_MOVE_UP,
    CONFIG_MOVE_DOWN,
    CONFIG_MOVE_LEFT,
    CONFIG_MOVE_RIGHT,
    CONFIG_JUMP,
    CONFIG_CHANGE_MODE,
    CONFIG_ROTATE_LEFT,
    CONFIG_ROTATE_RIGHT,
    CONFIG_PAUSE,

    CONFIG_MAX
};

/// @brief 入力の設定用構造体
struct InputConfigData {
    InputType inputType = INPUT_TYPE_NONE;
    int key = 0;
};

/// @brief 入力の設定を行うクラス
class InputConfig {
public:
    InputConfig(const InputConfig &) = delete;
    InputConfig &operator=(const InputConfig &) = delete;
    InputConfig(InputConfig &&) = delete;
    InputConfig &operator=(InputConfig &&) = delete;
    
    static InputConfig *GetInstance() {
        static InputConfig instance;
        return &instance;
    }

    /// @brief キー入力の設定
    /// @param type 変更するキーの種類
    /// @param key キーの値
    void SetConfig(InputConfigType inputConfigType, InputType inputType, int key);

    /// @brief キー入力の取得
    /// @param type 取得するキーの種類
    /// @return キーの値
    InputConfigData GetKey(InputConfigType type) const;

    /// @brief コントローラー入力の取得
    /// @param type 取得するキーの種類
    /// @return キーの値
    InputConfigData GetController(InputConfigType type) const;

private:
    InputConfig() = default;
    ~InputConfig() = default;

    InputConfigData keyConfig_[CONFIG_MAX] = {};
    InputConfigData contollerConfig_[CONFIG_MAX] = {};
};

#define INPUT_CONFIG InputConfig::GetInstance()
#define INPUT_CONFIG_KEY(type) INPUT_CONFIG->GetKey(type)
#define INPUT_CONFIG_CONTROLLER(type) INPUT_CONFIG->GetController(type)
#define INPUT_CONFIG_SET(type, inputType, key) INPUT_CONFIG->SetConfig(type, inputType, key)