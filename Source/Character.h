#pragma once
#include<DirectXMath.h>

//�L�����N�^�[
class Character {
public:
	Character() {}
	virtual ~Character() {}

	//�ʒu�擾
	const DirectX::XMFLOAT3& GetPosition() const { return position; }

	//�ʒu�ݒ�
	void SetPosition(const DirectX::XMFLOAT3& position) { this->position = position; }


	//��]�擾
	const DirectX::XMFLOAT3& GetAngle()const { return angle; }

	//��]�ݒ�
	void SetAngle(const DirectX::XMFLOAT3& angle) { this->angle = angle; }

	//�X�P�[���擾
	const DirectX::XMFLOAT3& GetScale() const { return scale; }

	//�X�P�[���擾
	void SetScale(const DirectX::XMFLOAT3& scale) { this->scale = scale; }

//�s��X�V����
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
