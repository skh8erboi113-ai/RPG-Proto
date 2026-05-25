#pragma once

namespace engine {

class CharacterController {
public:
  CharacterController();

  void SetPosition(float x, float y, float z);
  void Move(float dx, float dy, float dz);
  void Update(float dt);

private:
  float pos_[3];
};

} // namespace engine
