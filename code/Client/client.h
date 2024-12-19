#ifndef CLIENT_H
#define CLIENT_H
#include <atomic>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include <eventmanager.h>
#include <order.h>

namespace dimkashelk
{
  class OrderManager;
  class Client
  {
  public:
    Client(size_t id, OrderManager &order_manager);
    std::string to_string() const;
    void start();
    void stop();
    size_t get_orders_count() const;
    double get_failure_rate() const;
    size_t get_rejected_count() const;
    double get_average_stay_time() const;
    double get_average_waiting_time() const;
    void set_delay(size_t new_delay);
    ~Client();

  private:
    void generate_order();
    void run();
    size_t id_;
    std::atomic< size_t > delay_;
    std::atomic < bool > stopped_;
    std::vector < std::shared_ptr < Order > > orders_;
    OrderManager &order_manager_;
    std::thread worker_thread_;
    std::atomic < bool > stop_flag_;
    mutable std::mutex mtx_;
  };
}
#endif
