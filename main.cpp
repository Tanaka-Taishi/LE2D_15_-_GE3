#include"Input.h"
#include"WinApp.h"
#include"DirectXCommon.h"

#include"SpriteCommon.h"
#include"Sprite.h"

#include"ImGuiManager.h"

#include<vector>

#include"TextureManager.h"


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

    ImGuiManager* imgui = ImGuiManager::Create();
    ImGuiManager::Initialize(winApp_->GetHwnd(), dxCommon_);

    SpriteCommon* common = new SpriteCommon();
    common->Initialize(dxCommon_);


    TextureManager::GetInstance()->Initialize(dxCommon_);
    TextureManager::GetInstance()->LoadTexture(L"Resources/mario.jpg");


    std::vector<Sprite*> sprite;
    for (int i = 0; i < 5;i++) {
        Sprite* temp = new Sprite();
        temp->Initialize(common, L"Resources/mario.jpg");
        temp->SetPosition({ (float)i * 120,0 });
        sprite.push_back(temp);
    }

    // ゲームループ
    while (true) {
        if (winApp_->Update() == true) {
            break;
        }
        ImGuiManager::NewFrame();
        imgui->ShowDemo();

        input_->Update();

       // DirectX::XMFLOAT2 pos = sprite->GetPosition();
       // pos.x += 0.01;
       // sprite->SetPosition(pos);
       //
       // float rot = sprite->GetRotation();
       // rot += 0.005f;
       // sprite->SetRotation(rot);
       //
       //
       // DirectX::XMFLOAT4 color = sprite->GetColor();
       // color.x -= 0.01f;
       // if (color.x < 0) {
       //     color.x = 1.0f;
       // }
       // sprite->SetColor(color);
       //
       // DirectX::XMFLOAT2 size = sprite->GetSize();
       // size.y += 0.01f;
       // sprite->SetSize(size);


        for (int i = 0; i < 5; i++) {
            sprite[i]->Update();
        }
        ImGuiManager::CreateCommand();
        dxCommon_->PreDraw();
        


        for (int i = 0; i < 5; i++) {
            sprite[i]->Draw();
        }
        ImGuiManager::CommandeExcute(dxCommon_->GetCommandList());
        // ４．描画コマンドここまで
        dxCommon_->PostDraw();
    }

    for (int i = 0; i < 5; i++) {
        delete sprite[i];
    }
    TextureManager::GetInstance()->Finalize();

    delete common;
    delete imgui;

    delete input_;

    delete dxCommon_;

    winApp_->Finalize();
    delete winApp_;

    return 0;
}