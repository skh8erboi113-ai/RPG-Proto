#pragma once
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

namespace engine {

struct Skill {
  std::string id;
  std::string name;
  std::string type;
  int max_level;
  float scaling;
  float effect_base;
  int current_level = 0;
};

class SkillManager {
public:
  SkillManager();
  bool LoadFromJSON(const std::string& path);

  void LevelUpSkill(const std::string& skillId);
  int GetSkillLevel(const std::string& skillId) const;
  float GetSkillEffect(const std::string& skillId) const;

private:
  std::map<std::string, Skill> skills_;
};

} // namespace engine
