#include"Player.h"
#include"Input/Input.h"
#include<imgui.h>
#include"Camera.h"
#include"Graphics/Graphics.h"
#include"EnemyManager.h"
#include"Collision.h"
#include "ItemManager.h"
#include "SceneEnd.h"
#include "SceneLoading.h"
#include "SceneManager.h"
#include <Stage.h>
#include"GameUI.h"
using namespace DirectX;

template <typename T>
T clamp(T value, T minVal, T maxVal)
{
	if (value < minVal) return minVal;
	if (value > maxVal) return maxVal;
	return value;
}
//コンストラクタ
Player::Player()
{
	//model = new Model("Data/Model/Mr.Incredible/Mr.Incredible.mdl");
	model = new Model("Data/Model/Scooter/scooter.mdl");//koko//キャラクターモデル
	//モデルが大きいのでスケーリング
	scale.x = scale.y = scale.z = 0.01f;
	HP = 3;
}

//デストラクタ
Player::~Player() {
	delete model;
}

//更新処理
void Player::Update(float elapsedTime) {

	{
		GamePad& gamePad = Input::Instance().GetGamePad();
		axisX = gamePad.GetAxisLX();
		axisY = gamePad.GetAxisLY();
	}

	drunkenness(elapsedTime);
	//移動入力処理
	InputMove(elapsedTime);

	//プレイヤーと敵との衝突処理
	CollisionPlayerVsEnemies();

	CollisionPlayerVsBottleDelete();

	//オブジェクト行列を更新
	UpdateTransform();

	//モデル行列更新
	model->UpdateTransform(transform);

	//ダメージ判定
	PlayerDamage(elapsedTime);

	//クリア判定　条件は後ほど変えることを前提
	if (DeleteCount == 3 && position.x > 12 || HP == 0)
	{
		SceneManager::Instance().ChangeScene(new SceneLoading(new SceneEnd));
	}
	// 足元にレイを飛ばして地面の高さを取得
	HitResult hit;
	DirectX::XMFLOAT3 start = { position.x, position.y + 1.0f, position.z };
	DirectX::XMFLOAT3 end = { position.x, position.y - 100.0f, position.z };
	if (Stage::Instance().RayCast(start, end, hit)) {
		position.y = hit.position.y; // 地面に吸着
	}
}

//描画処理
void Player::Render(ID3D11DeviceContext* dc, Shader* shader) {
	shader->Draw(dc, model);
}

// デバッグプリミティブ描画
void Player::DrawDebugPrimitive()
{
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();

	//衝突判定用のデバック球を描画
	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4{ 0,0,0,1 });

	//衝突判定用のデバック円柱を描画
	debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));
}



//デバック用GUI描画
void Player::DrawDebugGUI() {
	ImGui::SetNextWindowPos(ImVec2(10, 10), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(300, 300), ImGuiCond_FirstUseEver);
	if (ImGui::Begin("Player", nullptr, ImGuiWindowFlags_None)) {

		//トランスフォーム
		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen)){
			//位置
			ImGui::InputFloat3("Position", &position.x);
			//回転
			DirectX::XMFLOAT3 a;
			a.x = DirectX::XMConvertToDegrees(angle.x);
			a.y = DirectX::XMConvertToDegrees(angle.y);
			a.z = DirectX::XMConvertToDegrees(angle.z);
			ImGui::InputFloat3("Angle", &a.x);
			angle.x = DirectX::XMConvertToRadians(a.x);
			angle.y = DirectX::XMConvertToRadians(a.y);
			angle.z = DirectX::XMConvertToRadians(a.z);
			//スケール
			ImGui::InputFloat3("Scale", &scale.x);
			//消したボトルの数
			ImGui::InputInt("DeleteCount", &DeleteCount);
			//HP関連
			ImGui::InputInt("HP", &HP);
			ImGui::InputInt("invincibleTime", &invincibleTime);
			ImGui::Checkbox("isDamage", &isDamage);
		}
	}
	ImGui::End();
}

