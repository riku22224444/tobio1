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

//垂直移動更新処理
void Character::UpdateVerticalMove(float elapsedTime)
{
	//垂直方向の移動量
	float my = velocity.y * elapsedTime;

	if (my < 0.0f) {
		//レイの開始位置は足元より少し上
		DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
		//レイの終点位置は移動後の位置
		DirectX::XMFLOAT3 end = { position.x,position.y + my, position.z };

		//レイキャストによる地面判定
		HitResult hit;
		if (Stage::Instance().Raycast(start, end, hit)) 
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