#include"Collision.h"

//���Ƌ��̓����蔻��
bool Collision::IntersectSphereVsSphere(
	const DirectX::XMFLOAT3& positionA,
	float radiusA,
	const DirectX::XMFLOAT3& positionB,
	float radiusB,
	DirectX::XMFLOAT3& outPosition
)

{
	//A��B�ւ̃x�N�g�����Z�o
	DirectX::XMVECTOR PositionA = DirectX::XMLoadFloat3(&positionA);
	DirectX::XMVECTOR PositionB = DirectX::XMLoadFloat3(&positionB);
	DirectX::XMVECTOR Vec = DirectX::XMVectorSubtract(PositionB, PositionA);
	DirectX::XMVECTOR LengthSq = DirectX::XMVector3LengthSq(Vec);
	
	float lengthSq;
	DirectX::XMStoreFloat(&lengthSq, LengthSq);
	
	//��������
	float range = radiusA + radiusB;
	if (lengthSq > range * range) {
		return false;
	}

	//A��B�������o��
	Vec = DirectX::XMVector3Normalize(Vec);
	Vec = DirectX::XMVectorScale(Vec, range);
	PositionB = DirectX::XMVectorAdd(PositionA, Vec);
	DirectX::XMStoreFloat3(&outPosition, PositionB);

	return true;

}

//���C�ƃ��f���̌�������
bool Collision::IntersectRayVsMode(
	const DirectX::XMFLOAT3& start,
	const DirectX::XMFLOAT3& end,
	const Model* model,
	HitResult& result)
{
	//�ȑO�̏����������������悤�ɉ��̎���
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