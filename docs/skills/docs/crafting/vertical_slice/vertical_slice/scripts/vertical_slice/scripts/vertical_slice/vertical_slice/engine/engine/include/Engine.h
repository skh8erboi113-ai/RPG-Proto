#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

namespace engine {

class Renderer;

class Engine {
public:
  Engine();
  ~Engine();

  bool Initialize();
  void Tick(float dt);
  void Shutdown();

  std::string GetName() const;

private:
  bool initialized_;
  std::string name_;

  GLFWwindow* window_;
  std::unique_ptr<Renderer> renderer_;
};

} // namespace engine
