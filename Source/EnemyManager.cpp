#include"EnemyManager.h"

//�X�V����
void EnemyManager::Update(float elapsedTime) {
	for (Enemy * enemy : enemies) {
		enemy->Update(elapsedTime);
	}
}


//�`�揈��
void EnemyManager::Render(ID3D11DeviceContext* context, Shader* shader) {
	for (Enemy* enemy : enemies) {
		enemy->Render(context,shader);
	}
}

//�G�l�~�[�o�^
void EnemyManager::Register(Enemy* enemy) {
	enemies.emplace_back(enemy);
}

//�G�l�~�[�S�폜
void EnemyManager::Clear() {
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	enemies.clear();
}