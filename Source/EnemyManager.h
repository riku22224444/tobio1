#pragma once

#include<vector>
#include"Enemy.h"

//�G�l�~�[�}�l�[�W���[
class EnemyManager {

private:
	EnemyManager() {}
	~EnemyManager() {}

public:
	//�B��̃C���X�^���X���擾
	static EnemyManager& Instance() {
		static EnemyManager instance;
		return instance;
	}
	//�X�V����
	void Update(float elapsedTime);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//�G�l�~�[�o�^
	void Register(Enemy* enemy);

	//�G�l�~�[�S�폜
	void Clear();
	
private:

	std::vector<Enemy*> enemies;

};