#include <json.hpp>
#include "Structures.h"

using Json = nlohmann::json;

// セーブデータの構造体
struct SaveData {
    // ステージのクリアフラグ
    bool isClear = false;
    // ステージのミッションクリアフラグ
    bool isMission1Clear = false;
    bool isMission2Clear = false;
    bool isMission3Clear = false;
};

/// @brief セーブデータ管理クラス
class SaveDataManager final {
public:
    SaveDataManager(const SaveDataManager &) = delete;
    SaveDataManager &operator=(const SaveDataManager &) = delete;
    SaveDataManager(SaveDataManager &&) = delete;
    SaveDataManager &operator=(SaveDataManager &&) = delete;

    /// @brief セーブデータ管理クラスのインスタンス取得
    /// @return セーブデータ管理クラスのインスタンス
    static SaveDataManager *GetInstance() {
        static SaveDataManager instance;
        return &instance;
    }

    /// @brief 初期化処理
    void Initialize();

    /// @brief 終了処理
    void Finalize();

    /// @brief セーブデータの保存
    /// @param stageUUID ステージのUUID
    /// @param isClear ステージのクリアフラグ
    /// @param isMission1Clear ステージのミッション1クリアフラグ
    /// @param isMission2Clear ステージのミッション2クリアフラグ
    /// @param isMission3Clear ステージのミッション3クリアフラグ
    void Save(
        std::string stageUUID,
        bool isClear,
        bool isMission1Clear,
        bool isMission2Clear,
        bool isMission3Clear
    );

    /// @brief セーブデータの読み込み
    /// @param stageUUID ステージのUUID
    SaveData Load(std::string stageUUID);

private:
    SaveDataManager() = default;
    ~SaveDataManager() = default;

    Json saveData_;
};