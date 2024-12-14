#ifndef ROBOT_H
#define ROBOT_H
#include <atomic>
#include <condition_variable>
#include <optional>
#include <mutex>
#include <thread>
#include <Order/order.h>

namespace dimkashelk
{
  class Robot
  {
  public:
    Robot();
    void set_order(const Order &order);
    void start_order();
    bool available() const;
    ~Robot();

  private:
    void finish_order();
    void run();
    size_t calculate_wait_time() const;
    std::optional < Order > current_order_{};
    bool work_now_;
    std::atomic < bool > stop_flag_;
    mutable std::mutex mtx_{};
    std::condition_variable cv_{};
    std::thread worker_thread_{};
  };
}
#endif
