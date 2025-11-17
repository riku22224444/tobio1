#pragma once
#include"Graphics/Model.h"
#include"Enemy.h"

//Ô
class EnemyPolice : public Enemy {
public:
	EnemyPolice();
	~EnemyPolice() override;
	//XVˆ—
	void Update(float elapsedTime) override;
	//•`‰æˆ—
	void Render(ID3D11DeviceContext* dc, Shader* shader) override;

	bool EnemyView();

private:
	Model* model = nullptr;
	int State = 0;
	float ViewRadius = 10.0f;
	float ViewAngle = 90.0f;

};