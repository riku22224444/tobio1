#include "Character.h"
#include "Stage.h"
#include "Mathf.h"
#include <cmath>
using namespace DirectX;

// ===== ユーティリティ =====
static inline float len2(float x, float z) { return std::sqrt(x * x + z * z); }
static constexpr float EPS_Y = 0.05f;  // 地面スナップの浮かせ量
static constexpr float EPS_WALL = 0.02f;  // 壁からの微小押し出し
static constexpr float RAY_DOWN = 200.0f; // 地面レイの到達距離

// 行列更新処理
void Character::UpdateTransform() {
    XMMATRIX S = XMMatrixScaling(scale.x, scale.y, scale.z);
    XMMATRIX X = XMMatrixRotationX(angle.x);
    XMMATRIX Y = XMMatrixRotationY(angle.y);
    XMMATRIX Z = XMMatrixRotationZ(angle.z);
    XMMATRIX R = Y * X * Z;
    XMMATRIX T = XMMatrixTranslation(position.x, position.y, position.z);
    XMMATRIX W = S * R * T;
    XMStoreFloat4x4(&transform, W);
}

// 操作：移動ベクトルと最高速をセット（加速は UpdateHorizontalVelocity が担当）
void Character::Move(float /*elapsedTime*/, float vx, float vz, float speed) {
    moveVecX = vx;
    moveVecZ = vz;
    maxMoveSpeed = speed;
}

void Character::Turn(float elapsedTime, float vx, float vz, float speed) {
    speed += elapsedTime;

    float length = std::sqrt(vx * vx + vz * vz);
    if (length < 0.001f) return;

    vx /= length; vz /= length;

    float frontX = std::sinf(angle.y);
    float frontZ = std::cosf(angle.y);

    float dot = (frontX * vx) + (frontZ * vz);
    float rot = 1.0f - dot;
    if (rot > speed) rot = speed;

    float cross = (frontZ * vx) - (frontX * vz);
    if (cross < 0.0f) angle.y -= rot;
    else              angle.y += rot;
}

// 速度処理更新
void Character::UpdateVelocity(float elapsedTime)
{
    float elapsedFrame = 60.0f * elapsedTime;

    UpdateVerticalVelocity(elapsedFrame);
    UpdateHorizontalVelocity(elapsedFrame);

    UpdateVerticalMove(elapsedTime);
    UpdateHorizontalMove(elapsedTime);

    // 最終ガード（必要なら）
    if (position.y < 0.0f) {
        position.y = 0.0f;
        velocity.y = 0.0f;
        if (!isGround) OnLanding();
        isGround = true;
    }
    else {
        isGround = false;
    }
}

// 垂直速力更新処理
void Character::UpdateVerticalVelocity(float elapsedFrame)
{
    velocity.y += gravity * elapsedFrame;
}

// 垂直移動更新処理
void Character::UpdateVerticalMove(float elapsedTime)
{

    // ★ 衝突無視モード：上からのレイで地面へ軽くスナップするのみ
    if (ignoreWorldCollision) {
        position.y += velocity.y * elapsedTime;

        HitResult hit;
        XMFLOAT3 s = { position.x, position.y + 1.0f, position.z };
        XMFLOAT3 e = { position.x, position.y - RAY_DOWN, position.z };
        if (Stage::Instance().RayCast(s, e, hit)) {
            position.y = hit.position.y + EPS_Y;
            isGround = true;
            velocity.y = 0.0f;
        }
        else {
            isGround = false;
        }
        // 傾き追従はスキップ
        return;
    }

    // --- 通常モード ---
    float my = velocity.y * elapsedTime;
    slopeRate = 0.0f;

    XMFLOAT3 normal = { 0,1,0 };

    if (my < 0.0f) {
        XMFLOAT3 start = { position.x, position.y + stepOffset, position.z };
        XMFLOAT3 end = { position.x, position.y + my,        position.z };

        HitResult hit;
        if (Stage::Instance().RayCast(start, end, hit)) {
            normal = hit.normal;

            // ★ +ε で接地（粘り対策）
            position.y = hit.position.y + EPS_Y;

            float normalLengthXZ = std::sqrt(hit.normal.x * hit.normal.x + hit.normal.z * hit.normal.z);
            slopeRate = 1.0f - (hit.normal.y / (normalLengthXZ + hit.normal.y));

            if (!isGround) OnLanding();
            isGround = true;
            velocity.y = 0.0f;
        }
        else {
            position.y += my;
            isGround = false;
        }
    }
    else if (my > 0.0f) {
        position.y += my;
        isGround = false;
    }

    // 地面の向きに沿うようにXZ軸回転（なめらかに）
    {
        float ax = std::atan2(normal.z, normal.y);
        float az = -std::atan2(normal.x, normal.y);

        angle.x = Mathf::Lerp(angle.x, ax, 0.2f);
        angle.z = Mathf::Lerp(angle.z, az, 0.2f);
    }
}

