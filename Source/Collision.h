#pragma once
#include<DirectXMath.h>

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

};