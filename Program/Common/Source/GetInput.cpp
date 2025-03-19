#include <Novice.h>

#include <Common/GetInput.h>
#include <Common/ScreenSizeGet.h>

//--------- 各更新処理 ---------//

void GetInput::UpdateKeys() {
    // キー取得
#pragma omp parallel for
    for (int i = 0; i < 256; i++) {
        preKeys_[i] = keys_[i];
    }
    Novice::GetHitKeyStateAll(keys_);
}

void GetInput::UpdateMouse() {
    if (mouseX_ != mousePreX_ || mouseY_ != mousePreY_) {
        isMouseMove_ = true;
    } else {
        isMouseMove_ = false;
    }
    // 座標取得
    mousePreX_ = mouseX_;
    mousePreY_ = mouseY_;
    Novice::GetMousePosition(&mouseX_, &mouseY_);
    // ずれてる分だけ引く
    mouseX_ -= static_cast<int>(ScreenSize::ShiftX());
    mouseY_ -= static_cast<int>(ScreenSize::ShiftY());

    // クリック取得
    memcpy(mousePrePushButton_, mousePushButton_, 8);
    for (int i = 0; i < 8; i++) {
        mousePushButton_[i] = static_cast<char>(Novice::IsPressMouse(i));
    }
}

void GetInput::UpdateJoystick() {
    // 接続されてるジョイスティックの数だけ要素を確保
    for (int i = 0; i < (Novice::GetNumberOfJoysticks() - joysticksNum_); i++) {
        joystickAnalogLeftX_.push_back(0);
        joystickAnalogLeftY_.push_back(0);
        joystickAnalogLeftPreX_.push_back(0);
        joystickAnalogLeftPreY_.push_back(0);
        joystickAnalogRightX_.push_back(0);
        joystickAnalogRightY_.push_back(0);
        joystickAnalogRightPreX_.push_back(0);
        joystickAnalogRightPreY_.push_back(0);
        for (int j = 0; j < 20; j++) {
            joystickPushButton_[j].push_back(0);
            joystickPrePushButton_[j].push_back(0);
        }
    }
    for (int i = 0; i < (joysticksNum_ - Novice::GetNumberOfJoysticks()); i++) {
        joystickAnalogLeftX_.pop_back();
        joystickAnalogLeftY_.pop_back();
        joystickAnalogLeftPreX_.pop_back();
        joystickAnalogLeftPreY_.pop_back();
        joystickAnalogRightX_.pop_back();
        joystickAnalogRightY_.pop_back();
        joystickAnalogRightPreX_.pop_back();
        joystickAnalogRightPreY_.pop_back();
        for (int j = 0; j < 20; j++) {
            joystickPushButton_[j].pop_back();
            joystickPrePushButton_[j].pop_back();
        }
    }

    joysticksNum_ = Novice::GetNumberOfJoysticks();

    for (int i = 0; i < joysticksNum_; i++) {
        joystickAnalogLeftPreX_[i] = joystickAnalogLeftX_[i];
        joystickAnalogLeftPreY_[i] = joystickAnalogLeftY_[i];
        joystickAnalogRightPreX_[i] = joystickAnalogRightX_[i];
        joystickAnalogRightPreY_[i] = joystickAnalogRightY_[i];
        Novice::GetAnalogInputLeft(i, &joystickAnalogLeftX_[i], &joystickAnalogLeftY_[i]);
        Novice::GetAnalogInputRight(i, &joystickAnalogRightX_[i], &joystickAnalogRightY_[i]);
        for (int j = 0; j < 20; j++) {
            joystickPrePushButton_[j][i] = joystickPushButton_[j][i];
            joystickPushButton_[j][i] = static_cast<char>(Novice::IsPressButton(i, static_cast<PadButton>(j)));
        }
    }
}

void GetInput::UpdateInputType() {
    if (nowInputType_ != InputType::KEYBOARD) {
        for (int i = 0; i < 256; i++) {
            if (keys_[i]) {
                nowInputType_ = InputType::KEYBOARD;
                return;
            }
        }
    }
    
    if (nowInputType_ != InputType::MOUSE) {
        for (int i = 0; i < 8; i++) {
            if (mousePushButton_[i]) {
                nowInputType_ = InputType::MOUSE;
                return;
            }
        }
    }

    if (nowInputType_ != InputType::JOYSTICK) {
        for (int i = 0; i < joysticksNum_; i++) {
            if (joystickAnalogLeftX_[i] != 0 || joystickAnalogLeftY_[i] != 0 || joystickAnalogRightX_[i] != 0 || joystickAnalogRightY_[i] != 0) {
                nowInputType_ = InputType::JOYSTICK;
                return;
            }
            for (int j = 0; j < 20; j++) {
                if (joystickPushButton_[j][i]) {
                    nowInputType_ = InputType::JOYSTICK;
                    return;
                }
            }
        }
    }
}

