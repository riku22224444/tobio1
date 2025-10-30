#pragma once

#include"Graphics/Shader.h"
#include"Graphics/Model.h"
#include"Collision.h"

//�X�e�[�W
class Stage {
public :
	Stage();
	~Stage();

	//�X�V����
	void Update(float elapsedTime);

	//�C���X�^���X���擾
	static Stage& Instance();

	//���C�L���X�g
	bool RayCast(const DirectX::XMFLOAT3& start,const DirectX::XMFLOAT3& end,HitResult& hit);

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

private :
	Model* model = nullptr;
};