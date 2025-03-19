#include <Novice.h>
#include <Common/GraphHandle.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

void GraphHandle::Load(int textureID, const char *fileName) {
    // 画像読み込み用
    static unsigned char *img = nullptr;
    
    // 読み込む前に情報を全てバックアップ
    TextureData preTexture = textures_[textureID];
    // IDが -1 でなければ一度Unloadをする
    if (textures_[textureID].id != -1) {
        Unload(textureID);
    }

    img = stbi_load(
        fileName,
        &textures_[textureID].width,
        &textures_[textureID].height,
        &textures_[textureID].channel,
        0
    );
    
    // 画像が見つかればそのまま読み込む
    if (img != nullptr) {
        textures_[textureID].id = Novice::LoadTexture(fileName);
    
    } else {
        // 見つからなければ前までの情報に戻してデバッグ用テクスチャを読み込む
        textures_[textureID] = preTexture;
        textures_[textureID].id = Novice::LoadTexture("white1x1.png");
    }

    stbi_image_free(img);
}

void GraphHandle::Unload(int textureID) {
    Novice::UnloadTexture(textures_[textureID].id);
    textures_[textureID].id = -1;
    textures_[textureID].width = 1;
    textures_[textureID].height = 1;
    textures_[textureID].channel = 0;
}

void GraphHandle::Load() {
    // デバッグ用
    Load(TX_WHITE1X1, "white1x1.png");

    /// 
    /// ↓ここから画像読み込み
    /// 
    
    Load(TX_SELECTELLLIPSE,     "./Resources/Images/Title/SelectEllipse.png");
    Load(TX_SELECTVIEW,         "./Resources/Images/SelectView.png");
    Load(TX_SELECTVIEWSC,       "./Resources/Images/SelectViewSc.png");

    Load(TX_TITLEROTATE,        "./Resources/Images/Title/Rotate.png");
    Load(TX_TITLEBLUE,          "./Resources/Images/Title/BlueLayer.png");
    Load(TX_TITLERED,           "./Resources/Images/Title/RedLayer.png");
    Load(TX_TITLEBOX,           "./Resources/Images/Title/TitleBox.png");
    
    Load(TX_TILEMAP_NORMAL,     "./Resources/Images/Blocks/tilemap_normal.png");
    Load(TX_TILEMAP_BRAILLE,    "./Resources/Images/Blocks/tilemap_braille.png");
    Load(TX_TILEMAP_ON,         "./Resources/Images/Blocks/tilemap_on.png");
    Load(TX_TILEMAP_OFF,        "./Resources/Images/Blocks/tilemap_off.png");
    Load(TX_BLOCK_GOAL,         "./Resources/Images/Blocks/goal.png");
    Load(TX_BLOCK_SWITCH,       "./Resources/Images/Blocks/switch.png");
    Load(TX_GOAL_LOCK,          "./Resources/Images/Blocks/goal_lock.png");

    Load(TX_KEY,                "./Resources/Images/Entity/key.png");
    
    Load(TX_PLAYER,             "./Resources/Images/Player/player.png");
    Load(TX_SCARED_PLAYER,      "./Resources/Images/Player/scared_player.png");
    Load(TX_DEATH_PLAYER,       "./Resources/Images/Player/death_player.png");
    Load(TX_CLEAR_PLAYER,       "./Resources/Images/Player/clear_player.png");

    Load(TX_COMICSIGN_ZZZ,      "./Resources/Images/UI/comic_sign_zzz.png");
    Load(TX_CHANGEMODE,         "./Resources/Images/UI/change_mode_ui.png");

    Load(TX_PLAY_UI,            "./Resources/Images/UI/play_ui.png");
    Load(TX_SPIN_UI,            "./Resources/Images/UI/spin_ui.png");
    Load(TX_SPIN_UI_XBOX,       "./Resources/Images/UI/spin_ui_xbox.png");
    Load(TX_MOVE_UI,            "./Resources/Images/UI/move_ui.png");
    Load(TX_CLICK_UI,           "./Resources/Images/UI/click_ui.png");
    Load(TX_INPUT_PAZZLE_UI,    "./Resources/Images/UI/input_pazzle.png");
    Load(TX_TUTORIAL_UI,        "./Resources/Images/UI/tutorial.png");
    Load(TX_TUTORIAL2_UI,       "./Resources/Images/UI/tutorial2.png");
    Load(TX_JUMP_UI,            "./Resources/Images/UI/jump_ui.png");
    Load(TX_PUZZLE_UI,          "./Resources/Images/UI/puzzle.png");
    Load(TX_SWITCH_UI,          "./Resources/Images/UI/switch_ui.png");
    Load(TX_SELECT_SECTION_CURSOR, "./Resources/Images/UI/select_section_cursor.png");
    Load(TX_FONT128X128,        "./Resources/Images/Fonts/font128x128.png");

    Load(TX_STAGE_CLEAR_LOGO,   "./Resources/Images/UI/stage_clear_logo.png");

    /// 
    /// ↑ここまで画像読み込み
    /// 
}
