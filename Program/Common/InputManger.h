#pragma once
#include "GetInput.h"
#include "InputConfig.h"

class InputManager {
public:
    InputManager(const InputManager &) = delete;
    InputManager &operator=(const InputManager &) = delete;
    InputManager(InputManager &&) = delete;
    InputManager &operator=(InputManager &&) = delete;

    static InputManager *GetInstance() {
        static InputManager instance;
        return &instance;
    }

    /// @brief 入力の判定
    /// @param inputConfigType 入力の種類
    /// @return true:押されている false:押されていない
    bool IsPush(InputConfigType inputConfigType);

    /// @brief 前フレームの入力の判定
    /// @param inputConfigType 入力の種類
    /// @return true:押されている false:押されていない
    bool IsPrePush(InputConfigType inputConfigType);

    /// @brief 入力のトリガー判定
    /// @param inputConfigType 入力の種類
    /// @return true:押された false:押されていない
    bool IsTrigger(InputConfigType inputConfigType);

    /// @brief 入力のリリース判定
    /// @param inputConfigType 入力の種類
    /// @return true:離された false:離されていない
    bool IsRelease(InputConfigType inputConfigType);

private:
    InputManager() = default;
    ~InputManager() = default;

    GetInput *getInput_ = GetInput::GetInstance();
    InputConfig *inputConfig_ = InputConfig::GetInstance();
};

/// @brief 入力の判定
/// @param inputConfigType 入力の種類
/// @return true:押されている false:押されていない
bool InputIsPush(InputConfigType inputConfigType);

/// @brief 前フレームの入力の判定
/// @param inputConfigType 入力の種類
/// @return true:押されている false:押されていない
bool InputIsPrePush(InputConfigType inputConfigType);

/// @brief 入力のトリガー判定
/// @param inputConfigType 入力の種類
/// @return true:押された false:押されていない
bool InputIsTrigger(InputConfigType inputConfigType);

/// @brief 入力のリリース判定
/// @param inputConfigType 入力の種類
/// @return true:離された false:離されていない
bool InputIsRelease(InputConfigType inputConfigType);