#pragma once

namespace engine {

class WorldStreamer {
public:
  WorldStreamer() = default;

  void SetPlayerPosition(float x, float y, float z);
  void Update(float dt);

private:
  float playerPos_[3]{0.0f, 0.0f, 0.0f};
};

} // namespace engine
