#include"Character.h"
#include"Stage.h"

//�s��X�V����
void Character::UpdateTransform() {

	//�X�P�[���s����쐬
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(scale.x, scale.y,scale.z);

   //��]�s����쐬
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationRollPitchYaw(angle.x,angle.y,angle.z);

	//�ʒu�s����쐬
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(position.x, position.y, position.z);

	//3�̍s���g�ݍ��킹�A���[���h�s����쐬
	DirectX::XMMATRIX W = S * R * T;

	//�v�Z�������[���h�s������o��
	DirectX::XMStoreFloat4x4(&transform, W);
}

//�����ړ��X�V����
void Character::UpdateVerticalMove(float elapsedTime)
{
	//���������̈ړ���
	float my = velocity.y * elapsedTime;

	if (my < 0.0f) {
		//���C�̊J�n�ʒu�͑�����菭����
		DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
		//���C�̏I�_�ʒu�͈ړ���̈ʒu
		DirectX::XMFLOAT3 end = { position.x,position.y + my, position.z };

		//���C�L���X�g�ɂ��n�ʔ���
		HitResult hit;
		if (Stage::Instance().Raycast(start, end, hit)) 
		{
			//�n�ʂɐڒn���Ă���
			position.y = hit.position.y;
		
			//���n����
			if (!isGround) {
				OnLanding();
			}
			isGround = true;
			velocity.y = 0.0f;
		}
		else
		{
		//�󒆂ɕ����Ă���
			position.y += my;
			isGround = false;
		}
	}
	//�㏸��
	else if (my > 0.0f) {
		position.y += my;
		isGround = false;
	}
}

void Character::UpdateHorizontalMove(float elapsedTime) {

	// �ړ�����
	position.x += velocity.x * elapsedTime;
	position.z += velocity.z * elapsedTime;

}