#ifndef ROBOT_H
#define ROBOT_H
#include <atomic>
#include <condition_variable>
#include <optional>
#include <mutex>
#include <thread>
#include <random>
#include <order.h>

namespace dimkashelk
{
  class Robot
  {
  public:
    explicit Robot(size_t id);
    void set_order(const std::shared_ptr < Order > &order);
    void start_order();
    bool available() const;
    std::string to_string() const;
    ~Robot();

  private:
    void finish_order();
    void run();
    size_t calculate_wait_time();
    size_t id_;
    double wait_time_coeff_;
    std::optional < std::shared_ptr < Order > > current_order_{};
    bool work_now_;
    std::atomic < bool > stop_flag_;
    std::random_device rd_{};
    std::mt19937 gen_;
    std::uniform_real_distribution < > dis_;
    mutable std::mutex mtx_{};
    std::condition_variable cv_{};
    std::thread worker_thread_{};
  };
}
#endif
