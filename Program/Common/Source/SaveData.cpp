#include <fstream>
#include <Common/SaveData.h>
#include <Common/CommonFunctions.h>

void SaveDataManager::Initialize() {
    // ファイルが存在していればそれを読み込む
    if (IsFileExists("SaveData.json")) {
        std::ifstream ifs("SaveData.json");
        ifs >> saveData_;
        ifs.close();

    } else {
        saveData_ = Json::object();
    }
}

void SaveDataManager::Finalize() {
    std::ofstream saveDataFile("SaveData.json");
    saveDataFile << saveData_.dump(4);
    saveDataFile.close();
}

void SaveDataManager::Save(std::string stageUUID,
    bool isClear, bool isMission1Clear, bool isMission2Clear, bool isMission3Clear) {
    std::ofstream saveDataFile("SaveData.json");
    saveData_[stageUUID]["isClear"] = isClear;
    saveData_[stageUUID]["isMission1Clear"] = isMission1Clear;
    saveData_[stageUUID]["isMission2Clear"] = isMission2Clear;
    saveData_[stageUUID]["isMission3Clear"] = isMission3Clear;
    saveDataFile << saveData_.dump(4);
    saveDataFile.close();
}

SaveData SaveDataManager::Load(std::string stageUUID) {
    SaveData loadData;
    if (saveData_[stageUUID].is_null()) {
        return loadData;
    }
    loadData.isClear = saveData_[stageUUID]["isClear"];
    loadData.isMission1Clear = saveData_[stageUUID]["isMission1Clear"];
    loadData.isMission2Clear = saveData_[stageUUID]["isMission2Clear"];
    loadData.isMission3Clear = saveData_[stageUUID]["isMission3Clear"];
    return loadData;
}