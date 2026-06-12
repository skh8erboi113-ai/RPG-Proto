#include "SkillManager.h"
#include <fstream>
#include <iostream>
#include <cmath>

namespace engine {

SkillManager::SkillManager() {}

bool SkillManager::LoadFromJSON(const std::string& path) {
  std::ifstream file(path);
  if (!file.is_open()) return false;

  nlohmann::json j;
  file >> j;

  for (auto& tree : j["trees"]) {
    for (auto& tier : tree["tiers"]) {
      for (auto& skillData : tier["skills"]) {
        Skill s;
        s.id = skillData["id"];
        s.name = skillData["name"];
        s.type = skillData["type"];
        s.max_level = skillData["max_level"];
        s.scaling = skillData["scaling"];
        s.effect_base = skillData.value("effect_base", 0.0f);
        skills_[s.id] = s;
      }
    }
  }
  return true;
}

void SkillManager::LevelUpSkill(const std::string& skillId) {
  if (skills_.count(skillId)) {
    if (skills_[skillId].current_level < skills_[skillId].max_level) {
      skills_[skillId].current_level++;
    }
  }
}

int SkillManager::GetSkillLevel(const std::string& skillId) const {
  if (skills_.count(skillId)) {
    return skills_.at(skillId).current_level;
  }
  return 0;
}

float SkillManager::GetSkillEffect(const std::string& skillId) const {
  if (skills_.count(skillId)) {
    const auto& s = skills_.at(skillId);
    return s.effect_base * std::pow(s.scaling, static_cast<float>(s.current_level));
  }
  return 0.0f;
}

} // namespace engine
