#pragma once

// ここに使うテクスチャのIDを記述。頭には必ず "TX_" を付ける
enum TexturesID {
    // デバッグ用テクスチャ
    TX_WHITE1X1,

    /// 
    /// ↓ここからID記述
    /// 
    
    TX_SELECTELLLIPSE,
    TX_SELECTVIEW,
    TX_SELECTVIEWSC,

    TX_TITLEROTATE,
    TX_TITLERED,
    TX_TITLEBLUE,
    TX_TITLEBOX,

    TX_TILEMAP_NORMAL,
    TX_TILEMAP_BRAILLE,
    TX_TILEMAP_ON,
    TX_TILEMAP_OFF,
    TX_BLOCK_GOAL,
    TX_BLOCK_SWITCH,
    TX_GOAL_LOCK,

    TX_KEY,
    
    TX_PLAYER,
    TX_SCARED_PLAYER,
    TX_DEATH_PLAYER,
    TX_CLEAR_PLAYER,

    TX_COMICSIGN_ZZZ,
    TX_CHANGEMODE,
    TX_PLAY_UI,

    TX_MOVE_UI,
    TX_CLICK_UI,
    TX_INPUT_PAZZLE_UI,
    TX_TUTORIAL_UI,
    TX_TUTORIAL2_UI,
    TX_JUMP_UI,
    TX_SPIN_UI,
    TX_SPIN_UI_XBOX,
    TX_PUZZLE_UI,
    TX_SWITCH_UI,
    TX_SELECT_SECTION_CURSOR,
    TX_FONT128X128,

    TX_STAGE_CLEAR_LOGO,

    /// 
    /// ↑ここまでID記述
    /// 

    // テクスチャの総数
    TEXTURES
};

// テクスチャの情報用構造体
struct TextureData {
    // Noviceでの描画用のID
    int id = -1;
    // 横幅
    int width = 1;
    // 縦幅
    int height = 1;
    // チャンネル数
    int channel = 0;
};

// グラフハンドル用のクラス
class GraphHandle final {
public:
    GraphHandle(const GraphHandle &) = delete;
    GraphHandle &operator=(const GraphHandle &) = delete;
    GraphHandle(GraphHandle &&) = delete;
    GraphHandle &operator=(GraphHandle &&) = delete;

    /// @brief グラフハンドルのインスタンス取得
    /// @return グラフハンドルのインスタンス
    static GraphHandle *GetInstance() {
        static GraphHandle instance;
        return &instance;
    }

    /// @brief テクスチャの読み込み用関数。2回目以降の呼び出しでは再読み込みする
    void Load();

    /// @brief 指定のテクスチャのデータを取得
    /// @param textureID テクスチャのID
    /// @return テクスチャのデータ
    TextureData Data(int textureID) { return textures_[textureID]; };

    /// @brief 指定のテクスチャのID取得
    /// @param textureID テクスチャのID
    /// @return テクスチャのID
    int ID(int textureID) { return textures_[textureID].id; };

    /// @brief 指定のテクスチャの横幅取得
    /// @param textureID テクスチャのID
    /// @return テクスチャの横幅
    int Width(int textureID) { return textures_[textureID].width; };

    /// @brief 指定のテクスチャの縦幅取得
    /// @param textureID テクスチャのID
    /// @return テクスチャの縦幅
    int Height(int textureID) { return textures_[textureID].height; };

    /// @brief 指定のテクスチャのチャンネル数取得
    /// @param textureID テクスチャのID
    /// @return テクスチャのチャンネル数
    int Channel(int textureID) { return textures_[textureID].channel; };

private:
    GraphHandle() = default;
    ~GraphHandle() = default;

    // テクスチャのデータ
    TextureData textures_[TEXTURES];

    /// @brief テクスチャの読み込み
    /// @param textureID テクスチャのID
    /// @param fileName ファイル名
    void Load(int textureID, const char *fileName);

    /// @brief テクスチャの解放
    /// @param textureID テクスチャのID
    void Unload(int textureID);
};

/// @brief 指定のテクスチャのデータを取得
/// @param textureID テクスチャのID
/// @return テクスチャのデータ
TextureData GraphHandleData(int textureID) {
    return GraphHandle::GetInstance()->Data(textureID);
}

/// @brief 指定のテクスチャのID取得
/// @param textureID テクスチャのID
/// @return テクスチャのID
int GraphHandleID(int textureID) {
    return GraphHandle::GetInstance()->ID(textureID);
}

/// @brief 指定のテクスチャの横幅取得
/// @param textureID テクスチャのID
/// @return テクスチャの横幅
int GraphHandleWidth(int textureID) {
    return GraphHandle::GetInstance()->Width(textureID);
}

/// @brief 指定のテクスチャの縦幅取得
/// @param textureID テクスチャのID
/// @return テクスチャの縦幅
int GraphHandleHeight(int textureID) {
    return GraphHandle::GetInstance()->Height(textureID);
}

/// @brief 指定のテクスチャのチャンネル数取得
/// @param textureID テクスチャのID
/// @return テクスチャのチャンネル数
int GraphHandleChannel(int textureID) {
    return GraphHandle::GetInstance()->Channel(textureID);
}