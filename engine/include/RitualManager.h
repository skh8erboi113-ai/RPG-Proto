#pragma once
#include <string>
#include <vector>

namespace engine {

class RitualManager {
public:
  RitualManager();

  void StartRitual(const std::string& type);
  bool Update(float dt, int inputKey); // Returns true if ritual finishes

  float GetProgress() const { return progress_; }
  bool WasSuccess() const { return success_; }

private:
  bool active_ = false;
  float progress_ = 0.0f;
  bool success_ = false;
  std::string currentType_;
};

} // namespace engine
