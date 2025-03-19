#include <cassert>
#include <Common/InputConfig.h>

void InputConfig::SetConfig(InputConfigType inputConfigType, InputType inputType, int key) {
    if ((inputConfigType < 0) || (inputConfigType >= CONFIG_MAX) || (inputType == INPUT_TYPE_NONE)) {
        assert(false);
        return;
    }
    
    if ((inputType == KEYBOARD) ||
        (inputType == MOUSE)) {
        keyConfig_[inputConfigType].inputType = inputType;
        keyConfig_[inputConfigType].key = key;

    } else if (inputType == JOYSTICK) {
        contollerConfig_[inputConfigType].inputType = inputType;
        contollerConfig_[inputConfigType].key = key;
    }
}

InputConfigData InputConfig::GetKey(InputConfigType inputConfigType) const {
    if ((inputConfigType < 0) || (inputConfigType >= CONFIG_MAX)) {
        assert(false);
        return { INPUT_TYPE_NONE, 0 };
    }

    return keyConfig_[inputConfigType];
}

InputConfigData InputConfig::GetController(InputConfigType inputConfigType) const {
    if ((inputConfigType < 0) || (inputConfigType >= CONFIG_MAX)) {
        assert(false);
        return { INPUT_TYPE_NONE, 0 };
    }

    return contollerConfig_[inputConfigType];
}