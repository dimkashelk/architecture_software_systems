#include "eventmanager.h"
#include <iostream>
#include <filesystem>
dimkashelk::EventManager::EventManager():
  events_()
{
  if (const std::filesystem::path logDir = "log"; !exists(logDir))
  {
    create_directory(logDir);
  }
  logFile.open("log/main.log", std::ios::app);
  if (!logFile.is_open())
  {
    throw std::runtime_error("Unable to open log file");
  }
}
dimkashelk::EventManager::~EventManager()
{
  if (logFile.is_open())
  {
    logFile.close();
  }
}
dimkashelk::EventManager &dimkashelk::EventManager::getInstance()
{
  static EventManager instance;
  return instance;
}
void dimkashelk::EventManager::logEvent(const std::string &event)
{
  std::lock_guard lock(logMutex);
  if (logFile.is_open())
  {
    const auto now = std::chrono::system_clock::now();
    const auto now_time_t = std::chrono::system_clock::to_time_t(now);
    const auto now_ms = std::chrono::duration_cast < std::chrono::milliseconds >(now.time_since_epoch()) % 1000;
    std::ostringstream timestamp;
    timestamp << "[" << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S")
      << "." << std::setfill('0') << std::setw(3) << now_ms.count() << "] ";
    logFile << timestamp.str() << event << std::endl;
    events_.push_back(timestamp.str() + event);
  }
  else
  {
    std::cerr << "Log file is not open!" << std::endl;
  }
}
std::mutex &dimkashelk::EventManager::getMutex()
{
  return logMutex;
}
std::vector < std::string > &dimkashelk::EventManager::getEvents()
{
  return events_;
}
void dimkashelk::EventManager::freeEvents()
{
  events_.clear();
}
