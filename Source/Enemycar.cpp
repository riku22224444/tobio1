#include"Enemycar.h"

//コンストラクタ
Enemycar::Enemycar() {
//車モデルを読み込み
 
model = new Model("Data/Model/Slime/Slime.mdl");

	//スケーリング
	scale.x = scale.y = scale.z = 0.01f;
}

//デストラクタ
Enemycar::~Enemycar() {
//車モデルを破棄
delete model;
	}

//更新処理
void Enemycar::Update(float elapsedTime) {
	//オブジェクト行列を更新
	UpdateTransform();
	//モデル行列更新
	model->UpdateTransform(transform);
}
//描画処理
void Enemycar::Render(ID3D11DeviceContext* dc, Shader* shader) {
	shader->Draw(dc, model);
}