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
#pragma once

#include <string>
#include <memory>

struct GLFWwindow;

namespace engine {

class Renderer;
class Camera;

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
  std::unique_ptr<Camera> camera_;

  float timeSeconds_;
};

} // namespace engine
