#include"Collision.h"

//球と球の当たり判定
bool Collision::IntersectSphereVsSphere(
	const DirectX::XMFLOAT3& positionA,
	float radiusA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB,
	DirectX::XMFLOAT3& outPosition
)

{
	//A→Bへのベクトルを算出
	DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
	DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
	DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
	
	float lengthSq;
	DirectX::XMStoreFloat(&lengthSq, LengthSq);
	
	//距離判定
	float range = radiusA + radiusB;
	if (lengthSq > range * range) {
		return false;
	}

	//AがBを押し出す
	Vec = DirectX::XMVector3Normalize(Vec);
	Vec = DirectX::XMVectorScale(Vec, range);
	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
	DirectX::XMStoreFloat3(&outPosition, PositionB);

	return true;

}

//レイとモデルの交差判定
bool Collision::IntersectRayVsMode(
	const DirectX::XMFLOAT3& start,
	const DirectX::XMFLOAT3& end,
	const Model* model,
	HitResult& result)
{
	//以前の処理が正しく動くように仮の実装
	if (end.y < 0.0f) {
		result.position.x = end.x;
		result.position.y = 0.0f;
		result.position.z = end.z;
		result.normal.x = 0.0f;
		result.normal.y = 1.0f;
		result.normal.z = 0.0f;
		return true;
	}
	return false;
}