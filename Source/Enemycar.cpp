#include"Enemycar.h"
#include"Enemy.h"
#include"Graphics/Graphics.h"


//�f�o�b�N�v���~�e�B�u�`��
void Enemy::DrawDebugPrimitive() {
	DebugRenderer* debugRenderer = Graphics::Instance().GetDebugRenderer();
	
	//�Փ˔���p�̃f�o�b�N����`��
	//debugRenderer->DrawSphere(position, radius, DirectX::XMFLOAT4(0, 0, 0, 1));

	//�Փ˔���p�̃f�o�b�N�~����`��
	debugRenderer->DrawCylinder(position, radius, height, DirectX::XMFLOAT4(0, 0, 0, 1));

}

//�R���X�g���N�^
Enemycar::Enemycar() {
//�ԃ��f����ǂݍ���
 
model = new Model("Data/Model/Slime/Slime.mdl");

	//�X�P�[�����O
	scale.x = scale.y = scale.z = 0.01f;


	//���A�����ݒ�
	radius = 0.5f;
	height = 1.0f;
}

//�f�X�g���N�^
Enemycar::~Enemycar() {
//�ԃ��f����j��
delete model;
	}

//�X�V����
void Enemycar::Update(float elapsedTime) {
	//�I�u�W�F�N�g�s����X�V
	UpdateTransform();
	//���f���s��X�V
	model->UpdateTransform(transform);
}
//�`�揈��
void Enemycar::Render(ID3D11DeviceContext* dc, Shader* shader) {
	shader->Draw(dc, model);
}