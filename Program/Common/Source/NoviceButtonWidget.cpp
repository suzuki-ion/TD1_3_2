#include <Common/NoviceButtonWidget.h>
#include <Common/CommonFunctions.h>
#include <Common/CustomNovice.h>
#include <Common/GraphHandle.h>
#include <Common/SoundHandle.h>
#include <Common/GetInput.h>

namespace {

// ボタン無選択の状態
const int kNullButtonNum = -2;
// GetInputのインスタンス
auto sGetInput = GetInput::GetInstance();

} // namespace

bool NoviceButtonWidget::IsPreButtonSelect() {
    // キーでの選択
    if (sGetInput->TriggerKeys(preButtonSelectKeys_)) {
        return true;
    }
    // コントローラーでの選択
    if (sGetInput->JoystickTriggerButton(0, preButtonSelectControllerButtons_)) {
        return true;
    }
    // ジョイスティックでの選択
    if (useJoystick_ != SelectUseJoystick::JOYSTICK_NONE) {
        if (useJoystick_ == SelectUseJoystick::JOYSTICK_LEFT_X) {
            if (sGetInput->JoystickAnalogLeftX(0) <= preUseJoystickValue_ && sGetInput->JoystickAnalogLeftPreX(0) > preUseJoystickValue_) {
                return true;
            }
        } else if (useJoystick_ == SelectUseJoystick::JOYSTICK_LEFT_Y) {
            if (sGetInput->JoystickAnalogLeftY(0) <= preUseJoystickValue_ && sGetInput->JoystickAnalogLeftPreY(0) > preUseJoystickValue_) {
                return true;
            }
        } else if (useJoystick_ == SelectUseJoystick::JOYSTICK_RIGHT_X) {
            if (sGetInput->JoystickAnalogRightX(0) <= preUseJoystickValue_ && sGetInput->JoystickAnalogRightPreX(0) > preUseJoystickValue_) {
                return true;
            }
        } else if (useJoystick_ == SelectUseJoystick::JOYSTICK_RIGHT_Y) {
            if (sGetInput->JoystickAnalogRightY(0) <= preUseJoystickValue_ && sGetInput->JoystickAnalogRightPreY(0) > preUseJoystickValue_) {
                return true;
            }
        }
    }
    return false;
}

bool NoviceButtonWidget::IsNextButtonSelect() {
    // キーでの選択
    if (sGetInput->TriggerKeys(nextButtonSelectKeys_)) {
        return true;
    }
    // コントローラーでの選択
    if (sGetInput->JoystickTriggerButton(0, nextButtonSelectControllerButtons_)) {
        return true;
    }
    // ジョイスティックでの選択
    if (useJoystick_ != SelectUseJoystick::JOYSTICK_NONE) {
        if (useJoystick_ == SelectUseJoystick::JOYSTICK_LEFT_X) {
            if (sGetInput->JoystickAnalogLeftX(0) >= nextUseJoystickValue_ && sGetInput->JoystickAnalogLeftPreX(0) < nextUseJoystickValue_) {
                return true;
            }
        } else if (useJoystick_ == SelectUseJoystick::JOYSTICK_LEFT_Y) {
            if (sGetInput->JoystickAnalogLeftY(0) >= nextUseJoystickValue_ && sGetInput->JoystickAnalogLeftPreY(0) < nextUseJoystickValue_) {
                return true;
            }
        } else if (useJoystick_ == SelectUseJoystick::JOYSTICK_RIGHT_X) {
            if (sGetInput->JoystickAnalogRightX(0) >= nextUseJoystickValue_ && sGetInput->JoystickAnalogRightPreX(0) < nextUseJoystickValue_) {
                return true;
            }
        } else if (useJoystick_ == SelectUseJoystick::JOYSTICK_RIGHT_Y) {
            if (sGetInput->JoystickAnalogRightY(0) >= nextUseJoystickValue_ && sGetInput->JoystickAnalogRightPreY(0) < nextUseJoystickValue_) {
                return true;
            }
        }
    }
    return false;
}

bool NoviceButtonWidget::IsPushButton() {
    // キーでの選択
    if (sGetInput->TriggerKeys(pushButtonKeys_)) {
        return true;
    }
    // コントローラーでの選択
    if (sGetInput->JoystickTriggerButton(0, pushButtonControllerButtons_)) {
        return true;
    }
    return false;
}

NoviceButtonWidget::NoviceButtonWidget() {

}

