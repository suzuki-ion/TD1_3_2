#pragma once
#include <Novice.h>

class Proccess {
public:
    Proccess(const Proccess &) = delete;
    Proccess &operator=(const Proccess &) = delete;
    Proccess(Proccess &&) = delete;
    Proccess &operator=(Proccess &&) = delete;
    
    static Proccess *GetInstance() {
        static Proccess instance;
        return &instance;
    }

    void Initialize();
    void Finalize();

    void Update();
    void Draw();

    void SetEnd() { isEnd_ = true; }
    bool IsEnd() { return isEnd_; }

private:
    Proccess() = default;
    ~Proccess() = default;

    bool isEnd_ = false;
};