//--------- キーボードの入力取得 ---------//

int GetInput::AnyKey() {
    for (int i = 0; i < 256; i++) {
        if (keys_[i]) {
            return i;
        }
    }
    return -1;
}
int GetInput::AnyPreKey() {
    for (int i = 0; i < 256; i++) {
        if (preKeys_[i]) {
            return i;
        }
    }
    return -1;
}
int GetInput::AnyTriggerKey() {
    for (int i = 0; i < 256; i++) {
        if (keys_[i] && !preKeys_[i]) {
            return i;
        }
    }
    return -1;
}
int GetInput::AnyReleaseKey() {
    for (int i = 0; i < 256; i++) {
        if (!keys_[i] && preKeys_[i]) {
            return i;
        }
    }
    return -1;
}
bool GetInput::Keys(int keyID) { return keys_[keyID]; }
bool GetInput::PreKeys(int keyID) { return preKeys_[keyID]; }
bool GetInput::TriggerKeys(int keyID) { return (keys_[keyID] && !preKeys_[keyID]); }
bool GetInput::ReleaseKeys(int keyID) { return (!keys_[keyID] && preKeys_[keyID]); }
bool GetInput::Keys(std::vector<int> keyID) {
    for (const auto &id : keyID) {
        if (keys_[id]) {
            return true;
        }
    }
    return false;
}
bool GetInput::PreKeys(std::vector<int> keyID) {
    for (const auto &id : keyID) {
        if (preKeys_[id]) {
            return true;
        }
    }
    return false;
}
bool GetInput::TriggerKeys(std::vector<int> keyID) {
    for (const auto &id : keyID) {
        if (keys_[id] && !preKeys_[id]) {
            return true;
        }
    }
    return false;
}
bool GetInput::ReleaseKeys(std::vector<int> keyID) {
    for (const auto &id : keyID) {
        if (!keys_[id] && preKeys_[id]) {
            return true;
        }
    }
    return false;
}

//--------- マウスの入力取得 ---------//

int GetInput::MouseX() { return mouseX_; }
int GetInput::MouseY() { return mouseY_; }
int GetInput::MousePreX() { return mousePreX_; }
int GetInput::MousePreY() { return mousePreY_; }
int GetInput::AnyMousePushButton() {
    for (int i = 0; i < 8; i++) {
        if (mousePushButton_[i]) {
            return i;
        }
    }
    return -1;
}
int GetInput::AnyMousePrePushButton() {
    for (int i = 0; i < 8; i++) {
        if (mousePrePushButton_[i]) {
            return i;
        }
    }
    return -1;
}
int GetInput::AnyMouseTriggerButton() {
    for (int i = 0; i < 8; i++) {
        if (mousePushButton_[i] && !mousePrePushButton_[i]) {
            return i;
        }
    }
    return -1;
}
int GetInput::AnyMouseReleaseButton() {
    for (int i = 0; i < 8; i++) {
        if (!mousePushButton_[i] && mousePrePushButton_[i]) {
            return i;
        }
    }
    return -1;
}
bool GetInput::MousePushButton(int buttonID) { return mousePushButton_[buttonID]; }
bool GetInput::MousePrePushButton(int buttonID) { return mousePrePushButton_[buttonID]; }
bool GetInput::MouseTriggerButton(int buttonID) { return (mousePushButton_[buttonID] && !mousePrePushButton_[buttonID]); }
bool GetInput::MouseReleaseButton(int buttonID) { return (!mousePushButton_[buttonID] && mousePrePushButton_[buttonID]); }
bool GetInput::MousePushButton(std::vector<int> buttonID) {
    for (const auto &id : buttonID) {
        if (mousePushButton_[id]) {
            return true;
        }
    }
    return false;
}
bool GetInput::MousePrePushButton(std::vector<int> buttonID) {
    for (const auto &id : buttonID) {
        if (mousePrePushButton_[id]) {
            return true;
        }
    }
    return false;
}
bool GetInput::MouseTriggerButton(std::vector<int> buttonID) {
    for (const auto &id : buttonID) {
        if (mousePushButton_[id] && !mousePushButton_[id]) {
            return true;
        }
    }
    return false;
}
bool GetInput::MouseReleaseButton(std::vector<int> buttonID) {
    for (const auto &id : buttonID) {
        if (!mousePushButton_[id] && mousePrePushButton_[id]) {
            return true;
        }
    }
    return false;
}
bool GetInput::IsMouseMove() { return isMouseMove_; }

