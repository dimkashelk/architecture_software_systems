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
    using time_point = std::chrono::high_resolution_clock::time_point;
    explicit Robot(size_t id);
    void set_order(const std::shared_ptr < Order > &order);
    void start();
    void start_order();
    bool available() const;
    double get_usage_percent() const;
    double get_usage_percent_relative() const;
    std::string to_string() const;
    ~Robot();

  private:
    void success_order();
    void failed_order();
    void finish_order();
    void run();
    size_t calculate_wait_time();
    size_t id_;
    double wait_time_coeff_;
    std::chrono::high_resolution_clock::time_point start_time_;
    std::pair< time_point, time_point > end_time_last_order_;
    long long work_time_;
    long long current_order_work_time_;
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
