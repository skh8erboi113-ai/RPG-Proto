#pragma once
#include <string>

namespace engine {

class Engine;

class SaveManager {
public:
  static bool SaveGame(const std::string& path, Engine& engine);
  static bool LoadGame(const std::string& path, Engine& engine);
};

} // namespace engine