void NoviceButtonWidget::SetButtonOption2Common(bool isSelectLoop) {
    isSelectLoop_ = isSelectLoop;
}

void NoviceButtonWidget::SetButtonOption2Keys(std::vector<int> preButtonSelectKeys, std::vector<int> nextButtonSelectKeys,
    std::vector<int> pushButtonKeys, bool isSelectButton2Mouse) {
    preButtonSelectKeys_ = preButtonSelectKeys;
    nextButtonSelectKeys_ = nextButtonSelectKeys;
    pushButtonKeys_ = pushButtonKeys;
    isSelectButton2Mouse_ = isSelectButton2Mouse;
}

void NoviceButtonWidget::SetButtonOption2Controller(std::vector<int> preButtonSelectControllerButtons, std::vector<int> nextButtonSelectControllerButtons,
    std::vector<int> pushButtonControllerButtons, SelectUseJoystick useJoystick, int preUseJoystickValue, int nextUseJoystickValue) {
    preButtonSelectControllerButtons_ = preButtonSelectControllerButtons;
    nextButtonSelectControllerButtons_ = nextButtonSelectControllerButtons;
    pushButtonControllerButtons_ = pushButtonControllerButtons;
    useJoystick_ = useJoystick;
    preUseJoystickValue_ = preUseJoystickValue;
    nextUseJoystickValue_ = nextUseJoystickValue;
}

void NoviceButtonWidget::AddButton(NoviceButton addButton) {
    buttons_.push_back(addButton);
}

NoviceButton *NoviceButtonWidget::SearchButton(int id) {
    for (int i = 0; i < static_cast<int>(buttons_.size()); i++) {
        if (buttons_[i].id == id) {
            // 見つかったらそのボタンへのポインタを返す
            preSearchButton_ = &buttons_[i];
            return &buttons_[i];
        }
    }

    // ここまで通ったら見つからなかったということなので nullptr を返す
    preSearchButton_ = nullptr;
    return nullptr;
}

void NoviceButtonWidget::ClearButton() {
    buttons_.clear();
}

int NoviceButtonWidget::GetPushedButtonID() const {
    // ボタンが押されている場合のみIDを返す
    if (pushedButton_ != -1) {
        return buttons_[pushedButton_].id;

    } else {
        // ボタンが押されていなければ -1 を返す
        return -1;
    }
}

NoviceButton *NoviceButtonWidget::GetPushedButton() {
    if (pushedButton_ == kNullButtonNum) {
        return nullptr;

    } else {
        return &buttons_[pushedButton_];
    }
}

int NoviceButtonWidget::GetSelectButtonID() const {
    // ボタンが選択されている場合のみIDを返す
    if (selectButton_ != -1) {
        return buttons_[selectButton_].id;

    } else {
        // ボタンが選択されていなければ -1 を返す
        return -1;
    }
}

NoviceButton *NoviceButtonWidget::GetSelectButton() {
    if (selectButton_ == kNullButtonNum) {
        return nullptr;

    } else {
        return &buttons_[selectButton_];
    }
}

void NoviceButtonWidget::ResetSelect(int selectButton) {
    selectButton_ = selectButton;
    pushedButton_ = -1;
}

