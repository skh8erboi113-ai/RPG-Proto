#include "CharacterController.h"

namespace engine {

CharacterController::CharacterController() {
  pos_[0] = 0.0f;
  pos_[1] = 0.0f;
  pos_[2] = 0.0f;
}

void CharacterController::SetPosition(float x, float y, float z) {
  pos_[0] = x;
  pos_[1] = y;
  pos_[2] = z;
}

void CharacterController::Move(float dx, float dy, float dz) {
  pos_[0] += dx;
  pos_[1] += dy;
  pos_[2] += dz;
}

void CharacterController::Update(float dt) {
  // Logic for character physics or animation could go here
  (void)dt;
}

} // namespace engine
