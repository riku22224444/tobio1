#include"EnemyManager.h"
#include"Collision.h"



//�X�V����
void EnemyManager::Update(float elapsedTime) {
	for (Enemy * enemy : enemies) {
		enemy->Update(elapsedTime);
	}
	//�G�l�~�[���m�̏Փ˔���
	CollisionEnemiVsEnemies();
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

//�f�o�b�N�v���~�e�B�u�`��
void EnemyManager::DrawDebugPrimitive() {
		for (Enemy* enemy : enemies) {
		enemy->DrawDebugPrimitive();
		}
}


// �G�l�~�[���m�̏Փˏ���
void EnemyManager::CollisionEnemiVsEnemies()
{
	size_t enemyCount = enemies.size();
	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemyA = enemies.at(i);
		for (int j = i + 1; j < enemyCount; ++j)
		{
			Enemy* enemyB = enemies.at(j);

			DirectX::XMFLOAT3 outPosition;
			if (Collision::IntersectSphereVsSphere(
				enemyA->GetPosition(),
				enemyA->GetRadius(),
				enemyB->GetPosition(),
				enemyB->GetRadius(),
				outPosition))
			{
				enemyB->SetPosition(outPosition);
			}
		}
	}
}
