#pragma once
#include "Scene.h"
#include"Stage.h"
#include"Player.h"
#include"CameraController.h"

// �Q�[���V�[��
class SceneGame : public Scene
{
public:
	SceneGame() {}
	~SceneGame() {}

	// ������
	void Initialize();

	// �I����
	void Finalize();

	// �X�V����
	void Update(float elapsedTime);

	// �`�揈��
	void Render();

	void DrawGUI() {};
private:
	Stage* stage = nullptr;
	Player* player = nullptr;
	CameraController* cameraController = nullptr;
};