void NoviceButtonWidget::Update() {
    // ボタンとマウスの当たり判定用の仮変数
    static bool isButton2MouseHit = false;

    // ボタンが存在しない場合は何もしない
    if (buttons_.size() <= 0) {
        return;
    }

    // 決定したボタンの値を -1 でリセット
    pushedButton_ = -1;

    //==================================================
    // ↓ ボタン選択 ↓
    //==================================================

    // ひとつ前のボタンを選択
    if (IsPreButtonSelect()) {
        // もし選択してるボタンが無選択の状態なら最後尾のボタンを選択
        if (selectButton_ == kNullButtonNum) {
            selectButton_ = static_cast<int>(buttons_.size()) - 1;

        } else {
            selectButton_--;

            // ボタンが -1 のとき、ボタンループのフラグが立ってたらループ
            if (selectButton_ == -1) {
                if (isSelectLoop_) {
                    selectButton_ = static_cast<int>(buttons_.size()) - 1;

                } else {
                    // フラグが立ってなければ 0 に固定
                    selectButton_ = 0;
                }
            }
        }
        if (buttons_[selectButton_].soundHandle2Select != -1) {
            SOUND_PLAY(buttons_[selectButton_].soundHandle2Select);
        }
    }

    // ひとつ後のボタンを選択
    if (IsNextButtonSelect()) {
        // もし選択してるボタンが無選択の状態なら最初のボタンを選択
        if (selectButton_ == kNullButtonNum) {
            selectButton_ = 0;

        } else {
            selectButton_++;

            // ボタンが size 以上のとき、ボタンループのフラグが立ってたらループ
            if (selectButton_ >= static_cast<int>(buttons_.size())) {
                if (isSelectLoop_) {
                    selectButton_ = 0;

                } else {
                    // フラグが立ってなければ最後尾のボタンに固定
                    selectButton_ = static_cast<int>(buttons_.size()) - 1;
                }
            }
        }
        if (buttons_[selectButton_].soundHandle2Select != -1) {
            SOUND_PLAY(buttons_[selectButton_].soundHandle2Select);
        }
    }

    // ボタンが選択されていればボタンの決定をできるようにする
    if (selectButton_ != kNullButtonNum) {
        if (IsPushButton()) {
            // 決定したボタンの値を更新
            pushedButton_ = selectButton_;
            if (buttons_[pushedButton_].soundHandle2Pushed != -1) {
                SOUND_PLAY(buttons_[pushedButton_].soundHandle2Pushed);
            }
        }
    }

    // ボタン個別のキーの処理
    for (int i = 0; i < static_cast<int>(buttons_.size()); i++) {
        // 個別の選択用キーが押されていたらそのボタンを選択
        if (sGetInput->Keys(buttons_[i].selectKeys)) {
            selectButton_ = i;
            if (buttons_[selectButton_].soundHandle2Select != -1) {
                SOUND_PLAY(buttons_[selectButton_].soundHandle2Select);
            }
        }
        // 個別の決定用キーが押されていたらそのボタンを決定
        if (sGetInput->Keys(buttons_[i].pushedKeys)) {
            pushedButton_ = i;
            if (buttons_[pushedButton_].soundHandle2Pushed != -1) {
                SOUND_PLAY(buttons_[pushedButton_].soundHandle2Pushed);
            }
        }
    }

    //==================================================
    // ↓ マウス操作 ↓
    //==================================================

    // マウスでの操作もできるよう設定されてたらボタンとマウスの当たり判定を行う
    if (isSelectButton2Mouse_) {
        // 前までのマウスの位置を保存
        preMousePos_ = mousePos_;
        // マウスの位置取得
        mousePos_ = { sGetInput->MouseX(), sGetInput->MouseY() };

        // 前までのマウスの位置と比較して、マウスが動いていたらボタンとの当たり判定を行う
        if ((preMousePos_.x != mousePos_.x) || (preMousePos_.y != mousePos_.y)) {
            for (int i = 0; i < static_cast<int>(buttons_.size()); i++) {
                isButton2MouseHit = IsPos2RectHit(
                    static_cast<float>(mousePos_.x),
                    static_cast<float>(mousePos_.y),
                    buttons_[i].pos.x,
                    buttons_[i].pos.y,
                    buttons_[i].width,
                    buttons_[i].height
                );

                if (isButton2MouseHit) {
                    // 当たってたら選択してるボタンを i に設定
                    selectButton_ = i;
                    if (buttons_[selectButton_].soundHandle2Select != -1) {
                        // 前までの座標で当たっていなかった場合、選択してるボタンの音を再生
                        isButton2MouseHit = IsPos2RectHit(
                            static_cast<float>(preMousePos_.x),
                            static_cast<float>(preMousePos_.y),
                            buttons_[selectButton_].pos.x,
                            buttons_[selectButton_].pos.y,
                            buttons_[selectButton_].width,
                            buttons_[selectButton_].height
                        );
                        if (!isButton2MouseHit) {
                            SOUND_PLAY(buttons_[selectButton_].soundHandle2Select);
                        }
                    }
                    // これ以上forを続ける意味はないので終了
                    break;

                } else {
                    // 当たっていなかった場合、前までの座標で当たり判定を行う
                    isButton2MouseHit = IsPos2RectHit(
                        static_cast<float>(preMousePos_.x),
                        static_cast<float>(preMousePos_.y),
                        buttons_[i].pos.x,
                        buttons_[i].pos.y,
                        buttons_[i].width,
                        buttons_[i].height
                    );

                    if (isButton2MouseHit) {
                        // 前までの座標で当たってたら選択してるボタンを無選択に設定
                        selectButton_ = kNullButtonNum;
                    }
                }
            }
        }

        // クリックしたらクリックした座標のボタンを決定
        if (sGetInput->MousePushButton(DIC_LEFT)) {
            // クリックした座標のボタンを探す
            for (int i = 0; i < static_cast<int>(buttons_.size()); i++) {
                isButton2MouseHit = IsPos2RectHit(
                    static_cast<float>(mousePos_.x),
                    static_cast<float>(mousePos_.y),
                    buttons_[i].pos.x,
                    buttons_[i].pos.y,
                    buttons_[i].width,
                    buttons_[i].height
                );

                if (isButton2MouseHit) {
                    pushedButton_ = i;
                    if (buttons_[pushedButton_].soundHandle2Pushed != -1) {
                        SOUND_PLAY(buttons_[pushedButton_].soundHandle2Pushed);
                    }
                    // これ以上forを続ける意味はないので終了
                    break;
                }
            }
        }
    }
}