// 水平速力更新処理
void Character::UpdateHorizontalVelocity(float elapsedFrame)
{

    // 減速：現在の速度ベクトルの長さで処理
    float velLen = len2(velocity.x, velocity.z);
    if (velLen > 0.0f) {
        float f = friction * elapsedFrame;
        if (velLen > f) {
            float ux = velocity.x / velLen;
            float uz = velocity.z / velLen;
            velocity.x -= ux * f;
            velocity.z -= uz * f;
            velLen -= f;
        }
        else {
            velocity.x = velocity.z = 0.0f;
            velLen = 0.0f;
        }
    }

    // 加速：入力ベクトル方向に加える
    float mvLen = len2(moveVecX, moveVecZ);
    if (mvLen > 0.0f) {
        float a = acceleration * elapsedFrame;
        float ux = moveVecX / mvLen;
        float uz = moveVecZ / mvLen;

        velocity.x += ux * a;
        velocity.z += uz * a;

        // 最高速クランプ
        float newLen = len2(velocity.x, velocity.z);
        if (newLen > maxMoveSpeed) {
            float s = maxMoveSpeed / newLen;
            velocity.x *= s;
            velocity.z *= s;
            newLen = maxMoveSpeed;
        }

        // 下り坂補正（必要なら）
        if (isGround && slopeRate > 0.0f) {
            velocity.y -= newLen * slopeRate * elapsedFrame;
        }
    }

    // 入力は毎フレーム消費
    moveVecX = 0.0f;
    moveVecZ = 0.0f;
}

// 水平移動更新処理
void Character::UpdateHorizontalMove(float elapsedTime)
{
    // ★ 衝突無視モード：そのまま進む（壁判定しない）
    if (ignoreWorldCollision) {
        position.x += velocity.x * elapsedTime;
        position.z += velocity.z * elapsedTime;
        return;
    }

    float vlen = len2(velocity.x, velocity.z);
    if (vlen <= 0.0f) return;

    float mx = velocity.x * elapsedTime;
    float mz = velocity.z * elapsedTime;

    XMFLOAT3 start = { position.x,       position.y + stepOffset, position.z };
    XMFLOAT3 end = { position.x + mx,  position.y + stepOffset, position.z + mz };

    HitResult hit;
    if (Stage::Instance().RayCast(start, end, hit))
    {
        XMVECTOR Start = XMLoadFloat3(&hit.position);
        XMVECTOR EndV = XMLoadFloat3(&end);
        XMVECTOR Vec = XMVectorSubtract(EndV, Start);

        XMVECTOR Normal = XMLoadFloat3(&hit.normal);

        XMVECTOR Dot = XMVector3Dot(XMVectorNegate(Vec), Normal);
        Dot = XMVectorScale(Dot, 1.1f); // 少し余裕を持たせる

        XMVECTOR CollectPosition = XMVectorMultiplyAdd(Normal, Dot, EndV);
        XMFLOAT3 collectPosition;
        XMStoreFloat3(&collectPosition, CollectPosition);

        // 壁ずり方向の再判定
        HitResult hit2;
        if (!Stage::Instance().RayCast(start, collectPosition, hit2))
        {
            position.x = collectPosition.x + hit.normal.x * EPS_WALL; // ★微小押し出し
            position.z = collectPosition.z + hit.normal.z * EPS_WALL;
        }
        else
        {
            position.x = hit2.position.x + hit2.normal.x * EPS_WALL;  // ★微小押し出し
            position.z = hit2.position.z + hit2.normal.z * EPS_WALL;
        }
    }
    else
    {
        // 壁に当たっていなければ通常移動
        position.x += mx;
        position.z += mz;
    }
}
