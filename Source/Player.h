#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"


//プレイヤー
class Player : public Character {
public:
	Player();
	~Player() override;

	//デバック用GUI描画
	void DrawDebugGUI();

	//デバックプリミティブ描画
	void DrawDebugPrimitive();

	//更新処理
	void Update(float elapsedTime);
	//描画処理
	void Render(ID3D11DeviceContext* dc, Shader* shader);

private :
	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec()const;
	//移動処理
	void Move(float elapsedTime, float vx, float vz, float speed);
	//移動入力処理
	void InputMove(float elapsedTime);
	void Turn(float elapsedTime, float vx, float vz, float speed);


private:
	Model* model = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
};












