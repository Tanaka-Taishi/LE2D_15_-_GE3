#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"

#include"SpriteCommon.h"
#include"Sprite.h"


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    Input* input_ = nullptr;
    WinApp* winApp_ = nullptr;
    DirectXCommon* dxCommon_ = nullptr;

    // WindowsAPI初期化処理
    winApp_ = new WinApp();
    winApp_->Initialize();

    // DirectX初期化処理
    dxCommon_ = new DirectXCommon();
    dxCommon_->Initialize(winApp_);

    input_ = new Input();
    input_->Initialize(winApp_);

    SpriteCommon* common = new SpriteCommon();
    common->Initialize(dxCommon_);

    Sprite* sprite = new Sprite();
    sprite->Initialize(dxCommon_, common);

    // ゲームループ
    while (true) {
        if (winApp_->Update() == true) {
            break;
        }

        input_->Update();

        dxCommon_->PreDraw();
        
        sprite->Draw();
        // ４．描画コマンドここまで
        dxCommon_->PostDraw();
    }

    delete sprite;
    delete common;
    delete input_;

    delete dxCommon_;

    winApp_->Finalize();
    delete winApp_;

    return 0;
}