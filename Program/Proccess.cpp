#include "Proccess.h"
#include <Common/GetInput.h>
#include <Common/CustomNovice.h>
#include <Common/GraphHandle.h>
#include <Common/SoundHandle.h>
#include <Scene/SceneManager.h>
#include <Blocks/BlockManager.h>

namespace {

const char kWindowTitle[] = "";
const float kWinWidth = 1920.0f;
const float kWinHeight = 1080.0f;

} // namespace

void Proccess::Initialize() {
    CustomNovice::Initialize(kWindowTitle, kWinWidth, kWinHeight);
    GraphHandle::GetInstance()->Load();
    SoundHandle::GetInstance()->Load();
    BlockManager::GetInstance()->Initialize();
#ifdef _DEBUG
    stageEditor_ = std::make_unique<StageEditor>();
#endif
    SceneManager::GetInstance()->Initialize();
}

void Proccess::Finalize()
{
}

void Proccess::Update() {

}

void Proccess::Draw()
{
}
