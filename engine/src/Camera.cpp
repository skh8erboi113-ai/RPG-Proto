#include "Camera.h"
#include <bx/math.h>
#include <bgfx/bgfx.h>

namespace engine {

Camera::Camera() {
  pos_[0] = 0.0f; pos_[1] = 0.0f; pos_[2] = -5.0f;
  target_[0] = 0.0f; target_[1] = 0.0f; target_[2] = 0.0f;
  SetPerspective(bx::toRad(60.0f), 16.0f / 9.0f, 0.1f, 100.0f);
  LookAt(target_[0], target_[1], target_[2]);
}

void Camera::SetPerspective(float fovYRadians, float aspect, float zNear, float zFar) {
  bx::mtxProj(proj_, fovYRadians, aspect, zNear, zFar, bgfx::getCaps()->homogeneousDepth);
}

void Camera::SetPosition(float x, float y, float z) {
  pos_[0] = x; pos_[1] = y; pos_[2] = z;
  LookAt(target_[0], target_[1], target_[2]);
}

void Camera::LookAt(float targetX, float targetY, float targetZ) {
  target_[0] = targetX; target_[1] = targetY; target_[2] = targetZ;
  bx::mtxLookAt(view_, bx::Vec3{pos_[0], pos_[1], pos_[2]}, bx::Vec3{target_[0], target_[1], target_[2]});
}

} // namespace engine
