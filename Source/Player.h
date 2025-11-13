#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"
#include"GameUI.h"

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
	void drunkenness(float elapsedTime);
	
	void SetUI(GameUI* p) { ui = p; };
private :
	//スティック入力値から移動ベクトルを取得
	DirectX::XMFLOAT3 GetMoveVec()const;

	//移動処理
	//void Move(float elapsedTime, float vx, float vz, float speed);

	//旋回処理
	//void Turn(float elapsedTime, float vx, float vz, float speed);
	
	//プレイヤーとエネミーとの衝突処理
	void CollisionPlayerVsEnemies();

	//プレイヤーとボトルとの消滅処理
	void CollisionPlayerVsBottleDelete();

	//移動入力処理

	void InputMove(float elapsedTime);

	//ダメージ処理
	void PlayerDamage(float elapsedTime);

	//ジャンプ処理
	//void Jump(float speed);

	//速力処理更新
	//void UpdateVelocity(float elapsedTime);

	//ジャンプ入力処理
	//void InputJump();

protected:

	// 着地した時に呼ばれる
	void OnLanding() override;

private:
	int jumpCount = 0;
	int jumpLimit = 2;

	Model* model = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
	/*float jumpspeed = 20.0f;
	float gravity = -1.0f;
	DirectX::XMFLOAT3 velocity = { 0,0,0 };*/

	int DeleteCount = 0;

	int HP = 0;
	bool isDamage = false;
	int invincibleTime = 0;
	DirectX::XMFLOAT2 stickyMove = { 0, 0 }; // XZ の残存ベクトル（-1..1）
	float stickyAccel = 12.0f;  // 追従の速さ（大きいほど目標に素早く寄る）
	float stickyDecay = 3.0f;   // 離した後の減衰の速さ（大きいほど早くゼロ）
	float stickyMaxMag = 1.0f;   // 残存ベクトルの最大長（1で十分）
	bool  stickyEnabled = true;   // 残存入力のON/OFF
	float drunkennessX;
	
	float axisX = 0.0f;
	float axisY = 0.0f;
	float axisZ = 0.0f;

	float randomTimer = 0.0f;
	int   randomValue = 0;

	float drunkennessY;

	float t = 0.0f; // デフォルト
	GameUI* ui = nullptr;
};