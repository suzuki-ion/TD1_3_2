#pragma once
#include "SceneBase.h"

enum Scene {
    TITLE,
    STAGE_SELECT,
    GAME,

    SCENE_MAX
};

class SceneManager final {
public:
    SceneManager(const SceneManager &) = delete;
    SceneManager &operator=(const SceneManager &) = delete;
    SceneManager(SceneManager &&) = delete;
    SceneManager &operator=(SceneManager &&) = delete;

    static SceneManager *GetInstance() {
        static SceneManager instance;
        return &instance;
    }

    void Initialize();
    void Finalize();

    void Update();
    void Draw();
    
    void SetActiveScene(Scene scene) { activeScene_ = scene; }
    void SetEnd() { isEnd_ = true; }
    bool IsEnd() { return isEnd_; }
    SceneBase *GetScene(Scene scene) { return scene_[scene]; }
    Scene GetActiveScene() { return activeScene_; }

private:
    SceneManager() = default;
    ~SceneManager() = default;

    SceneBase *scene_[SCENE_MAX];
    Scene activeScene_ = TITLE;
    bool isEnd_ = false;
};