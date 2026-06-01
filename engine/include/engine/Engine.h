#pragma once

#include <string>

namespace engine {

class Engine {
 public:
  Engine();
  ~Engine();

  // Lifecycle
  bool Initialize();
  void Tick(float deltaTime);
  void Shutdown();

  // Accessors
  std::string GetName() const;
  bool IsRunning() const;

 private:
  std::string name_;
  bool initialized_;
  bool running_;
};

}  // namespace engine
