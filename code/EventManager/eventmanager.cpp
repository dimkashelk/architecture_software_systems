#include "eventmanager.h"
#include <iostream>
dimkashelk::EventManager::EventManager()
{
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
    logFile << event << std::endl;
  }
  else
  {
    std::cerr << "Log file is not open!" << std::endl;
  }
}
