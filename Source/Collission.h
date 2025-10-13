#pragma once
#include<DirectXMath.h>

//ƒRƒŠƒWƒ‡ƒ“
class Collision {
	public :

		//‹…‚Æ‹…‚Ì“–‚½‚è”»’è
		static bool IntersectSphereVsSphere(
			const DirectX::XMFLOAT3& positionA,
			float radiusA,
			const DirectX::XMFLOAT3& positionB,
			float radiusB,
			DirectX::XMFLOAT3& outPosition
		
		
		
		);

};