//スティック入力値から移動ベクトルを取得
DirectX::XMFLOAT3 Player::GetMoveVec() const {

	////入力情報を取得
	//GamePad& gamePad = Input::Instance().GetGamePad();
	//float ax = gamePad.GetAxisLX();
	//float ay = gamePad.GetAxisLY();

	////カメラ方向とスティックの入力値によって進行方向を計算する
	//Camera& camera = Camera::Instance();
	//const DirectX::XMFLOAT3& cameraRight = camera.GetRight();
	//const DirectX::XMFLOAT3& cameraFront = camera.GetFront();
	//
	////移動ベクトルはXZ平面に水平なベクトルになるようにする
	//
	////カメラ右方向ベクトルをXZ単位ベクトルに変換
	//float cameraRightX = cameraRight.x;
	//float cameraRightZ = cameraRight.z;
	//float cameraRightLength = sqrtf(cameraRightX * cameraRightX + cameraRightZ * cameraRightZ);
	//
	//if (cameraRightLength > 0.0f) {
	//	//単位ベクトル化
	//	cameraRightX /= cameraRightLength;
	//	cameraRightZ /= cameraRightLength;
	//}
	////カメラ前方向ベクトルをXZベクトルに変換
	//float cameraFrontX = cameraFront.x;
	//float cameraFrontZ = cameraFront.z;

	//float cameraFrontLength = sqrtf(cameraFrontX * cameraFrontX + cameraFrontZ * cameraFrontZ);
	//if (cameraFrontLength > 0.0f) {
 //    //単位ベクトル化
	//	cameraFrontX /= cameraFrontLength;
	//	cameraFrontZ /= cameraFrontLength;
	//}
	////スティックの水平入力をカメラ右方向に反映し、
	////スティックの垂直入力値をカメラ前方向に反映し、
	////進行ベクトルを計算する
	//DirectX::XMFLOAT3 vec;
	//vec.x = (cameraRightX * ax) + (cameraFrontX * ay);
	//vec.z = (cameraRightZ * ax) + (cameraFrontZ * ay);
	////Y軸方向には移動しない
	//vec.y = 0.0f;
	//	return vec;
	float ax = axisX;  // ← メンバーを使う！
	float ay = axisY;

	Camera& camera = Camera::Instance();
	const auto& R = camera.GetRight();
	const auto& F = camera.GetFront();

	float rx = R.x, rz = R.z;
	float rl = sqrtf(rx * rx + rz * rz);
	if (rl > 0.0f) { rx /= rl; rz /= rl; }

	float fx = F.x, fz = F.z;
	float fl = sqrtf(fx * fx + fz * fz);
	if (fl > 0.0f) { fx /= fl; fz /= fl; }

	DirectX::XMFLOAT3 v;
	v.x = (rx * ax) + (fx * ay);
	v.z = (rz * ax) + (fz * ay);
	v.y = 0.0f;
	return v;
}

////移動処理
//void Player::Move(float elapsedTime, float vx, float vz, float speed) {
//	speed *= elapsedTime;
//	position.x += vx * speed;
//	position.z += vz * speed;
//}
//
//void Player::Turn(float elapsedTime, float vx, float vz, float speed) {
//	speed += elapsedTime;
//
//	//進行ベクトルがゼロベクトルの場合は処理する必要なし
//	float length = sqrtf(vx * vx + vz * vz);
//	if (length < 0.001f)return;
//
//	//進行ベクトルを単位ベクトル化
//	vx /= length;
//	vz /= length;
//
//	//自身の回転値から前方向を求める
//	float frontX = sinf(angle.y);
//	float frontZ = cosf(angle.y);
//
//
//	//回転角を求める為、2つの単位ベクトルの内積を計算する
//	float dot = (frontX * vx) + (frontZ * vz);
//
//	//内積値は-1.0～1.0で表現されており、2つの単位ベクトルの角度が
//	//小さいほどに1.0に近づくという性質を利用して回転速度を調整する
//	float rot = 1.0f - dot;
//	if (rot > speed)rot = speed;
//
//	//左右判定を行うために2つの単位ベクトルの外積を計算する
//	float cross = (frontZ * vx) - (frontX * vz);
//
//	//2Dの外積値が正の場合か負の場合によって左右判定が行える
//	//左右判定を行うことによって左右回転を選択する
//
//	if (cross < 0.0f) {
//		
//		//angle.y -= speed;
//		angle.y -= rot;
//	}
//	else {
//		
//		//angle.y += speed;
//		angle.y += rot;
//	}
//
//}

//移動入力処理
void Player::InputMove(float elapsedTime) {
	//進行ベクトル取得
	DirectX::XMFLOAT3 moveVec = GetMoveVec();
	//移動処理
	Move(elapsedTime, moveVec.x, moveVec.z, moveSpeed*4);
	//旋回処理
	Turn(elapsedTime, moveVec.x, moveVec.z, turnSpeed*2);
}


