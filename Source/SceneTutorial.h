#pragma once

#include "Graphics/Sprite.h"
#include "Scene.h"

class SceneTutorial :public Scene
{
public:
	SceneTutorial() {}
	~SceneTutorial() override {}

	//‰Šú‰»
	void Initialize() override;

	//I—¹‰»
	void Finalize() override;

	//XVŠÔ
	void Update(float elapsedTime) override;

	//•`‰æˆ—
	void Render() override;

	//GUI•`‰æ
	void DrawGUI() override;

private:
	Sprite* sprite1 = nullptr;
	Sprite* sprite2 = nullptr;

	int page = 0;
};