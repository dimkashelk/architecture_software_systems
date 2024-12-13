#include "warehousemanager.h"
dimkashelk::WarehouseManager::WarehouseManager(std::vector < Robot > robots):
  robots_(std::move(robots))
{}
bool dimkashelk::WarehouseManager::available_robots()
{
  std::lock_guard lock(mutex_);
  return std::any_of(robots_.begin(), robots_.end(), [](const Robot &robot)
  {
    return robot.available();
  });
}
