#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Character.h"


//�v���C���[
class Player : public Character {
public:
	Player();
	~Player() override;

	//�f�o�b�N�pGUI�`��
	void DrawDebugGUI();

	//�f�o�b�N�v���~�e�B�u�`��
	void DrawDebugPrimitive();

	//�X�V����
	void Update(float elapsedTime);
	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

private :
	//�X�e�B�b�N���͒l����ړ��x�N�g�����擾
	DirectX::XMFLOAT3 GetMoveVec()const;

	//�ړ�����
	//void Move(float elapsedTime, float vx, float vz, float speed);

	//���񏈗�
	//void Turn(float elapsedTime, float vx, float vz, float speed);
	
	//�v���C���[�ƃG�l�~�[�Ƃ̏Փˏ���
	void CollisionPlayerVsEnemies();

	//�ړ����͏���

	void InputMove(float elapsedTime);

	//�W�����v����
	//void Jump(float speed);

	//���͏����X�V
	//void UpdateVelocity(float elapsedTime);

	//�W�����v���͏���
	//void InputJump();

protected:

	// ���n�������ɌĂ΂��
	void OnLanding() override;

private:
	int					jumpCount = 0;
	Model* model = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
	/*float jumpspeed = 20.0f;
	float gravity = -1.0f;
	DirectX::XMFLOAT3 velocity = { 0,0,0 };*/
};











