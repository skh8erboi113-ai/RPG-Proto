#pragma once

#include <string>

namespace engine {

class Engine {
public:
  Engine();
  ~Engine();

  // Initialize engine systems, return false on failure
  bool Initialize();

  // Tick the engine for one frame, dt in seconds
  void Tick(float dt);

  // Shutdown and cleanup
  void Shutdown();

  // Simple debug name
  std::string GetName() const;

private:
  bool initialized_;
  std::string name_;
};

} // namespace engine