void NoviceButtonWidget::Draw(const Vector2 &shiftPos) {
    // 描画色
    static unsigned int drawColor = WHITE;
    // 描画画像
    static int drawGraphHandle = -1;
    // フォントの描画位置
    static Vector2 fontDrawPos;

    // ボタンの描画
    for (int i = 0; i < static_cast<int>(buttons_.size()); i++) {
        // どの色、どの画像で描画するかを決める
        drawGraphHandle = -1;
        if (i == pushedButton_) {
            drawColor = buttons_[i].color2Pushed;
            // 画像が設定されてなければ他の画像を使いまわす
            if (buttons_[i].graphHandle2Pushed != -1) {
                drawGraphHandle = buttons_[i].graphHandle2Pushed;

            } else if (buttons_[i].graphHandle2Select != -1) {
                drawGraphHandle = buttons_[i].graphHandle2Select;

            } else if (buttons_[i].graphHandle2Usually != -1) {
                drawGraphHandle = buttons_[i].graphHandle2Usually;
            }

        } else if (i == selectButton_) {
            drawColor = buttons_[i].color2Select;
            // 画像が設定されてなければ他の画像を使いまわす
            if (buttons_[i].graphHandle2Select != -1) {
                drawGraphHandle = buttons_[i].graphHandle2Select;

            } else if (buttons_[i].graphHandle2Usually != -1) {
                drawGraphHandle = buttons_[i].graphHandle2Usually;
            }

        } else {
            drawColor = buttons_[i].color2Usually;
            if (buttons_[i].graphHandle2Usually != -1) {
                drawGraphHandle = buttons_[i].graphHandle2Usually;
            }
        }

        // 描画する画像があれば画像を描画
        if (drawGraphHandle != -1) {
            CustomNovice::DrawSprite(
                buttons_[i].pos.x + shiftPos.x,
                buttons_[i].pos.y + shiftPos.y,
                GraphHandle::ID(drawGraphHandle),
                drawColor
            );
        }

        // フォントの画像が設定されていれば文字を描画
        if (buttons_[i].fontGh != -1) {
            // フォントの描画位置を計算
            if (buttons_[i].fontDrawMethod == LEFT) {
                fontDrawPos.x = buttons_[i].pos.x + buttons_[i].fontDrawShift.x;
                fontDrawPos.y = buttons_[i].pos.y + buttons_[i].fontDrawShift.y;

            } else if (buttons_[i].fontDrawMethod == CENTER) {
                fontDrawPos.x = buttons_[i].pos.x + (buttons_[i].width / 2.0f);
                fontDrawPos.y = buttons_[i].pos.y + buttons_[i].fontDrawShift.y;


            } else if (buttons_[i].fontDrawMethod == RIGHT) {
                fontDrawPos.x = buttons_[i].pos.x + (buttons_[i].width - buttons_[i].fontDrawShift.x);
                fontDrawPos.y = buttons_[i].pos.y + buttons_[i].fontDrawShift.y;
            }

            CustomNovice::DrawFont(
                fontDrawPos.x,
                fontDrawPos.y,
                buttons_[i].fontWidth,
                buttons_[i].fontHeight,
                buttons_[i].fontDrawWidth,
                buttons_[i].fontDrawHeight,
                buttons_[i].fontMargin.x,
                buttons_[i].fontMargin.y,
                GraphHandle::ID(buttons_[i].fontGh),
                buttons_[i].str.c_str(),
                static_cast<DrawMethod>(buttons_[i].fontDrawMethod),
                drawColor
            );
        }
    }
}