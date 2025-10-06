#pragma once
#include<DirectXMath.h>

//キャラクター
class Character {
public:
	Character() {}
	virtual ~Character() {}

	//位置取得
	const DirectX::XMFLOAT3& GetPosition() const { return position; }

	//位置設定
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }


	//回転取得
	const DirectX::XMFLOAT3& GetAngle()const { return angle; }

	//回転設定
	void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }

	//スケール取得
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//スケール取得
	void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }

//行列更新処理
	void UpdateTransform();
protected:
	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 angle = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 };

};
