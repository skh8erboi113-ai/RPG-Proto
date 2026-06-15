#include "WantedManager.h"
#include <algorithm>

namespace engine {

WantedManager::WantedManager() {}

void WantedManager::ReportCrime(const std::string& city, int points) {
  cityPoints_[city] += static_cast<float>(points);
}

void WantedManager::Update(float dt) {
  for (auto& [city, points] : cityPoints_) {
    points = std::max(0.0f, points - decayRate_ * dt);
  }
}

int WantedManager::GetCrimePoints(const std::string& city) const {
  if (cityPoints_.count(city)) {
    return static_cast<int>(cityPoints_.at(city));
  }
  return 0;
}

WantedLevel WantedManager::GetWantedLevel(const std::string& city) const {
  int p = GetCrimePoints(city);
  if (p >= 100) return WantedLevel::Maximum;
  if (p >= 60)  return WantedLevel::High;
  if (p >= 30)  return WantedLevel::Medium;
  if (p >= 10)  return WantedLevel::Low;
  return WantedLevel::Clean;
}

} // namespace engine
