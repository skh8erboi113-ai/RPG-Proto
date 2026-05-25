#pragma once

namespace engine {

class Terrain {
public:
  Terrain() = default;

  bool Initialize(int width, int height);
  void Update(float dt);
};

} // namespace engine
