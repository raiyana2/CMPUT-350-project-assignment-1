#include "Enemy.h"

#include "Bullet.h"

Enemy::Enemy(CMPUT350::Point2D loc)
    : mLoc(loc), mBounds(loc.x - 20, loc.y - 20, 40, 40) {
    // TODO: Update code
}

void Enemy::Initialize(CMPUT350::GameContext* context) {}

void Enemy::Update(CMPUT350::GameContext* context) {}

void Enemy::LateUpdate(CMPUT350::GameContext* context) {}

bool Enemy::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return false; }

void Enemy::RenderBackground(CMPUT350::GameContext* context) {}

void Enemy::RenderForeground(CMPUT350::GameContext* context) {
    CMPUT350::Rect enemyRect(mLoc.x - 20, mLoc.y - 20, 40, 40);

    context->ScreenContext->DrawRect(enemyRect, CMPUT350::Colors::green);
}

void Enemy::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) {
    auto bullet = std::dynamic_pointer_cast<Bullet>(obj);

    if (bullet && bullet->IsPlayerBullet()) {
        Kill();
    }
}


const CMPUT350::Rect& Enemy::GetBounds() {
    // (done)TODO: Update code
    mBounds = CMPUT350::Rect(mLoc.x - 20, mLoc.y - 20, 40, 40);
    return mBounds;
}
