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
    explicit Client(size_t id, OrderManager &order_manager);
    std::string to_string() const;
    const std::vector < std::shared_ptr < Order > > &get_orders() const;
    ~Client();

  private:
    void generate_order();
    void run();
    size_t id_;
    std::vector < std::shared_ptr < Order > > orders_;
    OrderManager &order_manager_;
    std::thread worker_thread_;
    std::atomic < bool > stop_flag_;
    mutable std::mutex mtx_;
  };
}
#endif
