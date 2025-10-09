#include"EnemyManager.h"

//更新処理
void EnemyManager::Update(float elapsedTime) {
	for (Enemy * enemy : enemies) {
		enemy->Update(elapsedTime);
	}
}


//描画処理
void EnemyManager::Render(ID3D11DeviceContext* context, Shader* shader) {
	for (Enemy* enemy : enemies) {
		enemy->Render(context,shader);
	}
}

//エネミー登録
void EnemyManager::Register(Enemy* enemy) {
	enemies.emplace_back(enemy);
}

//エネミー全削除
void EnemyManager::Clear() {
	for (Enemy* enemy : enemies) {
		delete enemy;
	}
	enemies.clear();
}