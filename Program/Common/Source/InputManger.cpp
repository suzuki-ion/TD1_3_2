#include <Common/InputManger.h>

bool InputManager::IsPush(InputConfigType inputConfigType) {
    auto key = inputConfig_->GetKey(inputConfigType);
    auto controller = inputConfig_->GetController(inputConfigType);
    if (key.inputType == KEYBOARD) {
        return getInput_->Keys(key.key);
    } else if (key.inputType == MOUSE) {
        return getInput_->MousePushButton(key.key);
    } else if (key.inputType == JOYSTICK) {
        return getInput_->JoystickPushButton(0, controller.key);
    }
    return false;
}

bool InputManager::IsPrePush(InputConfigType inputConfigType) {
    auto key = inputConfig_->GetKey(inputConfigType);
    auto controller = inputConfig_->GetController(inputConfigType);
    if (key.inputType == KEYBOARD) {
        return getInput_->PreKeys(key.key);
    } else if (key.inputType == MOUSE) {
        return getInput_->MousePrePushButton(key.key);
    } else if (key.inputType == JOYSTICK) {
        return getInput_->JoystickPrePushButton(0, controller.key);
    }
    return false;
}

bool InputManager::IsTrigger(InputConfigType inputConfigType) {
    auto key = inputConfig_->GetKey(inputConfigType);
    auto controller = inputConfig_->GetController(inputConfigType);
    if (key.inputType == KEYBOARD) {
        return getInput_->TriggerKeys(key.key);
    } else if (key.inputType == MOUSE) {
        return getInput_->MouseTriggerButton(key.key);
    } else if (key.inputType == JOYSTICK) {
        return getInput_->JoystickTriggerButton(0, controller.key);
    }
    return false;
}

bool InputManager::IsRelease(InputConfigType inputConfigType) {
    auto key = inputConfig_->GetKey(inputConfigType);
    auto controller = inputConfig_->GetController(inputConfigType);
    if (key.inputType == KEYBOARD) {
        return getInput_->ReleaseKeys(key.key);
    } else if (key.inputType == MOUSE) {
        return getInput_->MouseReleaseButton(key.key);
    } else if (key.inputType == JOYSTICK) {
        return getInput_->JoystickReleaseButton(0, controller.key);
    }
    return false;
}

bool InputIsPush(InputConfigType inputConfigType) {
    return InputManager::GetInstance()->IsPush(inputConfigType);
}

bool InputIsPrePush(InputConfigType inputConfigType) {
    return InputManager::GetInstance()->IsPrePush(inputConfigType);
}

bool InputIsTrigger(InputConfigType inputConfigType) {
    return InputManager::GetInstance()->IsTrigger(inputConfigType);
}

bool InputIsRelease(InputConfigType inputConfigType) {
    return InputManager::GetInstance()->IsRelease(inputConfigType);
}