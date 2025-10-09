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
	void Move(float elapsedTime, float vx, float vz, float speed);
	//�ړ����͏���
	void InputMove(float elapsedTime);
	void Turn(float elapsedTime, float vx, float vz, float speed);


private:
	Model* model = nullptr;
	float moveSpeed = 5.0f;
	float turnSpeed = DirectX::XMConvertToRadians(720);
};












