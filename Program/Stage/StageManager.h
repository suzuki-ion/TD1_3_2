#pragma once
#include <vector>
#include <string>
#include <memory>
#include <Common/Math/Vector2.h>
#include <Common/Math/Matrix3x3.h>
#include <Common/SaveData.h>
#include <Common/Camera.h>
#include "Stage.h"

const int kMapChipSize = 32;

enum StageLayer {
    LAYER_BACK,
    LAYER_FRONT,
    LAYER_SWITCH_OFF,
    LAYER_SWITCH_ON,
    LAYER_RASTER,

    // ステージレイヤーの総数
    LAYERS
};

enum RotateDirection {
    ROTATE_RIGHT,
    ROTATE_LEFT,
};

struct HitBlock {
    int x = 0;
    int y = 0;
    int blockID = 0;
};

// 区間のデータ
struct Section {
    // 区間の左下座標
    Vector2Int leftBottom;
    // 区間の大きさ
    int size = 0;
};

// 個々のステージデータ
struct StageData {
    // ステージデータ
    std::unique_ptr<Stage> stage[LAYERS];
    // 区間のデータ
    std::vector<Section> section;
    // ステージの名前
    std::string name = "\0";
    // ステージ固有のID
    std::string stageUUID;

    // プレイヤーの初期位置
    Vector2 playerPos;
    // 鍵の初期位置
    Vector2 keyPos;

    // ステージの番号
    int stageID = 0;
    // ステージの大きさ
    int stageSize = 16;
    // プレイヤーの初期向き
    int playerDirection = 1;
    // ミッション1の回転回数
    int mission1RotateStep = 9;
    // ミッション2の回転回数
    int mission2RotateStep = 6;
    // ミッション3の回転回数
    int mission3RotateStep = 3;

    // 鍵の有無 
    bool isKeyExist = false;
    // ステージクリアフラグ
    bool isClear = false;
    // ステージミッションクリアフラグ
    bool isMission1Clear = false;
    bool isMission2Clear = false;
    bool isMission3Clear = false;
};

// ステージの管理クラス
class StageManager {
public:
    /// @brief コンストラクタ
    StageManager() = default;
    /// @brief コンストラクタ(ファイル読み込み)
    /// @param stageFileName 読み込むステージのファイル名
    StageManager(const std::vector<std::string> &stageFileName);
    /// @brief コンストラクタ(ステージデータ読み込み)
    /// @param stageData ステージデータ
    StageManager(const std::vector<StageData> &stageData) {
        stageData_ = stageData;
    }

    void Update(Camera &camera);
    void Draw(Camera &camera);

    void SetIsPuzzleMode(bool isPuzzleMode) { isPuzzleMode_ = isPuzzleMode; }
    void SetStageData(const std::vector<StageData> &stageData) { stageData_ = stageData; }
    void SetCurrentStageID(int currentStageID) { currentStageID_ = currentStageID; }
    
    int GetCurrentStageID() { return currentStageID_; }
    bool GetIsPuzzleMode() { return isPuzzleMode_; }
    StageData &GetStageData() { return stageDataCurrent_; }
    StageData &GetStageData(int index) { return stageData_[index]; }

    /// @brief オブジェクトとの上下の当たり判定
    /// @param pos オブジェクトの左上ワールド座標
    /// @param width オブジェクトの横幅
    /// @return true:当たっている false:当たっていない
    bool IsHitTopBottom(Vector2 pos, float width);
    /// @brief オブジェクトとの左右の当たり判定
    /// @param pos オブジェクトの左上ワールド座標
    /// @param height オブジェクトの縦幅
    /// @return true:当たっている false:当たっていない
    bool IsHitLeftRight(Vector2 pos, float height);
    /// @brief ステージ左回転
    /// @param x 回転範囲の配列左下ワールド座標 X
    /// @param y 回転範囲の配列左下ワールド座標 Y
    /// @param range 回転範囲
    void UpdateRotateLeft(int x = 0, int y = 0, int range = 0);
    /// @brief ステージ右回転
    /// @param x 回転範囲の配列左下ワールド座標 X
    /// @param y 回転範囲の配列左下ワールド座標 Y
    /// @param range 回転範囲
    void UpdateRotateRight(int x = 0, int y = 0, int range = 0);

private:
    SaveDataManager *saveDataManager_ = SaveDataManager::GetInstance();

    Matrix3x3 rotateAnimationMatrix_ = MakeTranslateMatrix({ 0.0f, 0.0f });
    std::vector<StageData> stageData_;
    StageData stageDataCurrent_;
    Vector2 goalPos_ = { -1.0f, -1.0f };
    Vector2 cameraDefaultScale_ = { 1.0f, 1.0f };
    Section *selectSection_ = nullptr;
    Section *preSelectSection_ = nullptr;
    Section *rotateSection_ = nullptr;
    Section rotateSectionAll_ = { { 0, 0 }, 0 };
    float rotateAnimationDegree_ = 0.0f;
    int rotateStepCount_ = 0;
    int rotateAnimationCount_ = 0;
    int rotateAnimationMaxCount_ = 20;
    int rotateDirection_ = ROTATE_LEFT;
    int cameraEaseCount_ = 0;
    int cameraEaseMaxCount_ = 20;
    int currentStageID_ = 0;
    bool isRotateAnimation_ = false;
    bool isPuzzleMode_ = false;
    bool isPuzzleMode_ = false;

    /// @brief ファイルからのステージデータの読み込み
    /// @param fileName ファイル名
    void LoadStageData(const std::string &fileName);

    void UpdateCameraScale(Camera &camera);
    void UpdateSelectSection2Mouse(Camera &camera);
    void UpdateSelectSection2Controller();
    void UpdateRotateSection();
    void UpdateRasterize();

    bool IsHitMouse2Section(ArrayRange section, Camera &camera);
};