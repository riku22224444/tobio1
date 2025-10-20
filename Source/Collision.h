#pragma once
#include<DirectXMath.h>
#include"Graphics/Model.h"

//�q�b�g����
struct HitResult {
	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 normal = { 0,0,0 };
	float distance = 0.0f;
	int materialIndex = -1;
};

//�R���W����
class Collision {
	public :

		//���Ƌ��̓����蔻��
		static bool IntersectSphereVsSphere(
			const DirectX::XMFLOAT3& positionA,
			float radiusA,
			const DirectX::XMFLOAT3& positionB,
			float radiusB,
			DirectX::XMFLOAT3& outPosition
		);

		//���C�ƃ��f���̌�������
		static	bool Collision::IntersectRayVsMode(
			const DirectX::XMFLOAT3& start,
			const DirectX::XMFLOAT3& end,
			const Model* model,
			HitResult& result
		);
		
		};