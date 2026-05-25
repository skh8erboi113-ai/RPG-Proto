#pragma once

#include <string>

namespace engine {

class MagicSystem {
public:
  MagicSystem() = default;

  void CastSpell(const std::string& name);
  void Update(float dt);
};

} // namespace engine
