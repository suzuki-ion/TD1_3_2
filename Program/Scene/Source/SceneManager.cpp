#include <Scene/SceneManager.h>
#include <Scene/Title.h>
#include <Scene/StageSelect.h>
#include <Scene/Game.h>

void SceneManager::Initialize() {
    scene_[TITLE] = new Title();
    scene_[STAGE_SELECT] = new StageSelect();
    scene_[GAME] = new Game();
}

void SceneManager::Finalize() {
    for (int i = 0; i < SCENE_MAX; i++) {
        delete scene_[i];
    }
}

void SceneManager::Update() {
    scene_[activeScene_]->Update();
}

void SceneManager::Draw() {
    scene_[activeScene_]->Draw();
}
