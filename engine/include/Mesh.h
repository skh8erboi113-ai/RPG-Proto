#pragma once

#include <string>

namespace engine {

class Mesh {
public:
  Mesh() = default;
  bool LoadFromFile(const std::string& path);
};

} // namespace engine
