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

	// �n�ʂɐڒn���Ă��邩
	bool IsGround() const { return isGround; }

	

	//���a�擾
	float GetRadius() const { return radius; }

	//�����ړ��X�V����
	void Character::UpdateVerticalMove(float elapsedTime);

	// �����ړ��X�V����
	void UpdateHorizontalMove(float elapsedTime);

	//�����擾
	float GrtHeigth()const { return height; }

protected :

	//�ړ�����
	void Move(float elapsedTime, float vx, float vz, float speed);

	//���񏈗�
	void Turn(float elapsedTime, float vx, float vz, float speed);


protected:

	// ���n�������ɌĂ΂��
	virtual void OnLanding() {}



protected:
	DirectX::XMFLOAT3 position = { 0,0,0 };
	DirectX::XMFLOAT3 angle = { 0,0,0 };
	DirectX::XMFLOAT3 scale = { 1,1,1 };
	DirectX::XMFLOAT4X4 transform = {
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1 };
	bool				isGround = false;
	DirectX::XMFLOAT3	velocity = { 0, 0, 0 };
	float height = 2.0f;
	float radius = 0.5f;
	float stepOffset = 1.0f;
};
