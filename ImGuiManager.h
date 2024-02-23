#pragma once
#include"DirectXCommon.h"

class ImGuiManager
{
public:
	static void Initialize(HWND hwnd, DirectXCommon* dxCommon);

	static void NewFrame();
	static void CreateCount();
	static void CommandeExcute(ID3D12GraphicsCommandList* commandList);
	static ImGuiManager* Create();

public:
	~ImGuiManager();

public:
	void ShowDem0();
};

