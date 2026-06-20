#pragma once
#include <string>
#include <map>

namespace engine {

class Inventory {
public:
  Inventory();

  void AddItem(const std::string& itemId, int count = 1);
  bool RemoveItem(const std::string& itemId, int count = 1);
  int GetItemCount(const std::string& itemId) const;

  const std::map<std::string, int>& GetItems() const { return items_; }
  void Clear() { items_.clear(); }

private:
  std::map<std::string, int> items_;
};

} // namespace engine
