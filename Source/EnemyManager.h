#pragma once

#include<vector>
#include"Enemy.h"

//エネミーマネージャー
class EnemyManager {

private:
	EnemyManager() {}
	~EnemyManager() {}

public:
	//唯一のインスタンスを取得
	static EnemyManager& Instance() {
		static EnemyManager instance;
		return instance;
	}
	//更新処理
	void Update(float elapsedTime);

	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

	//エネミー登録
	void Register(Enemy* enemy);

	//エネミー全削除
	void Clear();
	
private:

	std::vector<Enemy*> enemies;

};