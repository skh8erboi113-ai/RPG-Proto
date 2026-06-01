#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

namespace engine {

class Renderer;
class Camera;
class WorldStreamer;

class Engine {
public:
  Engine();
  ~Engine();

  bool Initialize();
  void Tick(float dt);
  void Shutdown();

  std::string GetName() const;
  bool IsRunning() const { return initialized_; }

private:
  bool initialized_;
  std::string name_;

  GLFWwindow* window_;
  std::unique_ptr<Renderer> renderer_;
  std::unique_ptr<Camera> camera_;
  std::unique_ptr<WorldStreamer> worldStreamer_;

  float timeSeconds_;
};

} // namespace engine
