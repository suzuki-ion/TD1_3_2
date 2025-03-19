#include "Program/Proccess.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    // 初期化処理
    Proccess::GetInstance()->Initialize();
	
    // メインループ
    while (Novice::ProcessMessage() == 0) {
		Novice::BeginFrame();
		
        // 更新処理
        Proccess::GetInstance()->Update();
        // 描画処理
        Proccess::GetInstance()->Draw();
        
        Novice::EndFrame();

        // ProccessクラスのisEnd_がtrueならループを抜ける
        if (Proccess::GetInstance()->IsEnd()) break;
    }
    
    // 終了処理
    Proccess::GetInstance()->Finalize();
	return 0;
}