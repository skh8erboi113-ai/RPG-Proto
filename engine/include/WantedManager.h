#pragma once
#include <string>
#include <map>

namespace engine {

enum class WantedLevel {
  Clean,
  Low,
  Medium,
  High,
  Maximum
};

class WantedManager {
public:
  WantedManager();

  void ReportCrime(const std::string& city, int points);
  void Update(float dt);

  int GetCrimePoints(const std::string& city) const;
  WantedLevel GetWantedLevel(const std::string& city) const;

private:
  std::map<std::string, float> cityPoints_;
  float decayRate_ = 0.5f; // points per second
};

} // namespace engine
