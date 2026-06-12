#include "Inventory.h"

namespace engine {

Inventory::Inventory() {}

void Inventory::AddItem(const std::string& itemId, int count) {
  items_[itemId] += count;
}

bool Inventory::RemoveItem(const std::string& itemId, int count) {
  if (GetItemCount(itemId) >= count) {
    items_[itemId] -= count;
    return true;
  }
  return false;
}

int Inventory::GetItemCount(const std::string& itemId) const {
  auto it = items_.find(itemId);
  if (it != items_.end()) {
    return it->second;
  }
  return 0;
}

} // namespace engine
