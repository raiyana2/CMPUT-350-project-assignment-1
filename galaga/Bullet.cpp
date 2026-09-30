#include "Bullet.h"

#include "Enemy.h"

Bullet::Bullet(CMPUT350::Point2D location, CMPUT350::Point2D heading, bool player)
    : mLocation(location),
      mPreviousLocation(location),
      mHeading(heading),
      mBounds(location, location),
      mPlayerBullet(player) {}

bool Bullet::IsPlayerBullet() {
    // TODO: Update
    return mPlayerBullet;
}

void Bullet::Initialize(CMPUT350::GameContext* context) {}

void Bullet::Update(CMPUT350::GameContext* context) {
    auto height = context->ScreenContext->GetWindowHeight();
    auto width = context->ScreenContext->GetWindowWidth();

    mPreviousLocation = mLocation;
    mLocation += mHeading;
    mBounds = CMPUT350::Rect(mPreviousLocation, mLocation);
    mBounds.Inset(-2);  // Make the bounding box slightly larger for collision detection

    if (mLocation.x < 0 || mLocation.x > width || mLocation.y < 0 || mLocation.y > height) {
        Kill();
    }
}

void Bullet::LateUpdate(CMPUT350::GameContext* context) {}

bool Bullet::HandleKeyEvent(CMPUT350::GameContext* context, char key) { return false; }

void Bullet::RenderBackground(CMPUT350::GameContext* context) {}

void Bullet::RenderForeground(CMPUT350::GameContext* context) {
    // CMPUT350::Rect bulletRect(mLocation.x, mLocation.y, mHeading.x, mHeading.y);

    // context->ScreenContext->DrawRect(bulletRect, CMPUT350::Colors::yellow);
    context->ScreenContext->DrawLine(mPreviousLocation, mLocation, 2.0f, CMPUT350::Colors::yellow);
}

void Bullet::CollisionEnter(const std::shared_ptr<CMPUT350::CollisionObject>& obj) {
    auto enemy = std::dynamic_pointer_cast<Enemy>(obj);

    if (enemy && mPlayerBullet) {
        Kill();
    }
}

const CMPUT350::Rect& Bullet::GetBounds() {
    // TODO: Update code
    return mBounds;
}
