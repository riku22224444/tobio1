#pragma once
#include <DirectXMath.h>

// キャラクター
class Character {
public:
    Character() {}
    virtual ~Character() {}

    // 位置/回転/スケール
    const DirectX::XMFLOAT3& GetPosition() const { return position; }
    void SetPosition(const DirectX::XMFLOAT3& p) { position = p; }

    const DirectX::XMFLOAT3& GetAngle() const { return angle; }
    void SetAngle(const DirectX::XMFLOAT3& a) { angle = a; }

    const DirectX::XMFLOAT3& GetScale() const { return scale; }
    void SetScale(const DirectX::XMFLOAT3& s) { scale = s; }

    // 行列更新
    void UpdateTransform();

    // 接地
    bool IsGround() const { return isGround; }

    // 形状
    float GetRadius() const { return radius; }
    float GetHeight() const { return height; }  // ← 誤字修正

    // 速度系更新
    void UpdateVelocity(float elapsedTime);

    // （テスト用）ワールド衝突の無効化スイッチ
    void SetIgnoreWorldCollision(bool b) { ignoreWorldCollision = b; }
    bool GetIgnoreWorldCollision() const { return ignoreWorldCollision; }

protected:
    // 垂直・水平の内部処理
    void UpdateVerticalVelocity(float elapsedFrame);
    void UpdateVerticalMove(float elapsedTime);
    void UpdateHorizontalVelocity(float elapsedFrame);
    void UpdateHorizontalMove(float elapsedTime);

    // 操作
    void Move(float elapsedTime, float vx, float vz, float speed);
    void Turn(float elapsedTime, float vx, float vz, float speed);

    // 派生が着地時に受け取るフック
    virtual void OnLanding() {}

protected:
    DirectX::XMFLOAT3 position{ 0,0,0 };
    DirectX::XMFLOAT3 angle{ 0,0,0 };
    DirectX::XMFLOAT3 scale{ 1,1,1 };
    DirectX::XMFLOAT4X4 transform{
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };

    bool  isGround = false;
    float gravity = -1.0f;

    DirectX::XMFLOAT3 velocity{ 0,0,0 };

    // 当たり形状
    float height = 2.0f;
    float radius = 0.5f;
    float stepOffset = 1.0f;

    // モーション・地形
    float friction = 0.5f;
    float acceleration = 1.0f;
    float maxMoveSpeed = 5.0f;
    float moveVecX = 0.0f;
    float moveVecZ = 0.0f;
    float airControl = 0.3f;
    float slopeRate = 1.0f;

    // ← 追加：このフラグが true の時は床/壁の押し出しを無効化
    bool ignoreWorldCollision = false;
};
