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


//�ړ�����
void Character::Move(float elapsedTime, float vx, float vz, float speed) {
	speed *= elapsedTime;
	position.x += vx * speed;
	position.z += vz * speed;
}

void Character::Turn(float elapsedTime, float vx, float vz, float speed) {
	speed += elapsedTime;

	//�i�s�x�N�g�����[���x�N�g���̏ꍇ�͏�������K�v�Ȃ�
	float length = sqrtf(vx * vx + vz * vz);
	if (length < 0.001f)return;

	//�i�s�x�N�g����P�ʃx�N�g����
	vx /= length;
	vz /= length;

	//���g�̉�]�l����O���������߂�
	float frontX = sinf(angle.y);
	float frontZ = cosf(angle.y);


	//��]�p�����߂�ׁA2�̒P�ʃx�N�g���̓��ς��v�Z����
	float dot = (frontX * vx) + (frontZ * vz);

	//���ϒl��-1.0�`1.0�ŕ\������Ă���A2�̒P�ʃx�N�g���̊p�x��
	//�������قǂ�1.0�ɋ߂Â��Ƃ��������𗘗p���ĉ�]���x�𒲐�����
	float rot = 1.0f - dot;
	if (rot > speed)rot = speed;

	//���E������s�����߂�2�̒P�ʃx�N�g���̊O�ς��v�Z����
	float cross = (frontZ * vx) - (frontX * vz);

	//2D�̊O�ϒl�����̏ꍇ�����̏ꍇ�ɂ���č��E���肪�s����
	//���E������s�����Ƃɂ���č��E��]��I������

	if (cross < 0.0f) {

		//angle.y -= speed;
		angle.y -= rot;
	}
	else {

		//angle.y += speed;
		angle.y += rot;
	}

}


//�����ړ��X�V����
void Character::UpdateVerticalMove(float elapsedTime)
{
	//���������̈ړ���
	float my = velocity.y * elapsedTime;

	//������
	if (my < 0.0f) {
		//���C�̊J�n�ʒu�͑�����菭����
		DirectX::XMFLOAT3 start = { position.x,position.y + stepOffset,position.z };
		//���C�̏I�_�ʒu�͈ړ���̈ʒu
		DirectX::XMFLOAT3 end = { position.x,position.y + my, position.z };

		//���C�L���X�g�ɂ��n�ʔ���
		HitResult hit;
		if (Stage::Instance().RayCast(start, end, hit)) 
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