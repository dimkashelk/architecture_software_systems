#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <string>
#include <fstream>
#include <mutex>

namespace dimkashelk
{
  class EventManager
  {
  public:
    static EventManager &getInstance();
    void logEvent(const std::string &event);

  private:
    EventManager();
    ~EventManager();
    EventManager(const EventManager &) = delete;
    EventManager &operator=(const EventManager &) = delete;
    std::ofstream logFile;
    std::mutex logMutex;
  };
}
#endif
