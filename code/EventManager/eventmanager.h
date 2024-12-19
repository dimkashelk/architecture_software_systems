#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <string>
#include <fstream>
#include <mutex>
#include <vector>

namespace dimkashelk
{
  class EventManager
  {
  public:
    static EventManager &getInstance();
    void logEvent(const std::string &event);
    std::mutex &getMutex();
    std::vector < std::string > &getEvents();
    void freeEvents();

  private:
    EventManager();
    ~EventManager();
    EventManager(const EventManager &) = delete;
    EventManager &operator=(const EventManager &) = delete;
    std::vector < std::string > events_;
    std::ofstream logFile;
    std::mutex logMutex;
  };
}
#endif
