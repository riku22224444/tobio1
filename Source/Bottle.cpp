#include"ItemManager.h"
#include"Item.h"
#include"Graphics/Graphics.h"
#include "Bottle.h"


//デバックプリミティブ描画
void Item::DrawDebugPrimitive() {
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバック球を描画
	debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));
}

//コンストラクタ
Bottle::Bottle() {
	//モデルを読み込み

	model = new Model("Data/Model/Bottle_of_Rum/Bottle1.mdl");//ボトル

	//スケーリング
	scale.x = scale.y = scale.z = 0.004f;
	angle.z = 25;
	//position.x = 70.0f;
	//position.y = 8.0f;
}

//デストラクタ
Bottle::~Bottle() {
	//モデルを破棄
	delete model;
}

//更新処理
void Bottle::Update(float elapsedTime) {
	//オブジェクト行列を更新
	UpdateTransform();
	//モデル行列更新
	model->UpdateTransform(transform);
}
//描画処理
void Bottle::Render(ID3D11DeviceContext* dc, Shader* shader) {
	shader->Draw(dc, model);
}
