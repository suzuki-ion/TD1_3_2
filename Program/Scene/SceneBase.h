#pragma once

class SceneBase {
public:
    SceneBase() = default;
    virtual ~SceneBase() = default;
    virtual void Initialize() {};
    virtual void Finalize() {};
    virtual void Update() {};
    virtual void Draw() {};
};