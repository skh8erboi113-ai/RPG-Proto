#pragma once

#include <cstdint>

namespace engine {

class Camera {
public:
  Camera();

  void SetPerspective(float fovYRadians, float aspect, float zNear, float zFar);
  void SetPosition(float x, float y, float z);
  void LookAt(float targetX, float targetY, float targetZ);

  void UpdateDynamic(float time);

  const float* GetViewMatrix() const { return view_; }
  const float* GetProjMatrix() const { return proj_; }

private:
  float pos_[3];
  float target_[3];
  float view_[16];
  float proj_[16];
};

} // namespace engine
