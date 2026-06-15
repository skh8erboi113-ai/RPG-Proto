#pragma once

namespace engine {

class Engine;

class CharacterController {
public:
  CharacterController();

  void SetPosition(float x, float y, float z);
  void Move(float dx, float dy, float dz);
  void Update(float dt);

  bool PrimaryAttack(Engine& engine);

  const float* GetPosition() const { return pos_; }

private:
  float pos_[3];
};

} // namespace engine
