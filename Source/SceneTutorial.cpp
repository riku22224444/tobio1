#include "Graphics/Graphics.h"
#include "SceneTutorial.h"
#include "Input/Input.h"
#include "SceneGame.h"
#include "SceneManager.h"
#include "SceneLoading.h"
#include "Camera.h"

//初期化
void SceneTutorial::Initialize()
{
	//スプライト初期化
	sprite1 = new Sprite("Data/Sprite/Tutorial_1.png");
	sprite2 = new Sprite("Data/Sprite/Tutorial_2.png");
}

//終了化
void SceneTutorial::Finalize()
{
	//スプライト終了化
	if (sprite1 != nullptr)
	{
		delete sprite1;
		sprite1 = nullptr;
	}
}

//更新処理
void SceneTutorial::Update(float elapsedTime)
{
	GamePad& gamePad = Input::Instance().GetGamePad();

	//なにかボタンを押したらゲームシーンへ切り替え
	const GamePadButton anyButton =
		GamePad::BTN_A
		| GamePad::BTN_B
		| GamePad::BTN_X
		| GamePad::BTN_Y
		;

	if (gamePad.GetButtonDown() & anyButton)
	{
		if (page == 1)
			SceneManager::Instance().ChangeScene(new SceneLoading(new SceneGame));
		else
		page++;
	}
}

//描画処理
void SceneTutorial::Render()
{
	// ======== 2Dスプライト描画 ========
	{
		Graphics& graphics = Graphics::Instance();
		ID3D11DeviceContext* dc = graphics.GetDeviceContext();
		RenderState* renderState = graphics.GetRenderState();

		ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
		ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

		// 画面クリア＆レンダーターゲット設定
		FLOAT color[] = { 0.0f, 0.0f, 0.5f, 1.0f };	// RGBA(0.0～1.0)
		dc->ClearRenderTargetView(rtv, color);
		dc->ClearDepthStencilView(dsv, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		dc->OMSetRenderTargets(1, &rtv, dsv);

		// 2Dスプライト描画
		{
			// タイトル（スプライト）描画
			float screenWidth = static_cast<float>(graphics.GetScreenWidth());
			float screenHeight = static_cast<float>(graphics.GetScreenHeight());

			if(page == 0)
			sprite1->Render(dc, 0, 0, screenWidth, screenHeight, 0, 1, 1, 1, 1);
			else
			sprite2->Render(dc, 0, 0, screenWidth, screenHeight, 0, 1, 1, 1, 1);
		}
	}
}

//GUI描画
void SceneTutorial::DrawGUI()
{

}