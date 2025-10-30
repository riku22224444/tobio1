#pragma once
#include <memory>
#include "Graphics/Sprite.h"
#include "Scene.h" 
class GameUI :public Scene
{
public:
    void Initialize();
    void Finalize();
    void Render();
    void DrawGUI();
    void Update(float elapsedTime);
private:
    //std::unique_ptr<Sprite> sprite; // ���S��RAII�Ǘ�
    Sprite* sprite = nullptr;
    Sprite* sprite2 = nullptr;
    Sprite* face = nullptr;



    int clearcount = 0;
    float gauge = 1;
    float gauge_UP;
    float time = 0;
    bool gauge_UP_switch = false;
    int gauge_MAX = 320 - 50;
    int gauge_MIN = 620 - 32;
    float cool_time = 3;

    bool cool_time_switch = true;
    bool wasSpacePressed = false; // �N���X�����o�[��


    float blendFactor[4] = { 0,0,0,0 };
    ID3D11BlendState* blendStateEnable = nullptr;
    ID3D11BlendState* blendStateDisable = nullptr;

    ID3D11BlendState* alphaBlend = nullptr;



};