// プレイヤーとエネミーとの衝突処理
void Player::CollisionPlayerVsEnemies()
{
	EnemyManager& enemyManager = EnemyManager::Instance();

	// 全ての敵と総当たりで衝突処理
	int enemyCount = enemyManager.GetEnemyCount();
	for (int i = 0; i < enemyCount; ++i)
	{
		Enemy* enemy = enemyManager.GetEnemy(i);

		// 衝突処理
		DirectX::XMFLOAT3 outPosition;
		if (Collision::IntersectSphereVsSphere(
			position,radius,
			enemy->GetPosition(),
			enemy->GetRadius(),
			outPosition))
		{
		// 押し出し後の位置設定
			enemy->SetPosition(outPosition);
			isDamage = true;	//被弾した時TRUEにする
		}
	}
}

void Player::CollisionPlayerVsBottleDelete()
{
	ItemManager& itemManager = ItemManager::Instance();

	// 全ての敵と総当たりで衝突処理
	int enemyCount = itemManager.GetItemCount();
	for (int i = 0; i < enemyCount; ++i)
	{
		Item* item = itemManager.GetItem(i);

		// 衝突処理
		DirectX::XMFLOAT3 outPosition;
		if (Collision::IntersectSphereVsSphere(
			position, radius,
			item->GetPosition(),
			item->GetRadius(),
			outPosition))
		{// 押し出し後の位置設定
			item->Destroy();
			DeleteCount++;
			ui->gauge_UP_switch = true;
			ui->cool_time_switch = false;
		}
	}
}

// 着地した時に呼ばれる
void Player::OnLanding()
{
	jumpCount = 0;
}

// ダメージ処理
void Player::PlayerDamage(float elapsedTime)
{
	// ダメージ中は処理しない
	if (invincibleTime == 0) {
		if (isDamage) {
			HP -= 1;
			invincibleTime = 60;
			return;
		}
	}
	else
	{
		invincibleTime -= 1;

		auto* res = const_cast<ModelResource*>(model->GetResource());
		for (auto& mat : res->GetMaterials()) {
			mat.color.w = 0.4f;
		}

		if (invincibleTime <= 0)
		{
			invincibleTime = 0;
			isDamage = false;

			for (auto& mat : res->GetMaterials()) {
				mat.color.w = 1.0;
			}
		}
	}
}
void Player::drunkenness(float elapsedTime)
{

	//// タイマーを進める
	//randomTimer += elapsedTime;

	//// 3秒経過したら
	//if (randomTimer >= 3.0f)
	//{
	//	randomTimer = 0.0f; // リセット

	//	// ランダム生成（例：0〜99）
	//	randomValue = rand() % 20;
	//}
	//
	//	

	//

	//	if (axisX == 1)
	//	{
	//		position.x += randomValue *static_cast<float>(elapsedTime);
	//	}
	//	if (axisX == -1)
	//	{
	//		position.x -= randomValue * static_cast<float>(elapsedTime);
	//	}
	//	if (axisZ == 1)
	//	{
	//		position.y += randomValue *static_cast<float>(elapsedTime);
	//	}
	//	if (axisZ == -1)
	//	{
	//		position.y -= randomValue * static_cast<float>(elapsedTime);
	//	}




	randomTimer += elapsedTime;
	if (randomTimer >= 2.0f)
	{
		randomTimer = 0.0f;
		drunkennessX = ((rand() % 200) - 100) / 100.0f; // -1～1
		drunkennessY = ((rand() % 200) - 100) / 100.0f;


		// --- GameUIからゲージ値を取得 ---

		if (ui) {
			float gauge = ui->gauge;  // 現在のゲージ値
			float gaugeMin = ui->gauge_MIN;
			float gaugeMax = ui->gauge_MAX;

			// --- ゲージ比率（0～1に正規化） ---
			t = (gauge - gaugeMin) / (gaugeMax - gaugeMin);
			t = clamp(t, 0.0f, 1.0f);
		}
	}
	float drunkenPower = 0.05f + (t * 0.30f);
	// 操作入力に揺らぎを加える
	/*axisX += drunkennessX * 0.2f;
	axisY += drunkennessY * 0.2f;*/
	axisX += drunkennessX * drunkenPower;
	axisY += drunkennessY * drunkenPower;
	axisX = clamp(axisX, -1.0f, 1.0f);
	axisY = clamp(axisY, -1.0f, 1.0f);

}