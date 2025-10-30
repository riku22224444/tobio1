#include "GameUI.h"
#include "Graphics/Sprite.h"
#include "Graphics/Graphics.h"
#include "imgui.h"


void GameUI::Initialize()
{
    gauge = gauge_MAX;
    // �X�v���C�g�̐���
    sprite = new Sprite("Data/Sprite/cage.png");
    sprite2 = new Sprite("Data/Sprite/yazirusi.png");


    face = new Sprite("Data/Font/font1.png");

    // �� �t�H���g��ǉ��i���ꂾ���ŕ�������������\������܂��j
    //ImGuiIO& io = ImGui::GetIO();
   // io.Fonts->AddFontFromFileTTF("Data/Font/MyFont.ttf", 32.0f, nullptr, io.Fonts->GetGlyphRangesJapanese());

}

void GameUI::Finalize()
{
    // ���S�ȉ��
    if (sprite)
    {
        delete sprite;
        sprite = nullptr;
    }

    if (sprite2)
    {
        delete sprite2;
        sprite2 = nullptr;
    }
    if (face) { delete face; face = nullptr; }
}

void GameUI::Update(float elapsedTime)
{
    gauge += static_cast<float>(5 * elapsedTime);


    SHORT keyState = GetAsyncKeyState(VK_SPACE);
    bool isPressed = (keyState & 0x8000);
    // �������u�Ԃ�������
    if (isPressed && !wasSpacePressed && cool_time_switch == true)
    {
        // �X�y�[�X�������u�Ԃ̏���


        gauge_UP_switch = true;
        cool_time_switch = false;
    }

    if (gauge >= gauge_MIN)
    {
        gauge = gauge_MIN;
    }
    if (gauge_UP_switch == true)
    {

        gauge -= static_cast<float>(80 * elapsedTime);
        time += static_cast<float>(elapsedTime);

        if (time > 1)
        {
            gauge_UP_switch = false;
            time = 0;
        }
    }
    if (cool_time_switch == false)
    {
        cool_time += static_cast<float>(elapsedTime);
        if (cool_time >= 5)
        {
            cool_time_switch = true;
            cool_time = 0;
        }
    }
    if (gauge >= gauge_MIN)
    {
        gauge = gauge_MIN;
    }
    if (gauge <= gauge_MAX)
    {
        gauge = gauge_MAX;
    }



    if (GetAsyncKeyState('T') & 0x0001)
    {
        clearcount++;   //�����Ŕz�B�ł������̃J�E���g
    }
}

void GameUI::Render()
{
    if (!sprite || !sprite2)
        return;

    Graphics& graphics = Graphics::Instance();
    ID3D11DeviceContext* dc = graphics.GetDeviceContext();
    ID3D11RenderTargetView* rtv = graphics.GetRenderTargetView();
    ID3D11DepthStencilView* dsv = graphics.GetDepthStencilView();

    dc->OMSetRenderTargets(1, &rtv, dsv);

    float screenWidth = static_cast<float>(graphics.GetScreenWidth());
    float screenHeight = static_cast<float>(graphics.GetScreenHeight());

    //=============================================
    // �� �A���t�@�u�����h�L����
    //=============================================
   

    D3D11_BLEND_DESC blendDesc = {};
    blendDesc.AlphaToCoverageEnable = FALSE;
    blendDesc.RenderTarget[0].BlendEnable = TRUE;
    blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
    blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
    blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
    blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
    blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

    graphics.GetDevice()->CreateBlendState(&blendDesc, &alphaBlend);

    float blendFactor[4] = { 0, 0, 0, 0 };
    dc->OMSetBlendState(alphaBlend, blendFactor, 0xffffffff);

    //=============================================
    // �X�v���C�g�`��
    //=============================================

    // cage.png
    sprite->Render(dc,
        screenWidth - 64, 300, 84, 320,  // x, y, ��, ����
        0,
        1, 1, 1, 1);

    // yazirusi.png�i���ߕt���j
    sprite2->Render(dc,
        screenWidth - 64 - 64, gauge, 64, 64,
        0,
        1, 1, 1, 1);





    //=========================
   // �� �����iSprite::textout �����j
   //=========================
    if (face)
    {
        // �\���ʒu�͂��D�݂�
        const float textX = screenWidth - 128 - 20 - 160.0f;
        const float textY = 0;

        // ����ASCII�Ȃ̂� 1�����T�C�Y�����߂�i�g�債�Ȃ��̂���ԃN�b�L���j
        // font0.png �� 256x256 �� 16x16 �O���b�h�Ȃ�A���Z���� 16x16 px
        const float cellW = 64.0f;  // ������ 32 �ɂ���Ɗg��i�����ڂ��܂��j
        const float cellH = 64.0f;

        // �������g�ݗ��āiASCII�̂݁j
        char buf[128];
        std::snprintf(buf, sizeof(buf),
            "%3d/3",
            clearcount
        );

        // �������ŕ`��iRGBA�j
        face->textout(dc, buf, textX, textY, 64, 64, 1, 1, 1, 1);

        // ��F�^�C�g�����o��
       // face->textout(dc, "POWER", textX, textY - 20.0f, cellW, cellH, 1, 1, 1, 1);
    }







    // ��n��
    dc->OMSetBlendState(nullptr, blendFactor, 0xffffffff);
    if (alphaBlend) alphaBlend->Release();
}

void GameUI::DrawGUI()
{

}