//--------- ジョイスティックの入力取得 ---------//

int GetInput::JoysticksNum() { return joysticksNum_; }
int GetInput::JoystickAnalogLeftX(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogLeftX_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::JoystickAnalogLeftY(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogLeftY_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::JoystickAnalogLeftPreX(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogLeftPreX_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::JoystickAnalogLeftPreY(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogLeftPreY_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::JoystickAnalogRightX(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogRightX_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::JoystickAnalogRightY(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogRightY_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::JoystickAnalogRightPreX(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogRightPreX_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::JoystickAnalogRightPreY(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickAnalogRightPreY_[stickNo];
    } else {
        return 0;
    }
}
int GetInput::AnyJoystickPushButton(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (int i = 0; i < 20; i++) {
            if (joystickPushButton_[i][stickNo]) {
                return i;
            }
        }
        return -1;
    } else {
        return -1;
    }
}
int GetInput::AnyJoystickPrePushButton(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (int i = 0; i < 20; i++) {
            if (joystickPrePushButton_[i][stickNo]) {
                return i;
            }
        }
        return -1;
    } else {
        return -1;
    }
}
int GetInput::AnyJoystickTriggerButton(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (int i = 0; i < 20; i++) {
            if (joystickPushButton_[i][stickNo] && !joystickPrePushButton_[i][stickNo]) {
                return i;
            }
        }
        return -1;
    } else {
        return -1;
    }
}
int GetInput::AnyJoystickReleaseButton(int stickNo) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (int i = 0; i < 20; i++) {
            if (!joystickPushButton_[i][stickNo] && joystickPrePushButton_[i][stickNo]) {
                return i;
            }
        }
        return -1;
    } else {
        return -1;
    }
}
bool GetInput::JoystickPushButton(int stickNo, int buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickPushButton_[buttonID][stickNo];
    } else {
        return false;
    }
}
bool GetInput::JoystickPrePushButton(int stickNo, int buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return joystickPrePushButton_[buttonID][stickNo];
    } else {
        return false;
    }
}
bool GetInput::JoystickTriggerButton(int stickNo, int buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return (joystickPushButton_[buttonID][stickNo] && !joystickPrePushButton_[buttonID][stickNo]);
    } else {
        return false;
    }
}
bool GetInput::JoystickReleaseButton(int stickNo, int buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        return (!joystickPushButton_[buttonID][stickNo] && joystickPrePushButton_[buttonID][stickNo]);
    } else {
        return false;
    }
}
bool GetInput::JoystickPushButton(int stickNo, std::vector<int> buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (const auto &id : buttonID) {
            if (joystickPushButton_[id][stickNo]) {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}
bool GetInput::JoystickPrePushButton(int stickNo, std::vector<int> buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (const auto &id : buttonID) {
            if (joystickPrePushButton_[id][stickNo]) {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}
bool GetInput::JoystickTriggerButton(int stickNo, std::vector<int> buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (const auto &id : buttonID) {
            if (joystickPushButton_[id][stickNo] && !joystickPrePushButton_[id][stickNo]) {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}
bool GetInput::JoystickReleaseButton(int stickNo, std::vector<int> buttonID) {
    if (0 <= stickNo && stickNo <= (joysticksNum_ - 1)) {
        for (const auto &id : buttonID) {
            if (!joystickPushButton_[id][stickNo] && joystickPrePushButton_[id][stickNo]) {
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

//--------- 入力の種類の取得 ---------//

bool GetInput::IsInputType(InputType inputType) {
    return nowInputType_ == inputType;
}

bool GetInput::IsInputType(InputType inputType1, InputType inputType2) {
    return nowInputType_ == inputType1 || nowInputType_ == inputType2;
}

InputType GetInput::NowInputType() {
    return nowInputType_;
}
