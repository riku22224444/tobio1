#pragma once

#include"Graphics/Model.h"
#include"Enemy.h"

//��
class Enemycar : public Enemy {
public:
	Enemycar();
	~Enemycar() override;
	//�X�V����
	void Update(float elapsedTime) override;
	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader) override;

private:
	Model* model = nullptr;

};