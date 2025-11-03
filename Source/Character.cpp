#include"Character.h"
#include"Stage.h"

//行列更新処理
void Character::UpdateTransform() {

	//スケール行列を作成
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y,scale.z);

   //回転行列を作成
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x,angle.y,angle.z);

	//位置行列を作成
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//3つの行列を組み合わせ、ワールド行列を作成
	DirectX::XMMATRIX W = S * R * T;

	//計算したワールド行列を取り出す
	DirectX::XMStoreFloat4x4(&transform, W);
}


//移動処理
void Character::Move(float elapsedTime, float vx, float vz, float speed) {
	speed *= elapsedTime;
	position.x += vx * speed;
	position.z += vz * speed;
}

void Character::Turn(float elapsedTime, float vx, float vz, float speed) {
	speed += elapsedTime;

	//進行ベクトルがゼロベクトルの場合は処理する必要なし
	float length = sqrtf(vx * vx + vz * vz);
	if (length < 0.001f)return;

	//進行ベクトルを単位ベクトル化
	vx /= length;
	vz /= length;

	//自身の回転値から前方向を求める
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);


	//回転角を求める為、2つの単位ベクトルの内積を計算する
	float dot = (frontX * vx) + (frontZ * vz);

	//内積値は-1.0～1.0で表現されており、2つの単位ベクトルの角度が
	//小さいほどに1.0に近づくという性質を利用して回転速度を調整する
	float rot = 1.0f - dot;
	if (rot > speed)rot = speed;

	//左右判定を行うために2つの単位ベクトルの外積を計算する
	float cross = (frontZ * vx) - (frontX * vz);

	//2Dの外積値が正の場合か負の場合によって左右判定が行える
	//左右判定を行うことによって左右回転を選択する

	if (cross < 0.0f) {

		//angle.y -= speed;
		angle.y -= rot;
	}
	else {

		//angle.y += speed;
		angle.y += rot;
	}

}


//垂直移動更新処理
void Character::UpdateVerticalMove(float elapsedTime)
{
	//垂直方向の移動量
	float my = velocity.y * elapsedTime;

	//落下中
	if (my < 0.0f) {
		//レイの開始位置は足元より少し上
		DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
		//レイの終点位置は移動後の位置
		DirectX::XMFLOAT3 end = { position.x,position.y + my, position.z };

		//レイキャストによる地面判定
		HitResult hit;
		if (Stage::Instance().RayCast(start, end, hit)) 
		{
			//地面に接地している
			position.y = hit.position.y;
		
			//着地した
			if (!isGround) {
				OnLanding();
			}
			isGround = true;
			velocity.y = 0.0f;
		}
		else
		{
		//空中に浮いている
			position.y += my;
			isGround = false;
		}
	}
	//上昇中
	else if (my > 0.0f) {
		position.y += my;
		isGround = false;
	}
}

void Character::UpdateHorizontalMove(float elapsedTime) {

	// 移動処理
	position.x += velocity.x * elapsedTime;
	position.z += velocity.z * elapsedTime;

}