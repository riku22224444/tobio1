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

	//���C�L���X�g
	bool Raycast(const DirectX::XMFLOAT3& start,const DirectX::XMFLOAT3& end,HitResult& hit);

	//�C���X�^���X���擾
	static Stage& Instance();

	//�`�揈��
	void Render(ID3D11DeviceContext* dc, Shader* shader);

private :
	Model* model = nullptr;
};